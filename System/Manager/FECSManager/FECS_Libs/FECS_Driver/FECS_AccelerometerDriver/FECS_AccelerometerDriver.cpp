#include "FECS_AccelerometerDriver.h"

namespace FECS_System{
	namespace FECS_Drv_AccelerometerNS{

#ifdef _FECS_SYSTEM_
		//SDO pin on chip is connected to ground. Which cause address to change from 0x3A to 0x53
		unsigned char deviceAddress	=	0xA6;
#endif		
		
		namespace Parameter{		

			/************************************************************************	 
			*		ACCELEROMETER DATA-XYZ TYPE
			*/

			/*	Specific to Message: respMagValue 
			*	Parameter Size 
			*	XYZ -> 48 bit -> 6 bytes
			*	ACT_TAP_STATUS -> 8 bits -> 1 byte
			*	InterruptSource -> 8 bits -> 1 byte
			*	FIFOStatus		-> 8 bits -> 1 byte
			*	Total : 9 Bytes
			*/	
			const short ReadData::MessageParameterSize=9;

			ReadData::ReadData(short x_,short y_,short z_,unsigned char Act_Tap_Status_,unsigned char InterruptSource_,unsigned char FIFOStatus_){
				MessageParameter=new char[MessageParameterSize];
				setX((x_>>8)&0xFF,x_&0xFF);
				setY((y_>>8)&0xFF,y_&0xFF);
				setZ((z_>>8)&0xFF,z_&0xFF);
				setActive_Tap_Status(Act_Tap_Status_);
				setInterruptSource(InterruptSource_);
				setFIFOStatus(FIFOStatus_);
			}
			ReadData::~ReadData(){
				delete [] MessageParameter;
				MessageParameter=NULL;
			}
			void ReadData::setX(unsigned char MSB,unsigned char LSB){
				MessageParameter[0]=LSB;
				MessageParameter[1]=MSB;
			}
			short ReadData::getX(void){
				return (MessageParameter[1]<<8)|MessageParameter[0];
			}
			void ReadData::setY(unsigned char MSB,unsigned char LSB){
				MessageParameter[2]=LSB;
				MessageParameter[3]=MSB;
			}
			short ReadData::getY(void){
				return (MessageParameter[3]<<8)|MessageParameter[2];
			}
			void ReadData::setZ(unsigned char MSB,unsigned char LSB){
				MessageParameter[4]=LSB;
				MessageParameter[5]=MSB;
			}
			short ReadData::getZ(void){
				return (MessageParameter[5]<<8)|MessageParameter[4];
			}			
			/*--------------------------------------------------------------------*/
			/*	ACT_TAP_STATUS

				D0	:	TAPZ Source
				D1	:	TAPY Source
				D2	:	TAPX Source

				D3	:	ASleep

				D4	:	ACT_Z Source
				D5	:	ACT_Y Source
				D6	:	ACT_X Source		

				*/
			void ReadData::setActive_Tap_Status(unsigned char status_){
				MessageParameter[6]=status_;
			}
			unsigned char ReadData::getActive_Tap_Status(void){
				return MessageParameter[6];
			}
			BOOL ReadData::is_ACTX_Event(void){
				return (MessageParameter[6] & 0x40) > 0 ? TRUE : FALSE;
			}
			BOOL ReadData::is_ACTY_Event(void){
				return (MessageParameter[6] & 0x20) > 0 ? TRUE : FALSE;
			}
			BOOL ReadData::is_ACTZ_Event(void){
				return (MessageParameter[6] & 0x10) > 0 ? TRUE : FALSE;
			}
			BOOL ReadData::is_Asleep(void){
				return (MessageParameter[6] & 0x08) > 0 ? TRUE : FALSE;
			}
			BOOL ReadData::is_TAPX_Event(void){
				return (MessageParameter[6] & 0x04) > 0 ? TRUE : FALSE;
			}
			BOOL ReadData::is_TAPY_Event(void){
				return (MessageParameter[6] & 0x02) > 0 ? TRUE : FALSE;
			}
			BOOL ReadData::is_TAPZ_Event(void){
				return (MessageParameter[6] & 0x01) > 0 ? TRUE : FALSE;
			}
			/*-------------------------------------------------------------------------*/
			/*	INT_SOURCE
				D0:Overrun
				D1:Watermark
				D2:FREE_FALL
				D3:Inactivity
				D4:Activity
				D5:DOUBLE_TAP
				D6:SINGLE_TAP
				D7:DATA_READY
				*/
			void ReadData::setInterruptSource(unsigned char status_){
				MessageParameter[7]=status_;
			}
			unsigned char ReadData::getInterruptSource(void){
				return MessageParameter[7];
			}
			BOOL ReadData::is_Overrun_INT(void){
				return (MessageParameter[7] & 0x01) > 0 ? TRUE : FALSE;
			}
			BOOL ReadData::is_Watermark_INT(void){
				return (MessageParameter[7] & 0x02) > 0 ? TRUE : FALSE;
			}
			BOOL ReadData::is_FreeFall_INT(void){
				return (MessageParameter[7] & 0x04) > 0 ? TRUE : FALSE;
			}
			BOOL ReadData::is_Inactivity_INT(void){
				return (MessageParameter[7] & 0x08) > 0 ? TRUE : FALSE;
			}
			BOOL ReadData::is_Activity_INT(void){
				return (MessageParameter[7] & 0x10) > 0 ? TRUE : FALSE;
			}
			BOOL ReadData::is_DoubleTap_INT(void){
				return (MessageParameter[7] & 0x20) > 0 ? TRUE : FALSE;
			}
			BOOL ReadData::is_SingleTap_INT(void){
				return (MessageParameter[7] & 0x40) > 0 ? TRUE : FALSE;
			}
			BOOL ReadData::is_DataReady_INT(void){
				return (MessageParameter[7] & 0x80) > 0 ? TRUE : FALSE;
			}
			/*------------------------------------------------------------------------------*/
			/*	FIFO_STATUS

				D6,D5,D4,D3,D2,D1,D0	:	Entries
				D7						:	FIFO_TRIG				

				FIFO_TRIG Bit
				A 1 in the FIFO_TRIG bit corresponds to a trigger event occurring, and a 0 means that a
				FIFO trigger event has not occurred.

				Entries Bits
				These bits report how many data values are stored in FIFO. Access to collect the data
				from FIFO is provided through the DATAX, DATAY, and DATAZ registers. FIFO reads must
				be done in burst or multiple-byte mode because each FIFO level is cleared after any read
				(single- or multiple-byte) of FIFO. FIFO stores a maximum of 32 entries, which equates
				to a maximum of 33 entries available at any given time because an additional entry is 
				available at the output filter of the device.
				*/
			void ReadData::setFIFOStatus(unsigned char status_){
				MessageParameter[8]=status_;
			}
			unsigned char ReadData::getFIFOStatus(void){
				return MessageParameter[8];
			}
			unsigned char ReadData::getFIFOCount(void){
				return (unsigned char)(MessageParameter[8] & 0x3F);
			}
			BOOL ReadData::is_FIFOTrigger_Event(void){
				return (MessageParameter[8] & 0x80) > 0 ? TRUE : FALSE;
			}

