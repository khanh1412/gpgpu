#include"CL/opencl.h"
#include<fstream>
auto all_devices = cl::device::get_all_devices();
auto& device = all_devices[0];
auto *context = new cl::context({device});
auto *queue = new cl::queue(*context, device);
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
	device = all_devices[i];
	delete context;
	delete queue;
	context = new cl::context({device});
	queue = new cl::queue(*context, device);
}
cl::buffer createBuffer(size_t size, void *host_ptr = nullptr)
{
	return cl::buffer(*context, CL_MEM_READ_WRITE, size, host_ptr);
}
cl::kernel compileKernel(std::string& filepath)
{
	return cl::kernel(*context, device, {readfile(filepath)}, "-c-std=CL2.0");
}
double enqueueWriteBuffer(const cl::buffer& b, void *host_ptr, size_t size)
{
	cl::event e = queue->enqueueWriteBuffer(b, host_ptr, size);
	return e.profileEnd() - e.profileStart();
}
double enqueueReadBuffer(const cl::buffer& b, void *host_ptr, size_t size)
{
	cl::event e = queue->enqueueReadBuffer(b, host_ptr, size);
	return e.profileEnd() - e.profileStart();
}
double enqueueExecuteKernel(const cl::kernel& kernel, const std::initializer_list<param>& p, array<size_t> global_dim)
{
	cl::event e = queue->enqueueNDRangeKernel(kernel, p, global_dim, local_dim);
	e.join();
	return e.profileEnd() - e.profileStart();
}
}
