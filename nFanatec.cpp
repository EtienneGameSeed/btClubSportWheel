#include "SPI.h"
#include "nFanatec.h"
#include "TM16XXFonts.h"

//#define DEBUG_RAW_VALUES
#define DEBUG_VALUES
//#define TEST_DISPLAY
//#define USE_CUSTOM_BITE_POINT_SETTINGS

#if defined(DEBUG_VALUES) || defined(DEBUG_RAW_VALUES) 
#define fana_print		Serial.print
#define fana_println	Serial.println
#else
#define fana_print		nb_print
#define fana_println	nb_println
#endif

//--------------------------------------------------------------------------------------------------------

SPISettings settingsA(12000000,MSBFIRST,SPI_MODE1);

void cFanatecOut::Clear()
{
	ClearDisp();
	mLeds = 0;
	mRumble[0] = 0;
	mRumble[1] = 0;
}

void cFanatecOut::ClearDisp()
{
	mHeader = 0xA5;
	u8 disp_val = (mWheelType == MCLGT3) ? 0xA : 0;
	mDisp[0] = disp_val;
	mDisp[1] = disp_val;
	mDisp[2] = disp_val;
}

PROGMEM const u8 crc8_table[256] =
{
	0,94,188,226,97,63,221,131,
	194,156,126,32,163,253,31,65,
	157,195,33,127,252,162,64,30,
	95,1,227,189,62,96,130,220,
	35,125,159,193,66,28,254,160,
	225,191,93,3,128,222,60,98,
	190,224,2,92,223,129,99,61,
	124,34,192,158,29,67,161,255,
	70,24,250,164,39,121,155,197,
	132,218,56,102,229,187,89,7,
	219,133,103,57,186,228,6,88,
	25,71,165,251,120,38,196,154,
	101,59,217,135,4,90,184,230,
	167,249,27,69,198,152,122,36,
	248,166,68,26,153,199,37,123,
	58,100,134,216,91,5,231,185,
	140,210,48,110,237,179,81,15,
	78,16,242,172,47,113,147,205,
	17,79,173,243,112,46,204,146,
	211,141,111,49,178,236,14,80,
	175,241,19,77,206,144,114,44,
	109,51,209,143,12,82,176,238,
	50,108,142,208,83,13,239,177,
	240,174,76,18,145,207,45,115,
	202,148,118,40,171,245,23,73,
	8,86,180,234,105,55,213,139,
	87,9,235,181,54,104,138,212,
	149,203,41,119,244,170,72,22,
	233,183,85,11,136,214,52,106,
	43,117,151,201,74,20,246,168,
	116,42,200,150,21,75,169,247,
	182,232,10,84,215,137,107,53
};

PROGMEM const char segsToAscii[]={32,0,39,0,44,0,49,0,95,0,0,0,0,0,106,
93,0,0,0,0,0,77,0,0,0,0,0,0,117,87,0,74,96,0,34,0,0,0,0,55,0,0,86,
0,0,0,0,0,40,82,0,0,0,0,0,78,76,67,0,0,0,71,85,48,45,0,0,0,0,0,123,
122,61,0,0,0,0,0,0,51,114,0,47,63,110,109,0,0,99,0,0,50,111,0,100,
64,0,0,0,42,92,0,52,81,0,75,0,0,0,36,89,57,125,70,0,80,104,107,72,65,84,69,0,101,98,54,35,56,};

u8 crc8(const u8* buf,u8 len)
{
	u8 crc = 0xff;
	while (len)
	{
		crc = pgm_read_byte_near(crc8_table + (*buf ^ crc));
		buf++;
		len--;
	}
	return crc;
}

u8 ConvertCharTo7Seg(u8 c)
{
	return(FONT_DEFAULT[constrain(c-32,0,126)]);
}

