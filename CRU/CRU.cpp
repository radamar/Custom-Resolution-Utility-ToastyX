//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("AddCEADataFormClass.cpp", AddCEADataForm);
USEFORM("AddDIDDataFormClass.cpp", AddDIDDataForm);
USEFORM("AudioFormatFormClass.cpp", AudioFormatForm);
USEFORM("AudioFormatListFormClass.cpp", AudioFormatListForm);
USEFORM("ColorimetryFormClass.cpp", ColorimetryForm);
USEFORM("CommonFormClass.cpp", CommonForm);
USEFORM("DetailedResolutionFormClass.cpp", DetailedResolutionForm);
USEFORM("DIDDetailedResolutionListFormClass.cpp", DIDDetailedResolutionListForm);
USEFORM("DisplayFormClass.cpp", DisplayForm);
USEFORM("ExtensionBlockFormClass.cpp", ExtensionBlockForm);
USEFORM("FreeSyncRangeFormClass.cpp", FreeSyncRangeForm);
USEFORM("HDMIResolutionFormClass.cpp", HDMIResolutionForm);
USEFORM("HDMISupportFormClass.cpp", HDMISupportForm);
USEFORM("HDMI2SupportFormClass.cpp", HDMI2SupportForm);
USEFORM("PropertiesFormClass.cpp", PropertiesForm);
USEFORM("SpeakerSetupFormClass.cpp", SpeakerSetupForm);
USEFORM("StandardResolutionFormClass.cpp", StandardResolutionForm);
USEFORM("TiledDisplayTopologyFormClass.cpp", TiledDisplayTopologyForm);
USEFORM("TVResolutionFormClass.cpp", TVResolutionForm);
USEFORM("TVResolutionListFormClass.cpp", TVResolutionListForm);
USEFORM("VideoCapabilityFormClass.cpp", VideoCapabilityForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->Title = "Custom Resolution Utility";
		Application->CreateForm(__classid(TDisplayForm), &DisplayForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
