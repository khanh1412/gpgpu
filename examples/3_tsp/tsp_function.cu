#include<cstdint>
#include<ctime>
uint64_t hm_permutations(uint8_t size);
__global__ void tsp(float *result, const float *arr, const uint8_t size, const uint8_t *perm, const uint64_t num_threads);
uint64_t cu_call(float *result, const float *arr, uint8_t size, const uint8_t *perm)
{
	std::clock_t t1, t2;
	/*SET UP*/
	cudaStream_t stream;
	cudaStreamCreate(&stream);
	const uint64_t num_threads = hm_permutations(size);
	cudaDeviceProp prop;
	cudaGetDeviceProperties(&prop, 0);
	int max_block_dim = prop.maxThreadsPerBlock;
	//max_block_dim = 1;
	int hm_blocks = 1 + num_threads/max_block_dim;
	dim3 block_dim(max_block_dim);
	dim3 grid_dim(hm_blocks);
	/*BUFFER*/
	float *d_arr;    cudaMalloc((void**)&d_arr,    size*size*sizeof(float));
	uint8_t *d_perm; cudaMalloc((void**)&d_perm,   num_threads*size*sizeof(uint8_t));
	float *d_result; cudaMalloc((void**)&d_result, num_threads*sizeof(float));
	/*KERNEL*/
	t1 = std::clock();
	cudaMemcpyAsync(d_perm, perm,     num_threads*size*sizeof(uint8_t), cudaMemcpyHostToDevice, stream);
	cudaMemcpyAsync(d_arr,  arr,      size*size*sizeof(float), cudaMemcpyHostToDevice,          stream);
	        tsp<<<grid_dim, block_dim, 0, stream>>>(d_result, d_arr, size, d_perm, num_threads);
	cudaMemcpyAsync(result, d_result, num_threads*sizeof(float), cudaMemcpyDeviceToHost,        stream);
	cudaStreamSynchronize(stream);
	t2 = std::clock();
	/*CLEAN UP*/
	cudaFree(d_arr);
	cudaFree(d_perm);
	cudaFree(d_result);
	cudaStreamDestroy(stream); 
	return (1000000*(t2-t1))/CLOCKS_PER_SEC;
}