u8 Convert7SegToChar(u8 segs)
{
//	return(pgm_read_byte_near(&segsToAscii[segs]));
	u8 ascii = 0xA;

	switch (segs)
	{
		//case 0x40: ascii = 0x5B; break; // -
	case 0x39: ascii = 0x28; break; // [ (
	case 0x0F: ascii = 0x29; break; // ] )
	case 0x3F: ascii = 0x0; break; // 0
	case 0x06: ascii = 0x1; break; // 1
	case 0x5B: ascii = 0x2; break; // 2
	case 0x4F: ascii = 0x3; break; // 3
	case 0x66: ascii = 0x4; break; // 4
	case 0x6D: ascii = 0x5; break; // 5
	case 0x7D: ascii = 0x6; break; // 6
	case 0x07: ascii = 0x7; break; // 6
	case 0x7F: ascii = 0x8; break; // 8
	case 0x6F: ascii = 0x9; break; // 9

	case 0x54: ascii = 0x4E; break; // N
	case 0x50: ascii = 0x52; break; // R

	default:
		ascii = 0xA;
	}
	return(ascii);
}

void cFanatecOut::InitFromHIDData(const u8 *data)
{
	switch (data[2])
	{
	case 1:
		switch (data[3])
		{
		case 2:	// 7 seg
			mDisp[0] = data[4];
			mDisp[1] = data[5];
			mDisp[2] = data[6];
			if (mWheelType == MCLGT3)
				for (u8 i = 0; i < 3; i++)
					mDisp[i] = Convert7SegToChar(mDisp[i]);
			return;
		case 3:	// rumbles
			if ((mWheelType != UNIHUB) && (mWheelType != MCLGT3))
			{
				mRumble[0] = data[4];
				mRumble[1] = data[5];
			}
			return;
		}
		return;
	case 8:// Rev Lights
		if ((mWheelType != UNIHUB) && (mWheelType != MCLGT3))
		{
			mLeds = (data[3] << 8) | data[4];
		}
		return;
	}
}

void cFanatecOut::SetNumber(s16 value)
{
	String val = String(value);
	ClearDisp();
	for (u8 i = 0; i < val.length(); i++)
	{
		mDisp[i] = val.charAt(i);
		if (mWheelType != MCLGT3)
			mDisp[i] = ConvertCharTo7Seg(mDisp[i]);
	}
}

//------------------------------------------------------------------------------------------------

void nFanatec::begin()
{
	mCS.On();
	SPI.begin();
	mRotary = 0;
	mRotaryOnTime = 0;
	mSettingBitePoint = 0;
	mBitePoint = 50;
	mDebouncer.Init();
	memset(&mWheelIn, 0, sizeof(cHIDBufferIn));
	memset(&mWheelOut, 0, sizeof(cFanatecOut));
}

u8 fcnt = 0;

