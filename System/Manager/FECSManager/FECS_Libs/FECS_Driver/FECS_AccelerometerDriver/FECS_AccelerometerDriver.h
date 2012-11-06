/*
*
*	HMC5883L Magnetometer IC Driver Code
*
*
*
*/

#ifndef FECS_ACCELEROMETERDRIVER_H_
#define FECS_ACCELEROMETERDRIVER_H_

#include "../FECS_Driver.h"

#ifdef _FECS_SYSTEM_
	#include "FECS_System/FECS_Peripheral/FECS_I2CPeripheral/FECS_I2CPeripheral.h"
#endif

namespace FECS_System{
	namespace FECS_Drv_AccelerometerNS{

		namespace Parameter{

			/************************************************************************	 
			*		ACCELEROMETER DATA-XYZ TYPE
			*/

			struct ReadData{
				char * MessageParameter;
				const static short MessageParameterSize;

				ReadData(short x_=0,short y_=0,short z_=0,unsigned char Act_Tap_Status_=0,unsigned char InterruptSource_=0,unsigned char FIFOStatus_=0);
				~ReadData(void);

				void setX(unsigned char MSB,unsigned char LSB);
				short getX(void);
				void setY(unsigned char MSB,unsigned char LSB);
				short getY(void);
				void setZ(unsigned char MSB,unsigned char LSB);
				short getZ(void);

				void setActive_Tap_Status(unsigned char status_);
				unsigned char getActive_Tap_Status(void);
				BOOL is_ACTX_Event(void);
				BOOL is_ACTY_Event(void);
				BOOL is_ACTZ_Event(void);
				BOOL is_Asleep(void);
				BOOL is_TAPX_Event(void);
				BOOL is_TAPY_Event(void);
				BOOL is_TAPZ_Event(void);

				void setInterruptSource(unsigned char status_);
				unsigned char getInterruptSource(void);
				BOOL is_Overrun_INT(void);
				BOOL is_Watermark_INT(void);
				BOOL is_FreeFall_INT(void);
				BOOL is_Inactivity_INT(void);
				BOOL is_Activity_INT(void);
				BOOL is_DoubleTap_INT(void);
				BOOL is_SingleTap_INT(void);
				BOOL is_DataReady_INT(void);

				void setFIFOStatus(unsigned char status_);
				unsigned char getFIFOStatus(void);
				unsigned char getFIFOCount(void);
				BOOL is_FIFOTrigger_Event(void);


				const char* getAsMessageParameter(void);
				void setAsMessageParameter(const char* in_);

				ReadData&	operator=(const ReadData& in_);

			};//End of struct XYZ

			/************************************************************************	 
			*		ACCELEROMETER CONFIGURATION-MODE TYPE
			*/

			typedef enum{
				TAP_AXES_NONE=0x00,
				TAP_Z_EN	=0X01,
				TAP_Y_EN	=0X02,
				TAP_X_EN	=0X04,

				SUPRESS		=0X08
			}Tap_Axes_Type;

			typedef enum{
				ACT_INACT_NONE=0x00,

				INACT_Z_EN	=0X01,
				INACT_Y_EN	=0X02,
				INACT_X_EN	=0X04,
				INACT_AC	=0X08,

				ACT_Z_EN	=0X10,
				ACT_Y_EN	=0X20,
				ACT_X_EN	=0X40,
				ACT_AC		=0X80			
			}Act_Inact_Control_Type;

			typedef enum{
				INT_EN_NONE	=	0x00,
				OVERRUN		=	0X01,
				WATERMARK	=	0X02,
				FREEFALL	=	0X04,
				INACT		=	0X08,
				ACT			=	0X10,
				DOUBLE_TAP	=	0X20,
				SINGLE_TAP	=	0X40,
				DATA_READY	=	0X80
			}Int_Enable_Type;

			typedef enum{
				INT_MAP_NONE		=	0x00,
				OVERRUN_INT2pin		=	0X01,
				WATERMARK_INT2pin	=	0X02,
				FREEFALL_INT2pin	=	0X04,
				INACT_INT2pin		=	0X08,
				ACT_INT2pin			=	0X10,
				DOUBLE_TAP_INT2pin	=	0X20,
				SINGLE_TAP_INT2pin	=	0X40,
				DATA_READY_INT2pin	=	0X80
			}Int_Map_Type;
			
			typedef enum{
				BW_1600HZ		=	0XF,
				BW_800HZ		=	0XE,
				BW_400HZ		=	0XD,
				BW_200HZ		=	0XC,
				BW_100HZ		=	0XB,
				BW_50HZ			=	0XA,
				BW_25HZ			=	0X9,
				BW_12_5HZ		=	0X8,
				BW_6_25HZ		=	0X7,
				BW_3_125HZ		=	0X6,

				LOW_POWER		=	0x10,
			}Bandwidth_Type;