			/*-----------------------------------------------------------------------------*/
			const char* ReadData::getAsMessageParameter(void){
				//6 because size of X,Y,Z parameters are 6 bytes
				//Conversions are done in setX functions
				return MessageParameter;
			}
			void ReadData::setAsMessageParameter(const char* in_){
				memcpy(MessageParameter,in_,MessageParameterSize);
			}
			ReadData&	ReadData::operator=(const ReadData& in_){
				if (this == &in_)      // Same object?
					return *this;
				memcpy(MessageParameter,in_.MessageParameter,MessageParameterSize);
				return *this;
			}


			/************************************************************************	 
			*		ACCELEROMETER CONFIGURATION-MODE TYPE
			*/


			const short ConfigurationType::MessageParameterSize=20;

			
			ConfigurationType::ConfigurationType(void){
				MessageParameter=new char[MessageParameterSize];
				for(int i=0;i<MessageParameterSize;i++)
					MessageParameter[i]=0;
			}
			ConfigurationType::~ConfigurationType(void){
				delete [] MessageParameter;
				MessageParameter=NULL;
			}
			
			void ConfigurationType::setTapConf(
				unsigned char threshold_,
				unsigned char duration_,
				unsigned char latency_,
				unsigned char window_,
				Tap_Axes_Type axes_conf_
				)
			{
				MessageParameter[THRESH_TAP]	=	threshold_;
				MessageParameter[DUR]			=	duration_;
				MessageParameter[Latent]		=	latency_;
				MessageParameter[Window]		=	window_;
				MessageParameter[TAP_AXES]		=	axes_conf_;
			}

