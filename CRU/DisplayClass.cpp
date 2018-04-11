//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DisplayClass.h"
#include <cstdio>
#include <cstring>
#include <setupapi.h>
//---------------------------------------------------------------------------
unsigned char *DisplayClass::CopyData;
PropertiesClass DisplayClass::CopyProperties;
//---------------------------------------------------------------------------
DisplayClass::DisplayClass(const char *NewDisplayID, const char *NewDeviceID)
{
	int Size = MAX_EDID_BLOCKS * 128;

	if (Size < 256)
		Size = 256;

	ActiveData = new unsigned char[Size];
	std::memset(ActiveData, 0, Size);

	OverrideData = new unsigned char[Size];
	std::memset(OverrideData, 0, Size);

	ResetData = new unsigned char[Size];
	std::memset(ResetData, 0, Size);

	DisplayID = new char[TEXTSIZE];
	std::snprintf(DisplayID, TEXTSIZE, "%s", NewDisplayID);

	DeviceID = new char[TEXTSIZE];
	std::snprintf(DeviceID, TEXTSIZE, "%s", NewDeviceID);

	DeviceName = new char[TEXTSIZE];
	DeviceName[0] = 0;

	Active = false;
	Override = false;
	Matched = false;
	Deleted = false;
	Restart = false;

	DetailedResolutionList = new DetailedResolutionListClass(4);
	StandardResolutionList = new StandardResolutionListClass(32);
	EstablishedResolutionList = new EstablishedResolutionListClass;
	ExtensionBlockList = new ExtensionBlockListClass(MAX_EDID_EXTENSION_BLOCKS);
}
//---------------------------------------------------------------------------
bool DisplayClass::GetText(char *Text, int TextSize, bool GetStatus)
{
	char OverrideID[TEXTSIZE];
	char OverrideName[TEXTSIZE];
	const char *Name;
	const char *Status;

	OverrideProperties.GetProductID(OverrideID, TEXTSIZE);
	OverrideProperties.GetName(OverrideName, TEXTSIZE);

	if (OverrideName[0] != 0)
		Name = OverrideName;
	else if (DeviceName[0] != 0)
		Name = DeviceName;
	else
		Name = "Unknown Display";

	if (!GetStatus)
		Status = "";
	else if (Deleted)
		Status = " (delete)";
	else if (Active && Restart)
		Status = " (restart required)";
	else if (Active && Override)
		Status = " (active)*";
	else if (Active)
		Status = " (active)";
	else if (Override)
		Status = "*";
	else
		Status = "";

	std::snprintf(Text, TextSize, "%s - %s%s", OverrideID, Name, Status);
	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::Load()
{
	if (!LoadDeviceName())
		return false;

	Active = GetActiveStatus();
	Override = LoadOverrideData();

	if (!LoadActiveData())
	{
		if (!Active && !Override)
			return false;

		if (std::strcmp(DisplayID, "Default_Monitor") != 0)
			return false;

		if (!LoadDefaultData())
			return false;
	}

	Matched = false;
	Deleted = false;
	Restart = false;
	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::MatchFullActive(EDIDListClass &EDIDList)
{
	if (Active && !Matched)
		Matched = EDIDList.MatchFullActive(ActiveData);

	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::MatchFullOverride(EDIDListClass &EDIDList)
{
	if (Active && Override && !Matched)
		Matched = EDIDList.MatchFullOverride(ActiveData, OverrideData);

	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::MatchPartialOverride(EDIDListClass &EDIDList)
{
	if (Active && Override && !Matched)
		Matched = EDIDList.MatchPartialOverride(ActiveData, OverrideData);

	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::MatchFirstActive(EDIDListClass &EDIDList)
{
	if (Active && !Matched)
		Matched = EDIDList.MatchFirstActive(ActiveData);

	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::Init()
{
	int Block;

	if (Override)
	{
		if (std::memcmp(ActiveData, OverrideData, 128) != 0)
			Restart = true;

		for (Block = 1; Block < MAX_EDID_BLOCKS; Block++)
			if (ActiveData[Block * 128] != 0 && OverrideData[Block * 128] != 0)
				if (std::memcmp(&ActiveData[Block * 128], &OverrideData[Block * 128], 128) != 0)
					Restart = true;
	}
	else
	{
		std::memcpy(OverrideData, ActiveData, MAX_EDID_BLOCKS * 128);
		OverrideProperties = ActiveProperties;
	}

	FixData(OverrideData, Override);
	DisplayInit();
	DisplayWrite();
	OverrideProperties.FixIncludes(DetailedResolutions()->GetSlotsLeft());
	OverrideProperties.Write(OverrideData);
	std::memcpy(ResetData, OverrideData, MAX_EDID_BLOCKS * 128);
	ResetProperties = OverrideProperties;
	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::LoadDeviceName()
{
	HKEY Key;
	char Path[TEXTSIZE];
	char Buffer[256];
	unsigned long BufferSize;
	int Index;
	char *Text;

	if (std::snprintf(Path, TEXTSIZE, "SYSTEM\\CurrentControlSet\\Enum\\DISPLAY\\%s\\%s", DisplayID, DeviceID) >= TEXTSIZE)
		return false;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, Path, 0, KEY_QUERY_VALUE, &Key) != ERROR_SUCCESS)
		return false;

	BufferSize = sizeof Buffer - sizeof *Buffer;

	if (RegQueryValueEx(Key, "DeviceDesc", NULL, NULL, Buffer, &BufferSize) != ERROR_SUCCESS)
	{
		RegCloseKey(Key);
		return false;
	}

	RegCloseKey(Key);
	Buffer[BufferSize] = 0;

	for (Text = Buffer; *Text; Text++)
	{
		if (*Text == ';')
		{
			Text++;
			break;
		}
	}

	// Generic Non-PnP Monitor
	// ThinkPad Display 1920x1080
	// Wide viewing angle & High density FlexView Display
	for (Index = 0; Index < 29 && Text[Index] != 0; Index++)
		DeviceName[Index] = Text[Index];

	if (Index == 29)
	{
		DeviceName[26] = '.';
		DeviceName[27] = '.';
		DeviceName[28] = '.';
	}

	DeviceName[Index] = 0;
	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::GetActiveStatus()
{
	const GUID GUID_DEVINTERFACE_MONITOR = {0xE6F07B5F, 0xEE97, 0x4A90, {0xB0, 0x76, 0x33, 0xF5, 0x7B, 0xF4, 0xEA, 0xA7}};
	char Path[TEXTSIZE];
	HDEVINFO Devices;
	SP_DEVINFO_DATA Device;
	bool Status = false;

	if (std::snprintf(Path, TEXTSIZE, "DISPLAY\\%s\\%s", DisplayID, DeviceID) >= TEXTSIZE)
		return false;

	Devices = SetupDiGetClassDevs(&GUID_DEVINTERFACE_MONITOR, Path, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);

	if (Devices == INVALID_HANDLE_VALUE)
		return false;

	Device.cbSize = sizeof Device;

	if (SetupDiEnumDeviceInfo(Devices, 0, &Device))
		Status = true;

	SetupDiDestroyDeviceInfoList(Devices);
	return Status;
}
//---------------------------------------------------------------------------
bool DisplayClass::LoadOverrideData()
{
	HKEY Key;
	char Path[TEXTSIZE];
	unsigned char Buffer[256];
	unsigned long BufferSize;
	int Block;
	bool Status = false;

	std::memset(OverrideData, 0, MAX_EDID_BLOCKS * 128);

	if (std::snprintf(Path, TEXTSIZE, "SYSTEM\\CurrentControlSet\\Enum\\DISPLAY\\%s\\%s\\Device Parameters\\EDID_OVERRIDE", DisplayID, DeviceID) >= TEXTSIZE)
		return false;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, Path, 0, KEY_QUERY_VALUE, &Key) != ERROR_SUCCESS)
		return false;

	BufferSize = sizeof Buffer;

	if (RegQueryValueEx(Key, "0", NULL, NULL, Buffer, &BufferSize) == ERROR_SUCCESS && BufferSize >= 128)
	{
		if (IsValidData(Buffer))
		{
			std::memcpy(OverrideData, Buffer, 128);
			OverrideProperties.LoadBackupData(Key);
			OverrideProperties.SetResetID(DisplayID);
			OverrideProperties.Read(OverrideData, true);
			Status = true;

			for (Block = 1; Block < MAX_EDID_BLOCKS; Block++)
			{
				std::snprintf(Path, TEXTSIZE, "%d", Block);
				BufferSize = sizeof Buffer;

				if (RegQueryValueEx(Key, Path, NULL, NULL, Buffer, &BufferSize) != ERROR_SUCCESS || BufferSize < 128)
					continue;

				std::memcpy(&OverrideData[Block * 128], Buffer, 128);
			}
		}
	}

	RegCloseKey(Key);
	return Status;
}
//---------------------------------------------------------------------------
bool DisplayClass::LoadActiveData()
{
	HKEY Key;
	char Path[TEXTSIZE];
	unsigned char Buffer[MAX_EDID_BLOCKS * 128];
	unsigned long BufferSize;
	bool Status = false;

	std::memset(ActiveData, 0, MAX_EDID_BLOCKS * 128);

	if (std::snprintf(Path, TEXTSIZE, "SYSTEM\\CurrentControlSet\\Enum\\DISPLAY\\%s\\%s\\Device Parameters", DisplayID, DeviceID) >= TEXTSIZE)
		return false;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, Path, 0, KEY_QUERY_VALUE, &Key) != ERROR_SUCCESS)
		return false;

	BufferSize = sizeof Buffer;

	if (RegQueryValueEx(Key, "EDID", NULL, NULL, Buffer, &BufferSize) == ERROR_SUCCESS && BufferSize >= 128)
	{
		if (IsValidData(Buffer))
		{
			std::memcpy(ActiveData, Buffer, BufferSize / 128 * 128);
			ActiveProperties.SetResetID(DisplayID);
			ActiveProperties.Read(ActiveData, false);
			Status = true;
		}
	}

	RegCloseKey(Key);
	return Status;
}
//---------------------------------------------------------------------------
bool DisplayClass::LoadDefaultData()
{
	HKEY Key;
	char Path[TEXTSIZE];
	unsigned char Buffer[MAX_EDID_BLOCKS * 128];
	unsigned long BufferSize;
	bool Status = false;

	std::memset(ActiveData, 0, MAX_EDID_BLOCKS * 128);

	if (std::snprintf(Path, TEXTSIZE, "SYSTEM\\CurrentControlSet\\Enum\\DISPLAY\\%s\\%s\\Device Parameters", DisplayID, DeviceID) >= TEXTSIZE)
		return false;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, Path, 0, KEY_QUERY_VALUE, &Key) != ERROR_SUCCESS)
		return false;

	BufferSize = sizeof Buffer;

	if (BufferSize >= 128)
	{
		std::memset(Buffer, 0, BufferSize);
		std::memcpy(Buffer, "\x00\xFF\xFF\xFF\xFF\xFF\xFF\x00\x41\xD0\xFF\x09\x00\x00\x00\x00\x00\x00\x01\x03\x08\x00\x00\x78\xEA\xEE\x95\xA3\x54\x4C\x99\x26\x0F\x50\x54", 35);

		if (IsValidData(Buffer))
		{
			std::memcpy(ActiveData, Buffer, BufferSize / 128 * 128);
			ActiveProperties.SetResetID(DisplayID);
			ActiveProperties.Read(ActiveData, false);
			Status = true;
		}
	}

	RegCloseKey(Key);
	return Status;
}
//---------------------------------------------------------------------------
bool DisplayClass::IsValidData(unsigned char *Data)
{
	if (std::memcmp(Data, "\x00\xFF\xFF\xFF\xFF\xFF\xFF\x00", 8) != 0)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::FixData(unsigned char *Data, bool Override)
{
	unsigned char CompareData[127];

	if (!IsValidData(Data))
		return false;

	std::memset(&Data[12], 0, 4);

	if (Data[18] != 1 || Data[19] != 4)
	{
		Data[18] = 1;
		Data[19] = 3;

		if (Data[20] & 128)
			Data[20] = 128;
	}

	Data[24] |= 2;

	if (Override)
	{
		if (Data[126] == 1)
		{
			std::memset(CompareData, 0, 127);
			CompareData[0] = 0x02;
			CompareData[1] = 0x03;

			if (std::memcmp(&Data[128], CompareData, 127) == 0)
				Data[126] = 0;
		}
	}
	else
	{
		if (Data[126] == 1)
		{
			std::memset(CompareData, 0xFF, 127);

			if (std::memcmp(&Data[128], CompareData, 127) == 0)
				Data[126] = 0;
		}
	}

	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::Import(const char *FileName, bool Complete)
{
	std::FILE *File = std::fopen(FileName, "rb");

	if (!File)
		return false;

	DisplayWrite();
	OverrideData[126] = 0;

	if (!ImportFile(File, Complete, "(bbbbbbbbbbbbbbbb)"))
	if (!ImportFile(File, Complete, "(hhhhhhhhhhhhhhhh)"))
	if (!ImportFile(File, Complete, "lll(oshhhhhhhhhhhhhhhh)"))
	if (!ImportFile(File, Complete, "lll(sshhhhhhhhhh)"))
	if (!ImportFile(File, Complete, "(xcxcxcxcxcxcxcxcxcxcxcxcxcxcxcxc)"))
	if (!ImportINF(File, Complete))
	{
		std::fclose(File);
		return false;
	}

	std::fclose(File);
	FixData(OverrideData, true);
	DisplayRead();
	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::ImportFile(std::FILE *File, bool Complete, const char *Format)
{
	PropertiesClass Properties;
	unsigned char Buffer[128];
	int Index;
	int Block;
	const char *Byte;
	const char *Start;
	int Hex;
	char Text[256];
	bool Valid = false;
	bool Status = false;

	rewind(File);
	Index = 0;
	Block = 0;

	for (Byte = Format; Block < MAX_EDID_BLOCKS; Byte++)
	{
		switch (*Byte)
		{
			case '(':
				Start = Byte;
				break;

			case ')':
				Byte = Start;
				break;

			case 'b':
				if (std::fread(&Buffer[Index++], 1, 1, File) != 1)
					return Status;

				break;

			case 'c':
				if (std::fgetc(File) == EOF)
					return Status;

				break;

			case 'h':
				if (std::fscanf(File, "%2x", &Hex) != 1)
					return Status;

				Buffer[Index++] = Hex;
				break;

			case 'l':
				if (!std::fgets(Text, 256, File))
					return Status;

				break;

			case 'o':
				if (std::fscanf(File, "%x", &Hex) != 1)
					return Status;

				if (Hex % 128 != Index)
					return Status;

				if (Hex / 128 < Block)
					return Status;

				if (Index == 0)
					Block = Hex / 128;

				break;

			case 's':
				if (std::fscanf(File, "%255s", Text) != 1)
					return Status;

				break;

			case 'x':
				if (std::fscanf(File, "%x", &Hex) != 1)
					return Status;

				if (Hex > 255)
					return Status;

				Buffer[Index++] = Hex;
				break;

			default:
				return Status;
		}

		if (Index != 128)
			continue;

		if (Block == 0)
		{
			if (!IsValidData(Buffer))
				return Status;

			Valid = true;

			if (Complete)
				std::memcpy(OverrideData, Buffer, 128);
			else
				std::memcpy(&OverrideData[35], &Buffer[35], 93);

			if (!Status)
				std::memset(&OverrideData[128], 0, MAX_EDID_EXTENSION_BLOCKS * 128);

			Properties = OverrideProperties;
			Properties.Read(Buffer, true);
			Properties.ResetIncludes();

			if (Complete)
				OverrideProperties = Properties;
			else
				OverrideProperties.Import(Properties);

			Status = true;
		}
		else
		{
			if (!Valid && OverrideData[126] < Block)
				OverrideData[126] = Block;

			if (!Status)
				std::memset(&OverrideData[128], 0, MAX_EDID_EXTENSION_BLOCKS * 128);

			std::memcpy(&OverrideData[Block * 128], Buffer, 128);
			Status = true;
		}

		Index = 0;
		Block++;
	}

	return Status;
}
//---------------------------------------------------------------------------
bool DisplayClass::ImportINF(std::FILE *File, bool Complete)
{
	PropertiesClass Properties;
	unsigned char Buffer[128];
	char Line[1024];
	const char *Text;
	int Block;
	int Hex;
	int Index;
	bool Valid = false;
	bool Status = false;

	rewind(File);

	while (std::fgets(Line, 1024, File))
	{
		Text = std::strtok(Line, ", \"\r\n");

		if (!Text)
			continue;

		if (std::stricmp(Text, "HKR") != 0)
			continue;

		Text = std::strtok(NULL, ", \"\r\n");

		if (!Text)
			continue;

		if (std::stricmp(Text, "EDID_OVERRIDE") != 0)
			continue;

		Text = std::strtok(NULL, ", \"\r\n");

		if (!Text)
			continue;

		if (std::sscanf(Text, "%d", &Block) != 1)
			continue;

		if (Block < 0 || Block >= MAX_EDID_BLOCKS)
			continue;

		Text = std::strtok(NULL, ", \"\r\n");

		if (!Text)
			continue;

		if (std::sscanf(Text, "%x", &Hex) != 1)
			continue;

		if (Hex != 1)
			continue;

		for (Index = 0; Index < 128; Index++)
		{
			Text = std::strtok(NULL, ", \"\r\n");

			if (!Text)
				break;

			if (std::sscanf(Text, "%x", &Hex) != 1)
				break;

			if (Hex > 255)
				break;

			Buffer[Index] = Hex;
		}

		if (Index != 128)
			return Status;

		Text = std::strtok(NULL, ", \"\r\n");

		if (Text)
			return Status;

		if (Block == 0)
		{
			if (!IsValidData(Buffer))
				return Status;

			Valid = true;

			if (Complete)
				std::memcpy(OverrideData, Buffer, 128);
			else
				std::memcpy(&OverrideData[35], &Buffer[35], 93);

			if (!Status)
				std::memset(&OverrideData[128], 0, MAX_EDID_EXTENSION_BLOCKS * 128);

			Properties = OverrideProperties;
			Properties.Read(Buffer, true);
			Properties.ResetIncludes();

			if (Complete)
				OverrideProperties = Properties;
			else
				OverrideProperties.Import(Properties);

			Status = true;
		}
		else
		{
			if (!Valid && OverrideData[126] < Block)
				OverrideData[126] = Block;

			if (!Status)
				std::memset(&OverrideData[128], 0, MAX_EDID_EXTENSION_BLOCKS * 128);

			std::memcpy(&OverrideData[Block * 128], Buffer, 128);
			Status = true;
		}
	}

	return Status;
}
//---------------------------------------------------------------------------
const char *DisplayClass::GetImportFormats()
{
	return "EDID Files (*.bin, *.dat, *.inf)\0*.bin;*.dat;*.inf\0TXT Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0\0";
}
//---------------------------------------------------------------------------
const char *DisplayClass::GetExportFormats()
{
	return "BIN File (*.bin)\0*.bin\0DAT File (*.dat)\0*.dat\0INF File (*.inf)\0*.inf\0TXT File (*.txt)\0*.txt\0\0";
}
//---------------------------------------------------------------------------
bool DisplayClass::Export(const char *FileName, int FileType, const char *Name)
{
	std::FILE *File = std::fopen(FileName, "wb");

	if (!File)
		return false;

	DisplayWrite();
	OverrideProperties.Write(OverrideData);
	CalculateChecksums();

	if (!ExportFile(File, FileType, Name))
	{
		std::fclose(File);
		return false;
	}

	if (std::fclose(File) != 0)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::ExportFile(std::FILE *File, int FileType, const char *Name)
{
	const unsigned char *Byte;
	unsigned Count;
	unsigned Line;
	int Index;
	char OverrideID[TEXTSIZE];

	Byte = OverrideData;

	for (Count = MAX_EDID_EXTENSION_BLOCKS; Count > 0; Count--)
		if (OverrideData[Count * 128] != 0)
			break;

	Count++;

	switch (FileType)
	{
		case 1:
			Count *= 128;

			if (std::fwrite(OverrideData, 1, Count, File) != Count)
				return false;

			return true;

		case 2:
			Count *= 8;

			if (std::fprintf(File, "EDID BYTES:\r\n") <= 0)
				return false;

			if (std::fprintf(File, "0x %*s 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\r\n", Count <= 16 ? 1 : 3, "") <= 0)
				return false;

			if (std::fprintf(File, "%*s   ------------------------------------------------\r\n", Count <= 16 ? 1 : 3, "") <= 0)
				return false;

			for (Line = 0; Line < Count; Line++)
			{
				if (std::fprintf(File, "%0*X0 |", Count <= 16 ? 1 : 3, Line) <= 0)
					return false;

				for (Index = 0; Index < 16; Index++)
					if (std::fprintf(File, " %02X", *(Byte++)) <= 0)
						return false;

				if (std::fprintf(File, "\r\n") <= 0)
					return false;
			}

			return true;

		case 3:
			if (OverrideData[126] == 0 && OverrideProperties.GetExtensions())
			{
				Count++;
				OverrideData[126]++;
				OverrideData[127]--;
				ExtensionBlockList->WriteBlankExtension(&OverrideData[128], 128);
			}

			if (std::fprintf(File,
				"[Version]\r\n"
				"Signature=\"$Windows NT$\"\r\n"
				"Class=Monitor\r\n"
				"ClassGUID={4d36e96e-e325-11ce-bfc1-08002be10318}\r\n"
				"Provider=%%MFR%%\r\n"
				"\r\n"
				"[Manufacturer]\r\n"
				"%%MFR%%=Monitor,NTx86,NTamd64\r\n"
				) <= 0)
				return false;

			OverrideProperties.GetProductID(OverrideID, TEXTSIZE);

			if (std::fprintf(File,
				"\r\n"
				"[Monitor.NTx86]\r\n"
				"%%MODEL%%=Monitor.Install,MONITOR\\%s\r\n", OverrideID
				) <= 0)
				return false;

			if (std::fprintf(File,
				"\r\n"
				"[Monitor.NTamd64]\r\n"
				"%%MODEL%%=Monitor.Install,MONITOR\\%s\r\n", OverrideID
				) <= 0)
				return false;

			if (std::fprintf(File,
				"\r\n"
				"[Monitor.Install]\r\n"
				"DelReg=Monitor.DelReg\r\n"
				"\r\n"
				"[Monitor.Install.HW]\r\n"
				"DelReg=Monitor.DelReg\r\n"
				"AddReg=Monitor.AddReg\r\n"
				"\r\n"
				"[Monitor.DelReg]\r\n"
				"HKR,EDID_OVERRIDE\r\n"
				"HKR,MODES\r\n"
				"HKR,,DPMS\r\n"
				"HKR,,ICMProfile\r\n"
				"HKR,,MaxResolution\r\n"
				"HKR,,PreferredMode\r\n"
				"\r\n"
				"[Monitor.AddReg]\r\n"
				) <= 0)
				return false;

			for (Line = 0; Line < Count; Line++)
			{
				if (Line > 0 && *Byte == 0)
				{
					Byte += 128;
					continue;
				}

				if (std::fprintf(File, "HKR,EDID_OVERRIDE,\"%d\",0x01", Line) <= 0)
					return false;

				for (Index = 0; Index < 128; Index++)
					if (std::fprintf(File, ",0x%02X", *(Byte++)) <= 0)
						return false;

				if (std::fprintf(File, "\r\n") <= 0)
					return false;
			}

			if (std::fprintf(File,
				"\r\n"
				"[Strings]\r\n"
				"MFR=\"EDID Override\"\r\n"
				"MODEL=\"%s\"\r\n", Name
				) <= 0)
				return false;

			return true;

		case 4:
			Count *= 8;

			for (Line = 0; Line < Count; Line++)
			{
				if (std::fprintf(File, "%02X", *(Byte++)) <= 0)
					return false;

				for (Index = 1; Index < 16; Index++)
					if (std::fprintf(File, " %02X", *(Byte++)) <= 0)
						return false;

				if (std::fprintf(File, "\r\n") <= 0)
					return false;
			}

			return true;
	}

	return false;
}
//---------------------------------------------------------------------------
int DisplayClass::Save()
{
	if (Deleted)
		return DeleteData();

	DisplayWrite();
	OverrideProperties.Write(OverrideData);

	if (std::memcmp(OverrideData, ResetData, MAX_EDID_BLOCKS * 128) == 0 && OverrideProperties == ResetProperties)
		return 0;

	CalculateChecksums();
	return SaveOverrideData();
}
//---------------------------------------------------------------------------
int DisplayClass::SaveActiveData()
{
	HKEY Key;
	char Path[TEXTSIZE];
	int Count;

	if (!Active || Deleted)
		return 0;

	if (std::snprintf(Path, TEXTSIZE, "SYSTEM\\CurrentControlSet\\Enum\\DISPLAY\\%s\\%s\\Device Parameters", DisplayID, DeviceID) >= TEXTSIZE)
		return -2;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, Path, 0, KEY_SET_VALUE, &Key) != ERROR_SUCCESS)
		return -2;

	for (Count = MAX_EDID_EXTENSION_BLOCKS; Count > 0; Count--)
		if (ActiveData[Count * 128] != 0)
			break;

	Count++;

	if (RegSetValueEx(Key, "EDID", 0, REG_BINARY, ActiveData, Count * 128) != ERROR_SUCCESS)
	{
		RegCloseKey(Key);
		return -2;
	}

	RegCloseKey(Key);
	return 1;
}
//---------------------------------------------------------------------------
int DisplayClass::SaveOverrideData()
{
	HKEY Key;
	char Path[TEXTSIZE];
	int Block;

	if (std::snprintf(Path, TEXTSIZE, "SYSTEM\\CurrentControlSet\\Enum\\DISPLAY\\%s\\%s\\Device Parameters\\EDID_OVERRIDE", DisplayID, DeviceID) >= TEXTSIZE)
		return -2;

	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, Path, 0, NULL, 0, KEY_SET_VALUE, NULL, &Key, NULL) != ERROR_SUCCESS)
		return -2;

	if (OverrideData[126] == 0 && OverrideProperties.GetExtensions())
	{
		OverrideData[126]++;
		OverrideData[127]--;
		ExtensionBlockList->WriteBlankExtension(&OverrideData[128], 128);
	}

	if (RegSetValueEx(Key, "0", 0, REG_BINARY, OverrideData, 128) != ERROR_SUCCESS)
	{
		RegCloseKey(Key);
		return -2;
	}

	OverrideProperties.SaveBackupData(Key, DetailedResolutions()->GetSlotsLeft());

	for (Block = 1; Block < MAX_EDID_BLOCKS; Block++)
	{
		std::snprintf(Path, TEXTSIZE, "%d", Block);

		if (OverrideData[Block * 128] != 0)
		{
			if (RegSetValueEx(Key, Path, 0, REG_BINARY, &OverrideData[Block * 128], 128) != ERROR_SUCCESS)
			{
				RegCloseKey(Key);
				return -2;
			}
		}
		else
		{
			switch (RegDeleteValue(Key, Path))
			{
				case ERROR_SUCCESS:
				case ERROR_FILE_NOT_FOUND:
				case ERROR_PATH_NOT_FOUND:
					break;

				default:
					RegCloseKey(Key);
					return -2;
			}
		}
	}

	RegCloseKey(Key);
	return 1;
}
//---------------------------------------------------------------------------
int DisplayClass::DeleteData()
{
	HKEY Key;
	char Path[TEXTSIZE];

	if (std::snprintf(Path, TEXTSIZE, "SYSTEM\\CurrentControlSet\\Enum\\DISPLAY\\%s\\%s\\Device Parameters", DisplayID, DeviceID) >= TEXTSIZE)
		return -2;

	switch (RegOpenKeyEx(HKEY_LOCAL_MACHINE, Path, 0, KEY_SET_VALUE, &Key))
	{
		case ERROR_SUCCESS:
			switch (RegDeleteKey(Key, "EDID_OVERRIDE"))
			{
				case ERROR_SUCCESS:
				case ERROR_FILE_NOT_FOUND:
				case ERROR_PATH_NOT_FOUND:
					break;

				default:
					RegCloseKey(Key);
					return -2;
			}

			switch (RegDeleteValue(Key, "EDID"))
			{
				case ERROR_SUCCESS:
				case ERROR_FILE_NOT_FOUND:
				case ERROR_PATH_NOT_FOUND:
					break;

				default:
					RegCloseKey(Key);
					return -2;
			}

			RegCloseKey(Key);
			break;

		case ERROR_FILE_NOT_FOUND:
		case ERROR_PATH_NOT_FOUND:
			break;

		default:
			return -2;
	}

	return 1;
}
//---------------------------------------------------------------------------
bool DisplayClass::GetProperties(PropertiesClass &Properties)
{
	Properties = OverrideProperties;
	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::SetProperties(const PropertiesClass &Properties)
{
	OverrideProperties = Properties;
	return true;
}
//---------------------------------------------------------------------------
PropertiesClass *DisplayClass::Properties()
{
	return &OverrideProperties;
}
//---------------------------------------------------------------------------
bool DisplayClass::DisplayInit()
{
	DetailedInit();
	StandardInit();
	EstablishedInit();
	ExtensionInit();
	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::DisplayRead()
{
	DetailedRead();
	StandardRead();
	EstablishedRead();
	ExtensionRead();
	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::DisplayWrite()
{
	DetailedWrite();
	StandardWrite();
	EstablishedWrite();
	ExtensionWrite();
	ClearChecksums();
	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::DisplayCopyPossible()
{
	if (!CopyData)
		return true;

	DisplayWrite();

	if (std::memcmp(CopyData, &OverrideData[35], MAX_EDID_BLOCKS * 128 - 35) != 0)
		return true;

	if (OverrideProperties.CopyPossible(CopyProperties))
		return true;

	return false;
}
//---------------------------------------------------------------------------
bool DisplayClass::DisplayCopy()
{
	if (!CopyData)
		CopyData = new unsigned char[MAX_EDID_BLOCKS * 128 - 35];

	DisplayWrite();
	std::memcpy(CopyData, &OverrideData[35], MAX_EDID_BLOCKS * 128 - 35);
	CopyProperties = OverrideProperties;
	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::DisplayPastePossible()
{
	if (!CopyData)
		return false;

	DisplayWrite();

	if (std::memcmp(&OverrideData[35], CopyData, MAX_EDID_BLOCKS * 128 - 35) != 0)
		return true;

	if (OverrideProperties.PastePossible(CopyProperties))
		return true;

	return false;
}
//---------------------------------------------------------------------------
bool DisplayClass::DisplayPaste()
{
	if (!CopyData)
		return false;

	std::memcpy(&OverrideData[35], CopyData, MAX_EDID_BLOCKS * 128 - 35);
	OverrideProperties.Paste(CopyProperties);
	DisplayRead();
	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::DisplayResetPossible()
{
	DisplayWrite();

	if (std::memcmp(&OverrideData[35], &ResetData[35], MAX_EDID_BLOCKS * 128 - 35) != 0)
		return true;

	if (OverrideProperties != ResetProperties)
		return true;

	return false;
}
//---------------------------------------------------------------------------
bool DisplayClass::DisplayReset()
{
	std::memcpy(&OverrideData[35], &ResetData[35], MAX_EDID_BLOCKS * 128 - 35);
	OverrideProperties = ResetProperties;
	DisplayRead();
	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::DisplayDeletePossible()
{
	return !Deleted;
}
//---------------------------------------------------------------------------
bool DisplayClass::DisplayDelete()
{
	Deleted = true;
	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::DisplayRestore()
{
	Deleted = false;
	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::IsDigital()
{
	return OverrideData[20] & 128;
}
//---------------------------------------------------------------------------
bool DisplayClass::GetNative(DetailedResolutionClass &DetailedResolution)
{
	if (!DetailedResolutionList->GetNative(DetailedResolution))
		return false;

	if (!DetailedResolution.CalculateNative(IsDigital()))
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::DetailedInit()
{
	DetailedRead();
	DetailedResolutionList->UpdateUndo();
	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::DetailedRead()
{
	if (!DetailedResolutionList->Read(&OverrideData[54], 72))
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::DetailedWrite()
{
	int Slot;

	for (Slot = 0; Slot < 4; Slot++)
	{
		std::memset(&OverrideData[Slot * 18 + 54], 0, 18);
		OverrideData[Slot * 18 + 57] = '\x10';
	}

	if (!DetailedResolutionList->Write(&OverrideData[54], 72))
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::DetailedGetStandardText(int Slot, char *Text, int TextSize)
{
	return DetailedResolutionList->GetStandardText(Slot, Text, TextSize, StandardResolutionList->GetSlotsLeft());
}
//---------------------------------------------------------------------------
DetailedResolutionListClass *DisplayClass::DetailedResolutions()
{
	DetailedResolutionList->SetMaxCount(4 - (StandardResolutionList->GetCount() - 3) / 6);
	return DetailedResolutionList;
}
//---------------------------------------------------------------------------
bool DisplayClass::StandardInit()
{
	StandardRead();
	StandardResolutionList->UpdateUndo();
	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::StandardRead()
{
	if (!StandardResolutionList->Read(&OverrideData[38], 64))
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::StandardWrite()
{
	if (!StandardResolutionList->Write(&OverrideData[38], 64))
		return false;

	return true;
}
//---------------------------------------------------------------------------
StandardResolutionListClass *DisplayClass::StandardResolutions()
{
	StandardResolutionList->SetMaxCount((4 - DetailedResolutionList->GetCount()) * 6 + 8);
	return StandardResolutionList;
}
//---------------------------------------------------------------------------
bool DisplayClass::EstablishedInit()
{
	EstablishedRead();
	EstablishedResolutionList->UpdateUndo();
	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::EstablishedRead()
{
	if (!EstablishedResolutionList->Read(&OverrideData[35], 3))
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::EstablishedWrite()
{
	if (!EstablishedResolutionList->Write(&OverrideData[35], 3))
		return false;

	return true;
}
//---------------------------------------------------------------------------
EstablishedResolutionListClass *DisplayClass::EstablishedResolutions()
{
	return EstablishedResolutionList;
}
//---------------------------------------------------------------------------
bool DisplayClass::ExtensionInit()
{
	ExtensionRead();
	ExtensionBlockList->UpdateUndo();
	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::ExtensionRead()
{
	if (!ExtensionBlockList->Read(&OverrideData[126], MAX_EDID_EXTENSION_BLOCKS * 128 + 2))
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::ExtensionWrite()
{
	if (!ExtensionBlockList->Write(&OverrideData[126], MAX_EDID_EXTENSION_BLOCKS * 128 + 2))
		return false;

	return true;
}
//---------------------------------------------------------------------------
ExtensionBlockListClass *DisplayClass::ExtensionBlocks()
{
	return ExtensionBlockList;
}
//---------------------------------------------------------------------------
bool DisplayClass::ClearChecksums()
{
	int Block;

	for (Block = 0; Block < MAX_EDID_BLOCKS; Block++)
		OverrideData[Block * 128 + 127] = 0;

	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::CalculateChecksums()
{
	int Block;
	int Index;

	for (Block = 0; Block < MAX_EDID_BLOCKS; Block++)
	{
		OverrideData[Block * 128 + 127] = 0;

		for (Index = 0; Index < 127; Index++)
			OverrideData[Block * 128 + 127] -= OverrideData[Block * 128 + Index];
	}

	return true;
}
//---------------------------------------------------------------------------
bool DisplayClass::Compare(DisplayClass *Display1, DisplayClass *Display2)
{
	char Text1[TEXTSIZE];
	char Text2[TEXTSIZE];

	if (Display1->Active && !Display2->Active)
		return true;

	if (!Display1->Active && Display2->Active)
		return false;

	Display1->GetText(Text1, TEXTSIZE, false);
	Display2->GetText(Text2, TEXTSIZE, false);

	if (std::strnicmp(Text1, Text2, TEXTSIZE) < 0)
		return true;

	if (std::strnicmp(Text1, Text2, TEXTSIZE) > 0)
		return false;

	if (Display1->DeviceID < Display2->DeviceID)
		return true;

	if (Display1->DeviceID > Display2->DeviceID)
		return false;

	return false;
}
//---------------------------------------------------------------------------
