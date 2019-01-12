#include"cl.hpp"
using namespace cl;
Device::Device(const cl_device_id& device_id)
	: device_id(device_id)
{}
Device::~Device()
{}
