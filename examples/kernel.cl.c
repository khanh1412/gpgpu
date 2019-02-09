#define dtype float
typedef ulong uint64_t;
__kernel kronecker(uint64_t m, uint64_t n, uint64_t p, uint64_t q, __global const dtype *A, __global const dtype *B, __global dtype *C, __local dtype *localmem)
{
	uint64_t i = get_global_id(0);
	uint64_t j = get_global_id(1);
	uint64_t i_local = get_local_id(0);
	uint64_t j_local = get_local_id(1);
	//set up
	if (i_local == 0 && j_local == 0)
		localmem[0] = A[n*(i/m) + j/m];
	//calulation
	C[n*q*i + j] = localmem[0]*B[q*i_local+j_local];
}
