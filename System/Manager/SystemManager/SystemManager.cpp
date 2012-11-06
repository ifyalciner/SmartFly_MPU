/*
 * MPU_SystemManager.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: faruxx
 */

#include "SystemManager.h"

namespace SmartFly{


/* Thread Message Interpreter Procedure	*/
void SystemManager::thRoutine_MesssageInterpreter(void){
#ifdef __DEBUG_
	std::cout<<"SystemManager::thRoutine_MesssageInterpreter(void)"<<std::endl;
#endif


	boost::unique_lock<boost::mutex> lock(mut_postBox);

	while(true){

		//Continue to wait until postBox.size() is bigger than 0
		while(postBox.empty()){
			//Wait until conditional variable condv_messageAvailable is notified
			condv_messageAvailable.wait(lock);
		}

		//Retrieve Message from "postBox"
		MessageClass procMessage=postBox.front();

		//Process Message Here
		switch(procMessage.getDestination()){
		case MPU_ID_SystemManager:{

		}
		break;

		case MPU_ID_OutCommunicationLinkManager:
		case MPU_ID_ImageProcessingManager:
		case MPU_ID_FECSManager:
		case MPU_ID_FlightMonitorManager:{
			//Redirect Messages Here

		}
		break;
		}

		//Remove Message From "postBox"
		postBox.pop();
	}
}

/* Thread Timed Action Interpreter Procedure	*/
void SystemManager::thRoutine_TimedActionInterpreter(){
#ifdef __DEBUG_
	std::cout<<"SystemManager::thRoutine_TimedActionInterpreter()"<<std::endl;
#endif

}

SystemManager::SystemManager():SmartFly::ManagerClass(){
#ifdef __DEBUG_
	std::cout<<"SystemManager::SystemManager():SmartFly::ManagerClass()"<<std::endl;
#endif

	try{
		SM_Messenger= new MessengerClass(this);

		boost::shared_ptr<MessengerClass> tempMessenger(SM_Messenger);
		myMessenger= tempMessenger;



		FECSManager*	FECS_Manager_Instance_=new FECSManager();
		FECSManager_shrptr.reset(FECS_Manager_Instance_);
	}catch(std::exception& e){
		std::cout<<"Error in SystemManager() Constructor, while object creation"<<std::endl;
	}


}

SystemManager::~SystemManager() {
#ifdef __DEBUG_
	std::cout<<"SystemManager::~SystemManager()"<<std::endl;
#endif
}

}//End of namespace SmartFly

