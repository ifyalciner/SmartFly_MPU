#ifndef MANAGER_H_
#define MANAGER_H_

//Project Libraries
#include "../MPU_SystemAllInclude.h"
#include "Message.h"

#define MPU_ManagerDefaultPostBoxSize	100


namespace SmartFly{

class MessengerClass;

class ManagerClass{
protected:

	virtual void thRoutine_MesssageInterpreter(void);
	virtual void thRoutine_TimedActionInterpreter(void);

public:
	ManagerClass();
	ManagerClass(boost::shared_ptr<MessengerClass> messenger_);
	virtual ~ManagerClass();

	virtual bool pushMessage(MessageClass mess_);

protected:
	boost::thread th_messageInterpreter;
	boost::thread th_timedActionInterpreter;

	//PostBox related variables
	boost::mutex 				mut_postBox;
	boost::condition_variable	condv_messageAvailable;
	std::queue<MessageClass>	postBox;

	//Every manager has a Messenger to post its message to the its supermanager
	boost::shared_ptr<MessengerClass> myMessenger;

};//End of class MPU_Manager



/*
 * MessengerClass
 * System has star topology where in the middle there is supermanager
 * each submanager has a messenger to deliver its message to the supermanager
 * where supermanager either processes message directly by itself or redirects to
 * other managers
 *
 * MessengerClass is a wrapper class of supermanagers one function:pushMessage
 * so that submanagers can send their messages to supermanager while cannot
 * reach other methods of supermanager.
 */
class MessengerClass{
public:
	MessengerClass(){};
	MessengerClass(ManagerClass* mainManager_);
	~MessengerClass();

	bool pushToMessenger(MessageClass mess_);

private:
	ManagerClass* controllingManager;

};	//class MessengerClass{

}//End of namespace MPU_System


#endif /* MANAGER_H_ */

