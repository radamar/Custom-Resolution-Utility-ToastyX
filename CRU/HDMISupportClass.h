//---------------------------------------------------------------------------
#ifndef HDMISupportClassH
#define HDMISupportClassH
//---------------------------------------------------------------------------
#include "ItemClass.h"
#include "HDMIResolutionListClass.h"
//---------------------------------------------------------------------------
class HDMISupportClass : public ItemClass
{
private:
	static const int MinTMDSClock;
	static const int MaxTMDSClock;
	static const int ModTMDSClock;
	static const int MinContentType;
	static const int MaxContentType;
	static const int MinLatency;
	static const int MaxLatency;
	static const int ModLatency;

	int MaxDataSize;
	int MaxMaxDataSize;

	char *PhysicalAddress;
	bool DeepColorYCbCr444;
	bool DeepColor30bit;
	bool DeepColor36bit;
	bool DeepColor48bit;
	bool SupportsAI;
	bool DualLinkDVI;
	bool OverrideTMDSClock;
	int TMDSClock;
	bool ContentType[4];
	bool IncludeLatency;
	bool VideoSupported;
	int VideoLatency;
	bool AudioSupported;
	int AudioLatency;
	bool IncludeInterlacedLatency;
	bool InterlacedVideoSupported;
	int InterlacedVideoLatency;
	bool InterlacedAudioSupported;
	int InterlacedAudioLatency;
	int OtherFlags;
	HDMIResolutionListClass *HDMIResolutionList;
	int HDMI_3D_Length;
	int OtherSize;
	int MaxOtherSize;
	unsigned char *OtherData;

public:
	HDMISupportClass(int Bytes = 31);
	void Copy(const HDMISupportClass &);
	void Delete();
	HDMISupportClass(const HDMISupportClass &);
	HDMISupportClass &operator=(const HDMISupportClass &);
	~HDMISupportClass();
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	bool SetMaxSize(int);
	bool ReadPhysicalAddress(const unsigned char *);
	bool WritePhysicalAddress(unsigned char *);
	bool GetPhysicalAddressText(char *, int);
	bool SetPhysicalAddressText(const char *);
	bool ExtensionPossible();
	bool GetDeepColorYCbCr444();
	bool SetDeepColorYCbCr444(bool);
	bool GetDeepColor30bit();
	bool SetDeepColor30bit(bool);
	bool GetDeepColor36bit();
	bool SetDeepColor36bit(bool);
	bool GetDeepColor48bit();
	bool SetDeepColor48bit(bool);
	bool GetSupportsAI();
	bool SetSupportsAI(bool);
	bool GetDualLinkDVI();
	bool SetDualLinkDVI(bool);
	bool TMDSClockPossible();
	bool GetOverrideTMDSClock();
	bool SetOverrideTMDSClock(bool);
	int GetTMDSClock();
	bool SetTMDSClock(int);
	bool ContentTypesPossible();
	bool GetContentType(int);
	bool SetContentType(int, bool);
	bool IncludeLatencyPossible();
	bool GetIncludeLatency();
	bool SetIncludeLatency(bool);
	bool GetVideoSupported();
	bool SetVideoSupported(bool);
	int GetVideoLatency();
	bool SetVideoLatency(int);
	bool GetAudioSupported();
	bool SetAudioSupported(bool);
	int GetAudioLatency();
	bool SetAudioLatency(int);
	bool IncludeInterlacedLatencyPossible();
	bool GetIncludeInterlacedLatency();
	bool SetIncludeInterlacedLatency(bool);
	bool GetInterlacedVideoSupported();
	bool SetInterlacedVideoSupported(bool);
	int GetInterlacedVideoLatency();
	bool SetInterlacedVideoLatency(int);
	bool GetInterlacedAudioSupported();
	bool SetInterlacedAudioSupported(bool);
	int GetInterlacedAudioLatency();
	bool SetInterlacedAudioLatency(int);
	HDMIResolutionListClass *Resolutions();
	bool IsValid();
	bool IsValidPhysicalAddress();
	bool IsValidTMDSClock();
	bool IsValidLatency();
	bool IsValidVideoLatency();
	bool IsValidAudioLatency();
	bool IsValidInterlacedVideoLatency();
	bool IsValidInterlacedAudioLatency();
};
//---------------------------------------------------------------------------
#endif
