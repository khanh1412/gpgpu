#include"CL/opencl.h"
#include<fstream>
cl::device *device = nullptr;
cl::context *context = nullptr;
cl::queue *queue = nullptr;
inline std::string readfile(const std::string& filepath)
{
	std::ifstream ifs(filepath);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		std::istreambuf_iterator<char>());
	return content;
}
extern "C" {
void chooseDevice(size_t i = 0)
{
	auto all_devices = cl::device::get_all_devices();
	delete device;
	device = new cl::device(all_devices[i]);
	delete context;
	context = new cl::context({*device});
	delete queue;
	queue = new cl::queue(*context, *device);
}
cl::buffer createBuffer(size_t size, void *host_ptr = nullptr)
{
	return cl::buffer(*context, CL_MEM_READ_WRITE, size, host_ptr);
}
cl::kernel createKernel(const std::string& filepath, const std::string& options = "")
{
	return cl::kernel(*context, *device, {readfile(filepath)}, options);
}
double enqueueWriteBuffer(const cl::buffer& b, void *host_ptr, size_t size)
{
	cl::event e = queue->enqueueWriteBuffer(b, host_ptr, size);
	e.join();
	return e.profileEnd() - e.profileStart();
}
double enqueueReadBuffer(const cl::buffer& b, void *host_ptr, size_t size)
{
	cl::event e = queue->enqueueReadBuffer(b, host_ptr, size);
	e.join();
	return e.profileEnd() - e.profileStart();
}
double enqueueExecuteKernel(const cl::kernel& kernel, const std::initializer_list<cl::param>& p, cl::array<size_t> global_dim)
{
	cl::event e = queue->enqueueNDRangeKernel(kernel, p, global_dim);
	e.join();
	return e.profileEnd() - e.profileStart();
}
}
