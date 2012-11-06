/*
 * FECSManager.cpp
 *
 *  Created on: Oct 30, 2012
 *      Author: faruxx
 */

#include "FECSManager.h"

namespace SmartFly {

/* Thread Message Interpreter Procedure	*/
void FECSManager::thRoutine_MesssageInterpreter(void){
#ifdef __DEBUG_
	std::cout<<"FECSManager::thRoutine_MesssageInterpreter(void)"<<std::endl;
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
		if(procMessage.getDestination()==MPU_ID_FECSManager){
			//Process Messages here
		}
		//Remove Message From "postBox"
		postBox.pop();
	}
}

/* Thread Timed Action Interpreter Procedure	*/
void FECSManager::thRoutine_TimedActionInterpreter(){
#ifdef __DEBUG_
	std::cout<<"FECSManager::thRoutine_TimedActionInterpreter()"<<std::endl;
#endif

	while(true){
		bool result;

		FECS_System::FECS_EnvelopeClass* messageFromFECS;
		FECS_System::FECS_MessageNS::constructMessageStatusType incommingMessageStatus;

		FECS_System::FECS_MessageNS::MesgEnvParType charBuffer;
		size_t readAmount=CommunicationDevice_shrptr->read(&charBuffer,1);
		if(readAmount==1){
			result=FECS_System::FECS_EnvelopeClass::setMessagePartsReceived(charBuffer,&incommingMessageStatus,&messageFromFECS);
			if(result==true){

			}
		}




	}




}

FECSManager::FECSManager(){
#ifdef __DEBUG_
	std::cout<<"FECSManager::FECSManager()"<<std::endl;
#endif

	try{
		BufferedAsyncSerial* CommunicationDevice_=new BufferedAsyncSerial(
				SmartFly_SystemVariable.FECS_USB_SerialPort,
				SmartFly_SystemVariable.FECS_USB_SerialSpeed);

		CommunicationDevice_shrptr.reset(CommunicationDevice_);
		std::cout<<"Communication device opened"<<std::endl;

	} catch (boost::system::system_error &e)
	{
		boost::system::error_code ec = e.code();
		std::cout <<"Error "<<ec.category().name()<<" "<<ec.value()<<": "<<ec.message()<< std::endl;
		throw;
	}

#if 0
	FECS_libusb_context=NULL; //a libusb session
	FECS_devh_ptr=NULL;

	/*
	 * Init USB Procedures
	 */

	int r; //for return values

	r = libusb_init(&FECS_libusb_context); //initialize a library session
	switch(r){
	case 0:
		std::cout<<"libusb_init(...) successful"<<std::endl;
		break;
	default:
		std::cout<<"libusb_init(...) failed:	LIBUSB_ERROR"<<r<<std::endl; //there was an error
		break;
	}

	libusb_set_debug(FECS_libusb_context, FECS_LIBUSB_DEBUG_LEVEL); //set verbosity level to 3, as suggested in the documentation
	std::cout<<"libusb_set_debug(...) successful"<<std::endl;

	ssize_t cnt; //holding number of devices in list
	cnt = libusb_get_device_list(FECS_libusb_context, &FECS_devs_pptr); //get the list of devices
	if(cnt < 0) {
		std::cout<<"libusb_get_device_list(...) failed"<<std::endl; //there was an error
	}
	std::cout<<"libusb_get_device_list(...) successful"<<std::endl;

	std::cout<<cnt<<" Devices in list."<<std::endl; //print total number of usb devices
	ssize_t i; //for iterating through the list
	for(i = 0; i < cnt; i++) {
		FECS_libusb_printdev(FECS_devs_pptr[i]); //print specs of this device
	}

	libusb_free_device_list(FECS_devs_pptr, 1); //free the list, unref the devices in it
	std::cout<<"libusb_free_device_list(...) sucessful"<<std::endl;

	libusb_transfer* FECSTransfer;
	/*
	 * Transfers intended for non-isochronous endpoints (e.g. control, bulk, interrupt)
	 * should specify an iso_packets count of zero.
	 *
	 * When the new transfer is no longer needed, it should be freed with
	 * libusb_free_transfer().
	 */
	//FECSTransfer=libusb_alloc_transfer(0);

	//libusb_fill_bulk_transfer(FECSTransfer,)

#endif

}

