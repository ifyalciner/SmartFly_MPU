#include "FECS_Message.h"

/* Starts:FECS_EnvelopeClass Class Method Definitions
*
*
*
*/

FECS_System::FECS_EnvelopeClass::FECS_EnvelopeClass(){	
	Source=(FECS_MessageNS::MesgEnvAddrsType)0;					//1 bytes
	Destination=(FECS_MessageNS::MesgEnvAddrsType)0;			//1 bytes
	Urgency=0;				//1 byte
	Message=0;				//2 bytes
	ParameterLength=0;		//2 byte
	MessageParameterPtr=NULL;	//4 bytes
	
}

FECS_System::FECS_EnvelopeClass::FECS_EnvelopeClass(FECS_EnvelopeClass& copyClass){
	MessageParameterPtr=NULL;
	
	setSource(copyClass.Source);
	setDestination(copyClass.Destination);
	setUrgency(copyClass.Urgency);
	setMessage(copyClass.Message);
	setMessageParameter(copyClass.ParameterLength,copyClass.MessageParameterPtr);
}

FECS_System::FECS_EnvelopeClass::FECS_EnvelopeClass(
	FECS_MessageNS::MesgEnvAddrsType SrcAddr_,
	FECS_MessageNS::MesgEnvAddrsType DestAddr_,
	FECS_MessageNS::MesgEnvUrgType	urg_,
	FECS_MessageNS::MesgEnvMesgType	mesg_,
	FECS_MessageNS::MesgEnvParLenType	ParLeng_,
	FECS_MessageNS::MesgEnvParType const*	MessParPtr_)
{
	MessageParameterPtr=NULL;
	
	setSource(SrcAddr_);
	setDestination(DestAddr_);
	setUrgency(urg_);
	setMessage(mesg_);
	setMessageParameter(ParLeng_,MessParPtr_);
}

FECS_System::FECS_EnvelopeClass::FECS_EnvelopeClass(
	FECS_MessageNS::MesgEnvAddrsType SrcAddr_,
	FECS_MessageNS::MesgEnvAddrsType DestAddr_,
	FECS_MessageNS::MesgEnvUrgType urg_,
	FECS_MessageNS::MesgEnvMesgType mesg_)
{
	MessageParameterPtr=NULL;
	
	setSource(SrcAddr_);
	setDestination(DestAddr_);
	setUrgency(urg_);
	setMessage(mesg_);
	setMessageParameter(0,NULL);
}

FECS_System::FECS_EnvelopeClass& FECS_System::FECS_EnvelopeClass::operator=(const FECS_System::FECS_EnvelopeClass &rhs) {
	// Check for self-assignment!
	if (this == &rhs)      // Same object?
		return *this;        // Yes, so skip assignment, and just return *this.
	setSource(rhs.Source);
	setDestination(rhs.Destination);
	setUrgency(rhs.Urgency);
	setMessage(rhs.Message);
	setMessageParameter(rhs.ParameterLength,rhs.MessageParameterPtr);
	return *this;
}

FECS_System::FECS_EnvelopeClass::~FECS_EnvelopeClass(void){
	if(MessageParameterPtr!=NULL)
		delete [] MessageParameterPtr;
	MessageParameterPtr=NULL;
}

// Source
BOOL FECS_System::FECS_EnvelopeClass::setSource(FECS_System::FECS_MessageNS::MesgEnvAddrsType DestAddr_){
	Source=DestAddr_;
	return TRUE;
}

FECS_System::FECS_MessageNS::MesgEnvAddrsType FECS_System::FECS_EnvelopeClass::getSource(void){
	return Source;
}

// Destination
BOOL FECS_System::FECS_EnvelopeClass::setDestination(FECS_System::FECS_MessageNS::MesgEnvAddrsType DestAddr_){
	Destination=DestAddr_;
	return TRUE;
}

FECS_System::FECS_MessageNS::MesgEnvAddrsType FECS_System::FECS_EnvelopeClass::getDestination(void){
	return Destination;
}

//Urgency
/* Urgency parameter can be between 0 to 9
*/
BOOL FECS_System::FECS_EnvelopeClass::setUrgency(FECS_System::FECS_MessageNS::MesgEnvUrgType urg_){
	Urgency= (urg_ > maxUrgencyValue ? maxUrgencyValue : urg_) < minUrgencyValue ? minUrgencyValue : urg_;
	return TRUE;
}

FECS_System::FECS_MessageNS::MesgEnvUrgType FECS_System::FECS_EnvelopeClass::getUrgency(void){
	return Urgency ;
}

