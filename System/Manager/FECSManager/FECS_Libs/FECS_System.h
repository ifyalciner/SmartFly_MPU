/*

	System Header file contains:
 *Toggle LED Function


 *System Part Addresses
 */


#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#if 0
#define _FECS_SYSTEM_
#else
#define _MCU_SYSTEM_
#define BOOL bool
#define NULL 0
#define TRUE true
#define FALSE false
#include "../../../MPU_SystemAllInclude.h"
#endif

#ifdef _FECS_SYSTEM_
#include "../inc/allInclude.h"
#endif

namespace FECS_System{

#ifdef _FECS_SYSTEM_
/*
		Function:		ToogleLED(void)
		Parameters:		void
		Explanation:	*Every Manager Function Uses ToggleLED function to physically indicate that system is functioning.
 *This function checks the state of the pin then sets or clears pin P0.22. This pin is connected to
						Led on LPCXpresso1769 board.
		Returns:		void
 */
static void ToggleLED(void){
	unsigned long ulLEDState;

	/* Obtain the current P0 state. */
	ulLEDState = LPC_GPIO0->FIOPIN;

	/* Turn the LED off if it was on, and on if it was off. */
	LPC_GPIO0->FIOCLR = ulLEDState & (1 << 22);
	LPC_GPIO0->FIOSET = ((~ulLEDState) & (1 << 22));
}

#endif

//System Explanations and Required Information for all system units

/*
 * Below PartType and PartAddress enum type provides a Addressing mechanism for FECS system
 */

//Each Part can have at most "UnitsMessageSpectrum" of messages
const unsigned short UnitsMessageSpectrum	= 200;

typedef enum{
	//Outside
	EMainSystem=0,				//Connected Computer
	//Inside
	ECS_SystemManager,			//System Manager Unit
	ECS_SensorManager,			//Controller of all Sensor Units

	ECS_FlightMotorDriver,		//Flight Motor Control

	ECS_MagnetometerDriver,		//Magnetometer is sub unit of IMU
	ECS_AccelerometerDriver,	//Accelerometer is sub unit of IMU
	ECS_GyroscopeDriver,		//Gyroscope is sub unit of IMU
	ECS_UltraSonicSensorDriver,	//Sonar Distance Sensor Unit
	ECS_BarometerDriver,		//Barometer Sensor Driver
	ECS_LiPoFuelGaugeDriver,	//LiPo Fuel Gauger Driver
	ECS_GPSDriver,				//GPS Driver

}PartType,PartAddress;// End of ESystemParts

}//End of namespace FECS_System
#endif //End of _SYSTEM_H_