			typedef enum{
				RANGE_2G	=	0X00,
				RANGE_4G	=	0X01,
				RANGE_8G	=	0X02,
				RANGE_16G	=	0X04,

				JUSTIFY		=	0X08,
				FULLRES		=	0X10,
				INT_INVERT	=	0X20,
				SPI			=	0X40,
				SELF_TEST	=	0X80			
			}Data_Format_Type;

			typedef enum{
				FIFO_SAMPLEBITS_MASK=0x1F,
				
				TRIGGER		=	0X20,

				MODE_BYPASS	=	0X00,
				MODE_FIFO	=	0X40,
				MODE_STREAM	=	0X80,
				MODE_TRIGGER=	0XC0			
			}FIFO_Control_Type;

			typedef enum{
				WAKEUP_8HZ	=	0X00,
				WAKEUP_4HZ	=	0X01,
				WAKEUP_2HZ	=	0X02,
				WAKEUP_1HZ	=	0X03,

				SLEEP		=	0X04,
				MEASURE		=	0X08,
				AUTO_SLEEP	=	0X10,
				LINK		=	0X20				
			}Power_Control_Type;

			

			typedef enum{
				THRESH_TAP=0,//TAP, 62.5mg/LSB

				DUR,	//TAP,duration,625us/LSB, 0 disables THRESH_TAP
				Latent,	//TAP,1.25ms/LSB
				Window,	//TAP,1.25ms/LSB

				/*	TAP_AXES
				D0:TAP_Z enable
				D1:TAP_Y enable
				D2:TAP_X enable
				D3:Suppress
				Setting the suppress bit suppresses double tap detection if acceleration
				greater than the value in THRESH_TAP is present between taps.
				*/
				TAP_AXES,

				OFSX,	//15.6 mg/LSB	0x7F=+2g
				OFSY,	//15.6 mg/LSB	0x7F=+2g
				OFSZ,	//15.6 mg/LSB	0x7F=+2g			

				THRESH_ACT,		//62.5mg/LSB
				THRESH_INACT,	//62.5mg/LSB
				TIME_INCACT,	//1sec/LSB

				/*	ACT_INCACT_CTL

				D0:INACT_Z enable
				D1:INACT_Y enable
				D2:INACT_X enable
				D3:INACT ac/dc
				D4:ACT_Z enable
				D5:ACT_Y enable
				D6:ACT_X enable
				D7:ACT ac/dc

				A setting of 0 selects dc-coupled operation, and a setting of 1 enables 
				ac-coupled operation. In dc-coupled operation, the current acceleration 
				magnitude is compared directly with THRESH_ACT and THRESH_INACT to determine
				whether activity or inactivity is detected.

				In ac-coupled operation for activity detection, the acceleration value at the
				start of activity detection is taken as a reference value. New samples of
				acceleration are then compared to this reference value, and if the magnitude
				of the difference exceeds the THRESH_ACT value, the device triggers an activity
				interrupt.

				Similarly, in ac-coupled operation for inactivity detection, a reference value
				is used for comparison and is updated whenever the device exceeds the inactivity
				threshold. After the reference value is selected, the device compares the
				magnitude of the difference between the reference value and the current
				acceleration with THRESH_INACT. If the difference is less than the value in
				THRESH_INACT for the time in TIME_INACT, the device is considered inactive
				and the inactivity interrupt is triggered.
				*/
				ACT_INCACT_CTL,

				/*	THRESH_FF
				The THRESH_FF register is eight bits and holds the threshold value,
				in unsigned format, for free-fall detection. The root-sum-square (RSS)
				value of all axes is calculated and compared with the value in THRESH_FF
				to determine if a free-fall event occurred.

				Note that a value of 0 mg may result in undesirable behavior if the
				free-fall interrupt is enabled. Values between 300 mg and 600 mg
				(0x05 to 0x09) are recommended.
				*/
				THRESH_FF,	//62.5mg/LSB
				/*	TIME_FF
				A value of 0 may result in undesirable behavior if the free-fall interrupt
				is enabled. Values between 100 ms and 350 ms (0x14 to 0x46) are recommended.
				*/
				TIME_FF,	//5 ms/LSB.


				/*	INT_ENABLE

				D0:Overrun
				D1:Watermark
				D2:FREE_FALL
				D3:Inactivity
				D4:Activity
				D5:DOUBLE_TAP
				D6:SINGLE_TAP
				D7:DATA_READY
				*/
				INT_ENABLE,
				/*	INT_MAP

				D0:Overrun
				D1:Watermark
				D2:FREE_FALL
				D3:Inactivity
				D4:Activity
				D5:DOUBLE_TAP
				D6:SINGLE_TAP
				D7:DATA_READY

				Any bits set to 0 in this register send their respective interrupts to the
				INT1 pin, whereas bits set to 1 send their respective interrupts to the INT2
				pin.

				*/
				INT_MAP,


				/*	BW_RATE
				D3,D2,D1,D0 : Rate
				D4	: Low Power
				The default value is 0x0A

				-Normal Operation
				RateCode		Bandwidth (Hz)
				1111(0xF)		1600
				1110(0xE)		800
				1101(0xD)		400
				1100(0xC)		200
				1011(0xB)		100
				1010(0xA)		50
				1001(0x9)		25
				1000(0x8)		12.5
				0111(0x7)		6.25
				0110(0x6)		3.125

				-LowPower Operation
				RateCode		Bandwidth (Hz)
				1100(0xC)		200
				1011(0xB)		100
				1010(0xA)		50
				1001(0x9)		25
				1000(0x8)		12.5
				0111(0x7)		6.25

				LowPower
				A setting of 0 in the LOW_POWER bit selects normal operation, and a setting
				of 1 selects reduced power operation, which has somewhat higher noise

				*/
				BW_RATE,

				/*	POWER_CTL
				D1,D0	:Wakeup
				D2		:Sleep
				D3		:Measure
				D4		:AUTO_SLEEP
				D5		:Link

				LinkBit
				A setting of 1 in the link bit with both the activity and inactivity
				functions enabled delays the start of the activity function until
				inactivity is detected. After activity is detected, inactivity detection
				begins, preventing the detection of activity. This bit serially links the 
				activity and inactivity functions. When this bit is set to 0, the inactivity
				and activity functions are concurrent.

				AUTO_SLEEP
				If the link bit is set, a setting of 1 in the AUTO_SLEEP bit sets the ADXL345
				to switch to sleep mode when inactivity is detected (that is, when acceleration
				has been below the THRESH_INACT value for at least the time indicated by
				TIME_INACT). A setting of 0 disables automatic switching to sleep mode.

				Measure
				A setting of 0 in the measure bit places the part into standby mode, and a
				setting of 1 places the part into measurement mode. The ADXL345 powers up in
				standby mode with minimum power consumption.

				Sleep
				A setting of 0 in the sleep bit puts the part into the normal mode of operation,
				and a setting of 1 places the part into sleep mode. Sleep mode suppresses
				DATA_READY, stops transmission of data to FIFO, and switches the sampling rate 
				to one specified by the wakeup bits. In sleep mode, only the activity function
				can be used.

				Wakeup Bits
				These bits control the frequency of readings in sleep mode as described
				D1	D0		Frequency
				0	0		8
				0	1		4
				1	0		2
				1	1		1
				*/
				POWER_CTL,

				/*	DATA_FORMAT

				D1,D0	:Range
				D2		:Justify
				D3		:FULL_RES
				D5		:INT_INVERT
				D6		:SPI
				D7		:SELF_TEST

				SELF_TEST Bit
				A setting of 1 in the SELF_TEST bit applies a self-test force to the sensor,
				causing a shift in the output data. A value of 0 disables the self-test force.

				SPI Bit
				A value of 1 in the SPI bit sets the device to 3-wire SPI mode, and a value
				of 0 sets the device to 4-wire SPI mode.

				INT_INVERT Bit
				A value of 0 in the INT_INVERT bit sets the interrupts to active high, and 
				a value of 1 sets the interrupts to active low.

				FULL_RES Bit
				When this bit is set to a value of 1, the device is in full resolution mode,
				where the output resolution increases with the g range set by the range bits
				to maintain a 4 mg/LSB scale factor. When the FULL_RES bit is set to 0, the
				device is in 10-bit mode, and the range bits determine the maximum g range and
				scale factor.

				Justify Bit
				A setting of 1 in the justify bit selects left (MSB) justified mode, and a
				setting of 0 selects right justified mode with sign extension.

				Range Bits
				These bits set the g range as described
				D1	D0	g Range
				0	0	+-2g
				0	1	+-4g
				1	0	+-8g
				1	1	+-16g

				*/
				DATA_FORMAT,

				/*	FIFO_CTL

				D4,D3,D2,D1,D0	:	Samples
				D5				:	Trigger
				D7,D6			:	FIFO_MODE

				Settings
				D7	D6		Mode		Function
				0	0		Bypass		FIFO is Bypassed
				0	1		FIFO		FIFO collects up to 32 values and then stops collecting data, collecting new data only when FIFO is not full.
				1	0		Stream		FIFO holds the last 32 data values. When FIFO is full, the oldest data is overwritten with newer data.
				1	1		Trigger		When triggered by the trigger bit, FIFO holds the last data samples before the trigger event and then continues to collect data until full. New data is collected only when FIFO is not full.


				Samples
				FIFO MODE		Samples Bits Function
				Bypass			None
				FIFO			Specifies how many FIFO entries are needed to trigger a watermark interrupt.
				Stream			Specifies how many FIFO entries are needed to trigger a watermark interrupt.
				Trigger			Specifies how many FIFO samples are retained in the FIFO buffer before a trigger event.
				*/
				FIFO_CTL
			}ConfRegMessID;	//Configuration Registers Message Map



