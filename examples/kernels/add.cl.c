void kernel add(
		global float* s, 
		global const float* a, 
		global const float* b)
{
	ulong i = get_global_id(0);
	s[i] = a[i] + b[i];
}
