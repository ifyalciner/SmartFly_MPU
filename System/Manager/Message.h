/*
 * MPU_Message.h
 *
 *  Created on: Oct 18, 2012
 *      Author: faruxx
 */



#ifndef MESSAGE_H_
#define MESSAGE_H_

//Project Libraries
#include "../MPU_SystemAllInclude.h"

namespace SmartFly{

//In order to change a parameters data type this are will be used

typedef ManagerID								MessageAddressType;
typedef unsigned char							MessageUrgencyType;
typedef unsigned short							MessageWordType;
typedef std::string								MessageParameterType;
typedef boost::shared_ptr<MessageParameterType> MessParamPtrType;



class MessageClass{
private:
	static const unsigned char maxUrgencyValue=9;
	static const unsigned char minUrgencyValue=0;

	MessageAddressType		Source;
	MessageAddressType		Destination;
	MessageWordType			Word;
	MessageUrgencyType		Urgency;
	MessParamPtrType		MessageParameterPtr;
	//Total:	11 bytes

public:


	/*
			Function:		FECS_EnvelopeClass(void)
			Parameters:		void
			Explanation:	*Default Constructor. Initializes all parameters with 0 value.
			Returns:		void
	 */
	MessageClass();

	/*
			Function:		FECS_EnvelopeClass
			Parameters:		All Important attributes are given as parameters
			Explanation:
			Returns:		void
	 */
	MessageClass(
			MessageAddressType		SrcAddr_,
			MessageAddressType		DestAddr_,
			MessageUrgencyType		urg_,
			MessageWordType			word_,
			MessParamPtrType		MessPar_ptr_);

	/*
			Function:		FECS_EnvelopeClass
			Parameters:		All Important attributes are given as parameters but the parameter size is 0
			Explanation:	Used when there is no parameter. Parameterlength is 0, ParameterPointer is NULL
			Returns:		void
	 */
	MessageClass(
			MessageAddressType		SrcAddr_,
			MessageAddressType		DestAddr_,
			MessageUrgencyType		urg_,
			MessageWordType			word_);

	/*
			Function:		~FECS_EnvelopeClass
			Parameters:		All Important attributes are given as parameters but the parameter size is 0
			Explanation:	Destructor deletes all dynamically allocated memory spaces.
			Returns:		void
	 */
	~MessageClass();

	MessageClass& operator=(const MessageClass &rhs);

	bool					setSource(MessageAddressType source_);
	MessageAddressType		getSource(void);

	bool					setDestination(MessageAddressType destination_);
	MessageAddressType		getDestination(void);

	bool					setUrgency(MessageUrgencyType urgency_);
	MessageUrgencyType		getUrgency(void);

	bool					setWord(MessageWordType word_);
	MessageWordType			getWord(void);

	bool					setMessageParameter(MessParamPtrType messageParameter_shrdptr_);
	bool					setMessageParameter();
	MessParamPtrType		getMessageParameter(void);



};// End of Class Message

}// End of namespace SmartFly

#endif /* MPU_MESSAGE_H_ */