			struct ConfigurationType{
				char * MessageParameter;
				static const short MessageParameterSize;
				

				ConfigurationType(void);
				~ConfigurationType();
				ConfigurationType&	operator=(const ConfigurationType& in_);

				/*	setTapConf:
				*		Configure Tap Recognition Function
				*	INPUT:
				*		threshold_ (THRESH_TAP): 
				*			-Unsigned 8 bit  holds threshold value for tap interrupt. 
				*			-If a (force) tap needs to be recognized it must be bigger than this 
				*				this threshold value.
				*			-Scale factor is 62.5 mg/LSB, (0xFF= +16g)
				*			-A value of 0 may result in undesirable behavior, if tap-double tap is enabled
				*			-Reset Value is 0
				*
				*		duration_(DUR):
				*			-Unsigned 8 bit holds time value representing the maximum time that an
				*				event must be above the threshold_ (THRESH_TAP) value
				*			-Scale factor is 625us/LSB. (0xFF = 159,375 us ~=159 ms)
				*			-A value 0 disables the tap-double tap function
				*			-Reset value is 0
				*
				*		latency_(Latent):
				*			-Unsigned 8 bit holds wait time from the detection of a tap event to the 
				*				start of the time window during which a possible second tap event can be detected
				*			-Scale Factor is 1.25 ms/LSB (0xFF=318.75 ms).
				*			-A value of 0 disables the double tap function
				*			-Reset value is 0
				*
				*		window_(Window):
				*			-Unsigned 8 bit holds time value representing the amount of time after the expiration 
				*				of the latency time (determined by the Latent register) during which a second 
				*				valid tap can begin.
				*			-Scale factor is 1.25 ms/LSB (0xFF=318.75 ms).
				*			-A value of 0 disables the double tap function
				*			-Reset value is 0
				*
				*		axes_conf_(TAP_AXES):
				*			-Available values,(combination any of these values):
				*				TAP_AXES_NONE=0x00,
				*				TAP_Z_EN	=0X01,
				*				TAP_Y_EN	=0X02,
				*				TAP_X_EN	=0X04,
				*				SUPRESS		=0X08
				*				Example: In order to activate TAP_Z and TAP_X with SUPRESS function
				*					"TAP_X_EN|TAP_Z_EN|SUPRESS"
				*			-Setting the suppress bit suppresses double tap detection if acceleration greater 
				*				than the value in THRESH_TAP is present between taps.
				*			-A setting of 1 in the TAP_X enable, TAP_Y enable, or TAP_Z enable bit 
				*				enables x-, y-, or z-axis participation in tap detection.
				*			-Reset Value is TAP_AXES_NONE(=0).
				*/
				void setTapConf(
					unsigned char threshold_=0,
					unsigned char duration_=0,
					unsigned char latency_=0,
					unsigned char window_=0,
					Tap_Axes_Type axes_conf_=TAP_AXES_NONE
					);

