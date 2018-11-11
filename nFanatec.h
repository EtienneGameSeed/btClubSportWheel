#ifndef _FANATEC_
#define _FANATEC_

//---------------------------------------------------------------------
//------------------------- Credits -----------------------------------
//---------------------------------------------------------------------
//	Firstly thanks To Mike and Darknao ;)
//	Created by Etienne Saint-Paul
//  Based on code from Mike and Darknao's firmware.
//	You can find Darknao's firmware here : https ://github.com/darknao/btClubSportWheel (And you can donate at the end of page).
//---------------------------------------------------------------------
//---------------------------------------------------------------------

#include "cDigitalPin.h"
#include "cDebouncer.h"
#include "cModule.h"

// Protocols
#define NO_WHEEL		0
#define CSW_PROTOCOL	0xA5
#define CSL_PROTOCOL	0xC0		// Todo : check this
#define MCL_PROTOCOL	0x4A		// I think this is bullshit, there's only 2 protocols... The McLaren wheel I have uses the CSW protocol

// Wheel types
#define NO_RIM		0
#define BMW_RIM		1
#define FORMULA_RIM 2
#define PORSCHE_RIM 3
#define UNIHUB		4
#define XBOXHUB		6
#define CSLP1XBOX	7
#define CSLP1PS4	8
#define MCLGT3		9

#define AM_BITE_POINT			1
#define AM_CLUTCH_HANDBRAKE		2
#define AM_BRAKE_THROTTLE		3
#define AM_ANALOG_AXES			4

#define NB_FW_VERSION	101
#define NUM_FANATEC_DB	48

class cFanatecIn
{
public:

	u8 mProtocol;
	u8 mWheelType;
	u8 mButtons[3];		// 2
	s8 mAxisX;			// 5
	s8 mAxisY;			// 6
	s8 mEncoder;		// 7
	u8 mBtnHub[2];		// 8
	u8 mBtnPS[2];		// 10
	u8 mSendId;			// 12

	u8 mUnused0;		// 13
	u8 mModeRotary;		// 14
	u8 mLRRotary;		// 15

	u8 mUnused[15];		// 16
	u8 mFWver;			// 31
	u8 mCrc;			// 32
}__attribute__((__packed__));

class cHIDBufferIn
{
public:
	void ClearAllAxis()
	{
		ZeroMem(&mAxisX, 12);
		mAxisX = 0x7fff;
		mAxisY = 0x7fff;
	}

	u8 mButtons[11];	// 0
	s16 mAxisX;			// 11
	s16 mAxisY;			// 13
	u16 mAxisZ;			// 15
	u16 mAxisRx;		// 17
	u16 mAxisRy;		// 19
	u16 mAxisRz;		// 21
	s8 mHatSwitch;		// 23
	u8 pad[5];			// 24
	u8 mWheelType;		// 29
}__attribute__((__packed__));

class cFanatecOut
{
public:
	cFanatecOut() { Clear(); }
	void Clear();
	void ClearDisp();
	void InitFromHIDData(const u8 *data);
	void SetNumber(s16 value);

	u8 mHeader;
	u8 mWheelType;
	u8 mDisp[3];
	u16 mLeds;
	u8  mRumble[2];

	u8 nothing[23];
	u8 mCrc;
}__attribute__((__packed__));

class nFanatec : public cModule
{
public:
	nFanatec(cModule *parent,u8 cs_pin,u8 debounce_time) :
		cModule(parent,0x80,DATA_TYPE_BUFFER,DATA_TYPE_BUFFER),
		mCS(cs_pin),
		mDebouncer(NUM_FANATEC_DB,8),
		mBuffer(&mWheelIn.mButtons[0],32),//sizeof(cFanatecIn) - 2),				// The buffer is only used as an interface, no data is allocated
		mRotaryPulseDuration(debounce_time)
	{
	}

	virtual u8 Command(eCommand cmd,u8 *param = NULL,char **result = NULL)
	{
		switch (cmd)
		{
		case CMD_GET_NAME: *result = nb_name("Fanatec"); return(0);
		case CMD_INIT:begin(); break;
		default:break;
		}
		return(cModule::Command(cmd,param,result));
	}

	virtual void Update();

	void begin();

	virtual void SetInput(u8 index, const u8 *data)				{ mWheelOut.InitFromHIDData(GetBuffer(data).Data()); }

	virtual u8 *GetOutput(u8 index)								{ return((u8*)&mBuffer); }

	cDigitalOutput mCS;
	cHIDBufferIn mWheelIn;
	cFanatecOut mWheelOut;
	cGroupDebouncer mDebouncer;
	cBuffer mBuffer;
	u32 mRotaryOnTime;
	u8 mRotaryPulseDuration;
	s8 mRotary;
	u8 mAnalogMode;
	u8 mSettingBitePoint;
	u8 mBitePoint;
};

#endif //_FANATEC_