//Message
/* Message parameter can be between 0 to 9
*/
BOOL FECS_System::FECS_EnvelopeClass::setMessage(FECS_System::FECS_MessageNS::MesgEnvMesgType comm_){
	Message=comm_;
	return TRUE;
}

FECS_System::FECS_MessageNS::MesgEnvMesgType FECS_System::FECS_EnvelopeClass::getMessage(void){
	return Message ;
}

//Parameter Length
FECS_System::FECS_MessageNS::MesgEnvParLenType FECS_System::FECS_EnvelopeClass::getParameterLength(void){
	return ParameterLength ;
}

/*
	Total memory copy from one space to this objects
	Must be called after set message parameter length
*/
BOOL FECS_System::FECS_EnvelopeClass::setMessageParameter(
	FECS_MessageNS::MesgEnvParLenType ParLeng_,
	FECS_System::FECS_MessageNS::MesgEnvParType const * MessParPtr_)
{
	if(MessageParameterPtr!=NULL){
		delete [] MessageParameterPtr;
		MessageParameterPtr=NULL;
	}
	

	if(ParLeng_>0)
		MessageParameterPtr = new FECS_MessageNS::MesgEnvParType[ParLeng_];
	ParameterLength=ParLeng_;	
	memcpy (MessageParameterPtr,MessParPtr_,ParameterLength);
	return TRUE;
}


/*
	Index starts from 0
	returned value will be stored in the MessageParameterPtr[index]
*/
FECS_System::FECS_MessageNS::MesgEnvParType  FECS_System::FECS_EnvelopeClass::getMessageParameter(unsigned int index){
	if(MessageParameterPtr==NULL || index>=ParameterLength){
		return 0;
	}
	return MessageParameterPtr[index];
}

/*
	returns MessageParameterPtr. Contend of the returned address is constant
*/
FECS_System::FECS_MessageNS::MesgEnvParType const * FECS_System::FECS_EnvelopeClass::getMessageParameter(void){
	return MessageParameterPtr;
}


BOOL	FECS_System::FECS_EnvelopeClass::setMessagePartsReceived(
	FECS_MessageNS::MesgEnvParType& newByte,
	FECS_System::FECS_MessageNS::constructMessageStatusType* mesStatus,
	FECS_EnvelopeClass** constructedMessage)
{
		using namespace FECS_MessageNS;

		FECS_EnvelopeClass* tempMesg_=mesStatus->mesg_;

		switch(mesStatus->curState){

		case SOURCE:
			tempMesg_->setSource((MesgEnvAddrsType)newByte);
			mesStatus->curState=DESTINATION;
			break;

		case DESTINATION:
			tempMesg_->setDestination((MesgEnvAddrsType)newByte);
			mesStatus->curState=URGENCY;
			break;

		case URGENCY:
			tempMesg_->setUrgency((MesgEnvUrgType)newByte);
			mesStatus->curState=MESSAGE_1;
			break;

		case MESSAGE_1:
			tempMesg_->setMessage((newByte<<8) & 0xFF00);
			mesStatus->curState=MESSAGE_2;
			break;

		case MESSAGE_2:
			tempMesg_->setMessage(tempMesg_->getMessage()	|	(newByte & 0xFF));
			mesStatus->curState=PARAMETERLENGTH_1;
			break;

		case PARAMETERLENGTH_1:
			mesStatus->parLen=((newByte<<8) & ~0xFF);			
			mesStatus->curState=PARAMETERLENGTH_2;
			break;

		case PARAMETERLENGTH_2:
			mesStatus->parLen|=(newByte & 0xFF);		
			mesStatus->curState=MESSAGEPARAMETER;
			
			if(mesStatus->parLen==0)
				mesStatus->curState=CLOSING;
			else
				mesStatus->parameters_= new MesgEnvParType[mesStatus->parLen];
			
			break;

		case MESSAGEPARAMETER:
			mesStatus->parameters_[mesStatus->parameterIndex]=newByte;
			mesStatus->parameterIndex++;
			mesStatus->curState=MESSAGEPARAMETER;
			if(mesStatus->parameterIndex>=mesStatus->parLen){
				mesStatus->curState=CLOSING;
				
				tempMesg_->setMessageParameter(mesStatus->parLen,mesStatus->parameters_);
				
				delete mesStatus->parameters_;
				mesStatus->parameters_=NULL;
			}
			break;
		}

		if(mesStatus->curState==CLOSING){
			*constructedMessage= new FECS_EnvelopeClass(*(mesStatus->mesg_));
			mesStatus->reset();
			return true;
		}
		else{
			*constructedMessage=NULL;
			return false;
		}
		
}

