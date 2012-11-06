#ifndef FECS_DRIVER_H_
#define FECS_DRIVER_H_

#include "../FECS_System.h"

namespace FECS_System{
	
	namespace FECS_DriverNS{
		typedef unsigned int timeMS;
	}

	class FECS_DriverClass{
	public:
		FECS_DriverClass(void);
		~FECS_DriverClass(void);
	/*
	private:
		virtual void	SetupHardware(void);
	public:
		virtual void	PowerTurnTo(BOOL a);
		virtual void	Reset(void);
	*/

	};//End of class FECS_DriverClass

}//End of namespace FECS_System




#endif	//FECS_DRIVER_H_
