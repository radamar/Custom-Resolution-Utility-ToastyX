//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AddDIDDataClass.h"
//---------------------------------------------------------------------------
const int AddDIDDataClass::MinType = 0;
const int AddDIDDataClass::MaxType = 1;

const int AddDIDDataClass::MinSize[] = {3, 25};
//---------------------------------------------------------------------------
AddDIDDataClass::AddDIDDataClass()
{
	MaxSize = 0;
	Type = 0;
}
//---------------------------------------------------------------------------
bool AddDIDDataClass::SetMaxSize(int NewMaxSize)
{
	MaxSize = NewMaxSize;
	return true;
}
//---------------------------------------------------------------------------
bool AddDIDDataClass::TypePossible(int Type)
{
	if (Type < MinType || Type > MaxType)
		return false;

	if (MinSize[Type] > MaxSize)
		return false;

	return true;
}
//---------------------------------------------------------------------------
int AddDIDDataClass::GetType()
{
	return Type;
}
//---------------------------------------------------------------------------
bool AddDIDDataClass::SetType(int Value)
{
	Type = Value;
	return true;
}
//---------------------------------------------------------------------------
bool AddDIDDataClass::IsType(int Value)
{
	return Type == Value;
}
//---------------------------------------------------------------------------
bool AddDIDDataClass::IsValid()
{
	return TypePossible(Type);
}
//---------------------------------------------------------------------------
