//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "PropertiesClass.h"
#include <cctype>
#include <cstdio>
#include <cstring>
//---------------------------------------------------------------------------
const long long PropertiesClass::MinSerialID = 0;
const long long PropertiesClass::MaxSerialID = 4294967295LL;

const unsigned long PropertiesClass::MaxNameSize = 13;
const unsigned long PropertiesClass::MaxSerialNumberSize = 13;

const int PropertiesClass::MinVRange = 1;
const int PropertiesClass::MaxVRange = 255;
const int PropertiesClass::MinHRange = 1;
const int PropertiesClass::MaxHRange = 255;
const int PropertiesClass::MinPClockRange = 10;
const int PropertiesClass::MaxPClockRange = 2550;
const int PropertiesClass::ModPClockRange = 10;

const char *PropertiesClass::RegName = "CRU_Name";
const char *PropertiesClass::RegSerialNumber = "CRU_Serial_Number";
const char *PropertiesClass::RegRangeLimits = "CRU_Range_Limits";
const char *PropertiesClass::RegExtensions = "CRU_Extensions";
//---------------------------------------------------------------------------
PropertiesClass::PropertiesClass()
{
	ProductID[0] = 0;
	ResetID[0] = 0;
	SerialID = BLANK;

	Name[0] = 0;
	IncludeName = true;
	IncludedName = false;

	SerialNumber[0] = 0;
	IncludeSerialNumber = false;
	IncludedSerialNumber = false;

	ExtRange = 0;
	MinVRate = BLANK;
	MaxVRate = BLANK;
	MinHRate = BLANK;
	MaxHRate = BLANK;
	MaxPClock = BLANK;
	IncludeRangeLimits = false;
	IncludedRangeLimits = false;

	Extensions = BLANK;
}
//---------------------------------------------------------------------------
bool PropertiesClass::operator==(const PropertiesClass &Properties)
{
	if (std::strcmp(ProductID, Properties.ProductID) != 0)
		return false;

	if (SerialID != Properties.SerialID)
		return false;

	if (std::strcmp(Name, Properties.Name) != 0)
		return false;

	if (IncludeName != Properties.IncludeName)
		return false;

	if (std::strcmp(SerialNumber, Properties.SerialNumber) != 0)
		return false;

	if (IncludeSerialNumber != Properties.IncludeSerialNumber)
		return false;

	if (ExtRange != Properties.ExtRange)
		return false;

	if (MinVRate != Properties.MinVRate)
		return false;

	if (MaxVRate != Properties.MaxVRate)
		return false;

	if (MinHRate != Properties.MinHRate)
		return false;

	if (MaxHRate != Properties.MaxHRate)
		return false;

	if (MaxPClock != Properties.MaxPClock)
		return false;

	if (IncludeRangeLimits != Properties.IncludeRangeLimits)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::operator!=(const PropertiesClass &Properties)
{
	return !(*this == Properties);
}
//---------------------------------------------------------------------------
bool PropertiesClass::Read(const unsigned char *Data, bool Include)
{
	ReadProductID(Data);
	ReadSerialID(Data);
	ReadName(Data, Include);
	ReadSerialNumber(Data, Include);
	ReadRangeLimits(Data, Include);
	ReadExtensions(Data, Include);
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::ReadProductID(const unsigned char *Data)
{
	ProductID[0] = 64 | ((Data[8] >> 2) & 31);
	ProductID[1] = 64 | ((Data[8] << 3) & 24) | ((Data[9] >> 5) & 7);
	ProductID[2] = 64 | (Data[9] & 31);
	ProductID[3] = Data[11] >> 4;
	ProductID[4] = Data[11] & 15;
	ProductID[5] = Data[10] >> 4;
	ProductID[6] = Data[10] & 15;
	ProductID[3] += ProductID[3] < 10 ? 48 : 55;
	ProductID[4] += ProductID[4] < 10 ? 48 : 55;
	ProductID[5] += ProductID[5] < 10 ? 48 : 55;
	ProductID[6] += ProductID[6] < 10 ? 48 : 55;
	ProductID[7] = 0;
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::ReadSerialID(const unsigned char *Data)
{
	SerialID = Data[12];
	SerialID += Data[13] << 8;
	SerialID += Data[14] << 16;
	SerialID += (long long)Data[15] << 24;
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::ReadName(const unsigned char *Data, bool Include)
{
	int Slot;
	const char *Byte;
	unsigned long Index;
	const char *Text;

	for (Slot = 0; Slot < 4; Slot++)
	{
		Byte = &Data[Slot * 18 + 54];

		if (Byte[0] == 0 && Byte[1] == 0 && Byte[2] == 0 && Byte[3] == '\xFC')
		{
			for (Index = 0, Text = &Byte[5]; Index < MaxNameSize && Text[Index] != 0 && Text[Index] != '\x0A'; Index++)
				Name[Index] = Text[Index];

			Name[Index] = 0;

			if (Include)
				IncludeName = true;

			IncludedName = true;
			return true;
		}
	}

	IncludedName = false;
	return false;
}
//---------------------------------------------------------------------------
bool PropertiesClass::ReadSerialNumber(const unsigned char *Data, bool Include)
{
	int Slot;
	const char *Byte;
	unsigned long Index;
	const char *Text;

	for (Slot = 0; Slot < 4; Slot++)
	{
		Byte = &Data[Slot * 18 + 54];

		if (Byte[0] == 0 && Byte[1] == 0 && Byte[2] == 0 && Byte[3] == '\xFF')
		{
			for (Index = 0, Text = &Byte[5]; Index < MaxSerialNumberSize && Text[Index] != 0 && Text[Index] != '\x0A'; Index++)
				SerialNumber[Index] = Text[Index];

			SerialNumber[Index] = 0;

			if (Include)
				IncludeSerialNumber = true;

			IncludedSerialNumber = true;
			return true;
		}
	}

	IncludedSerialNumber = false;
	return false;
}
//---------------------------------------------------------------------------
bool PropertiesClass::ReadRangeLimits(const unsigned char *Data, bool Include)
{
	int Slot;
	const unsigned char *Byte;
	int OldMinVRate = MinVRate;
	int OldMaxVRate = MaxVRate;
	int OldMinHRate = MinHRate;
	int OldMaxHRate = MaxHRate;
	int OldMaxPClock = MaxPClock;

	if (Data[18] == 1 && Data[19] >= 4)
		ExtRange = 255;
	else
		ExtRange = 0;

	for (Slot = 0; Slot < 4; Slot++)
	{
		Byte = &Data[Slot * 18 + 54];

		if (Byte[0] == 0 && Byte[1] == 0 && Byte[2] == 0 && Byte[3] == 0xFD)
		{
			MinVRate = Byte[5];
			MaxVRate = Byte[6];
			MinHRate = Byte[7];
			MaxHRate = Byte[8];

			if (Byte[4] & 1)
				MinVRate += 255;

			if (Byte[4] & 2)
				MaxVRate += 255;

			if (Byte[4] & 4)
				MinHRate += 255;

			if (Byte[4] & 8)
				MaxHRate += 255;

			MaxPClock = Byte[9] * 10;

			if (!IsValidRangeLimits())
			{
				MinVRate = OldMinVRate;
				MaxVRate = OldMaxVRate;
				MinHRate = OldMinHRate;
				MaxHRate = OldMaxHRate;
				MaxPClock = OldMaxPClock;

				if (!IsValidRangeLimits())
				{
					MinVRate = BLANK;
					MaxVRate = BLANK;
					MinHRate = BLANK;
					MaxHRate = BLANK;
					MaxPClock = BLANK;
				}

				IncludedRangeLimits = false;
				return false;
			}

			if (Include || ExtRange && (Data[24] & 1) && MinHRate == MaxHRate && Byte[10] == 1)
				IncludeRangeLimits = true;

			IncludedRangeLimits = true;
			return true;
		}
	}

	if (!IsValidRangeLimits())
	{
		MinVRate = BLANK;
		MaxVRate = BLANK;
		MinHRate = BLANK;
		MaxHRate = BLANK;
		MaxPClock = BLANK;
	}

	IncludedRangeLimits = false;
	return false;
}
//---------------------------------------------------------------------------
bool PropertiesClass::ReadExtensions(const unsigned char *Data, bool Include)
{
	if (Extensions == BLANK)
		Extensions = Data[126];

	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::Write(unsigned char *Data)
{
	WriteProductID(Data);
	WriteSerialID(Data);
	WriteRangeLimits(Data);
	WriteName(Data);
	WriteSerialNumber(Data);
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::WriteProductID(unsigned char *Data)
{
	if (!IsProductID())
		return false;

	Data[8] = ((ProductID[0] & 31) << 2) | ((ProductID[1] & 24) >> 3);
	Data[9] = ((ProductID[1] & 7) << 5) | (ProductID[2] & 31);
	Data[10] = 0;
	Data[10] |= std::isdigit(ProductID[5]) ? ProductID[5] << 4 : (ProductID[5] - 7) << 4;
	Data[10] |= std::isdigit(ProductID[6]) ? ProductID[6] & 15 : (ProductID[6] - 7) & 15;
	Data[11] = 0;
	Data[11] |= std::isdigit(ProductID[3]) ? ProductID[3] << 4 : (ProductID[3] - 7) << 4;
	Data[11] |= std::isdigit(ProductID[4]) ? ProductID[4] & 15 : (ProductID[4] - 7) & 15;
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::WriteSerialID(unsigned char *Data)
{
	if (!IsValidSerialID())
		return false;

	Data[12] = SerialID & 255;
	Data[13] = (SerialID >> 8) & 255;
	Data[14] = (SerialID >> 16) & 255;
	Data[15] = (SerialID >> 24) & 255;
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::WriteName(unsigned char *Data)
{
	int Slot;
	char *Byte;
	unsigned long Index;

	if (!IncludeName || !IsValidName() || Name[0] == 0)
		return false;

	for (Slot = 0; Slot < 4; Slot++)
	{
		Byte = &Data[Slot * 18 + 54];

		if (Byte[0] == 0 && Byte[1] == 0 && Byte[2] == 0 && Byte[3] == '\x10')
		{
			Byte[3] = '\xFC';
			Byte[4] = 0;

			for (Index = 0; Index < MaxNameSize && Name[Index] != 0 && Name[Index] != '\x0A'; Index++)
				Byte[Index + 5] = Name[Index];

			if (Index < MaxNameSize)
				Byte[Index + 5] = '\x0A';

			for (Index++; Index < MaxNameSize; Index++)
				Byte[Index + 5] = '\x20';

			return true;
		}
	}

	return false;
}
//---------------------------------------------------------------------------
bool PropertiesClass::WriteSerialNumber(unsigned char *Data)
{
	int Slot;
	char *Byte;
	unsigned long Index;

	if (!IncludeSerialNumber || !IsValidSerialNumber() || SerialNumber[0] == 0)
		return false;

	for (Slot = 0; Slot < 4; Slot++)
	{
		Byte = &Data[Slot * 18 + 54];

		if (Byte[0] == 0 && Byte[1] == 0 && Byte[2] == 0 && Byte[3] == '\x10')
		{
			Byte[3] = '\xFF';
			Byte[4] = 0;

			for (Index = 0; Index < MaxSerialNumberSize && SerialNumber[Index] != 0 && SerialNumber[Index] != '\x0A'; Index++)
				Byte[Index + 5] = SerialNumber[Index];

			if (Index < MaxSerialNumberSize)
				Byte[Index + 5] = '\x0A';

			for (Index++; Index < MaxSerialNumberSize; Index++)
				Byte[Index + 5] = '\x20';

			return true;
		}
	}

	return false;
}
//---------------------------------------------------------------------------
bool PropertiesClass::WriteRangeLimits(unsigned char *Data)
{
	int Slot;
	unsigned char *Byte;

	Data[24] &= 254;

	if (!IncludeRangeLimits || !IsValidRangeLimits() || IsBlankRangeLimits())
		return false;

	for (Slot = 0; Slot < 4; Slot++)
	{
		Byte = &Data[Slot * 18 + 54];

		if (Byte[0] == 0 && Byte[1] == 0 && Byte[2] == 0 && Byte[3] == 0x10)
		{
			if (ExtRange)
				Data[24] |= 1;

			Byte[3] = 0xFD;
			Byte[4] = 0;
			Byte[5] = (MinVRate - 1) % 255 + 1;
			Byte[6] = (MaxVRate - 1) % 255 + 1;
			Byte[7] = (MinHRate - 1) % 255 + 1;
			Byte[8] = (MaxHRate - 1) % 255 + 1;

			if (MinVRate > 255)
				Byte[4] |= 1;

			if (MaxVRate > 255)
				Byte[4] |= 2;

			if (MinHRate > 255)
				Byte[4] |= 4;

			if (MaxHRate > 255)
				Byte[4] |= 8;

			Byte[9] = MaxPClock / 10;

			if (ExtRange)
				Byte[10] = 1;
			else
				Byte[10] = 0;

			Byte[11] = 0x0A;
			Byte[12] = 0x20;
			Byte[13] = 0x20;
			Byte[14] = 0x20;
			Byte[15] = 0x20;
			Byte[16] = 0x20;
			Byte[17] = 0x20;
			return true;
		}
	}

	return false;
}
//---------------------------------------------------------------------------
bool PropertiesClass::LoadBackupData(HKEY Key)
{
	LoadOldBackupName(Key);
	LoadBackupName(Key);
	LoadBackupSerialNumber(Key);
	LoadBackupRangeLimits(Key);
	LoadBackupExtensions(Key);
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::LoadOldBackupName(HKEY Key)
{
	char Buffer[256];
	unsigned long BufferSize = 256;
	unsigned long Index;

	if (RegQueryValueEx(Key, "", NULL, NULL, Buffer, &BufferSize) != ERROR_SUCCESS)
		return false;

	if (BufferSize > MaxNameSize)
		BufferSize = MaxNameSize;

	for (Index = 0; Index < BufferSize && Buffer[Index] != 0 && Buffer[Index] != '\x0A'; Index++)
		Name[Index] = Buffer[Index];

	Name[Index] = 0;
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::LoadBackupName(HKEY Key)
{
	char Buffer[256];
	unsigned long BufferSize = 256;
	unsigned long Index;

	if (RegQueryValueEx(Key, RegName, NULL, NULL, Buffer, &BufferSize) != ERROR_SUCCESS)
		return false;

	if (BufferSize == 0)
		return false;

	if (BufferSize > 1 + MaxNameSize)
		BufferSize = 1 + MaxNameSize;

	IncludeName = Buffer[0];

	for (Index = 1; Index < BufferSize && Buffer[Index] != 0 && Buffer[Index] != '\x0A'; Index++)
		Name[Index - 1] = Buffer[Index];

	Name[Index - 1] = 0;
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::LoadBackupSerialNumber(HKEY Key)
{
	char Buffer[256];
	unsigned long BufferSize = 256;
	unsigned long Index;

	if (RegQueryValueEx(Key, RegSerialNumber, NULL, NULL, Buffer, &BufferSize) != ERROR_SUCCESS)
		return false;

	if (BufferSize == 0)
		return false;

	if (BufferSize > 1 + MaxSerialNumberSize)
		BufferSize = 1 + MaxSerialNumberSize;

	IncludeSerialNumber = Buffer[0];

	for (Index = 1; Index < BufferSize && Buffer[Index] != 0 && Buffer[Index] != '\x0A'; Index++)
		SerialNumber[Index - 1] = Buffer[Index];

	SerialNumber[Index - 1] = 0;
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::LoadBackupRangeLimits(HKEY Key)
{
	unsigned char Buffer[256];
	unsigned long BufferSize = 256;

	if (RegQueryValueEx(Key, RegRangeLimits, NULL, NULL, Buffer, &BufferSize) != ERROR_SUCCESS)
		return false;

	if (BufferSize == 0)
		return false;

	if (BufferSize >= 11)
	{
		MinVRate = (Buffer[1] << 8) + Buffer[2];
		MaxVRate = (Buffer[3] << 8) + Buffer[4];
		MinHRate = (Buffer[5] << 8) + Buffer[6];
		MaxHRate = (Buffer[7] << 8) + Buffer[8];
		MaxPClock = (Buffer[9] << 8) + Buffer[10];

		if (!IsValidRangeLimits())
		{
			MinVRate = BLANK;
			MaxVRate = BLANK;
			MinHRate = BLANK;
			MaxHRate = BLANK;
			MaxPClock = BLANK;
		}
	}
	else
	{
		MinVRate = BLANK;
		MaxVRate = BLANK;
		MinHRate = BLANK;
		MaxHRate = BLANK;
		MaxPClock = BLANK;
	}

	IncludeRangeLimits = Buffer[0];
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::LoadBackupExtensions(HKEY Key)
{
	unsigned char Buffer[256];
	unsigned long BufferSize = 256;

	if (RegQueryValueEx(Key, RegExtensions, NULL, NULL, Buffer, &BufferSize) != ERROR_SUCCESS)
		return false;

	if (BufferSize == 0)
		return false;

	Extensions = Buffer[0];
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SaveBackupData(HKEY Key, int Slots)
{
	SaveOldBackupName(Key, Slots);
	SaveBackupName(Key);
	SaveBackupSerialNumber(Key);
	SaveBackupRangeLimits(Key);
	SaveBackupExtensions(Key);
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SaveOldBackupName(HKEY Key, int Slots)
{
	int Count = 0;

	if (IncludeRangeLimits && IsValidRangeLimits() && !IsBlankRangeLimits())
		Count++;

	if (IsValidName() && Name[0] != 0)
	{
		if (!IncludeName || Count >= Slots)
		{
			if (RegSetValueEx(Key, "", 0, REG_SZ, Name, std::strlen(Name) + 1) != ERROR_SUCCESS)
				return false;

			return true;
		}
	}

	if (RegDeleteValue(Key, "") != ERROR_SUCCESS)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SaveBackupName(HKEY Key)
{
	char Buffer[256];
	unsigned long BufferSize;
	unsigned long Index;

	Buffer[0] = IncludeName;
	BufferSize = 1;

	if (IsValidName() && Name[0] != 0)
		for (Index = 0; Index < MaxNameSize && Name[Index] != 0 && Name[Index] != '\x0A'; Index++, BufferSize++)
			Buffer[BufferSize] = Name[Index];

	if (RegSetValueEx(Key, RegName, 0, REG_BINARY, Buffer, BufferSize) != ERROR_SUCCESS)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SaveBackupSerialNumber(HKEY Key)
{
	char Buffer[256];
	unsigned long BufferSize;
	unsigned long Index;

	Buffer[0] = IncludeSerialNumber;
	BufferSize = 1;

	if (IsValidSerialNumber() && SerialNumber[0] != 0)
		for (Index = 0; Index < MaxSerialNumberSize && SerialNumber[Index] != 0 && SerialNumber[Index] != '\x0A'; Index++, BufferSize++)
			Buffer[BufferSize] = SerialNumber[Index];

	if (RegSetValueEx(Key, RegSerialNumber, 0, REG_BINARY, Buffer, BufferSize) != ERROR_SUCCESS)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SaveBackupRangeLimits(HKEY Key)
{
	unsigned char Buffer[256];
	unsigned long BufferSize;

	Buffer[0] = IncludeRangeLimits;
	BufferSize = 1;

	if (IsValidRangeLimits() && !IsBlankRangeLimits())
	{
		Buffer[1] = MinVRate >> 8;
		Buffer[2] = MinVRate & 255;
		Buffer[3] = MaxVRate >> 8;
		Buffer[4] = MaxVRate & 255;
		Buffer[5] = MinHRate >> 8;
		Buffer[6] = MinHRate & 255;
		Buffer[7] = MaxHRate >> 8;
		Buffer[8] = MaxHRate & 255;
		Buffer[9] = MaxPClock >> 8;
		Buffer[10] = MaxPClock & 255;
		BufferSize = 11;
	}

	if (RegSetValueEx(Key, RegRangeLimits, 0, REG_BINARY, Buffer, BufferSize) != ERROR_SUCCESS)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SaveBackupExtensions(HKEY Key)
{
	unsigned char Buffer[256];
	unsigned long BufferSize;

	Buffer[0] = Extensions;
	BufferSize = 1;

	if (RegSetValueEx(Key, RegExtensions, 0, REG_BINARY, Buffer, BufferSize) != ERROR_SUCCESS)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::CopyPastePossible(PropertiesClass Properties)
{
	if (IncludeName != Properties.IncludeName)
		return true;

	if (IncludeSerialNumber != Properties.IncludeSerialNumber)
		return true;

	return false;
}
//---------------------------------------------------------------------------
bool PropertiesClass::CopyPossible(PropertiesClass Properties)
{
	if (CopyPastePossible(Properties))
		return true;

	if (Properties.IncludeRangeLimits)
	{
		if (MinVRate != Properties.MinVRate)
			return true;

		if (MaxVRate != Properties.MaxVRate)
			return true;

		if (MinHRate != Properties.MinHRate)
			return true;

		if (MaxHRate != Properties.MaxHRate)
			return true;

		if (MaxPClock != Properties.MaxPClock)
			return true;
	}

	if (IncludeRangeLimits != Properties.IncludeRangeLimits)
		return true;

	return false;
}
//---------------------------------------------------------------------------
bool PropertiesClass::PastePossible(PropertiesClass Properties)
{
	if (CopyPastePossible(Properties))
		return true;

	Properties.ExtRange = ExtRange;

	if (Properties.IsValidRangeLimits())
	{
		if (Properties.IncludeRangeLimits)
		{
			if (MinVRate != Properties.MinVRate)
				return true;

			if (MaxVRate != Properties.MaxVRate)
				return true;

			if (MinHRate != Properties.MinHRate)
				return true;

			if (MaxHRate != Properties.MaxHRate)
				return true;

			if (MaxPClock != Properties.MaxPClock)
				return true;
		}

		if (IncludeRangeLimits != Properties.IncludeRangeLimits)
			return true;
	}
	else
	{
		if (IncludeRangeLimits != false)
			return true;
	}

	return false;
}
//---------------------------------------------------------------------------
bool PropertiesClass::Paste(PropertiesClass Properties)
{
	return PasteImport(Properties);
}
//---------------------------------------------------------------------------
bool PropertiesClass::Import(PropertiesClass Properties)
{
	return PasteImport(Properties);
}
//---------------------------------------------------------------------------
bool PropertiesClass::PasteImport(PropertiesClass Properties)
{
	IncludeName = Properties.IncludeName;
	IncludeSerialNumber = Properties.IncludeSerialNumber;
	Properties.ExtRange = ExtRange;

	if (Properties.IsValidRangeLimits())
	{
		if (Properties.IncludeRangeLimits)
		{
			MinVRate = Properties.MinVRate;
			MaxVRate = Properties.MaxVRate;
			MinHRate = Properties.MinHRate;
			MaxHRate = Properties.MaxHRate;
			MaxPClock = Properties.MaxPClock;
		}

		IncludeRangeLimits = Properties.IncludeRangeLimits;
	}
	else
	{
		IncludeRangeLimits = false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::ResetIncludes()
{
	IncludeName = IncludedName;
	IncludeSerialNumber = IncludedSerialNumber;
	IncludeRangeLimits = IncludedRangeLimits;
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::FixIncludes(int Slots)
{
	int Count = 0;

	if (Count >= Slots)
		return true;

	if (IncludeRangeLimits && IsValidRangeLimits() && !IsBlankRangeLimits())
	{
		if (!IncludedRangeLimits)
			return ResetIncludes();

		Count++;

		if (Count >= Slots)
			return true;
	}

	if (IncludeName && IsValidName() && Name[0] != 0)
	{
		if (!IncludedName)
			return ResetIncludes();

		Count++;

		if (Count >= Slots)
			return true;
	}

	if (IncludeSerialNumber && IsValidSerialNumber() && SerialNumber[0] != 0)
	{
		if (!IncludedSerialNumber)
			return ResetIncludes();

		Count++;

		if (Count >= Slots)
			return true;
	}

	return true;
}
//---------------------------------------------------------------------------
int PropertiesClass::GetCount()
{
	int Count = 0;

	if (IncludeRangeLimits && IsValidRangeLimits() && !IsBlankRangeLimits())
		Count++;

	if (IncludeName && IsValidName() && Name[0] != 0)
		Count++;

	if (IncludeSerialNumber && IsValidSerialNumber() && SerialNumber[0] != 0)
		Count++;

	return Count;
}
//---------------------------------------------------------------------------
bool PropertiesClass::GetText(int Slot, char *Text, int TextSize)
{
	if (Slot == 0)
		return GetRangeLimitsText(Text, TextSize);

	if (Slot == 1)
		return GetNameText(Text, TextSize);

	if (Slot == 2)
		return GetSerialNumberText(Text, TextSize);

	return false;
}
//---------------------------------------------------------------------------
bool PropertiesClass::GetProductID(char *Text, int TextSize)
{
	std::snprintf(Text, TextSize, "%s", ProductID);
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SetProductID(const char *NewProductID)
{
	std::snprintf(ProductID, sizeof ProductID, "%s", NewProductID);
	std::strupr(ProductID);
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SetResetID(const char *NewResetID)
{
	if (std::strcmp(NewResetID, "Default_Monitor") == 0)
	{
		std::snprintf(ResetID, sizeof ResetID, "PNP09FF");
		return true;
	}

	std::snprintf(ResetID, sizeof ResetID, "%s", NewResetID);
	std::strupr(ResetID);
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::ResetProductIDPossible()
{
	return std::strcmp(ProductID, ResetID) != 0;
}
//---------------------------------------------------------------------------
bool PropertiesClass::ResetProductID()
{
	std::snprintf(ProductID, sizeof ProductID, "%s", ResetID);
	return true;
}
//---------------------------------------------------------------------------
long long PropertiesClass::GetSerialID()
{
	return SerialID;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SetSerialID(long long Value)
{
	SerialID = Value;
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::GetNameText(char *Text, int TextSize)
{
	if (!IncludeName || !IsValidName() || Name[0] == 0)
		return false;

	std::snprintf(Text, TextSize, "Name: %s", Name);
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::GetName(char *Text, int TextSize)
{
	std::snprintf(Text, TextSize, "%s", Name);
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SetName(const char *NewName)
{
	std::snprintf(Name, sizeof Name, "%s", NewName);
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::GetIncludeName()
{
	return IncludeName;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SetIncludeName(bool Enabled)
{
	IncludeName = Enabled;
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::GetSerialNumberText(char *Text, int TextSize)
{
	if (!IncludeSerialNumber || !IsValidSerialNumber() || SerialNumber[0] == 0)
		return false;

	std::snprintf(Text, TextSize, "Serial number: %s", SerialNumber);
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::GetSerialNumber(char *Text, int TextSize)
{
	std::snprintf(Text, TextSize, "%s", SerialNumber);
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SetSerialNumber(const char *NewSerialNumber)
{
	std::snprintf(SerialNumber, sizeof SerialNumber, "%s", NewSerialNumber);
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::GetIncludeSerialNumber()
{
	return IncludeSerialNumber;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SetIncludeSerialNumber(bool Enabled)
{
	IncludeSerialNumber = Enabled;
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::GetRangeLimitsText(char *Text, int TextSize)
{
	if (!IncludeRangeLimits || !IsValidRangeLimits() || IsBlankRangeLimits())
		return false;

	std::snprintf(Text, TextSize, "Range limits: %d-%d Hz, %d-%d kHz, %d MHz", MinVRate, MaxVRate, MinHRate, MaxHRate, MaxPClock);
	return true;
}
//---------------------------------------------------------------------------
int PropertiesClass::GetExtRange()
{
	return ExtRange;
}
//---------------------------------------------------------------------------
int PropertiesClass::GetMinVRate()
{
	return MinVRate;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SetMinVRate(int NewMinVRate)
{
	MinVRate = NewMinVRate;
	return true;
}
//---------------------------------------------------------------------------
int PropertiesClass::GetMaxVRate()
{
	return MaxVRate;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SetMaxVRate(int NewMaxVRate)
{
	MaxVRate = NewMaxVRate;
	return true;
}
//---------------------------------------------------------------------------
int PropertiesClass::GetMinHRate()
{
	return MinHRate;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SetMinHRate(int NewMinHRate)
{
	MinHRate = NewMinHRate;
	return true;
}
//---------------------------------------------------------------------------
int PropertiesClass::GetMaxHRate()
{
	return MaxHRate;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SetMaxHRate(int NewMaxHRate)
{
	MaxHRate = NewMaxHRate;
	return true;
}
//---------------------------------------------------------------------------
int PropertiesClass::GetMaxPClock()
{
	return MaxPClock;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SetMaxPClock(int NewMaxPClock)
{
	MaxPClock = NewMaxPClock;
	return true;
}
//---------------------------------------------------------------------------
bool PropertiesClass::GetIncludeRangeLimits()
{
	return IncludeRangeLimits;
}
//---------------------------------------------------------------------------
bool PropertiesClass::SetIncludeRangeLimits(bool Enabled)
{
	IncludeRangeLimits = Enabled;
	return true;
}
//---------------------------------------------------------------------------
int PropertiesClass::GetExtensions()
{
	return Extensions;
}
//---------------------------------------------------------------------------
bool PropertiesClass::IsValid()
{
	if (IsProductID())
	if (IsValidSerialID())
	if (IsValidName())
	if (IsValidSerialNumber())
	if (IsValidRangeLimits())
		return true;

	return false;
}
//---------------------------------------------------------------------------
bool PropertiesClass::IsProductID()
{
	if (std::strlen(ProductID) != 7)
		return false;

	if (ProductID[0] >= '@' && ProductID[0] <= '_')
	if (ProductID[1] >= '@' && ProductID[1] <= '_')
	if (ProductID[2] >= '@' && ProductID[2] <= '_')
	if (isxdigit(ProductID[3]))
	if (isxdigit(ProductID[4]))
	if (isxdigit(ProductID[5]))
	if (isxdigit(ProductID[6]))
		return true;

	return false;
}
//---------------------------------------------------------------------------
bool PropertiesClass::IsValidProductID()
{
	if (std::strlen(ProductID) != 7)
		return false;

	if (ProductID[0] >= 'A' && ProductID[0] <= 'Z')
	if (ProductID[1] >= 'A' && ProductID[1] <= 'Z')
	if (ProductID[2] >= 'A' && ProductID[2] <= 'Z')
	if (isxdigit(ProductID[3]))
	if (isxdigit(ProductID[4]))
	if (isxdigit(ProductID[5]))
	if (isxdigit(ProductID[6]))
		return true;

	return false;
}
//---------------------------------------------------------------------------
bool PropertiesClass::IsValidSerialID()
{
	return SerialID >= MinSerialID && SerialID <= MaxSerialID;
}
//---------------------------------------------------------------------------
bool PropertiesClass::IsValidName()
{
	return std::strlen(Name) <= MaxNameSize;
}
//---------------------------------------------------------------------------
bool PropertiesClass::IsValidSerialNumber()
{
	return std::strlen(SerialNumber) <= MaxSerialNumberSize;
}
//---------------------------------------------------------------------------
bool PropertiesClass::IsValidMinVRate()
{
	if (MinVRate < MinVRange || MinVRate > MaxVRange + ExtRange)
		return false;

	if (MaxVRate < MinVRange || MaxVRate > MaxVRange + ExtRange)
		return true;

	return MinVRate <= MaxVRate;
}
//---------------------------------------------------------------------------
bool PropertiesClass::IsValidMaxVRate()
{
	if (MaxVRate < MinVRange || MaxVRate > MaxVRange + ExtRange)
		return false;

	if (MinVRate < MinVRange || MinVRate > MaxVRange + ExtRange)
		return true;

	return MaxVRate >= MinVRate;
}
//---------------------------------------------------------------------------
bool PropertiesClass::IsValidMinHRate()
{
	if (MinHRate < MinHRange || MinHRate > MaxHRange + ExtRange)
		return false;

	if (MaxHRate < MinHRange || MaxHRate > MaxHRange + ExtRange)
		return true;

	return MinHRate <= MaxHRate;
}
//---------------------------------------------------------------------------
bool PropertiesClass::IsValidMaxHRate()
{
	if (MaxHRate < MinHRange || MaxHRate > MaxHRange + ExtRange)
		return false;

	if (MinHRate < MinHRange || MinHRate > MaxHRange + ExtRange)
		return true;

	return MaxHRate >= MinHRate;
}
//---------------------------------------------------------------------------
bool PropertiesClass::IsValidMaxPClock()
{
	return MaxPClock >= MinPClockRange && MaxPClock <= MaxPClockRange && MaxPClock % ModPClockRange == 0;
}
//---------------------------------------------------------------------------
bool PropertiesClass::IsBlankRangeLimits()
{
	return MinVRate == BLANK && MaxVRate == BLANK && MinHRate == BLANK && MaxHRate == BLANK && MaxPClock == BLANK;
}
//---------------------------------------------------------------------------
bool PropertiesClass::IsValidRangeLimits()
{
	if (IsBlankRangeLimits())
		return true;

	return IsValidMinVRate() && IsValidMaxVRate() && IsValidMinHRate() && IsValidMaxHRate() && IsValidMaxPClock();
}
//---------------------------------------------------------------------------
