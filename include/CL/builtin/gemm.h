#ifndef _GEMM_H_
#define _GEMM_H_
#include"CL/opencl/queue.h"
#include<clblast_c.h>
#include<clblast.h>
namespace cl {
namespace builtin {
template<class type>
event gemm(queue& q, size_t m, size_t n, size_t k, type alpha, type beta, const buffer& A, const buffer& B, buffer& C, size_t a_offset=0, size_t b_offset=0, size_t c_offset=0)
{
	size_t a_ld = k;
	size_t b_ld = n;
	size_t c_ld = n;
	cl_event e;
	/*
	CLBlastTranspose transposeA = CLBlastTransposeNo;
	CLBlastTranspose transposeB = CLBlastTransposeNo;
	cl_assert(CLBlastSgemm(CLBlastLayoutRowMajor, transposeA, transposeB, 
				m, n, k, 
				alpha, A.handler, a_offset, a_ld, B.handler, b_offset, b_ld, 
				beta, C.handler, c_offset, c_ld, &q.handler, &e));
	*/
	clblast::Transpose transposeA = clblast::Transpose::kNo;
	clblast::Transpose transposeB = clblast::Transpose::kNo;
	cl_assert((cl_int)clblast::Gemm<type>(clblast::Layout::kRowMajor,
				transposeA, transposeB,
				m, n, k,
				alpha,
				A.handler, 0, a_ld,
				B.handler, 0, b_ld,
				beta,
				C.handler, 0, c_ld,
				&q.handler, &e));
	return event(e);
}
}
}
#endif
