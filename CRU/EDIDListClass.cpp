//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "EDIDListClass.h"
#include <cstring>
//---------------------------------------------------------------------------
EDIDListClass::EDIDListClass()
{
	Count = 0;
}
//---------------------------------------------------------------------------
void EDIDListClass::Copy(const EDIDListClass &Source)
{
	int Index;

	Items = Source.Items;
	Count = Source.Count;

	for (Index = 0; Index < Count; Index++)
	{
		Items[Index] = new unsigned char[MAX_EDID_BLOCKS * 128];
		std::memcpy(Items[Index], Source.Items[Index], MAX_EDID_BLOCKS * 128);
	}
}
//---------------------------------------------------------------------------
void EDIDListClass::Delete()
{
	int Index;

	for (Index = 0; Index < Count; Index++)
		delete[] Items[Index];

	Items.clear();
	Count = 0;
}
//---------------------------------------------------------------------------
EDIDListClass::EDIDListClass(const EDIDListClass &Source)
{
	Copy(Source);
}
//---------------------------------------------------------------------------
EDIDListClass &EDIDListClass::operator=(const EDIDListClass &Source)
{
	Delete();
	Copy(Source);
	return *this;
}
//---------------------------------------------------------------------------
EDIDListClass::~EDIDListClass()
{
	Delete();
}
//---------------------------------------------------------------------------
bool EDIDListClass::Add(unsigned char *Item)
{
	unsigned char *NewItem;

	NewItem = new unsigned char[MAX_EDID_BLOCKS * 128];
	std::memcpy(NewItem, Item, MAX_EDID_BLOCKS * 128);
	Items.push_back(NewItem);
	Count++;
	return true;
}
//---------------------------------------------------------------------------
bool EDIDListClass::Delete(int Index)
{
	if (Index < 0 || Index >= Count)
		return false;

	delete[] Items[Index];
	Items.erase(&Items[Index]);
	Count--;
	return true;
}
//---------------------------------------------------------------------------
int EDIDListClass::GetCount()
{
	return Count;
}
//---------------------------------------------------------------------------
bool EDIDListClass::MatchFullActive(unsigned char *ActiveData)
{
	int Index;

	for (Index = 0; Index < Count; Index++)
	{
		if (std::memcmp(ActiveData, Items[Index], MAX_EDID_BLOCKS * 128) == 0)
		{
			Delete(Index);
			return true;
		}
	}

	return false;
}
//---------------------------------------------------------------------------
bool EDIDListClass::MatchFullOverride(unsigned char *ActiveData, unsigned char *OverrideData)
{
	int Index;

	for (Index = 0; Index < Count; Index++)
	{
		if (std::memcmp(ActiveData, Items[Index], 128) == 0)
		{
			if (std::memcmp(&OverrideData[128], &Items[Index][128], MAX_EDID_EXTENSION_BLOCKS * 128) == 0)
			{
				std::memcpy(&ActiveData[128], &Items[Index][128], MAX_EDID_EXTENSION_BLOCKS * 128);
				Delete(Index);
				return true;
			}
		}
	}

	return false;
}
//---------------------------------------------------------------------------
bool EDIDListClass::MatchPartialOverride(unsigned char *ActiveData, unsigned char *OverrideData)
{
	int Index;
	int Block;
	bool Matched;

	for (Index = 0; Index < Count; Index++)
	{
		if (std::memcmp(ActiveData, Items[Index], 128) == 0)
		{
			Matched = false;

			for (Block = 1; Block < MAX_EDID_BLOCKS; Block++)
			{
				if (OverrideData[Block * 128] != 0 && Items[Index][Block * 128] != 0)
				{
					if (std::memcmp(&OverrideData[Block * 128], &Items[Index][Block * 128], 128) != 0)
					{
						Matched = false;
						break;
					}

					Matched = true;
				}
			}

			if (Matched)
			{
				std::memcpy(&ActiveData[128], &Items[Index][128], MAX_EDID_EXTENSION_BLOCKS * 128);
				Delete(Index);
				return true;
			}
		}
	}

	return false;
}
//---------------------------------------------------------------------------
bool EDIDListClass::MatchFirstActive(unsigned char *ActiveData)
{
	int Index;

	for (Index = 0; Index < Count; Index++)
	{
		if (std::memcmp(ActiveData, Items[Index], 128) == 0)
		{
			std::memcpy(&ActiveData[128], &Items[Index][128], MAX_EDID_EXTENSION_BLOCKS * 128);
			Delete(Index);
			return true;
		}
	}

	return false;
}
//---------------------------------------------------------------------------