FECSManager::~FECSManager() {

	CommunicationDevice_shrptr->close();
	std::cout<<"FECS Communication Interface,"
			<<SmartFly_SystemVariable.FECS_USB_SerialPort
			<<" is closed"<<std::endl;

	// TODO Auto-generated destructor stub
#if 0
	libusb_exit(FECS_libusb_context);
	std::cout<<"FECS libusb_exit successful"<<std::endl;
#endif

}

void FECSManager::initFECSComponents(void){



}

#if 0
void FECSManager::FECS_libusb_printdev(libusb_device *dev) {
	using namespace std;

	libusb_device_descriptor desc;
	int r = libusb_get_device_descriptor(dev, &desc);
	if (r < 0) {
		cout<<"failed to get device descriptor"<<endl;
		return;
	}
	cout<<"Number of possible configurations: "<<(int)desc.bNumConfigurations<<"  ";
	cout<<"Device Class: "<<(int)desc.bDeviceClass<<"  ";
	cout<<"VendorID: "<<desc.idVendor<<"  ";
	cout<<"ProductID: "<<desc.idProduct<<endl;
	libusb_config_descriptor *config;
	libusb_get_config_descriptor(dev, 0, &config);
	cout<<"Interfaces: "<<(int)config->bNumInterfaces<<" ||| ";
	const libusb_interface *inter;
	const libusb_interface_descriptor *interdesc;
	const libusb_endpoint_descriptor *epdesc;
	for(int i=0; i<(int)config->bNumInterfaces; i++) {
		inter = &config->interface[i];
		cout<<"Number of alternate settings: "<<inter->num_altsetting<<" | ";
		for(int j=0; j<inter->num_altsetting; j++) {
			interdesc = &inter->altsetting[j];
			cout<<"Interface Number: "<<(int)interdesc->bInterfaceNumber<<" | ";
			cout<<"Number of endpoints: "<<(int)interdesc->bNumEndpoints<<" | ";
			for(int k=0; k<(int)interdesc->bNumEndpoints; k++) {
				epdesc = &interdesc->endpoint[k];
				cout<<"Descriptor Type: "<<(int)epdesc->bDescriptorType<<" | ";
				cout<<"EP Address: "<<(int)epdesc->bEndpointAddress<<" | ";
			}
		}
	}
	cout<<endl<<endl;
	libusb_free_config_descriptor(config);
}

void FECSManager::FECS_libusb_opendevice(void){
	int r;
	FECS_devh_ptr = libusb_open_device_with_vid_pid(FECS_libusb_context, FECS_USB_VendorID,FECS_USB_ProductID); //these are vendorID and productID I found for my usb device
	if(FECS_devh_ptr == NULL)
		std::cout<<"Device could not be found"<<std::endl;
	else
		std::cout<<"Device Opened"<<std::endl;


	int actual; //used to find out how many bytes were written
	if(libusb_kernel_driver_active(FECS_devh_ptr, 0) == 1) { //find out if kernel driver is attached
		std::cout<<"Kernel Driver Active"<<std::endl;
		if(libusb_detach_kernel_driver(FECS_devh_ptr, 0) == 0) //detach it
			std::cout<<"Kernel Driver Detached!"<<std::endl;
	}
	r = libusb_claim_interface(FECS_devh_ptr, 0); //claim interface 0 (the first) of device (mine had jsut 1)
	if(r < 0) {
		std::cout<<"Cannot Claim Interface"<<std::endl;
	}
	std::cout<<"Claimed Interface"<<std::endl;
}
#endif

} /* namespace SmartFly */
