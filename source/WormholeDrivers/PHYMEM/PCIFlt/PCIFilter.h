#ifndef	__PCIFILTER_H
#define	__PCIFILTER_H

typedef enum tagDEVICE_PNP_STATE
{
	NotStarted=0,           // Not started yet
	Started,                // Device has received the START_DEVICE IRP
	StopPending,            // Device has received the QUERY_STOP IRP
	Stopped,                // Device has received the STOP_DEVICE IRP
	RemovePending,          // Device has received the QUERY_REMOVE IRP
	SurpriseRemovePending,  // Device has received the SURPRISE_REMOVE IRP
	Deleted                 // Device has received the REMOVE_DEVICE IRP
} DEVICE_PNP_STATE;

#define INITIALIZE_PNP_STATE(_Data_)	\
	(_Data_)->DevicePnPState=NotStarted;\
	(_Data_)->PreviousPnPState=NotStarted;

#define SET_NEW_PNP_STATE(_Data_, _state_)	\
	(_Data_)->PreviousPnPState=(_Data_)->DevicePnPState;	\
	(_Data_)->DevicePnPState=(_state_);

#define RESTORE_PREVIOUS_PNP_STATE(_Data_)	\
	(_Data_)->DevicePnPState=(_Data_)->PreviousPnPState;

typedef struct tagDEVICE_EXTENSION
{
	//physical device object
	PDEVICE_OBJECT pdo;

	//the device object we attached to
	PDEVICE_OBJECT lowerdo;

	//current pnp state
	DEVICE_PNP_STATE DevicePnPState;

	//previous pnp state
	DEVICE_PNP_STATE PreviousPnPState;

	//Remove Lock
	IO_REMOVE_LOCK rmLock;

} DEVICE_EXTENSION, *PDEVICE_EXTENSION;

#endif	//__PCIFILTERZ_H