/*
 * FlightMonitorManager.cpp
 *
 *  Created on: Oct 25, 2012
 *      Author: faruxx
 */

#include "FlightMonitorManager.h"

namespace SmartFly {

/* Thread Message Interpreter Procedure	*/
void FlightMonitorManager::thRoutine_MesssageInterpreter(void){
#ifdef __DEBUG_
	std::cout<<"MPU_System::FlightMonitorManager::MI_Operation()"<<std::endl;
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
		if(procMessage.getDestination()==MPU_ID_FlightMonitorManager){


		}

		//Remove Message From "postBox"
		postBox.pop();
	}
}

/* Thread Timed Action Interpreter Procedure	*/
void FlightMonitorManager::thRoutine_TimedActionInterpreter(){
#ifdef __DEBUG_
	std::cout<<"MPU_System::FlightMonitorManager::TAI_Operation()"<<std::endl;
#endif

}

FlightMonitorManager::FlightMonitorManager() {
	// TODO Auto-generated constructor stub

}

FlightMonitorManager::~FlightMonitorManager() {
	// TODO Auto-generated destructor stub
}

} /* namespace SmartFly */
