//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AMDDisplayClass.h"
#include <cstdlib>
#include <cstring>
//---------------------------------------------------------------------------
#define ADL_OK                          0
#define ADL_MAX_PATH                    256
#define ADL_MAX_EDIDDATA_SIZE           256
//---------------------------------------------------------------------------
struct ADLAdapterInfo
{
	int Size;
	int AdapterIndex;
	char UDID[ADL_MAX_PATH];
	int BusNumber;
	int DeviceNumber;
	int FunctionNumber;
	int VendorID;
	char AdapterName[ADL_MAX_PATH];
	char DisplayName[ADL_MAX_PATH];
	int Present;
	int Exist;
	char DriverPath[ADL_MAX_PATH];
	char DriverPathExt[ADL_MAX_PATH];
	char PNPString[ADL_MAX_PATH];
	int OSDisplayIndex;
};

struct ADLDisplayID
{
	int DisplayLogicalIndex;
	int DisplayPhysicalIndex;
	int DisplayLogicalAdapterIndex;
	int DisplayPhysicalAdapterIndex;
};

struct ADLDisplayInfo
{
	struct ADLDisplayID DisplayID;
	int DisplayControllerIndex;
	char DisplayName[ADL_MAX_PATH];
	char DisplayManufacturerName[ADL_MAX_PATH];
	int DisplayType;
	int DisplayOutputType;
	int DisplayConnector;
	int DisplayInfoMask;
	int DisplayInfoValue;
};

