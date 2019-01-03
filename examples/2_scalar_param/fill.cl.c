__kernel void fill(
		__global float *a,
		const float x)
{
	ulong i = get_global_id(0);
	a[i] = x;
}
