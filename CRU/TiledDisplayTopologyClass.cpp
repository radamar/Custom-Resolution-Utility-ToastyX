//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TiledDisplayTopologyClass.h"
#include <cstdio>
#include <cstring>
//---------------------------------------------------------------------------
const int TiledDisplayTopologyClass::MinPhysicalEnclosures = 0;
const int TiledDisplayTopologyClass::MaxPhysicalEnclosures = 1;
const int TiledDisplayTopologyClass::MinSingleTileBehavior = 0;
const int TiledDisplayTopologyClass::MaxSingleTileBehavior = 3;
const int TiledDisplayTopologyClass::MinMultipleTileBehavior = 0;
const int TiledDisplayTopologyClass::MaxMultipleTileBehavior = 1;
const int TiledDisplayTopologyClass::MinHTiles = 1;
const int TiledDisplayTopologyClass::MaxHTiles = 64;
const int TiledDisplayTopologyClass::MinVTiles = 1;
const int TiledDisplayTopologyClass::MaxVTiles = 64;
const int TiledDisplayTopologyClass::MinHLocation = 1;
const int TiledDisplayTopologyClass::MaxHLocation = 64;
const int TiledDisplayTopologyClass::MinVLocation = 1;
const int TiledDisplayTopologyClass::MaxVLocation = 64;
const int TiledDisplayTopologyClass::MinHSize = 1;
const int TiledDisplayTopologyClass::MaxHSize = 65536;
const int TiledDisplayTopologyClass::MinVSize = 1;
const int TiledDisplayTopologyClass::MaxVSize = 65536;
const int TiledDisplayTopologyClass::MinPixelMultiplier = 0;
const int TiledDisplayTopologyClass::MaxPixelMultiplier = 255;
const int TiledDisplayTopologyClass::MinTopBezelSize = 0;
const int TiledDisplayTopologyClass::MaxTopBezelSize = 255;
const int TiledDisplayTopologyClass::MinBottomBezelSize = 0;
const int TiledDisplayTopologyClass::MaxBottomBezelSize = 255;
const int TiledDisplayTopologyClass::MinRightBezelSize = 0;
const int TiledDisplayTopologyClass::MaxRightBezelSize = 255;
const int TiledDisplayTopologyClass::MinLeftBezelSize = 0;
const int TiledDisplayTopologyClass::MaxLeftBezelSize = 255;
const long long TiledDisplayTopologyClass::MinSerialID = 0;
const long long TiledDisplayTopologyClass::MaxSerialID = 4294967295LL;
//---------------------------------------------------------------------------
TiledDisplayTopologyClass::TiledDisplayTopologyClass()
{
	PhysicalEnclosures = 1;
	SingleTileBehavior = 1;
	MultipleTileBehavior = 1;
	HTiles = 1;
	VTiles = 1;
	HLocation = 1;
	VLocation = 1;
	HSize = BLANK;
	VSize = BLANK;
	PixelMultiplier = 0;
	TopBezelSize = 0;
	BottomBezelSize = 0;
	RightBezelSize = 0;
	LeftBezelSize = 0;
	ProductID[0] = 0;
	ResetID[0] = 0;
	SerialID = BLANK;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::Read(const unsigned char *Data, int MaxSize)
{
	int Type;
	int Size;

	if (!Data)
		return false;

	if (MaxSize < 25)
		return false;

	Type = Data[0];
	Size = Data[2];

	if (Type != 18)
		return false;

	if (Size < 22)
		return false;

	PhysicalEnclosures = (Data[3] >> 7) & 1;
	SingleTileBehavior = Data[3] & 7;
	MultipleTileBehavior = (Data[3] >> 3) & 3;

	if (SingleTileBehavior > 3)
		SingleTileBehavior = 0;

	if (MultipleTileBehavior > 1)
		MultipleTileBehavior = 0;

	HTiles = ((Data[4] >> 4) & 15) + ((Data[6] >> 2) & 48) + 1;
	VTiles = (Data[4] & 15) + (Data[6] & 48) + 1;
	HLocation = ((Data[5] >> 4) & 15) + ((Data[6] << 2) & 48) + 1;
	VLocation = (Data[5] & 15) + ((Data[6] << 4) & 48) + 1;
	HSize = (Data[8] << 8) + Data[7] + 1;
	VSize = (Data[10] << 8) + Data[9] + 1;
	PixelMultiplier = Data[11];
	TopBezelSize = Data[12];
	BottomBezelSize = Data[13];
	RightBezelSize = Data[14];
	LeftBezelSize = Data[15];
	ReadProductID(Data);
	ReadSerialID(Data);
	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::ReadProductID(const unsigned char *Data)
{
	ProductID[0] = Data[16];
	ProductID[1] = Data[17];
	ProductID[2] = Data[18];
	ProductID[3] = Data[20] >> 4;
	ProductID[4] = Data[20] & 15;
	ProductID[5] = Data[19] >> 4;
	ProductID[6] = Data[19] & 15;
	ProductID[3] += ProductID[3] < 10 ? 48 : 55;
	ProductID[4] += ProductID[4] < 10 ? 48 : 55;
	ProductID[5] += ProductID[5] < 10 ? 48 : 55;
	ProductID[6] += ProductID[6] < 10 ? 48 : 55;
	ProductID[7] = 0;
	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::ReadSerialID(const unsigned char *Data)
{
	SerialID = Data[21];
	SerialID += Data[22] << 8;
	SerialID += Data[23] << 16;
	SerialID += (long long)Data[24] << 24;
	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (MaxSize < 25)
		return false;

	std::memset(Data, 0, MaxSize);
	Data[0] = 18;
	Data[2] = 22;
	Data[3] = ((PhysicalEnclosures & 1) << 7) + (SingleTileBehavior & 7) + ((MultipleTileBehavior & 3) << 3) + (PixelMultiplier ? 64 : 0);
	Data[4] = ((--HTiles & 15) << 4) + (--VTiles & 15);
	Data[5] = ((--HLocation & 15) << 4) + (--VLocation & 15);
	Data[6] = ((HTiles++ & 48) << 2) + (VTiles++ & 48) + ((HLocation++ & 48) >> 2) + ((VLocation++ & 48) >> 4);
	Data[7] = --HSize & 255;
	Data[8] = (HSize++ >> 8) & 255;
	Data[9] = --VSize & 255;
	Data[10] = (VSize++ >> 8) & 255;
	Data[11] = PixelMultiplier & 255;
	Data[12] = TopBezelSize & 255;
	Data[13] = BottomBezelSize & 255;
	Data[14] = RightBezelSize & 255;
	Data[15] = LeftBezelSize & 255;
	WriteProductID(Data);
	WriteSerialID(Data);
	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::WriteProductID(unsigned char *Data)
{
	if (!IsValidProductID())
		return false;

	Data[16] = ProductID[0];
	Data[17] = ProductID[1];
	Data[18] = ProductID[2];
	Data[19] = 0;
	Data[19] |= std::isdigit(ProductID[5]) ? ProductID[5] << 4 : (ProductID[5] - 7) << 4;
	Data[19] |= std::isdigit(ProductID[6]) ? ProductID[6] & 15 : (ProductID[6] - 7) & 15;
	Data[20] = 0;
	Data[20] |= std::isdigit(ProductID[3]) ? ProductID[3] << 4 : (ProductID[3] - 7) << 4;
	Data[20] |= std::isdigit(ProductID[4]) ? ProductID[4] & 15 : (ProductID[4] - 7) & 15;
	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::WriteSerialID(unsigned char *Data)
{
	if (!IsValidSerialID())
		return false;

	Data[21] = SerialID & 255;
	Data[22] = (SerialID >> 8) & 255;
	Data[23] = (SerialID >> 16) & 255;
	Data[24] = (SerialID >> 24) & 255;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetPhysicalEnclosures()
{
	return PhysicalEnclosures;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetPhysicalEnclosures(int Value)
{
	PhysicalEnclosures = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetSingleTileBehavior()
{
	return SingleTileBehavior;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetSingleTileBehavior(int Value)
{
	SingleTileBehavior = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetMultipleTileBehavior()
{
	return MultipleTileBehavior;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetMultipleTileBehavior(int Value)
{
	MultipleTileBehavior = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetHTiles()
{
	return HTiles;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetHTiles(int Value)
{
	HTiles = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetVTiles()
{
	return VTiles;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetVTiles(int Value)
{
	VTiles = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetHLocation()
{
	return HLocation;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetHLocation(int Value)
{
	HLocation = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetVLocation()
{
	return VLocation;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetVLocation(int Value)
{
	VLocation = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetHSize()
{
	return HSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetHSize(int Value)
{
	HSize = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetVSize()
{
	return VSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetVSize(int Value)
{
	VSize = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetPixelMultiplier()
{
	return PixelMultiplier;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetPixelMultiplier(int Value)
{
	PixelMultiplier = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetTopBezelSize()
{
	return TopBezelSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetTopBezelSize(int Value)
{
	TopBezelSize = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetBottomBezelSize()
{
	return BottomBezelSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetBottomBezelSize(int Value)
{
	BottomBezelSize = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetRightBezelSize()
{
	return RightBezelSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetRightBezelSize(int Value)
{
	RightBezelSize = Value;
	return true;
}
//---------------------------------------------------------------------------
int TiledDisplayTopologyClass::GetLeftBezelSize()
{
	return LeftBezelSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetLeftBezelSize(int Value)
{
	LeftBezelSize = Value;
	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::GetProductID(char *Text, int TextSize)
{
	std::snprintf(Text, TextSize, "%s", ProductID);
	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetProductID(const char *NewProductID)
{
	std::snprintf(ProductID, sizeof ProductID, "%s", NewProductID);
	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetResetID(const char *NewResetID)
{
	std::snprintf(ResetID, sizeof ResetID, "%s", NewResetID);
	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::ResetProductIDPossible()
{
	return std::strcmp(ProductID, ResetID) != 0;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::ResetProductID()
{
	std::snprintf(ProductID, sizeof ProductID, "%s", ResetID);
	return true;
}
//---------------------------------------------------------------------------
long long TiledDisplayTopologyClass::GetSerialID()
{
	return SerialID;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::SetSerialID(long long Value)
{
	SerialID = Value;
	return true;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValid()
{
	if (IsValidPhysicalEnclosures())
	if (IsValidSingleTileBehavior())
	if (IsValidMultipleTileBehavior())
	if (IsValidHTiles())
	if (IsValidVTiles())
	if (IsValidHLocation())
	if (IsValidVLocation())
	if (IsValidHSize())
	if (IsValidVSize())
	if (IsValidPixelMultiplier())
	if (IsValidTopBezelSize())
	if (IsValidBottomBezelSize())
	if (IsValidRightBezelSize())
	if (IsValidLeftBezelSize())
	if (IsValidProductID())
	if (IsValidSerialID())
		return true;

	return false;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidPhysicalEnclosures()
{
	return PhysicalEnclosures >= MinPhysicalEnclosures && PhysicalEnclosures <= MaxPhysicalEnclosures;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidSingleTileBehavior()
{
	return SingleTileBehavior >= MinSingleTileBehavior && SingleTileBehavior <= MaxSingleTileBehavior;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidMultipleTileBehavior()
{
	return MultipleTileBehavior >= MinMultipleTileBehavior && MultipleTileBehavior <= MaxMultipleTileBehavior;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidHTiles()
{
	return HTiles >= MinHTiles && HTiles <= MaxHTiles;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidVTiles()
{
	return VTiles >= MinVTiles && VTiles <= MaxVTiles;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidHLocation()
{
	return HLocation >= MinHLocation && HLocation <= MaxHLocation;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidVLocation()
{
	return VLocation >= MinVLocation && VLocation <= MaxVLocation;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidHSize()
{
	return HSize >= MinHSize && HSize <= MaxHSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidVSize()
{
	return VSize >= MinVSize && VSize <= MaxVSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidPixelMultiplier()
{
	return PixelMultiplier >= MinPixelMultiplier && PixelMultiplier <= MaxPixelMultiplier;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidTopBezelSize()
{
	return TopBezelSize >= MinTopBezelSize && TopBezelSize <= MaxTopBezelSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidBottomBezelSize()
{
	return BottomBezelSize >= MinBottomBezelSize && BottomBezelSize <= MaxBottomBezelSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidRightBezelSize()
{
	return RightBezelSize >= MinRightBezelSize && RightBezelSize <= MaxRightBezelSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidLeftBezelSize()
{
	return LeftBezelSize >= MinLeftBezelSize && LeftBezelSize <= MaxLeftBezelSize;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidProductID()
{
	if (std::strlen(ProductID) != 7)
		return false;

	if (isxdigit(ProductID[3]))
	if (isxdigit(ProductID[4]))
	if (isxdigit(ProductID[5]))
	if (isxdigit(ProductID[6]))
		return true;

	return false;
}
//---------------------------------------------------------------------------
bool TiledDisplayTopologyClass::IsValidSerialID()
{
	return SerialID >= MinSerialID && SerialID <= MaxSerialID;
}
//---------------------------------------------------------------------------