BOOL FECS_System::FECS_EnvelopeClass::getMessagePartsToBeSend(
	FECS_System::FECS_EnvelopeClass& messg,
	FECS_System::FECS_MessageNS::retrieveMessageStatusType* messageToSendStatus,
	FECS_System::FECS_MessageNS::MesgEnvParType& nextByte)
{


		using namespace FECS_MessageNS;
		EMessageState preState=messageToSendStatus->curState;

		switch(messageToSendStatus->curState){

		case SOURCE:
			nextByte=messg.getSource();
			messageToSendStatus->curState=DESTINATION;
			break;

		case DESTINATION:
			nextByte=messg.getDestination();
			messageToSendStatus->curState=URGENCY;
			break;

		case URGENCY:
			nextByte=messg.getUrgency();
			messageToSendStatus->curState=MESSAGE_1;
			break;

		case MESSAGE_1:
			nextByte=((messg.getMessage()>>8) & 0xFF);
			messageToSendStatus->curState=MESSAGE_2;
			break;

		case MESSAGE_2:
			nextByte=(messg.getMessage() & 0xFF);
			messageToSendStatus->curState=PARAMETERLENGTH_1;
			break;

		case PARAMETERLENGTH_1:
			nextByte=((messg.getParameterLength()>>8) & 0xFF);
			messageToSendStatus->curState=PARAMETERLENGTH_2;
			break;

		case PARAMETERLENGTH_2:
			nextByte=(messg.getParameterLength() & 0xFF);
			messageToSendStatus->curState=MESSAGEPARAMETER;
			break;

		case MESSAGEPARAMETER:
			nextByte=messg.getMessageParameter(messageToSendStatus->parameterIndex);			
			messageToSendStatus->parameterIndex++;
			if(messageToSendStatus->parameterIndex==messg.getParameterLength()){
				messageToSendStatus->curState=CLOSING;				
			}
			break;
		}

		if(preState==CLOSING){
			messageToSendStatus->reset();
			return FALSE;
		}
		return TRUE;
}


#ifdef _FECS_SYSTEM_

/* Ends:FECS_EnvelopeClass Class Method Definitions */



/* Starts:FECS_PostBoxClass Class Method Definitions
*
*
*
*/
FECS_System::FECS_PostBoxClass::FECS_PostBoxClass(int queueMessSize_){

	//Create Message Queue
	maxMessageQueueSize=queueMessSize_;
	xMessageQueueHandle =	xQueueCreate((unsigned portBASE_TYPE)maxMessageQueueSize, (unsigned portBASE_TYPE)sizeof(FECS_EnvelopeClass*));

	waitingMessageNumber=0;
	//priorityActive=pdFALSE;
}

FECS_System::FECS_PostBoxClass::~FECS_PostBoxClass(void){

	//Check if there are unprocessed message. If there is delete them all to clear memory 		
	unsigned portBASE_TYPE messageQueueSize=uxQueueMessagesWaiting(xMessageQueueHandle);
	int maxNumberOftickToWait = 2;
	if(messageQueueSize>0){
		FECS_EnvelopeClass * temp;
		for(unsigned short i=0;i<messageQueueSize;i++){
			if(xQueueReceive(xMessageQueueHandle,&temp,maxNumberOftickToWait)==pdTRUE){
				if(temp!=0){
					delete temp;
					temp=NULL;
				}
			}				
		}	
	}

	//Delete the MessageQueue itself
	vQueueDelete(xMessageQueueHandle);
	xMessageQueueHandle=NULL;

}

portBASE_TYPE	FECS_System::FECS_PostBoxClass::pushMessage(FECS_EnvelopeClass* pMessage_,int tickTimeToWait){
	if(tickTimeToWait>100){
		//send Error Message
		return pdFALSE;	
	}

	if(xQueueSend(xMessageQueueHandle,&pMessage_,tickTimeToWait)!=pdTRUE){
		return pdFALSE;	
	}
	//Increase the Number
	waitingMessageNumber++;

	return pdTRUE;
}


FECS_System::FECS_EnvelopeClass*	FECS_System::FECS_PostBoxClass::retrieveMessage(int tickTimeToWait){
	if(tickTimeToWait>100){
		//send Error Message
		//return 0;	
	}
	FECS_EnvelopeClass* retrievedMessage;
	portBASE_TYPE result;

	result=xQueueReceive(xMessageQueueHandle,&retrievedMessage,tickTimeToWait);

	if(result==pdTRUE){
		waitingMessageNumber--;
		return retrievedMessage;
	}
	else{
		return NULL;
	}
}
/* Ends:FECS_PostBoxClass Class Method Definitions */

#endif
