/*
 * MPU_SystemManager.h
 *
 *  Created on: Oct 17, 2012
 *      Author: faruxx
 */

#ifndef SYSTEMMANAGER_H_
#define SYSTEMMANAGER_H_

#include "../Manager.h"

#include "../FECSManager/FECSManager.h"


namespace SmartFly{

class SystemManager:public ManagerClass{

protected:
		//MessageInterpreter Callable
		virtual void thRoutine_MesssageInterpreter(void);
		virtual void thRoutine_TimedActionInterpreter(void);

public:
	SystemManager();
	~SystemManager();


private:
	/*
	 * TO DO:
	 * Create other managers here
	 */
	MessengerClass* SM_Messenger;

	boost::shared_ptr<FECSManager> FECSManager_shrptr;

};

}


#endif /* SYSTEMMANAGER_H_ */
