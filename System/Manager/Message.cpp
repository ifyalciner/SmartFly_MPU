/*
 * MPU_Message.cpp
 *
 *  Created on: Oct 18, 2012
 *      Author: faruxx
 */


#include "Message.h"

namespace SmartFly{

MessageClass::MessageClass(void) {
	setSource(MPU_ID_NullManager);
	setDestination(MPU_ID_NullManager);
	setUrgency(0);
	setWord(0);
	setMessageParameter();
}

MessageClass::MessageClass(
		MessageAddressType 	SrcAddr_,
		MessageAddressType 	DestAddr_,
		MessageUrgencyType 	urg_,
		MessageWordType 	word_,
		MessParamPtrType 	MessPar_ptr_) {

	setSource(SrcAddr_);
	setDestination(DestAddr_);
	setUrgency(urg_);
	setWord(word_);
	setMessageParameter(MessPar_ptr_);

}

MessageClass::MessageClass(
		MessageAddressType SrcAddr_,
		MessageAddressType DestAddr_,
		MessageUrgencyType urg_,
		MessageWordType word_) {
	setSource(SrcAddr_);
	setDestination(DestAddr_);
	setUrgency(urg_);
	setWord(word_);
	setMessageParameter();
}

MessageClass::~MessageClass() {

	/*	Erase the message pointed by the contend of shared_ptr "MessageParameterPtr"
	 *	by using reset() function
	 */
	this->MessageParameterPtr.reset();
}

MessageClass& MessageClass::operator =(const MessageClass& rhs) {
	if(this==&rhs)
		return (*this);
	setSource(rhs.Source);
	setDestination(rhs.Destination);
	setUrgency(rhs.Urgency);
	setWord(rhs.Word);
	setMessageParameter(rhs.MessageParameterPtr);
	return (*this);
}

bool MessageClass::setSource(MessageAddressType source_) {
	this->Source=source_;
	return (true);
}

MessageAddressType MessageClass::getSource(void) {
	return (this->Source);
}

bool MessageClass::setDestination(MessageAddressType destination_) {
	this->Destination=destination_;
	return (true);
}

MessageAddressType MessageClass::getDestination(void) {
	return (this->Destination);
}

bool MessageClass::setUrgency(MessageUrgencyType urgency_) {
	this->Urgency=urgency_;
	return (true);
}

MessageUrgencyType MessageClass::getUrgency(void) {
	return (this->Destination);
}

bool MessageClass::setWord(MessageWordType word_) {
	this->Word=word_;
	return (true);
}

MessageWordType MessageClass::getWord(void) {
	return (this->Word);
}

bool MessageClass::setMessageParameter(MessParamPtrType messageParameter_shrdptr_) {
	this->MessageParameterPtr=messageParameter_shrdptr_;

	return(true);
}

bool MessageClass::setMessageParameter(void) {
	this->MessageParameterPtr.reset();
	return(true);
}



MessParamPtrType MessageClass::getMessageParameter(void) {
	return (this->MessageParameterPtr);
}


/*
 * End of MesssageClass Class Definitions
 */



}// End of namespace MPU_System