			void ConfigurationType::setAxisOffsetConf(
				signed char x_,
				signed char y_,
				signed char z_
				)
			{
				MessageParameter[OFSX]=x_;
				MessageParameter[OFSY]=y_;
				MessageParameter[OFSZ]=z_;
			}

			void ConfigurationType::setActInactConf(
				unsigned char act_treshold_,
				unsigned char inact_treshold_,
				unsigned char inact_time_,
				Act_Inact_Control_Type act_inact_cont_
				)
			{
				MessageParameter[THRESH_ACT]	=	act_treshold_;
				MessageParameter[THRESH_INACT]	=	inact_treshold_;
				MessageParameter[TIME_INCACT]	=	inact_time_;
				MessageParameter[ACT_INCACT_CTL]=	act_inact_cont_;				
			}

			void ConfigurationType::setFreeFallConf(
				unsigned char treshold_,
				unsigned char time_
				)
			{
				MessageParameter[THRESH_FF]	=	treshold_;
				MessageParameter[TIME_FF]	=	time_;
			}

			void ConfigurationType::setOperationConf(
				Bandwidth_Type		bandwidth_,
				Data_Format_Type	dataFormat_,
				FIFO_Control_Type	FIFO_Cont_,
				Power_Control_Type	Power_Cont_				
				)
			{
				MessageParameter[BW_RATE]		=	bandwidth_;
				MessageParameter[DATA_FORMAT]	=	dataFormat_;
				MessageParameter[FIFO_CTL]		=	FIFO_Cont_;
				MessageParameter[POWER_CTL]		=	Power_Cont_;
			}

			void ConfigurationType::setInterruptControl(
				Int_Enable_Type		Int_Enable_,
				Int_Map_Type		Int_Map_
				)
			{
				MessageParameter[INT_ENABLE]	=	Int_Enable_;
				MessageParameter[INT_MAP]		=	Int_Map_;
			}

			unsigned char	ConfigurationType::getControlValue(ConfRegMessID valueAddress){
				return MessageParameter[valueAddress];
			}
			const char* ConfigurationType::getAsMessageParameter(void){
				return MessageParameter;
			}
			void ConfigurationType::setAsMessageParameter(const char* in_){
				memcpy(MessageParameter,in_,MessageParameterSize);
			}
			ConfigurationType&	ConfigurationType::operator=(const ConfigurationType& in_){
				if (this == &in_)      // Same object?
					return *this;
				memcpy(MessageParameter,in_.MessageParameter,MessageParameterSize);
				return *this;
			}

			

			
		}//End of namespace Parameters
	}//End of namespace FECS_Drv_AccelerometerNS


#ifdef _FECS_SYSTEM_
	/*
	Address and id mapping of 

	ConfRegMessID	&  InternalRegisterAdresses

	*/
	const unsigned char FECS_Drv_AccelerometerClass::RegisterMap[]={
		FECS_Drv_AccelerometerNS::RegAdd_THRESH_TAP,
		FECS_Drv_AccelerometerNS::RegAdd_DUR,
		FECS_Drv_AccelerometerNS::RegAdd_Latent,
		FECS_Drv_AccelerometerNS::RegAdd_Window,
		FECS_Drv_AccelerometerNS::RegAdd_TAP_AXES,	

		FECS_Drv_AccelerometerNS::RegAdd_OFSX,
		FECS_Drv_AccelerometerNS::RegAdd_OFSY,
		FECS_Drv_AccelerometerNS::RegAdd_OFSZ,

		FECS_Drv_AccelerometerNS::RegAdd_THRESH_ACT,	
		FECS_Drv_AccelerometerNS::RegAdd_THRESH_INACT,		
		FECS_Drv_AccelerometerNS::RegAdd_TIME_INACT,
		FECS_Drv_AccelerometerNS::RegAdd_ACT_INACT_CTL,

		FECS_Drv_AccelerometerNS::RegAdd_THRESH_FF,	
		FECS_Drv_AccelerometerNS::RegAdd_TIME_FF,	

		FECS_Drv_AccelerometerNS::RegAdd_INT_ENABLE,		
		FECS_Drv_AccelerometerNS::RegAdd_INT_MAP,

		FECS_Drv_AccelerometerNS::RegAdd_BW_RATE,
		FECS_Drv_AccelerometerNS::RegAdd_POWER_CTL,
		FECS_Drv_AccelerometerNS::RegAdd_DATA_FORMAT,				
		FECS_Drv_AccelerometerNS::RegAdd_FIFO_CTL
	};

