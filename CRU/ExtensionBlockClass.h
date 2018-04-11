//---------------------------------------------------------------------------
#ifndef ExtensionBlockClassH
#define ExtensionBlockClassH
//---------------------------------------------------------------------------
#include "ItemClass.h"
#include "ColorFormatListClass.h"
#include "DetailedResolutionListClass.h"
#include "CEADataListClass.h"
#include "StandardResolutionListClass.h"
#include "DIDDataListClass.h"
//---------------------------------------------------------------------------
enum
{
	CEA_861,
	VTB_EXT,
	DISPLAYID_EXT,
	DEFAULT_EXT,
};
//---------------------------------------------------------------------------
class ExtensionBlockClass : public ItemClass
{
private:
	static const int MinType;
	static const int MaxType;
	static const char *TypeText[];
	static const int TypeCode[];

	static unsigned char *CopyExtensionData;
	unsigned char *OldExtensionData;
	unsigned char *NewExtensionData;

	int ExtensionType;
	int ExtensionCode;

	ColorFormatListClass *ColorFormatList;
	DetailedResolutionListClass *DetailedResolutionList;
	CEADataListClass *CEADataList;
	StandardResolutionListClass *StandardResolutionList;
	DIDDataListClass *DIDDataList;

public:
	ExtensionBlockClass();
	void Copy(const ExtensionBlockClass &);
	void Delete();
	ExtensionBlockClass(const ExtensionBlockClass &);
	ExtensionBlockClass &operator=(const ExtensionBlockClass &);
	~ExtensionBlockClass();
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	bool GetText(char *, int);
	bool GetTypeText(int, char *, int);
	int GetType();
	bool SetType(int);
	bool ReadType();

	bool ExtensionInit();
	bool ExtensionRead();
	bool ExtensionWrite();
	bool ExtensionCopyPossible();
	bool ExtensionCopy();
	bool ExtensionPastePossible();
	bool ExtensionPaste();
	bool ExtensionResetPossible();
	bool ExtensionReset();
	int ExtensionGetBytesLeft();

	bool ColorFormatsInit();
	bool ColorFormatsRead();
	bool ColorFormatsWrite();
	ColorFormatListClass *ColorFormats();

	bool DetailedInit();
	bool DetailedRead();
	bool DetailedWrite();
	bool DetailedGetExtensionText(int, char *, int);
	DetailedResolutionListClass *DetailedResolutions();

	bool CEADataInit();
	bool CEADataRead();
	bool CEADataWrite();
	CEADataListClass *CEAData();

	bool StandardInit();
	bool StandardRead();
	bool StandardWrite();
	StandardResolutionListClass *StandardResolutions();

	bool DIDDataInit();
	bool DIDDataRead();
	bool DIDDataWrite();
	bool DIDDataChecksum(int);
	DIDDataListClass *DIDData();

	bool IsValidType();
	bool IsSupported();
};
//---------------------------------------------------------------------------
#endif
