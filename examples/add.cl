__kernel void add(
		__global float* s, 
		__global const float* a, 
		__global const float* b)
{
	ulong i = get_global_id(0);
	s[i] = a[i] + b[i];
}
