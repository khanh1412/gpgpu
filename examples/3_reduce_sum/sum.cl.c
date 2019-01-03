#pragma OPENCL EXTENSION cl_khr_int32_base_atomics : enable
__kernel void sum(__global float* a)
{
	ulong global_id = get_global_id(0);
	ulong global_size = get_global_size(0);
	ulong local_id = get_local_id(0);
	ulong local_size = get_local_size(0);

	__local float temp[512];
	temp[local_id] = a[global_id];
	barrier(CLK_LOCAL_MEM_FENCE);

	ulong sum_size = local_size;
	if (global_id >= local_size * (global_size/local_size))
		sum_size = global_size % local_size;
	ulong half_size;
	ulong addon_local_id;

	while (sum_size > 1)
	{
		half_size = (1+sum_size)/2;
		if (local_id < half_size) //local_id in first half
		{
			addon_local_id = local_id + half_size;//corressponding local_id in second half
			if (addon_local_id < sum_size)
				temp[local_id] = temp[local_id] + temp[addon_local_id];
		}
		sum_size = sum_size/2;
		barrier(CLK_LOCAL_MEM_FENCE);
	}
	__global int *mutex; *mutex = 0;
	int res;
	if (local_id == 0)
	{
		while (1)
		{
			res = atomic_xchg(mutex, -1);
			if (-1 != res)
				break;
		}

		a[0] = a[0] + temp[0];
		atomic_exchange(mutex, res+1);
	}
	if (global_id == 0)
	{
		while (1)
		{
			res = atomic_xchg(mutex, -1);
			if ((global_size-1)/2+1 == res)
				break;
		}
	}
}