				/*	setAxisOffsetConf:
				*		Configure Accelerometer Offset configuration
				*
				*		INPUT:
				*			x_(OFSX),y_(OFSY),z_(OFSZ):
				*				each eight bits and offer user-set offset adjustments in twos complement
				*				format with a scale factor of 15.6 mg/LSB (that is, 0x7F = +2 g).
				*
				*/
				void setAxisOffsetConf(
					signed char x_=0,
					signed char y_=0,
					signed char z_=0
					);

				/*	setActInactConf:
				*		Configure Accelerometers automatic active-inactive  modes
				*
				*	INPUT:
				*		act_treshold_(THRESH_ACT):
				*			-eight bits hold the threshold value for detecting activity.
				*				The data format is unsigned, so the magnitude of the activity event is compared with the
				*				value in the THRESH_ACT register. 
				*			-The scale factor is 62.5 mg/LSB.
				*			-Reset value is 0.
				*			-A value of 0 may result in undesirable behavior if the activity interrupt is enabled.
				*
				*		inact_treshold_(THRESH_INACT):
				*			-eight bits hold the threshold value for detecting activity.
				*				The data format is unsigned, so the magnitude of the activity event is compared with the
				*				value in the THRESH_INACT register. 
				*			-The scale factor is 62.5 mg/LSB.
				*			-Reset value is 0.
				*			-A value of 0 may result in undesirable behavior if the inactivity interrupt is enabled.
				*
				*		inact_time_(TIME_INACT):
				*			-eight bits and contains an unsigned time value representing the amount of time that acceleration
				*				must be less than the value in the THRESH_INACT register for inactivity to be declared.  
				*				Unlike the other interrupt functions, which use unfiltered data (see the Threshold section),
				*				the inactivity function uses filtered output data. At least one output sample must be generated
				*				for the inactivity interrupt to be triggered. This results in the function appearing unresponsive
				*				if the TIME_INACT register is set to a value less than the time constant of the output data rate.				*				
				*			-The scale factor is 1 sec/LSB.
				*			-A value of 0 results in an interrupt when the output data is less than the value in the THRESH_INACT register.
				*
				*		act_inact_cont_(ACT_INACT_CTL):
				*			-Available Values, (Combination any of these values)
				*				ACT_INACT_NONE=0x00,
				*				INACT_Z_EN	=0X01,
				*				INACT_Y_EN	=0X02,
				*				INACT_X_EN	=0X04,
				*				INACT_AC	=0X08,
				*				ACT_Z_EN	=0X10,
				*				ACT_Y_EN	=0X20,
				*				ACT_X_EN	=0X40,
				*				ACT_AC		=0X80
				*				Example: INACT_Z_EN|ACT_Y_EN
				*			-A setting of 0 selects dc-coupled operation, and a setting of 1 enables ac-coupled operation. In order to 
				*				use DC just don't use INACT_AC or ACT_AC.
				*			-In dc-coupled operation, the current acceleration magnitude is compared directly with THRESH_ACT and 
				*				THRESH_INACT to determine whether activity or inactivity is detected.
				*			-In ac-coupled operation for activity detection, the acceleration value at the start of activity detection
				*				is taken as a reference value. New samples of acceleration are then compared to this reference value, 
				*				and if the magnitude of the difference exceeds the THRESH_ACT value, the device triggers an activity 
				*				interrupt.
				*			-Similarly, in ac-coupled operation for inactivity detection, a reference value is used for comparison and
				*				is updated whenever the device exceeds the inactivity threshold. After the reference value is selected,
				*				the device compares the magnitude of the difference between the reference value and the current 
				*				acceleration with THRESH_INACT. If the difference is less than the value in THRESH_INACT for the time
				*				in TIME_INACT, the device is considered inactive and the inactivity interrupt is triggered.
				*			-A setting of 1 (Using ACT_X,Y,Z_EN or INACT_X,Y,Z_EN) enables x-, y-, or z-axis participation in detecting 
				*				activity or inactivity. A setting of 0 excludes	the selected axis from participation. 
				*			-If all axes are excluded, the function is disabled.
				*			-Reset value is ACT_INACT_NONE (=0)
				*
				*/
				void setActInactConf(
					unsigned char act_treshold_=0,
					unsigned char inact_treshold_=0,
					unsigned char inact_time_=0,
					Act_Inact_Control_Type act_inact_cont_=ACT_INACT_NONE
					);

