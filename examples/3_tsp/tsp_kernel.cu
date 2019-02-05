typedef unsigned char uint8_t;
typedef unsigned long uint64_t;
__global__ void tsp(float *result, const float *arr, const uint8_t size, const uint8_t *perm, const uint64_t num_threads)
{
	/*Get global_id*/
        uint64_t block_id = blockIdx.x;
        uint64_t thread_id = threadIdx.x;
        uint64_t threads = blockDim.x;
        uint64_t global_id = thread_id + block_id * threads;
        if (global_id >= num_threads) return;
	/*Loop*/
	uint64_t perm_addon = global_id*size;
	float cost = 0;
	uint8_t lastp, currp;
	for (uint64_t i=0; i<size-1; i++)
	{	
		lastp = perm[perm_addon + i];
		currp = perm[perm_addon + i+1];
		cost += arr[lastp*size + currp];
	}
	{
		lastp = perm[perm_addon + size-1];
		currp = perm[perm_addon + 0];
		cost += arr[lastp*size + currp];
	}
	result[global_id] = cost;
}