struct ADLDisplayEDIDData
{
	int Size;
	int Flag;
	int EDIDSize;
	int BlockIndex;
	char EDIDData[ADL_MAX_EDIDDATA_SIZE];
	int Reserved[4];
};
//---------------------------------------------------------------------------
typedef void *(__stdcall *ADL_MAIN_MALLOC_CALLBACK)(int);
typedef int (*ADL_MAIN_CONTROL_CREATE)(ADL_MAIN_MALLOC_CALLBACK, int);
typedef int (*ADL_ADAPTER_NUMBEROFADAPTERS_GET)(int *);
typedef int (*ADL_ADAPTER_ADAPTERINFO_GET)(struct ADLAdapterInfo *, int);
typedef int (*ADL_DISPLAY_DISPLAYINFO_GET)(int, int *, struct ADLDisplayInfo **, int);
typedef int (*ADL_DISPLAY_EDIDDATA_GET)(int, int, struct ADLDisplayEDIDData *);
typedef int (*ADL_MAIN_CONTROL_DESTROY)();
//---------------------------------------------------------------------------
void *__stdcall ADL_Main_Memory_Alloc(int Size)
{
	return std::malloc(Size);
}
//---------------------------------------------------------------------------
ADL_MAIN_CONTROL_CREATE                 ADL_Main_Control_Create;
ADL_ADAPTER_NUMBEROFADAPTERS_GET        ADL_Adapter_NumberOfAdapters_Get;
ADL_ADAPTER_ADAPTERINFO_GET             ADL_Adapter_AdapterInfo_Get;
ADL_DISPLAY_DISPLAYINFO_GET             ADL_Display_DisplayInfo_Get;
ADL_DISPLAY_EDIDDATA_GET                ADL_Display_EdidData_Get;
ADL_MAIN_CONTROL_DESTROY                ADL_Main_Control_Destroy;
//---------------------------------------------------------------------------
bool AMDDisplayClass::LoadEDIDList(EDIDListClass &EDIDList)
{
	HMODULE Library;
	int AdapterCount;
	int AdapterInfoSize;
	struct ADLAdapterInfo *AdapterInfo;
	int AdapterNumber;
	int AdapterIndex;
	struct ADLDisplayInfo *DisplayInfo;
	int DisplayCount;
	int DisplayNumber;
	ADLDisplayEDIDData DisplayEDID;
	int DataSize;
	unsigned char NewDisplayEDID[MAX_EDID_BLOCKS * 128];
	int BlockIndex;
	bool Status = false;

	Library = LoadLibrary("atiadlxx.dll");

	if (!Library)
	{
		Library = LoadLibrary("atiadlxy.dll");

		if (!Library)
			return false;
	}

	ADL_Main_Control_Create = (ADL_MAIN_CONTROL_CREATE)GetProcAddress(Library, "ADL_Main_Control_Create");
	ADL_Adapter_NumberOfAdapters_Get = (ADL_ADAPTER_NUMBEROFADAPTERS_GET)GetProcAddress(Library, "ADL_Adapter_NumberOfAdapters_Get");
	ADL_Adapter_AdapterInfo_Get = (ADL_ADAPTER_ADAPTERINFO_GET)GetProcAddress(Library, "ADL_Adapter_AdapterInfo_Get");
	ADL_Display_DisplayInfo_Get = (ADL_DISPLAY_DISPLAYINFO_GET)GetProcAddress(Library, "ADL_Display_DisplayInfo_Get");
	ADL_Display_EdidData_Get = (ADL_DISPLAY_EDIDDATA_GET)GetProcAddress(Library, "ADL_Display_EdidData_Get");
	ADL_Main_Control_Destroy = (ADL_MAIN_CONTROL_DESTROY)GetProcAddress(Library, "ADL_Main_Control_Destroy");

	if (!ADL_Main_Control_Create)
		return false;

	if (!ADL_Adapter_NumberOfAdapters_Get)
		return false;

	if (!ADL_Adapter_AdapterInfo_Get)
		return false;

	if (!ADL_Display_DisplayInfo_Get)
		return false;

	if (!ADL_Display_EdidData_Get)
		return false;

	if (!ADL_Main_Control_Destroy)
		return false;

	if (ADL_Main_Control_Create(ADL_Main_Memory_Alloc, 1) != ADL_OK)
		return false;

	if (ADL_Adapter_NumberOfAdapters_Get(&AdapterCount) != ADL_OK)
		return false;

	if (AdapterCount > 0)
	{
		AdapterInfoSize = AdapterCount * sizeof(struct ADLAdapterInfo);
		AdapterInfo = (struct ADLAdapterInfo *)std::malloc(AdapterInfoSize);

		if (ADL_Adapter_AdapterInfo_Get(AdapterInfo, AdapterInfoSize) == ADL_OK)
		{
			for (AdapterNumber = 0; AdapterNumber < AdapterCount; AdapterNumber++)
			{
				for (AdapterIndex = 0; AdapterIndex < AdapterNumber; AdapterIndex++)
					if (std::strcmp(AdapterInfo[AdapterNumber].DriverPathExt, AdapterInfo[AdapterIndex].DriverPathExt) == 0)
						break;

				if (AdapterIndex < AdapterNumber)
					continue;

				DisplayInfo = NULL;

				if (ADL_Display_DisplayInfo_Get(AdapterInfo[AdapterNumber].AdapterIndex, &DisplayCount, &DisplayInfo, 0) != ADL_OK)
					continue;

				for (DisplayNumber = 0; DisplayNumber < DisplayCount; DisplayNumber++)
				{
					if (DisplayInfo[DisplayNumber].DisplayInfoValue & 1)
					{
						std::memset(&DisplayEDID, 0, sizeof DisplayEDID);
						DisplayEDID.Size = sizeof DisplayEDID;
						DisplayEDID.BlockIndex = 0;

						if (ADL_Display_EdidData_Get(AdapterInfo[AdapterNumber].AdapterIndex, DisplayInfo[DisplayNumber].DisplayID.DisplayLogicalIndex, &DisplayEDID) != ADL_OK)
							continue;

						DataSize = MAX_EDID_BLOCKS * 128;

						if (DataSize > DisplayEDID.EDIDSize)
							DataSize = DisplayEDID.EDIDSize;

						std::memset(NewDisplayEDID, 0, MAX_EDID_BLOCKS * 128);
						std::memcpy(NewDisplayEDID, DisplayEDID.EDIDData, DataSize);

						for (BlockIndex = 1; BlockIndex < MAX_EDID_BLOCKS; BlockIndex++)
						{
							std::memset(&DisplayEDID, 0, sizeof DisplayEDID);
							DisplayEDID.Size = sizeof DisplayEDID;
							DisplayEDID.BlockIndex = BlockIndex;

							if (ADL_Display_EdidData_Get(AdapterInfo[AdapterNumber].AdapterIndex, DisplayInfo[DisplayNumber].DisplayID.DisplayLogicalIndex, &DisplayEDID) != ADL_OK)
								break;

							std::memcpy(&NewDisplayEDID[BlockIndex * 128], DisplayEDID.EDIDData, 128);
						}

						EDIDList.Add(NewDisplayEDID);
						Status = true;
					}
				}

				std::free(DisplayInfo);
			}
		}

		std::free(AdapterInfo);
	}

	ADL_Main_Control_Destroy();
	FreeLibrary(Library);
	return Status;
}
//---------------------------------------------------------------------------