	FECS_Drv_AccelerometerClass::FECS_Drv_AccelerometerClass(void){
		using namespace FECS_Drv_AccelerometerNS;
		using namespace Parameter;

		AccConf=new ConfigurationType;

		FECS_Per_I2CClass::I2C_Init(ACC_USED_I2C_PORT);

	
		setConfiguration(*AccConf);
	}

	FECS_Drv_AccelerometerClass::~FECS_Drv_AccelerometerClass(void){
		delete AccConf;
		AccConf=NULL;
	}
	
	void FECS_Drv_AccelerometerClass::setConfiguration(
		FECS_Drv_AccelerometerNS::Parameter::ConfigurationType conf_)
	{
		using namespace FECS_Drv_AccelerometerNS;
		using namespace Parameter;

		char temp[2];
		for(int i=0;i<ConfigurationType::MessageParameterSize;i++){
			if(conf_.MessageParameter[i]!=AccConf->MessageParameter[i]){
				temp[0]=RegisterMap[i];
				temp[1]=conf_.MessageParameter[i];
				FECS_Per_I2CClass::I2C_Write(ACC_USED_I2C_PORT,FECS_Drv_AccelerometerNS::deviceAddress,2,temp);
			}
		}
		*AccConf=conf_;
	}

	FECS_Drv_AccelerometerNS::Parameter::ConfigurationType 
		FECS_Drv_AccelerometerClass::readConfiguration(void)
	{
		using namespace FECS_Drv_AccelerometerNS;
		using namespace Parameter;
		char temp;
		char result;

		for(int i=0;i<ConfigurationType::MessageParameterSize;i++){
			temp=RegisterMap[i];
			FECS_Per_I2CClass::I2C_Read(ACC_USED_I2C_PORT,FECS_Drv_AccelerometerNS::deviceAddress,1,&temp,1,&result);
			AccConf->MessageParameter[i]=result;
		}
		
		return *AccConf;
	}

	FECS_Drv_AccelerometerNS::Parameter::ConfigurationType 
		FECS_Drv_AccelerometerClass::getConfiguration(void)
	{
		using namespace FECS_Drv_AccelerometerNS;
		using namespace Parameter;

		return *AccConf;
	}

	FECS_Drv_AccelerometerNS::Parameter::ReadData 
		FECS_Drv_AccelerometerClass::readValue(void)
	{
		using namespace FECS_Drv_AccelerometerNS;
		using namespace Parameter;

		FECS_Drv_AccelerometerNS::Parameter::ReadData	res_;

		char AddrTemp=RegAdd_DATAX0;//First Address of data registers
		char result[6];
		FECS_Per_I2CClass::I2C_Read(ACC_USED_I2C_PORT,FECS_Drv_AccelerometerNS::deviceAddress,1,&AddrTemp,6,result);
		/*
		The output data is twos complement, with DATAx0 as the least significant byte and
		DATAx1 as the most significant byte, where x represent X, Y, or Z.
		*/
		res_.setX(result[1],result[0]);
		res_.setY(result[3],result[2]);
		res_.setZ(result[5],result[3]);

		AddrTemp=RegAdd_ACT_TAP_STATUS;//First Address of data registers
		FECS_Per_I2CClass::I2C_Read(ACC_USED_I2C_PORT,FECS_Drv_AccelerometerNS::deviceAddress,1,&AddrTemp,1,result);

		res_.setActive_Tap_Status(result[0]);

		AddrTemp=RegAdd_INT_SOURCE;//First Address of data registers
		FECS_Per_I2CClass::I2C_Read(ACC_USED_I2C_PORT,FECS_Drv_AccelerometerNS::deviceAddress,1,&AddrTemp,1,result);

		res_.setInterruptSource(result[0]);

		AddrTemp=RegAdd_FIFO_STATUS;//First Address of data registers
		FECS_Per_I2CClass::I2C_Read(ACC_USED_I2C_PORT,FECS_Drv_AccelerometerNS::deviceAddress,1,&AddrTemp,1,result);

		res_.setFIFOStatus(result[0]);

		return res_;
	}

#endif	//#ifdef _FECS_SYSTEM_

}//End of namespace FECS_System