void nFanatec::Update()
{
	const u8 len = 33;
	cFanatecIn buf_in;
	u8 *buf_inp = (u8*)&buf_in;
	u8 *buf_outp = (u8*)&mWheelOut;
	if (mWheelIn.mWheelType == MCLGT3)
		mWheelOut.mWheelType = 0x11;
	mWheelOut.mCrc = crc8(buf_outp, 32);
	mCS.Off();
	SPI.beginTransaction(settingsA);
	for (u8 i = 0; i < len; i++)
	{
		buf_inp[i] = SPI.transfer(buf_outp[i]);
		delayNanoseconds(250);
	}
	SPI.endTransaction();
	mCS.On();
	
	mWheelIn.mWheelType = buf_in.mWheelType;
	mWheelOut.mWheelType = buf_in.mWheelType;

	u32 nowms = millis();

	if (mRotary == 0)											// Rotary pulse generation
	{
		if (buf_in.mEncoder != 0)
			mRotaryOnTime = nowms;
		mRotary = buf_in.mEncoder;
	}

	mDebouncer.mNbButtonsGroup = 3;
	for (u8 i = 0; i < 3; i++)
		mWheelIn.mButtons[i] = buf_in.mButtons[i];
	if (buf_in.mWheelType == UNIHUB || buf_in.mWheelType == XBOXHUB)
	{
		mWheelIn.mButtons[3] = buf_in.mBtnHub[0] & 0x38;
		mWheelIn.mButtons[4] = buf_in.mBtnPS[0];
		mWheelIn.mButtons[5] = buf_in.mBtnPS[1];
		mDebouncer.mNbButtonsGroup = 6;
		if (buf_in.mWheelType == XBOXHUB)			// Xbox Hub has 1 extra button
			mWheelIn.mButtons[3] |= (buf_in.mBtnHub[1] & 0x08)>>1;
	}

	mDebouncer.Update(mWheelIn.mButtons);

#ifdef USE_CUSTOM_BITE_POINT_SETTINGS
	u8 last_settings_button_state = mWheelIn.mButtons[2] & 0x20;
#endif

	for (u8 i = 0; i < mDebouncer.mNbButtonsGroup; i++)
		mWheelIn.mButtons[i] = mDebouncer.mButtons[i];

	if (mRotary == 1)
		mWheelIn.mButtons[2] |= 1 << 4;
	else if (mRotary == -1)
		mWheelIn.mButtons[2] |= 1 << 3;
	if ((nowms - mRotaryOnTime) > mRotaryPulseDuration)
		mRotary = 0;

	if (buf_in.mWheelType == MCLGT3)
	{
		u8 left_rotary = buf_in.mLRRotary & 0xF;
		u8 right_rotary = (buf_in.mLRRotary & 0xF0) >> 4;

		ZeroMem(&mWheelIn.mButtons[3],8);

		b8 settings_not_pressed = ((mWheelIn.mButtons[2] & 0x20) == 0);
		if (settings_not_pressed && (left_rotary>0))
		{
			if (left_rotary<8)
				Bset(mWheelIn.mButtons[3],1 << left_rotary);
			else if (left_rotary<16)
				Bset(mWheelIn.mButtons[4],1 << (left_rotary - 8));
		}
		Bclr(mWheelIn.mButtons[2], 0x20);

#ifdef USE_CUSTOM_BITE_POINT_SETTINGS
		if (settings_not_pressed == last_settings_button_state)					// Not used, I thougt I had to do it, but in fact it's the wheel that deals with the bite point
		{
			mWheelOut.ClearDisp();
			if ((settings_not_pressed == 0) && (last_settings_button_state == 0))
				mSettingBitePoint = !mSettingBitePoint;
		}
#endif		
		if (right_rotary > 1)
		{
			u8 rt = (mWheelIn.mButtons[1] & 0x2)>>1;
			Bclr(mWheelIn.mButtons[1], 0x2);
			u8 lt = (mWheelIn.mButtons[1] & 0x10)>>3;
			Bclr(mWheelIn.mButtons[1], 0x10);
			u8 rb = (mWheelIn.mButtons[2] & 0x40)>>4;
			Bclr(mWheelIn.mButtons[2], 0x40);
			u8 lb = (mWheelIn.mButtons[2] & 0x80)>>4;
			Bclr(mWheelIn.mButtons[2], 0x80);

			u8 m = lb | rb | lt | rt;
			if ((right_rotary & 1) != 0)
				m <<= 4;

			right_rotary >>= 1;
			mWheelIn.mButtons[4 + right_rotary] = m;
		}
		
		mWheelIn.ClearAllAxis();

		u16 x = ((u16)(255 - buf_in.mAxisX)) << 8;
		u16 y = ((u16)(255 - buf_in.mAxisY)) << 8;
		switch (buf_in.mModeRotary)
		{
		case AM_BITE_POINT:
			mWheelIn.mAxisZ = max(x, y);
			break;
		case AM_CLUTCH_HANDBRAKE:
			mWheelIn.mAxisZ = x;
			mWheelIn.mAxisRx = y;
			break;
		case AM_BRAKE_THROTTLE:
			mWheelIn.mAxisRy = x;
			mWheelIn.mAxisRz = y;
			break;
		case AM_ANALOG_AXES:
			mWheelIn.mAxisX = x;
			mWheelIn.mAxisY = y;
			break;
		}
	}
	else
	{
		mWheelIn.mAxisX = ((s16)(128 - buf_in.mAxisX)) << 8;
		mWheelIn.mAxisY = ((s16)(127 + buf_in.mAxisY)) << 8;
	}

	u8 hat;														// Hat encoding
	switch (mWheelIn.mButtons[0] & 0x0f)
	{
	case 0: hat = 0xFF; break;
	case 1: hat = 0; break;
	case 2: hat = 6; break;
	case 4: hat = 2; break;
	case 8: hat = 4; break;
	default: hat = 0xFF;
	}
	mWheelIn.mHatSwitch = hat;

	u32 elapsed = millis();
	if (elapsed < 3000)
	{
#ifdef TEST_DISPLAY
		u32 cnt = elapsed / 100;
		mWheelOut.mDisp[0] = 1 << (cnt % 8);
		mWheelOut.mDisp[1] = 1 << (cnt % 8);
		mWheelOut.mDisp[2] = 1 << (cnt % 8);
		mWheelOut.mLeds = 1 << ((cnt++) % 9);
#else
		if ((buf_in.mProtocol == CSW_PROTOCOL) && (buf_in.mWheelType >= NO_RIM) && (buf_in.mWheelType <= PORSCHE_RIM))
		{
			u32 cnt = elapsed / 150;
			String init_str = "ElectroSeed " + String(NB_FW_VERSION);
			u8 slen = init_str.length();
			if ((cnt + 2) < slen)
			{
				mWheelOut.mDisp[0] = ConvertCharTo7Seg((u8)init_str.charAt(cnt % slen));
				mWheelOut.mDisp[1] = ConvertCharTo7Seg((u8)init_str.charAt((cnt + 1) % slen));
				mWheelOut.mDisp[2] = ConvertCharTo7Seg((u8)init_str.charAt((cnt + 2) % slen));
			}
		}
		else if (buf_in.mWheelType == MCLGT3)
		{
			mWheelOut.SetNumber(buf_in.mFWver);
		}
#endif
		if (elapsed > 2900)
			mWheelOut.Clear();
	}
	else
	{
		if (buf_in.mWheelType == MCLGT3)
		{
			if (mSettingBitePoint)
			{
				mWheelOut.ClearDisp();
				mBitePoint = constrain(mBitePoint + buf_in.mEncoder, 0, 100);
				u32 blink = elapsed / 200;
				if (blink & 1)
					mWheelOut.SetNumber(mBitePoint);
			}
		}
	}
#ifdef DEBUG_VALUES
	static u32 last_buttons;
	u32 bt = mWheelIn.mButtons[0] | (mWheelIn.mButtons[1] << 8) | (mWheelIn.mButtons[2] << 16);
// 	fana_println(bt,BIN);
//	u32 bt = *((u32*)&mWheelIn.mButtons[0]);
	if (bt != last_buttons)
	{
		fana_print(F("Protocol : ")); fana_println(buf_in.mProtocol, HEX);
		fana_print(F("Id : ")); fana_println(buf_in.mWheelType, HEX);
		fana_print(F("FW ver : ")); fana_println(buf_in.mFWver, HEX);
		last_buttons = bt;
		fana_print(F("Buttons : ")); fana_print(bt, BIN);
		fana_print(F(" , Analog : "));
		fana_print(mWheelIn.mAxisX);
		fana_print(F(" , "));
		fana_println(mWheelIn.mAxisY);
	}
#endif
#ifdef DEBUG_RAW_VALUES
	static u8 last_buf[len];
	u8 changed = FALSE;
	for (u8 i = 0; i < 31; i++)
		if (last_buf[i] != buf_inp[i])
		{
			const char *id_str[] = {
				"mProtocol",	// 0
				"mWheelType",	// 1
				"mButtons 0",	// 2
				"mButtons 1",	// 3
				"mButtons 2",	// 4
				"mAxisX",		// 5
				"mAxisY",		// 6
				"mEncoder",		// 7
				"mBtnHub 0",	// 8
				"mBtnHub 1",	// 9
				"mBtnPS 0",		// 10
				"mBtnPS 1",		// 11
				"mUnused0",		// 12
				"mUnused1",		// 13
				"mModeRotary",	// 14
				"mLRRotary",	// 15
			};
//			fana_print(i);  fana_print(" : "); fana_print(buf_inp[i], HEX);
			if (i <= 15)
			{
//				fana_print("\t");
				fana_print(id_str[i]);
			}
			fana_print(" - "); fana_print(buf_inp[i], HEX);
			fana_println();
			changed = TRUE;
		}
	if (changed)
	{
		for (u8 i = 0; i < 31; i++)
		{
			last_buf[i] = buf_inp[i];
//			fana_print(i);  fana_print(" : "); fana_println(buf_inp[i], HEX); //fana_print(",");
		}
//		fana_println();
	}
#endif
//	if (bt != last_buttons)
		Send();
}

