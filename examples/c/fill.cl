__kernel void fill(
		__global float *a,
		__global float *X)
{
	ulong i = get_global_id(0);
	a[i] = *X;
}
