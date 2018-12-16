#include"Queue.h"
Queue::Queue(const cl::Context& context, const cl::Device& device)
	: context(context), device(device)
{
	queue = cl::CommandQueue(context, device);
}
Queue::~Queue()
{}
