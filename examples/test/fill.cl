__kernel void fill(
		__global float *a,
		__constant float *X)
{
	ulong i = get_global_id(0);
	a[i] = *X;
}