				/*	setFreeFallConf:
				*		Configure Accelerometers free fall function
				*
				*	INPUT:
				*		treshold_(THRESH_FF):
				*			-eight bits holds the threshold value, in unsigned format, for free-fall detection. The root-sum-square (RSS) 
				*				value of all axes is calculated and compared with the value in THRESH_FF to determine if a free-fall event
				*				occurred. 
				*			-The scale factor is 62.5 mg/LSB. 
				*			-Note that a value of 0 mg may result in undesirable behavior if the free-fall interrupt is enabled. 
				*			-Values between 300 mg and 600 mg (0x05 to 0x09) are recommended.
				*			-Reset value is 0
				*
				*		time_(TIME_FF):
				*			-eight bits and stores an unsigned time value representing the minimum time that the RSS value of all axes must
				*				be less than THRESH_FF to generate a free-fall interrupt. 
				*			-The scale factor is 5 ms/LSB. 
				*			-A value of 0 may result in undesirable behavior if the free-fall interrupt is enabled. 
				*			-Values between 100 ms and 350 ms (0x14 to 0x46) are recommended.
				*			-Reset value is 0
				*/
				void setFreeFallConf(
					unsigned char treshold_=0,
					unsigned char time_=0
					);
				/*	setInterruptControl:
				*		Configure Accelerometers Interrupt functions
				*
				*	INPUT:
				*		Int_Enable_(INT_ENABLE):
				*			-Available Values (Combination any of these values)
				*				INT_EN_NONE=	0x00,
				*				OVERRUN		=	0X01,
				*				WATERMARK	=	0X02,
				*				FREEFALL	=	0X04,
				*				INACT		=	0X08,
				*				ACT			=	0X10,
				*				DOUBLE_TAP	=	0X20,
				*				SINGLE_TAP	=	0X40,
				*				DATA_READY	=	0X80
				*			-Setting bits in this register to a value of 1 enables their respective functions to generate interrupts, 
				*				whereas a value of 0 prevents the functions from generating interrupts. 
				*			-The DATA_READY, watermark, and overrun bits enable only the interrupt output; the functions are always enabled.
				*			-It is recommended that interrupts be configured before enabling their outputs.
				*
				*		Int_Map_(INT_MAP):
				*			-Available Values (Combination any of these values)
				*				INT_MAP_NONE		=	0x00,
				*				OVERRUN_INT2pin		=	0X01,
				*				WATERMARK_INT2pin	=	0X02,
				*				FREEFALL_INT2pin	=	0X04,
				*				INACT_INT2pin		=	0X08,
				*				ACT_INT2pin			=	0X10,
				*				DOUBLE_TAP_INT2pin	=	0X20,
				*				SINGLE_TAP_INT2pin	=	0X40,
				*				DATA_READY_INT2pin	=	0X80
				*			-Any bits set to 0 in this register send their respective interrupts to the INT1 pin, whereas bits set to 1 send
				*				their respective interrupts to the INT2 pin. All selected interrupts for a given pin are OR�ed.
				*/
				void setInterruptControl(
					Int_Enable_Type		Int_Enable_=INT_EN_NONE,
					Int_Map_Type		Int_Map_=INT_MAP_NONE
					);

