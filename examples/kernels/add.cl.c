void kernel add(
		global float* c, 
		global const float* a, 
		global const float* b)
{
	ulong i = get_global_id(0);
	c[i] = a[i] + b[i];
}
