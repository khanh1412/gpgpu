void kernel fill(
		global float* a, 
		global float x;	
{
	ulong i = get_global_id(0);
	a[i] = x;
}
