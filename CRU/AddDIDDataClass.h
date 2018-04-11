//---------------------------------------------------------------------------
#ifndef AddDIDDataClassH
#define AddDIDDataClassH
//---------------------------------------------------------------------------
enum
{
	ADD_DID_DETAILED_RESOLUTIONS,
	ADD_DID_TILED_DISPLAY_TOPOLOGY,
};
//---------------------------------------------------------------------------
class AddDIDDataClass
{
private:
	static const int MinType;
	static const int MaxType;

	static const int MinSize[];

	int MaxSize;
	int Type;

public:
	AddDIDDataClass();
	bool SetMaxSize(int);
	bool TypePossible(int);
	int GetType();
	bool SetType(int);
	bool IsType(int);
	bool IsValid();
};
//---------------------------------------------------------------------------
#endif
