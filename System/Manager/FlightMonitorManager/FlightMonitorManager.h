/*
 * FlightMonitorManager.h
 *
 *  Created on: Oct 25, 2012
 *      Author: faruxx
 */

#ifndef FLIGHTMONITORMANAGER_H_
#define FLIGHTMONITORMANAGER_H_

#include "../Manager.h"

namespace SmartFly {

class FlightMonitorManager: public SmartFly::ManagerClass {
protected:
	//MessageInterpreter Callable
	virtual void thRoutine_MesssageInterpreter(void);
	virtual void thRoutine_TimedActionInterpreter(void);
public:
	FlightMonitorManager();
	virtual ~FlightMonitorManager();
};

} /* namespace SmartFly */
#endif /* FLIGHTMONITORMANAGER_H_ */
