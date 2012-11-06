/*
 * MPU_System.h
 *
 *  Created on: Oct 19, 2012
 *      Author: faruxx
 */

#ifndef MPU_SYSTEM_H_
#define MPU_SYSTEM_H_

#include "main.h"
#include "MPU_SystemAllInclude.h"
#include "Manager/SystemManager/SystemManager.h"


namespace SmartFly{



class SmartFlyClass{
private:
	SystemManager* SystemManagerInstance;
	boost::shared_ptr<SystemManager> SystemManager_shptr;
public:
	SmartFlyClass();
	~SmartFlyClass();

	void init(void);
	void readConfigFile(void);
};



}// End of namespace MPU_System{



#endif /* SYSTEM_H_ */
