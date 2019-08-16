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
// This file is generated once. Modify this file to your needs. 
// If you want the toolchain to re-generate this file, please 
// delete it before running the code generator.
//--------------------------------------------------------------------------
#ifndef _GETIMAGE_HH
#define _GETIMAGE_HH

#include "GetImageCore.hh"
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

class GetImage  : public GetImageCore
{
private:
    rs2::colorizer color_map;
    rs2::rates_printer printer;
    rs2::pipeline pipe;
    rs2::frameset current_frameset;

    rs2::pipeline_profile profile;
    rs2::device dev;
//    rs2::depth_sensor ds;
    float depth_scale;


    void getrgbimage(DomainVision::CommVideoImage& comm_rgb_frame);
    void getdepthimage(DomainVision::CommDepthImage& comm_depth_frame);
    void getpointcloud(DomainVision::Comm3dPointCloud& comm_pointcloud_frame, DomainVision::CommDepthImage comm_depth_frame);
public:
	GetImage(SmartACE::SmartComponent *comp);
	virtual ~GetImage();
	
	virtual int on_entry();
	virtual int on_execute();
	virtual int on_exit();
};

#endif
