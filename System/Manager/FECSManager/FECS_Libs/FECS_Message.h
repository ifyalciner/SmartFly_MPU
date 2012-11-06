

#ifndef FECS_MESSAGE_H_
#define FECS_MESSAGE_H_


#include "FECS_System.h"


namespace FECS_System{

	class FECS_EnvelopeClass;

	namespace FECS_MessageNS{

		struct st_contMesStatType;
		typedef struct st_contMesStatType constructMessageStatusType;

		struct st_retrMesStatType;
		typedef struct st_retrMesStatType retrieveMessageStatusType;

		typedef PartAddress			MesgEnvAddrsType;
		typedef unsigned char		MesgEnvUrgType;
		typedef unsigned short		MesgEnvMesgType;
		typedef unsigned short		MesgEnvParLenType;
		typedef char				MesgEnvParType;

		typedef enum messReadingStates{
			SOURCE,
			DESTINATION,
			URGENCY,
			MESSAGE_1,
			MESSAGE_2,
			PARAMETERLENGTH_1,
			PARAMETERLENGTH_2,
			MESSAGEPARAMETER,
			CLOSING,
		}EMessageState;

	}// end of namespace FECS_MessageNS{


	/*
		Class:			FECS_EnvelopeClass
		Explanation:	*FECS_EnvelopeClass class is a message container.
						
		Parameters:		Most important parameters are explained here.Rest can be found above the declaration
				
			Source:			Address of message. This address belongs to domain "PartAddress" which is indicated in FECS_System.h header file. Sender of the message writes its "PartAddress" type value here.
			Destination:	Address of message. This address belongs to domain "PartAddress" which is indicated in FECS_System.h header file. Sender of the message writes the intended arrivals "PartAddress" type value here.
			Urgency:		Indicates the priority of a message. If priority is higher then message is more likely to be processed before lover priority messages.
			Message:		Indicates the functional meaning of the message. Message parameters are going to be processed depending on the "Message".
			ParameterLenght:		Length in bytes of the MesssageParameterPtr.
			MessageParameterPtr:	Contains the required data to accomplish the "Message"s requirements.

		Returns:		void
	*/

	class FECS_EnvelopeClass{		
	private:
		static const unsigned char maxUrgencyValue=9;
		static const unsigned char minUrgencyValue=0;

		FECS_MessageNS::MesgEnvAddrsType	Source;					//1 bytes
		FECS_MessageNS::MesgEnvAddrsType	Destination;			//1 bytes
		FECS_MessageNS::MesgEnvUrgType		Urgency;				//1 byte
		FECS_MessageNS::MesgEnvMesgType		Message;				//2 bytes
		FECS_MessageNS::MesgEnvParLenType	ParameterLength;		//2 byte
		FECS_MessageNS::MesgEnvParType*		MessageParameterPtr;	//4 bytes
		//Total:	11 bytes		

	public:


		/*
			Function:		FECS_EnvelopeClass(void)
			Parameters:		void
			Explanation:	*Default Constructor. Initializes all parameters with 0 value.
			Returns:		void
		*/
		FECS_EnvelopeClass();

		/*
			Function:		FECS_EnvelopeClass(FECS_EnvelopeClass&)
			Parameters:		FECS_EnvelopeClass
			Explanation:	*Copy the given objects properties to new created object.
			Returns:		void
		*/
		FECS_EnvelopeClass(FECS_EnvelopeClass&);
		
		/*
			Function:		FECS_EnvelopeClass(FECS_EnvelopeClass*)
			Parameters:		FECS_EnvelopeClass*
			Explanation:	*Copy the given pointers indicating objects properties to new created object.
			Returns:		void
		*/
		FECS_EnvelopeClass(FECS_EnvelopeClass*);
		
		/*
			Function:		FECS_EnvelopeClass
			Parameters:		All Important attributes are given as parameters
			Explanation:	
			Returns:		void
		*/
		FECS_EnvelopeClass(	
			FECS_MessageNS::MesgEnvAddrsType		SrcAddr_,
			FECS_MessageNS::MesgEnvAddrsType		DestAddr_,
			FECS_MessageNS::MesgEnvUrgType			urg_,
			FECS_MessageNS::MesgEnvMesgType			mesg_,
			FECS_MessageNS::MesgEnvParLenType		ParLeng_,
			FECS_MessageNS::MesgEnvParType const*	MessParPtr_);
		
		/*
			Function:		FECS_EnvelopeClass
			Parameters:		All Important attributes are given as parameters but the parameter size is 0
			Explanation:	Used when there is no parameter. Parameterlength is 0, ParameterPointer is NULL
			Returns:		void
		*/
		FECS_EnvelopeClass(	
			FECS_MessageNS::MesgEnvAddrsType	SrcAddr_,
			FECS_MessageNS::MesgEnvAddrsType	DestAddr_,
			FECS_MessageNS::MesgEnvUrgType		urg_,
			FECS_MessageNS::MesgEnvMesgType		mesg_);
		
