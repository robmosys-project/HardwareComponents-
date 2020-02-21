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

#ifndef ZEDCAMERA_ACE_PORTFACTORY_HH_
#define ZEDCAMERA_ACE_PORTFACTORY_HH_

// include ACE/SmartSoft component implementation
#include "ZedCameraImpl.hh"

// include the main component-definition class
#include "ZedCameraPortFactoryInterface.hh"

class ZedCameraAcePortFactory: public ZedCameraPortFactoryInterface
{
private:
	ZedCameraImpl *componentImpl;
public:
	ZedCameraAcePortFactory();
	virtual ~ZedCameraAcePortFactory();

	virtual void initialize(ZedCamera *component, int argc, char* argv[]) override;
	virtual int onStartup() override;

	
	virtual Smart::IPushServerPattern<DomainVision::Comm3dPointCloud> * createPointCloudPushServiceOut(const std::string &serviceName) override;
	virtual Smart::IPushServerPattern<DomainVision::CommRGBDImage> * createRGBDImagePushServiceOut(const std::string &serviceName) override;
	virtual Smart::IPushServerPattern<DomainVision::CommVideoImage> * createRGBImagePushServiceOut(const std::string &serviceName) override;
	
	// get a pointer to the internal component implementation
	SmartACE::SmartComponent* getComponentImpl();

	virtual int onShutdown(const std::chrono::steady_clock::duration &timeoutTime=std::chrono::seconds(2)) override;
	virtual void destroy() override;
};

#endif /* ZEDCAMERA_ACE_PORTFACTORY_HH_ */
