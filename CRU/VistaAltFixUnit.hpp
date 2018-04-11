// Borland C++ Builder
// Copyright (c) 1995, 2005 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Vistaaltfixunit.pas' rev: 10.00

#ifndef VistaaltfixunitHPP
#define VistaaltfixunitHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Vistaaltfixunit
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVistaAltFix;
class PASCALIMPLEMENTATION TVistaAltFix : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	bool FInstalled;
	bool __fastcall VistaWithTheme(void);
	
public:
	__fastcall virtual TVistaAltFix(Classes::TComponent* AOwner);
	__fastcall virtual ~TVistaAltFix(void);
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Vistaaltfixunit */
using namespace Vistaaltfixunit;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vistaaltfixunit
