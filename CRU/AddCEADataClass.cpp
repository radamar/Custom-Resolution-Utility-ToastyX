//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AddCEADataClass.h"
//---------------------------------------------------------------------------
const int AddCEADataClass::MinType = 0;
const int AddCEADataClass::MaxType = 7;

const int AddCEADataClass::MinSize[] = {1, 1, 4, 6, 8, 9, 4, 3};
//---------------------------------------------------------------------------
AddCEADataClass::AddCEADataClass()
{
	MaxSize = 0;
	Type = 0;
}
//---------------------------------------------------------------------------
bool AddCEADataClass::SetMaxSize(int NewMaxSize)
{
	MaxSize = NewMaxSize;
	return true;
}
//---------------------------------------------------------------------------
bool AddCEADataClass::TypePossible(int Type)
{
	if (Type < MinType || Type > MaxType)
		return false;

	if (MinSize[Type] > MaxSize)
		return false;

	return true;
}
//---------------------------------------------------------------------------
int AddCEADataClass::GetType()
{
	return Type;
}
//---------------------------------------------------------------------------
bool AddCEADataClass::SetType(int Value)
{
	Type = Value;
	return true;
}
//---------------------------------------------------------------------------
bool AddCEADataClass::IsType(int Value)
{
	return Type == Value;
}
//---------------------------------------------------------------------------
bool AddCEADataClass::IsValid()
{
	return TypePossible(Type);
}
//---------------------------------------------------------------------------
