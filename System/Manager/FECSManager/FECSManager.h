/*
 * FECSManager.h
 *
 *  Created on: Oct 30, 2012
 *      Author: faruxx
 */

#ifndef FECSMANAGER_H_
#define FECSMANAGER_H_

#include "../Manager.h"
#include "Serial/BufferedAsyncSerial.h"
#include "FECS_Libs/FECS_System.h"
#include "FECS_Libs/FECS_Message.h"

#if 0
#include "../../Linux/libusb/libusb.h"
#endif


namespace SmartFly {


class FECSManager: public SmartFly::ManagerClass {

public:

protected:
	virtual void thRoutine_MesssageInterpreter(void);
	virtual void thRoutine_TimedActionInterpreter(void);

public:
	FECSManager();
	virtual ~FECSManager();

private:
	boost::shared_ptr<BufferedAsyncSerial> CommunicationDevice_shrptr;

	void initFECSComponents(void);

/*
 * USB Parameters and Funtions
 */
private:

#if 0
#define	FECS_USB_VendorID	0xFFFF
#define	FECS_USB_ProductID	0x0005

	libusb_context *FECS_libusb_context; //a libusb session
	libusb_device **FECS_devs_pptr; //pointer to pointer of device, used to retrieve a list of devices
	libusb_device_handle * FECS_devh_ptr;

#define FECS_LIBUSB_DEBUG_LEVEL	3

	void FECS_libusb_printdev(libusb_device *dev);

	void FECS_libusb_opendevice(void);
#endif



};

} /* namespace SmartFly */
#endif /* FECSMANAGER_H_ */
