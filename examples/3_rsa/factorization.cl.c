typedef ulong uint64_t;
/* global_size(0) = ((int)sqrt(modulo) - 1)/2 */
__kernel void factorization64(__global uint64_t *factor, const uint64_t modulo)
{
	uint64_t p = 3 + 2*get_global_id(0);
	if (modulo % p == 0) factor[0] = p;
}
