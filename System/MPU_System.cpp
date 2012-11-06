/*
 * MPU_System.cpp
 *
 *  Created on: Nov 3, 2012
 *      Author: faruxx
 */

#include "MPU_System.h"
#include "Manager/SystemManager/SystemManager.h"

namespace SmartFly{

/*
 * SmartFly Global Variable
 */

SF_SystemVariables SmartFly_SystemVariable;

#if 0
void SF_SystemVariables::setFecsUsbSerialPort(std::string fecsUsbSerialPort) {
	FECS_USB_SerialPort = fecsUsbSerialPort;
}

std::string SF_SystemVariables::getFecsUsbSerialPort() const
{
	return (FECS_USB_SerialPort);
}
#endif


SmartFlyClass::SmartFlyClass(){
	std::cout<<"SmartFly Automated Flight Project"<<std::endl
			<<"10.2013"<<std::endl
			<<"Fatih University, Robotics Club"<<std::endl
			<<"www.smartflyproject.com"<<std::endl;

	std::cout<<"*---------------------------------------*"<<std::endl;
	pid_t mypid;
	mypid=getpid();
	std::cout<<"SmartFly Program PID is "<<mypid<<std::endl;
	std::cout<<"*---------------------------------------*"<<std::endl;
	char cCurrentPath[FILENAME_MAX];

	if (!getcwd(cCurrentPath, sizeof(cCurrentPath))){
		std::cout<<"Error: Couldn't Read Current Working Directory"<<std::endl;
		return;
	}

	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

	printf ("The current working directory is %s \n", cCurrentPath);
	std::cout<<"*---------------------------------------*"<<std::endl;

	/*
	 *	Configuration File Read Operations
	 */

	readConfigFile();
}

SmartFlyClass::~SmartFlyClass(){

}

void SmartFlyClass::init(void){
	SystemManagerInstance = new SystemManager;
	SystemManager_shptr.reset(SystemManagerInstance);
}

void SmartFlyClass::readConfigFile(void){
	std::cout<<"Loading System Variables from \"configuration.conf file\""<<std::endl;
	std::ifstream confFile("configuration.conf",std::ifstream::in);
	if(!confFile.is_open()){
		std::cout<<"Error: Could not open \"configuration file\""<<std::endl;
		return;
	}
	else{
		std::cout<<"\"configuration file\" opened"<<std::endl;
	}

	char inLineData_[512];
	std::string inLineString;
	typedef boost::tokenizer<boost::char_separator<char> > tokenize;
	boost::char_separator<char> sep("\n\t\v ");
	tokenize tok(inLineString, sep);

	while(confFile.good()){
		confFile.getline(inLineData_,512,'\n');
		inLineString=(std::string)inLineData_;
		//std::cout<<inLineString<<std::endl;

		tok.assign(inLineString,sep);
		for(tokenize::iterator beg=tok.begin(); beg!=tok.end();++beg){
			if(beg.current_token()[0]=='#')
				break;

			if(strcmp(beg.current_token().c_str(),"FECS_USB_SerialPort")==0){
				++beg;
				SmartFly_SystemVariable.FECS_USB_SerialPort=beg.current_token();
				std::cout<<"FECS_USB_SerialPort parameter set as: "<<SmartFly_SystemVariable.FECS_USB_SerialPort<<'\n';

				++beg;
				SmartFly_SystemVariable.FECS_USB_SerialSpeed=std::atoi(beg.current_token().c_str());
				std::cout<<"FECS_USB_SerialSpeed parameter set as: "<<SmartFly_SystemVariable.FECS_USB_SerialSpeed<<'\n';
			}
			else if(strcmp(beg.current_token().c_str(),"FECS_Accelerometer")==0){
				for(int i=0;i<SmartFly_SystemVariable.FECS_Accelerometer_DataArraySize;i++){
					++beg;
					SmartFly_SystemVariable.FECS_Accelerometer_DataArray[i]=std::atoi(beg.current_token().c_str());
					std::cout<<SmartFly_SystemVariable.FECS_Accelerometer_NameArray[i]<<" parameter set as: "<<SmartFly_SystemVariable.FECS_Accelerometer_DataArray[i]<<'\n';
				}
			}

		}
	}
}

}

