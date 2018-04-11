//---------------------------------------------------------------------------
#ifndef AddCEADataClassH
#define AddCEADataClassH
//---------------------------------------------------------------------------
enum
{
	ADD_CEA_VIDEO,
	ADD_CEA_AUDIO,
	ADD_CEA_SPEAKER_ALLOCATION,
	ADD_CEA_HDMI,
	ADD_CEA_HDMI2,
	ADD_CEA_FREESYNC,
	ADD_CEA_COLORIMETRY,
	ADD_CEA_VIDEO_CAPABILITY,
};
//---------------------------------------------------------------------------
class AddCEADataClass
{
private:
	static const int MinType;
	static const int MaxType;

	static const int MinSize[];

	int MaxSize;
	int Type;

public:
	AddCEADataClass();
	bool SetMaxSize(int);
	bool TypePossible(int);
	int GetType();
	bool SetType(int);
	bool IsType(int);
	bool IsValid();
};
//---------------------------------------------------------------------------
#endif