				/*	setOperationConf:
				*		Configure Accelerometers Interrupt functions
				*
				*	INPUT:
				*		bandwidth_(BW_RATE):
				*			-Available Values (One of BW_X must be chosen and LOW_POWER is optional)
				*			BW_1600HZ		=	0XF,
				*			BW_800HZ		=	0XE,
				*			BW_400HZ		=	0XD,
				*			BW_200HZ		=	0XC,
				*			BW_100HZ		=	0XB,
				*			BW_50HZ			=	0XA,
				*			BW_25HZ			=	0X9,
				*			BW_12_5HZ		=	0X8,
				*			BW_6_25HZ		=	0X7,
				*			BW_3_125HZ		=	0X6,
				*
				*			LOW_POWER		=	0x10,
				*			Example: "BW_200HZ" or "BW_200HZ | LOW_POWER" or "BW_100HZ | LOW_POWER"
				*			
				*			-A setting of 0 in the LOW_POWER bit selects normal operation, and 
				*				a setting of 1 selects reduced power operation, which has somewhat higher noise
				*			-Reset value is BW_50HZ(=0x0A)
				*			-Selecting too high of an output data rate with a low communication speed results in samples being discarded !.
				*
				*		dataFormat_(DATA_FORMAT):
				*			-Available Values (One of RAGNE_X must be chosen and others are optional)
				*			RANGE_2G	=	0X00,
				*			RANGE_4G	=	0X01,
				*			RANGE_8G	=	0X02,
				*			RANGE_16G	=	0X04,
				*
				*			JUSTIFY		=	0X08,
				*			FULLRES		=	0X10,
				*			INT_INVERT	=	0X20,
				*			SPI			=	0X40,
				*			SELF_TEST	=	0X80
				*			-The DATA_FORMAT register controls the presentation of data to Register 0x32 through Register 0x37. All data, 
				*				except that for the �16 g range, must be clipped to avoid rollover.
				*			-SELF_TEST Bit:A setting of 1 in the SELF_TEST bit applies a self-test force to the sensor, causing a shift 
				*				in the output data. A value of 0 disables the self-test force.
				*			-SPI Bit:A value of 1 in the SPI bit sets the device to 3-wire SPI mode, and a value of 0 sets the device to 
				*				4-wire SPI mode.
				*			-INT_INVERT Bit:A value of 0 in the INT_INVERT bit sets the interrupts to active high, and a value of 1 sets 
				*				the interrupts to active low.
				*			-FULL_RES Bit:When this bit is set to a value of 1, the device is in full resolution mode, where the output 
				*				resolution increases with the g range set by the range bits to maintain a 4 mg/LSB scale factor. When the
				*				FULL_RES bit is set to 0, the device is in 10-bit mode, and the range bits determine the maximum g range 
				*				and scale factor.
				*			-Justify Bit:A setting of 1 in the justify bit selects left (MSB) justified mode, and a setting of 0 selects 
				*				right justified mode with sign extension.
				*			-Range Bits:These bits set the g range as described in list above.
				*			-Reset value is RANGE_2G(=0).
				*			
				*
				*		FIFO_Cont_(FIFO_CTL):
				*			-Available values are (One of the MODE_X must be chosen, TRIGGER is optional if mode MODE_TRIGGER is used:
				*				FIFO_SAMPLEBITS_MASK=0x1F,
				*		
				*				TRIGGER		=	0X20,
				*
				*				MODE_BYPASS	=	0X00,
				*				MODE_FIFO	=	0X40,
				*				MODE_STREAM	=	0X80,
				*				MODE_TRIGGER=	0XC0
				*
				*			-Mode Explanations
				*				Bypass				FIFO is bypassed.
				*				FIFO				FIFO collects up to 32 values and then stops collecting data, collecting new data only 
				*									when FIFO is not full.
				*				Stream				FIFO holds the last 32 data values. When FIFO is full, the oldest data is overwritten
				*									with newer data.
				*				Trigger				When triggered by the trigger bit, FIFO holds the last data samples before the trigger
				*									event and then continues to collect data until full. New data is collected only when
				*									FIFO is not full.
				*
				*			-Trigger Bit:A value of 0 in the trigger bit links the trigger event of trigger mode to INT1, and a value of 1
				*				links the trigger event to INT2.
				*
				*			-Samples Bits:Five bits determine number of samples.The function of these bits depends on the FIFO mode selected .
				*				Entering a value of 0 in the samples bits immediately sets the watermark status bit in the INT_SOURCE register,
				*				regardless of which FIFO mode is selected. Undesirable operation may occur if a value of 0 is used for the  
				*				samples bits when trigger mode is used. Sample
				*
				*			-Sample Bits Explanation
				*				Bypass				None.
				*				FIFO				Specifies how many FIFO entries are needed to trigger a watermark interrupt.
				*				Stream				Specifies how many FIFO entries are needed to trigger a watermark interrupt.
				*				Trigger				Specifies how many FIFO samples are retained in the FIFO buffer before a trigger event.
				*			-Sample bit
				*			-Example Usage:
				*				"MODE_TRIGGER | (FIFO_SAMPLEBITS_MASK & 3)"
				*				"MODE_TRIGGER | TRIGGER | (FIFO_SAMPLEBITS_MASK & 14)"
				*				"MODE_STREAM | (FIFO_SAMPLEBITS_MASK & 23)"
				*				"MODE_FIFO	| (FIFO_SAMPLEBITS_MASK & 5)"
				*				"MODE_BYPASS"
				*
				*		Power_Cont_(POWER_CTL):
				*			-Available Values (Combination of one of the WAKEUP_X and others)
				*				WAKEUP_8HZ	=	0X00,
				*				WAKEUP_4HZ	=	0X01,
				*				WAKEUP_2HZ	=	0X02,
				*				WAKEUP_1HZ	=	0X03,
				*				
				*				SLEEP		=	0X04,
				*				MEASURE		=	0X08,
				*				AUTO_SLEEP	=	0X10,
				*				LINK		=	0X20	
				*
				*			-Link Bit:	A setting of 1 in the link bit with both the activity and inactivity functions enabled delays 
				*				the start of the activity function until inactivity is detected. After activity is detected, inactivity
				*				detection begins, preventing the detection of activity. This bit serially links the activity and inactivity
				*				functions. When this bit is set to 0, the inactivity and activity functions are concurrent. Additional 
				*				information can be found in the Link Mode section.
				*				When clearing the link bit, it is recommended that the part be placed into standby mode and then set back
				*				to measurement mode with a subsequent write. This is done to ensure that the device is properly biased if
				*				sleep mode is manually disabled; otherwise, the first few samples of data after the link bit is cleared
				*				may have additional noise, especially if the device was asleep when the bit was cleared.
				*
				*			-AUTO_SLEEP Bit:If the link bit is set, a setting of 1 in the AUTO_SLEEP bit sets the ADXL345 to switch to
				*				sleep mode when inactivity is detected (that is, when acceleration has been below the THRESH_INACT
				*				value for at least the time indicated by TIME_INACT). A setting of 0 disables automatic switching to
				*				sleep mode. See the description of the sleep bit in this section for more information.
				*				When clearing the AUTO_SLEEP bit, it is recommended that the part be placed into standby mode and then
				*				set back to measurement mode with a subsequent write. This is done to ensure that the device is properly
				*				biased if sleep mode is manually disabled; otherwise, the first few samples of data after the AUTO_SLEEP
				*				bit is cleared may have additional noise, especially if the device was asleep when the bit was cleared.
				*
				*			-Measure Bit:A setting of 0 in the measure bit places the part into standby mode, and a setting of 1 places
				*				the part into measurement mode. The ADXL345 powers up in standby mode with minimum power consumption.
				*			
				*			-Sleep Bit:	A setting of 0 in the sleep bit puts the part into the normal mode of operation, and a setting
				*				of 1 places the part into sleep mode. Sleep mode suppresses DATA_READY, stops transmission of data to 
				*				FIFO, and switches the sampling rate to one specified by the wakeup bits. In sleep mode, only the activity
				*				function can be used.
				*				When clearing the sleep bit, it is recommended that the part be placed into standby mode and then set back
				*				to measurement mode with a subsequent write. This is done to ensure that the device is properly biased if
				*				sleep mode is manually disabled; otherwise, the first few samples of data after the sleep bit is cleared
				*				may have additional noise, especially if the device was asleep when the bit was cleared.
				*
				*			-Wakeup Bits:These bits control the frequency of readings in sleep mode as described above.
				*
				*			-Reset value is 0
				*			
				*/
				void setOperationConf(
					Bandwidth_Type		bandwidth_=BW_50HZ,
					Data_Format_Type	dataFormat_=RANGE_2G,
					FIFO_Control_Type	FIFO_Cont_=MODE_FIFO,
					Power_Control_Type	Power_Cont_=MEASURE				
					);

				

