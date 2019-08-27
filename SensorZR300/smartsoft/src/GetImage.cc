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
#include "GetImage.hh"
#include "SensorZR300.hh"

#include <iostream>

GetImage::GetImage(SmartACE::SmartComponent *comp) 
:	GetImageCore(comp)
{
	std::cout << "constructor GetImage\n";

    if (ctx.get_device_count() == 0) throw std::runtime_error("No device detected. Is it plugged in?");
    dev = ctx.get_device(0);

    printf("\nUsing device 0, an %s\n", dev->get_name());
    printf("    Serial number: %s\n", dev->get_serial());
    printf("    Firmware version: %s\n", dev->get_firmware_version());

    // Configure depth to run at VGA resolution at 30 frames per second
    dev->enable_stream(rs::stream::color, 640, 480, rs::format::bgr8, 30);
    dev->enable_stream(rs::stream::depth, 640, 480, rs::format::z16, 30);

    // Start our device
    dev->start();


}
GetImage::~GetImage() 
{
	std::cout << "destructor GetImage\n";
}


void GetImage::getrgbimage(DomainVision::CommVideoImage& comm_rgb_frame)
{
    const int frame_height = dev->get_stream_height(rs::stream::color);
    const int frame_width =  dev->get_stream_width(rs::stream::color);

	const unsigned char *color_frame = reinterpret_cast<const  unsigned char *>(dev->get_frame_data(rs::stream::color));

	comm_rgb_frame.set_parameters(frame_width, frame_height, DomainVision::FormatType::RGB24);
	comm_rgb_frame.setIs_valid(true);
    comm_rgb_frame.setSeq_count(dev->get_frame_number(rs::stream::color));
	comm_rgb_frame.set_data(color_frame);



}

void GetImage::getdepthimage(DomainVision::CommDepthImage& comm_depth_frame)
{
    const int frame_height = dev->get_stream_height(rs::stream::depth);
    const int frame_width =  dev->get_stream_width(rs::stream::depth);
	const uint16_t * depth_frame = reinterpret_cast<const uint16_t *>(dev->get_frame_data(rs::stream::depth));

	// std::cout << "The camera is facing an object " << depth_frame[240*640+320] << " meters away "<<std::endl;

	comm_depth_frame.setWidth(frame_width);
	comm_depth_frame.setHeight(frame_height);
	comm_depth_frame.setScale(dev->get_depth_scale());
	//std::cout << "depth height =" << comm_depth_frame.getHeight()<<"depth width  =" << comm_depth_frame.getWidth()<<std::endl;

	comm_depth_frame.setFormat(DomainVision::DepthFormatType::UINT16);
	comm_depth_frame.setPixel_size(16);
	comm_depth_frame.setSeq_count(dev->get_frame_number(rs::stream::depth));
//
	comm_depth_frame.set_distances(depth_frame, frame_width, frame_height);
}

void GetImage::getpointcloud(DomainVision::Comm3dPointCloud& comm_pointcloud_frame, DomainVision::CommDepthImage comm_depth_frame)
{
    const int img_height = dev->get_stream_height(rs::stream::depth);
    const int img_width =  dev->get_stream_width(rs::stream::depth);
	const uint16_t * depth_frame = reinterpret_cast<const uint16_t *>(dev->get_frame_data(rs::stream::depth));
	float scale = dev->get_depth_scale();

	std::vector<CommBasicObjects::CommPosition3d> points;

	float cx=308.2192687988281,  cy = 245.59515380859375; //rgb intrinsic
	//float fx = 473.1015319824219, fy = 473.1015625;
	float fx =  618.5377197265625, fy = 618.5377807617188;

	//float* data = (float*) comm_depth_frame.get_distances_float();


    for (int x = 0;x < img_width; x++)//To loop through all the pixels
           for (int y = 0; y < img_height; y++)
        	if ( depth_frame[y*img_width+x] != 0){
				CommBasicObjects::CommPosition3d pt;
				double ptx, pty, ptz;

				ptz = depth_frame[y*img_width+x]*scale;
				ptx =  (x - cx)*ptz/fx;
				pty =  (y - cy)*ptz/fy;

				pt.setX(ptx);	pt.setY(pty);	pt.setZ(ptz);
				points.push_back(pt);
				if(x == img_width/2 && y == img_height/2)
					std::cout << "point x:" << ptx << " y:"<< pty << " z:"<< ptz<< " sc:"<< scale <<std::endl;
		}

	comm_pointcloud_frame.setPoints(points);


}


int GetImage::on_entry()
{
	// do initialization procedures here, which are called once, each time the task is started
	// it is possible to return != 0 (e.g. when initialization fails) then the task is not executed further
	return 0;
}
int GetImage::on_execute()
{

	Smart::StatusCode status;

	DomainVision::CommRGBDImage rgbd_frame;
	DomainVision::CommDepthImage comm_depth_frame;
	DomainVision::CommVideoImage comm_rgb_frame;
	DomainVision::Comm3dPointCloud comm_pointcloud_frame;
	
	dev->wait_for_frames();

	getrgbimage(comm_rgb_frame);
	getdepthimage(comm_depth_frame);
	getpointcloud(comm_pointcloud_frame, comm_depth_frame);

	COMP->rGBImagePushServiceOut->put(comm_rgb_frame);
	COMP->pointCloudPushServiceOut->put(comm_pointcloud_frame);

	rgbd_frame.setColor_image(comm_rgb_frame);
	rgbd_frame.setDepth_image(comm_depth_frame);
	rgbd_frame.setSeq_count(comm_rgb_frame.getSeq_count());
	rgbd_frame.setIs_valid(true);
	COMP->rGBDImagePushServiceOut->put(rgbd_frame);

	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}
int GetImage::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	return 0;
}
