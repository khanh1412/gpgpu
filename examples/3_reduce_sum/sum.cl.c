__kernel void sum(__global float* a)
{
	ulong i = get_global_id(0);
	ulong size = get_global_size(0);
	float s = 0;
	if (0==i)
	{
		for (ulong j = 0; j<size; j++)
		{
			s += a[j];
		}
	}
	a[0] = s;
}
