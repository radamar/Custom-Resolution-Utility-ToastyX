//---------------------------------------------------------------------------
#ifndef DIDDataListClassH
#define DIDDataListClassH
//---------------------------------------------------------------------------
#include "ListClass.h"
//---------------------------------------------------------------------------
enum
{
	DID_INVALID,
	DID_PRODUCT_IDENTIFICATION,
	DID_DISPLAY_PARAMETERS,
	DID_COLOR_CHARACTERISTICS,
	DID_DETAILED_RESOLUTIONS,
	DID_TYPE_2_RESOLUTIONS,
	DID_TYPE_3_RESOLUTIONS,
	DID_TYPE_4_RESOLUTIONS,
	DID_VESA_RESOLUTIONS,
	DID_CEA_RESOLUTIONS,
	DID_RANGE_LIMITS,
	DID_SERIAL_NUMBER,
	DID_ASCII_STRING,
	DID_DISPLAY_DEVICE_DATA,
	DID_INTERFACE_POWER_SEQUENCING,
	DID_TRANSFER_CHARACTERISTICS,
	DID_DISPLAY_INTERFACE,
	DID_STEREO_DISPLAY_INTERFACE,
	DID_TYPE_5_RESOLUTIONS,
	DID_TILED_DISPLAY_TOPOLOGY,
	DID_TYPE_6_RESOLUTIONS,
	DID_VENDOR_SPECIFIC_DATA,
	DID_OTHER,
};
//---------------------------------------------------------------------------
class DIDDataListClass : public ListClass
{
private:
	static const char *SlotTypeText[];

public:
	DIDDataListClass(int);
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	int GetSlotType(int);
	int GetSlotSize(int);
	bool UpdateSize();
	bool SetMaxCount(int);
	bool SetMaxSize(int);
	bool GetSlotTypeText(int, char *, int);
	bool GetSlotInfoText(int, char *, int);
	bool AddPossible();
	bool EditPossible(int);
};
//---------------------------------------------------------------------------
#endif
