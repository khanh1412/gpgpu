#ifndef _GEMM_H_
#define _GEMM_H_
#include"CL/opencl/queue.h"
#include<clblast_c.h>
namespace cl {
namespace builtin {
event gemm(queue& q, size_t m, size_t n, size_t k, float alpha, float beta, const buffer& A, const buffer& B, buffer& C, size_t a_offset=0, size_t b_offset=0, size_t c_offset=0)
{
	size_t a_ld = k;
	size_t b_ld = n;
	size_t c_ld = n;
	CLBlastTranspose transposeA = CLBlastTransposeNo;
	CLBlastTranspose transposeB = CLBlastTransposeNo;
	cl_event e;
	cl_assert(CLBlastSgemm(CLBlastLayoutRowMajor, transposeA, transposeB, 
				m, n, k, 
				alpha, A.handler, a_offset, a_ld, B.handler, b_offset, b_ld, 
				beta, C.handler, c_offset, c_ld, &q.handler, &e));
	return event(e);
}
event gemm(queue& q, size_t m, size_t n, size_t k, double alpha, double beta, const buffer& A, const buffer& B, buffer& C, size_t a_offset=0, size_t b_offset=0, size_t c_offset=0)
{
	size_t a_ld = k;
	size_t b_ld = n;
	size_t c_ld = n;
	CLBlastTranspose transposeA = CLBlastTransposeNo;
	CLBlastTranspose transposeB = CLBlastTransposeNo;
	cl_event e;
	cl_assert(CLBlastDgemm(CLBlastLayoutRowMajor, transposeA, transposeB, 
				m, n, k, 
				alpha, A.handler, a_offset, a_ld, B.handler, b_offset, b_ld, 
				beta, C.handler, c_offset, c_ld, &q.handler, &e));
	return event(e);
}
}
}
#endif
