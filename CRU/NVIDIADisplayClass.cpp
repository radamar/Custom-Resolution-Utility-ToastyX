//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "NVIDIADisplayClass.h"
#include <cstring>
//---------------------------------------------------------------------------
#define NVAPI_OK                        0
#define NV_EDID_DATA_SIZE               256
#define NVAPI_MAX_PHYSICAL_GPUS         64
#define NVAPI_MAX_HEADS_PER_GPU         32
#define NV_EDID_VER3                    ((3 << 16) | sizeof(struct NV_EDID_V3))
//---------------------------------------------------------------------------
struct NV_EDID_V3
{
	int Version;
	unsigned char EDIDData[NV_EDID_DATA_SIZE];
	int EDIDSize;
	int EDIDID;
	int Offset;
};
//---------------------------------------------------------------------------
typedef void *(*NVAPI_QUERYINTERFACE)(int);
typedef int (*NVAPI_INITIALIZE)();
typedef int (*NVAPI_ENUMPHYSICALGPUS)(int **, int *);
typedef int (*NVAPI_GPU_GETACTIVEOUTPUTS)(int *, int *);
typedef int (*NVAPI_GPU_GETEDID)(int *, int, struct NV_EDID_V3 *);
typedef int (*NVAPI_UNLOAD)();
//---------------------------------------------------------------------------
NVAPI_QUERYINTERFACE                    NvAPI_QueryInterface;
NVAPI_INITIALIZE                        NvAPI_Initialize;
NVAPI_ENUMPHYSICALGPUS                  NvAPI_EnumPhysicalGPUs;
NVAPI_GPU_GETACTIVEOUTPUTS              NvAPI_GPU_GetActiveOutputs;
NVAPI_GPU_GETEDID                       NvAPI_GPU_GetEDID;
NVAPI_UNLOAD                            NvAPI_Unload;
//---------------------------------------------------------------------------
bool NVIDIADisplayClass::LoadEDIDList(EDIDListClass &EDIDList)
{
	HMODULE Library;
	int *GPUHandle[NVAPI_MAX_PHYSICAL_GPUS];
	int GPUCount;
	int GPUIndex;
	int OutputMask;
	int OutputIndex;
	int OutputID;
	struct NV_EDID_V3 DisplayEDID;
	int EDIDSize;
	int DataSize;
	unsigned char NewDisplayEDID[MAX_EDID_BLOCKS * 128];
	int Offset;
	bool Status = false;

	Library = LoadLibrary("nvapi.dll");

	if (!Library)
		return false;

	NvAPI_QueryInterface = (NVAPI_QUERYINTERFACE)GetProcAddress(Library, "nvapi_QueryInterface");

	if (!NvAPI_QueryInterface)
		return false;

	NvAPI_Initialize = (NVAPI_INITIALIZE)NvAPI_QueryInterface(0x0150E828);
	NvAPI_EnumPhysicalGPUs = (NVAPI_ENUMPHYSICALGPUS)NvAPI_QueryInterface(0xE5AC921F);
	NvAPI_GPU_GetActiveOutputs = (NVAPI_GPU_GETACTIVEOUTPUTS)NvAPI_QueryInterface(0xE3E89B6F);
	NvAPI_GPU_GetEDID = (NVAPI_GPU_GETEDID)NvAPI_QueryInterface(0x37D32E69);
	NvAPI_Unload = (NVAPI_UNLOAD)NvAPI_QueryInterface(0xD22BDD7E);

	if (!NvAPI_Initialize)
		return false;

	if (!NvAPI_EnumPhysicalGPUs)
		return false;

	if (!NvAPI_GPU_GetActiveOutputs)
		return false;

	if (!NvAPI_GPU_GetEDID)
		return false;

	if (!NvAPI_Unload)
		return false;

	if (NvAPI_Initialize() != NVAPI_OK)
		return false;

	if (NvAPI_EnumPhysicalGPUs(GPUHandle, &GPUCount) != NVAPI_OK)
		return false;

	for (GPUIndex = 0; GPUIndex < GPUCount; GPUIndex++)
	{
		if (NvAPI_GPU_GetActiveOutputs(GPUHandle[GPUIndex], &OutputMask) != NVAPI_OK)
			continue;

		for (OutputIndex = 0; OutputIndex < NVAPI_MAX_HEADS_PER_GPU; OutputIndex++)
		{
			OutputID = 1 << OutputIndex;

			if (OutputMask & OutputID)
			{
				std::memset(&DisplayEDID, 0, sizeof DisplayEDID);
				DisplayEDID.Version = NV_EDID_VER3;

				if (NvAPI_GPU_GetEDID(GPUHandle[GPUIndex], OutputID, &DisplayEDID) != NVAPI_OK)
					continue;

				EDIDSize = MAX_EDID_BLOCKS * 128;

				if (EDIDSize > DisplayEDID.EDIDSize)
					EDIDSize = DisplayEDID.EDIDSize;

				DataSize = EDIDSize;

				if (DataSize > NV_EDID_DATA_SIZE)
					DataSize = NV_EDID_DATA_SIZE;

				std::memset(NewDisplayEDID, 0, MAX_EDID_BLOCKS * 128);
				std::memcpy(NewDisplayEDID, DisplayEDID.EDIDData, DataSize);

				for (Offset = 256; Offset < EDIDSize; Offset += 256)
				{
					std::memset(&DisplayEDID, 0, sizeof DisplayEDID);
					DisplayEDID.Version = NV_EDID_VER3;
					DisplayEDID.Offset = Offset;

					if (NvAPI_GPU_GetEDID(GPUHandle[GPUIndex], OutputID, &DisplayEDID) != NVAPI_OK)
						break;

					DataSize = EDIDSize - Offset;

					if (DataSize > NV_EDID_DATA_SIZE)
						DataSize = NV_EDID_DATA_SIZE;

					std::memcpy(&NewDisplayEDID[Offset], DisplayEDID.EDIDData, DataSize);
				}

				EDIDList.Add(NewDisplayEDID);
				Status = true;
			}
		}
	}

	NvAPI_Unload();
	FreeLibrary(Library);
	return Status;
}
//---------------------------------------------------------------------------
