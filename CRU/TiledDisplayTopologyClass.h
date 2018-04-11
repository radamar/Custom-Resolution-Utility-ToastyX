//---------------------------------------------------------------------------
#ifndef TiledDisplayTopologyClassH
#define TiledDisplayTopologyClassH
//---------------------------------------------------------------------------
#include "ItemClass.h"
//---------------------------------------------------------------------------
class TiledDisplayTopologyClass : public ItemClass
{
private:
	static const int MinPhysicalEnclosures;
	static const int MaxPhysicalEnclosures;
	static const int MinSingleTileBehavior;
	static const int MaxSingleTileBehavior;
	static const int MinMultipleTileBehavior;
	static const int MaxMultipleTileBehavior;
	static const int MinHTiles;
	static const int MaxHTiles;
	static const int MinVTiles;
	static const int MaxVTiles;
	static const int MinHLocation;
	static const int MaxHLocation;
	static const int MinVLocation;
	static const int MaxVLocation;
	static const int MinHSize;
	static const int MaxHSize;
	static const int MinVSize;
	static const int MaxVSize;
	static const int MinPixelMultiplier;
	static const int MaxPixelMultiplier;
	static const int MinTopBezelSize;
	static const int MaxTopBezelSize;
	static const int MinBottomBezelSize;
	static const int MaxBottomBezelSize;
	static const int MinRightBezelSize;
	static const int MaxRightBezelSize;
	static const int MinLeftBezelSize;
	static const int MaxLeftBezelSize;
	static const long long MinSerialID;
	static const long long MaxSerialID;

	int PhysicalEnclosures;
	int SingleTileBehavior;
	int MultipleTileBehavior;
	int HTiles;
	int VTiles;
	int HLocation;
	int VLocation;
	int HSize;
	int VSize;
	int PixelMultiplier;
	int TopBezelSize;
	int BottomBezelSize;
	int RightBezelSize;
	int LeftBezelSize;
	char ProductID[8];
	char ResetID[8];
	long long SerialID;

public:
	TiledDisplayTopologyClass();
	bool Read(const unsigned char *, int);
	bool ReadProductID(const unsigned char *);
	bool ReadSerialID(const unsigned char *);
	bool Write(unsigned char *, int);
	bool WriteProductID(unsigned char *);
	bool WriteSerialID(unsigned char *);
	int GetPhysicalEnclosures();
	bool SetPhysicalEnclosures(int);
	int GetSingleTileBehavior();
	bool SetSingleTileBehavior(int);
	int GetMultipleTileBehavior();
	bool SetMultipleTileBehavior(int);
	int GetHTiles();
	bool SetHTiles(int);
	int GetVTiles();
	bool SetVTiles(int);
	int GetHLocation();
	bool SetHLocation(int);
	int GetVLocation();
	bool SetVLocation(int);
	int GetHSize();
	bool SetHSize(int);
	int GetVSize();
	bool SetVSize(int);
	int GetPixelMultiplier();
	bool SetPixelMultiplier(int);
	int GetTopBezelSize();
	bool SetTopBezelSize(int);
	int GetBottomBezelSize();
	bool SetBottomBezelSize(int);
	int GetRightBezelSize();
	bool SetRightBezelSize(int);
	int GetLeftBezelSize();
	bool SetLeftBezelSize(int);
	bool GetProductID(char *, int);
	bool SetProductID(const char *);
	bool SetResetID(const char *);
	bool ResetProductIDPossible();
	bool ResetProductID();
	long long GetSerialID();
	bool SetSerialID(long long);
	bool IsValid();
	bool IsValidPhysicalEnclosures();
	bool IsValidSingleTileBehavior();
	bool IsValidMultipleTileBehavior();
	bool IsValidHTiles();
	bool IsValidVTiles();
	bool IsValidHLocation();
	bool IsValidVLocation();
	bool IsValidHSize();
	bool IsValidVSize();
	bool IsValidPixelMultiplier();
	bool IsValidTopBezelSize();
	bool IsValidBottomBezelSize();
	bool IsValidRightBezelSize();
	bool IsValidLeftBezelSize();
	bool IsValidProductID();
	bool IsValidSerialID();
};
//---------------------------------------------------------------------------
#endif