		/*
			Function:		~FECS_EnvelopeClass
			Parameters:		All Important attributes are given as parameters but the parameter size is 0
			Explanation:	Destructor deletes all dynamically allocated memory spaces.
			Returns:		void
		*/
		~FECS_EnvelopeClass();

		FECS_EnvelopeClass& operator=(const FECS_System::FECS_EnvelopeClass &rhs);

		BOOL									setSource(FECS_MessageNS::MesgEnvAddrsType);
		FECS_MessageNS::MesgEnvAddrsType		getSource(void);

		BOOL									setDestination(FECS_MessageNS::MesgEnvAddrsType);
		FECS_MessageNS::MesgEnvAddrsType		getDestination(void);

		BOOL									setUrgency(FECS_MessageNS::MesgEnvUrgType);
		FECS_MessageNS::MesgEnvUrgType			getUrgency(void);

		BOOL									setMessage(FECS_MessageNS::MesgEnvMesgType);
		FECS_MessageNS::MesgEnvMesgType			getMessage(void);

		FECS_MessageNS::MesgEnvParLenType		getParameterLength(void);

		FECS_MessageNS::MesgEnvParType			getMessageParameter(unsigned int index);
		BOOL									setMessageParameter(FECS_MessageNS::MesgEnvParLenType ParLeng_,FECS_MessageNS::MesgEnvParType const *);
		FECS_MessageNS::MesgEnvParType const *	getMessageParameter(void);

		// Message Constructor from Discrete Bytes

		/*	setMessagePartsReceived:
		*
		*	Incoming single bytes are processed in this function to construct 
		*	a whole message.
		*
		*	INPUT:
		*		NewByte: new byte read from communication line
		*		MesStatus: indicates the place where newbyte belongs
		*		constructedMessage: After all bytes are completed constructed 
		*			message can be read from this object. During the message 
		*			reading this object contains NULL
		*
		*	RETURNS: If message construction is completed returns true. This means
		*		constructedMessage object is ready. Else is false means constructedMessage
		*		is NULL
		*/
		static BOOL	setMessagePartsReceived(FECS_MessageNS::MesgEnvParType& newByte,
			FECS_MessageNS::constructMessageStatusType* messageToSendStatus,
			FECS_EnvelopeClass** constructedMessage);
		
		/*	getMessagePartsToBeSend:
		*	Prepare a package EnvelopeClass object to be posted through communication
		*	line.
		*
		*	INPUT:
		*		constructedMessage: After all bytes are completed constructed 
		*			message can be read from this object. During the message 
		*			reading this object contains NULL
		*		messageToSendStatus: indicates the place where next newbyte belongs
		*		NewByte: newbyte has been set to the byte to be send
		*		
		*
		*	RETURNS: If message construction is completed returns true. This means
		*		constructedMessage object is ready. Else is false means constructedMessage
		*		is NULL
		*/
		static BOOL getMessagePartsToBeSend(FECS_EnvelopeClass& messg,
			FECS_MessageNS::retrieveMessageStatusType* mesStatus,
			FECS_MessageNS::MesgEnvParType& nextByte);


	};// End of Class Message

#ifdef _FECS_SYSTEM_

	class FECS_PostBoxClass{


	public:
		FECS_PostBoxClass(int);
		~FECS_PostBoxClass(void);

		portBASE_TYPE		pushMessage(FECS_EnvelopeClass*,int=2);
		FECS_EnvelopeClass*	retrieveMessage(int=2);

		//unsigned char		activatePriorityFeature();
		//unsigned char		deactivatePriorityFeature();

		friend class FECS_Manager;

	private:	
		//portBASE_TYPE		priorityActive;
		int					maxMessageQueueSize;
		xQueueHandle		xMessageQueueHandle;
		int					waitingMessageNumber;
	};
		
#endif

	namespace FECS_MessageNS{
		
		struct st_contMesStatType{
			int parameterIndex;
			EMessageState curState;
			MesgEnvParLenType parLen;
			MesgEnvParType*		parameters_;
			FECS_EnvelopeClass* mesg_;

			st_contMesStatType(){
				parameters_=NULL;
				parameterIndex=0;
				parLen=0;
				curState=SOURCE;
				mesg_=new FECS_EnvelopeClass();
			}

			~st_contMesStatType(){
				if(mesg_!=NULL){
					delete mesg_;
					mesg_=NULL;
				}
				if(parameters_!=NULL){
					delete parameters_;
					parameters_=NULL;
				}
			}
			void reset(void){
				if(mesg_!=NULL){
					delete mesg_;
					mesg_=NULL;
				}
				if(parameters_!=NULL){
					delete parameters_;
					parameters_=NULL;
				}				
				parameterIndex=0;
				parLen=0;
				curState=SOURCE;
				mesg_=new FECS_EnvelopeClass();
			}
		};

		struct st_retrMesStatType{
			int parameterIndex;
			EMessageState curState;
			st_retrMesStatType(void){
				parameterIndex=0;
				curState=SOURCE;
			}
			void reset(void){
				parameterIndex=0;
				curState=SOURCE;
			}
		};
	}


}//End of namespace FECS_System


#endif