				unsigned char	getControlValue(ConfRegMessID	ValueAddress);

				const char* getAsMessageParameter(void);
				void setAsMessageParameter(const char* in_);

			};//End of struct ConfigurationType

		}//End of namespace Parameters

		const unsigned char ACC_USED_I2C_PORT=0;

		namespace Message{
			typedef enum{

				/*	ACCELEROMETER MESSAGE
				*	Message:[AccMessage]
				*	Parameters:[Text Message in Variable Size]
				*	
				*/
				AccMessage=ECS_AccelerometerDriver*UnitsMessageSpectrum,

				/*	RESPONSE ACCELEROMETER VALUE
				*	Message:[respAccValue] 
				*	Parameters:[MagnetometerParameters::ReadData]	//6 bytes
				*	Send Magnetometers values to [Destination Address]
				*/
				respAccValue,


				/*	SEND ACCELEROMETER CONFIGURATION	
				*	Message:[setAccConfiguration]
				*	Parameters:[MagnetometerParameters::ConfigurationType]	//3 bytes
				*	Send Magnetometers values to [Destination Address]
				*/
				setAccConfiguration,
				/*	SEND ACCELEROMETER CONFIGURATION	
				*	Message:[sendAccConfiguration]
				*	Send Magnetometers values to [Destination Address]
				*/
				sendAccConfiguration,
				/*	READ ACCELEROMETER CONFIGURATION	
				*	Message:[readAccConfiguration]
				*	First Read Configuration from device then,
				*		Send Magnetometers values to [Destination Address]
				*/
				readAccConfiguration,
				/*	RESPONSE ACCELEROMETER CONFIGURATION
				*	Message:[respAccConfiguration] 
				*	Parameters:[MagnetometerParameters::ConfigurationType]	//3 bytes
				*	Send Magnetometers values to [Destination Address]
				*/
				respAccConfiguration,

			}Type; // End of Enum	

		}//End of namespace Messages

#ifdef _FECS_SYSTEM_

