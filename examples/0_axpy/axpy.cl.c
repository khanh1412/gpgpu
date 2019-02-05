__kernel void axpy(	__global float* res,
			const float a,
			__global const float* x,
			__global const float* y)
{
	ulong i = get_global_id(0);
	res[i] = a*x[i] + y[i];
}
