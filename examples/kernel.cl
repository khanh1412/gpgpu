__kernel void add(	__global float* z,
			__global const float* x,
			__global const float* y)
{
	ulong i = get_global_id(0);
	z[i] = x[i] + y[i];
}
