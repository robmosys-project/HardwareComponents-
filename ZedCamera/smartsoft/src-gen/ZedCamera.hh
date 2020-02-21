//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
// The SmartSoft Toolchain has been developed by:
//  
// Service Robotics Research Center
// University of Applied Sciences Ulm
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// www.servicerobotik-ulm.de
//
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------
#ifndef _ZEDCAMERA_HH
#define _ZEDCAMERA_HH

#include <map>
#include <iostream>
#include "aceSmartSoft.hh"
#include "smartQueryServerTaskTrigger_T.h"
#include "ZedCameraCore.hh"

#include "ZedCameraPortFactoryInterface.hh"
#include "ZedCameraExtension.hh"

// forward declarations
class ZedCameraPortFactoryInterface;
class ZedCameraExtension;

// includes for OpcUaBackendComponentGeneratorExtension

// includes for PlainOpcUaZedCameraExtension
// include plain OPC UA device clients
// include plain OPC UA status servers

// includes for ZedCameraROSExtension


// include communication objects
#include <DomainVision/Comm3dPointCloud.hh>
#include <DomainVision/Comm3dPointCloudACE.hh>
#include <DomainVision/CommRGBDImage.hh>
#include <DomainVision/CommRGBDImageACE.hh>
#include <DomainVision/CommVideoImage.hh>
#include <DomainVision/CommVideoImageACE.hh>

// include tasks
#include "GetImage.hh"
// include UpcallManagers

// include input-handler(s)
// include request-handler(s)

// include handler
#include "CompHandler.hh"


#include "SmartStateChangeHandler.hh"

#define COMP ZedCamera::instance()

class ZedCamera : public ZedCameraCore {
private:
	static ZedCamera *_zedCamera;
	
	// constructor
	ZedCamera();
	
	// copy-constructor
	ZedCamera(const ZedCamera& cc);
	
	// destructor
	~ZedCamera() { };
	
	// load parameter from ini file
	void loadParameter(int argc, char* argv[]);
	
	// instantiate comp-handler
	CompHandler compHandler;
	
	// helper method that maps a string-name to an according TaskTriggerSubject
	Smart::TaskTriggerSubject* getInputTaskTriggerFromString(const std::string &client);
	
	// internal map storing the different port-creation factories (that internally map to specific middleware implementations)
	std::map<std::string, ZedCameraPortFactoryInterface*> portFactoryRegistry;
	
	// internal map storing various extensions of this component class
	std::map<std::string, ZedCameraExtension*> componentExtensionRegistry;
	
public:
	
	// define tasks
	Smart::TaskTriggerSubject* getImageTrigger;
	GetImage *getImage;
	
	// define input-ports
	
	// define request-ports
	
	// define input-handler
	
	// define output-ports
	Smart::IPushServerPattern<DomainVision::Comm3dPointCloud> *pointCloudPushServiceOut;
	Smart::IPushServerPattern<DomainVision::CommRGBDImage> *rGBDImagePushServiceOut;
	Smart::IPushServerPattern<DomainVision::CommVideoImage> *rGBImagePushServiceOut;
	
	// define answer-ports
	
	// define request-handlers
	
	// definitions of OpcUaBackendComponentGeneratorExtension
	
	// definitions of PlainOpcUaZedCameraExtension
	
	// definitions of ZedCameraROSExtension
	
	
	// define default slave ports
	SmartACE::StateSlave *stateSlave;
	SmartStateChangeHandler *stateChangeHandler;
	SmartACE::WiringSlave *wiringSlave;
	
	
	/// this method is used to register different PortFactory classes (one for each supported middleware framework)
	void addPortFactory(const std::string &name, ZedCameraPortFactoryInterface *portFactory);
	
	SmartACE::SmartComponent* getComponentImpl();
	
	/// this method is used to register different component-extension classes
	void addExtension(ZedCameraExtension *extension);
	
	/// this method allows to access the registered component-extensions (automatically converting to the actuall implementation type)
	template <typename T>
	T* getExtension(const std::string &name) {
		auto it = componentExtensionRegistry.find(name);
		if(it != componentExtensionRegistry.end()) {
			return dynamic_cast<T*>(it->second);
		}
		return 0;
	}
	
	/// initialize component's internal members
	void init(int argc, char *argv[]);
	
	/// execute the component's infrastructure
	void run();
	
	/// clean-up component's resources
	void fini();
	
	/// call this method to set the overall component into the Alive state (i.e. component is then ready to operate)
	void setStartupFinished();
	
	/// connect all component's client ports
	Smart::StatusCode connectAndStartAllServices();
	
	/// start all assocuated Activities
	void startAllTasks();
	
	/// start all associated timers
	void startAllTimers();
	

	// return singleton instance
	static ZedCamera* instance()
	{
		if(_zedCamera == 0) {
			_zedCamera = new ZedCamera();
		}
		return _zedCamera;
	}
	
	static void deleteInstance() {
		if(_zedCamera != 0) {
			delete _zedCamera;
		}
	}
	
	// connections parameter
	struct connections_struct
	{
		// component struct
		struct component_struct
		{
			// the name of the component
			std::string name;
			std::string initialComponentMode;
			std::string defaultScheduler;
			bool useLogger;
		} component;
		
		//--- task parameter ---
		struct GetImage_struct {
			double minActFreq;
			double maxActFreq;
			std::string trigger;
			// only one of the following two params is 
			// actually used at run-time according 
			// to the system config model
			double periodicActFreq;
			// or
			std::string inPortRef;
			int prescale;
			// scheduling parameters
			std::string scheduler;
			int priority;
			int cpuAffinity;
		} getImage;
		
		//--- upcall parameter ---
		
		//--- server port parameter ---
		struct PointCloudPushServiceOut_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} pointCloudPushServiceOut;
		struct RGBDImagePushServiceOut_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} rGBDImagePushServiceOut;
		struct RGBImagePushServiceOut_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} rGBImagePushServiceOut;
	
		//--- client port parameter ---
		
		// -- parameters for OpcUaBackendComponentGeneratorExtension
		
		// -- parameters for PlainOpcUaZedCameraExtension
		
		// -- parameters for ZedCameraROSExtension
		
	} connections;
};
#endif
