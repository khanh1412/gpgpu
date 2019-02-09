typedef ulong uint64_t;
__kernel void kronecker(uint64_t m, uint64_t n, uint64_t p, uint64_t q, __global const dtype *A, __global const dtype *B, __global dtype *C)
{
	uint64_t global_y = get_global_id(0);
	uint64_t global_x = get_global_id(1);
	uint64_t local_y = get_local_id(0);
	uint64_t local_x = get_local_id(1);

	__local dtype localmem;

	if (local_x==0 && local_y==0)
		localmem = A[n*(global_y/m) + (global_x/n)];

	barrier(CLK_LOCAL_MEM_FENCE);

	C[n*q*global_y + global_x] = localmem * B[q*local_y + local_x];
}
