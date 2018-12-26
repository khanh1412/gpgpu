__kernel void fill(
		__global float* a, 
		__global const float x)	
{
	ulong i = get_global_id(0);
	a[i] = x;
	printf("%d\n", x);
}
