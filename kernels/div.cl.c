void kernel div(
		global float* s, 
		global const float* a, 
		global const float* b)
{
	int i = get_global_id(0);
	s[i] = a[i] / b[i];
}