		typedef enum{
			RegAdd_DEVID		=0x00,	//	R
			RegAdd_THRESH_TAP	=0x1D,	//	R/W
			RegAdd_OFSX,				//	R/W
			RegAdd_OFSY,				//	R/W
			RegAdd_OFSZ,				//	R/W
			RegAdd_DUR,					//	R/W
			RegAdd_Latent,				//	R/W
			RegAdd_Window,				//	R/W
			RegAdd_THRESH_ACT,			//	R/W
			RegAdd_THRESH_INACT,		//	R/W
			RegAdd_TIME_INACT,			//	R/W
			RegAdd_ACT_INACT_CTL,		//	R/W
			RegAdd_THRESH_FF,			//	R/W
			RegAdd_TIME_FF,				//	R/W
			RegAdd_TAP_AXES,			//	R/W
			RegAdd_ACT_TAP_STATUS,		//	R
			RegAdd_BW_RATE,				//	R/W
			RegAdd_POWER_CTL,			//	R/W
			RegAdd_INT_ENABLE,			//	R/W
			RegAdd_INT_MAP,				//	R/W
			RegAdd_INT_SOURCE,			//	R
			RegAdd_DATA_FORMAT,			//	R/W
			RegAdd_DATAX0,				//	R
			RegAdd_DATAX1,				//	R
			RegAdd_DATAY0,				//	R
			RegAdd_DATAY1,				//	R
			RegAdd_DATAZ0,				//	R
			RegAdd_DATAZ1,				//	R
			RegAdd_FIFO_CTL,			//	R/W
			RegAdd_FIFO_STATUS			//	R
		}InternalRegisterAdresses;

		extern unsigned char deviceAddress;
#endif	//#ifdef _FECS_SYSTEM_

	}//End of namespace FECS_Drv_AccelerometerNS

#ifdef _FECS_SYSTEM_
	class FECS_Drv_AccelerometerClass:FECS_DriverClass{
	private:
		FECS_Drv_AccelerometerNS::Parameter::ConfigurationType* AccConf;
		static const unsigned char RegisterMap[];

	public:
		FECS_Drv_AccelerometerClass(void);
		~FECS_Drv_AccelerometerClass(void);

		//Configuration
		void setConfiguration(
			FECS_Drv_AccelerometerNS::Parameter::ConfigurationType);

		FECS_Drv_AccelerometerNS::Parameter::ConfigurationType 
			readConfiguration(void);	

		FECS_Drv_AccelerometerNS::Parameter::ConfigurationType 
			getConfiguration(void);	

		//Value
		FECS_Drv_AccelerometerNS::Parameter::ReadData 
			readValue(void);

	};
#endif	//#ifdef _FECS_SYSTEM_

}//End of namespace FECS_System

#endif //FECS_MAGNETOMETERCOMPONENT_H_
