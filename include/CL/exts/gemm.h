#ifndef _GEMM_H_
#define _GEMM_H_
#include"CL/opencl/queue.h"
#include<clblast_c.h>
namespace cl {
	class clblast
	{
		public:
			template<class type>
			static event gemm(queue& q, size_t m, size_t n, size_t k, bool transposeA, bool transposeB, type alpha, type beta, const buffer& A, const buffer& B, buffer& C);
			static event gemm(queue& q, size_t m, size_t n, size_t k, bool transposeA, bool transposeB, float alpha, float beta, const buffer& A, const buffer& B, buffer& C);
	};
	event clblast::gemm(queue& q, size_t m, size_t n, size_t k, bool transposeA, bool transposeB, float alpha, float beta, const buffer& A, const buffer& B, buffer& C)
	{
		cl_event e;
		cl_assert(CLBlastSgemm(CLBlastLayoutRowMajor, (transposeA)?CLBlastTransposeYes:CLBlastTransposeNo, (transposeB)?CLBlastTransposeYes:CLBlastTransposeNo, m, n, k, alpha, A.handler, 0, 0, B.handler, 0, 0, beta, C.handler, 0, 0, &q.handler, &e));
		return event(e);
	}
}
#endif
