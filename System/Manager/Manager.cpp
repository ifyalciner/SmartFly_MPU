
#include "Manager.h"

namespace SmartFly{

void ManagerClass::thRoutine_MesssageInterpreter(){
#ifdef __DEBUG_
	std::cout<<"MPU_System::MPU_Manager::MICallable::operator ()"<<std::endl;
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

		//Remove Message From "postBox"
		postBox.pop();
	}


}

void ManagerClass::thRoutine_TimedActionInterpreter(){
#ifdef __DEBUG_
	std::cout<<"MPU_System::MPU_Manager::TAICallable::operator ()"<<std::endl;
#endif

}


ManagerClass::ManagerClass(){
#ifdef __DEBUG_
	std::cout<<"MPU_System::MPU_Manager::MPU_Manager()"<<std::endl;
#endif

	this->th_messageInterpreter 		= boost::thread(boost::bind(&ManagerClass::thRoutine_MesssageInterpreter, this));
	//th_messageInterpreter.join();

	this->th_timedActionInterpreter 	= boost::thread(boost::bind(&ManagerClass::thRoutine_TimedActionInterpreter, this));
	//th_timedActionInterpreter.join();

	this->myMessenger.reset();
}

//Destructor
ManagerClass::~ManagerClass() {
#ifdef __DEBUG_
	std::cout<<"MPU_System::MPU_Manager::~MPU_Manager()"<<std::endl;
#endif

}

bool ManagerClass::pushMessage(MessageClass mess_){
	try{
		boost::unique_lock<boost::mutex> lock(mut_postBox);
	}
	catch(...){
		return(false);
	}
	postBox.push(mess_);
	condv_messageAvailable.notify_one();
	return (true);
}

/*
 *
 * MESSENGER CLASS METHODS
 *
 */

MessengerClass::MessengerClass(ManagerClass* mainManager_){
#ifdef __DEBUG_
	std::cout<<"MessengerClass::MessengerClass(ManagerClass* mainManager_)"<<std::endl;
#endif
	controllingManager=mainManager_;
}
MessengerClass::~MessengerClass(){
	controllingManager=NULL;
}

bool MessengerClass::pushToMessenger(MessageClass mess_){
	return (controllingManager->pushMessage(mess_));
}


}//End of namespace SmartFly


