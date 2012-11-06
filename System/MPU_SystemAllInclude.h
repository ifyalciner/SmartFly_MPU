/*
 * MPU_SystemAllInclude.h
 *
 *  Created on: Nov 5, 2012
 *      Author: faruxx
 */

#ifndef MPU_SYSTEMALLINCLUDE_H_
#define MPU_SYSTEMALLINCLUDE_H_

#include "main.h"

#include <exception>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include <sstream>
#include <queue>

//3.Party Libraries
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/tokenizer.hpp>

namespace SmartFly{
/*
 * List Of System Managers
 * This enumerated constants represent corresponding "Manager" in messaging
 * and also these are key ID's of Managers
 */
enum ManagerID{
	MPU_ID_NullManager=0,
	MPU_ID_SystemManager,
	MPU_ID_FlightMonitorManager,
	MPU_ID_FECSManager,
	MPU_ID_OutCommunicationLinkManager,
	MPU_ID_ImageProcessingManager,
};


class SmartFlyClass;

class SF_SystemVariables{
public:
	/*FECS_USB_SerialPort*/
	std::string FECS_USB_SerialPort;
	int			FECS_USB_SerialSpeed;

	/*FECS_Accelerometer*/
	static const int	FECS_Accelerometer_DataArraySize=20;
	static const std::string	FECS_Accelerometer_NameArray[FECS_Accelerometer_DataArraySize];
	int			FECS_Accelerometer_DataArray[FECS_Accelerometer_DataArraySize];
};




extern SF_SystemVariables SmartFly_SystemVariable;


}

#endif /* MPU_SYSTEMALLINCLUDE_H_ */
