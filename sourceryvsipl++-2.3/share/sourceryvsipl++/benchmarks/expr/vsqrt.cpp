/* Copyright (c) 2009 by CodeSourcery.  All rights reserved.

   This file is available for license from CodeSourcery, Inc. under the terms
   of a commercial license and under the GPL.  It is not part of the VSIPL++
   reference implementation and is not available under the BSD license.
*/
/** @file    benchmarks/expr/vsqrt.cpp
    @author  Mike LeBlanc
    @date    2009-09-26
    @brief   VSIPL++ Library: Benchmark for vector square-root.

*/

/***********************************************************************
  Included Files
***********************************************************************/

#include <iostream>

#include <vsip/initfin.hpp>
#include <vsip/support.hpp>
#include <vsip/math.hpp>
#include <vsip/random.hpp>
#include <vsip/opt/assign_diagnostics.hpp>

#include "../benchmarks.hpp"

using namespace vsip;


/***********************************************************************
  Definitions - vector element-wise square-root
***********************************************************************/

template <typename T>
struct t_vsqrt1 : Benchmark_base
{
  char const* what() { return "t_vsqrt1"; }
  int ops_per_point(length_type)  { return 1; }
  int riob_per_point(length_type) { return 2*sizeof(T); }
  int wiob_per_point(length_type) { return 1*sizeof(T); }
  int mem_per_point(length_type)  { return 3*sizeof(T); }

  void operator()(length_type size, length_type loop, float& time)
    VSIP_IMPL_NOINLINE
  {
    Vector<T>   A(size, T());
    Vector<T>   C(size);

    Rand<T> gen(0, 0);
    A = gen.randu(size);

    A.put(0, T(16));

    vsip::impl::profile::Timer t1;
    
    t1.start();
    for (index_type l=0; l<loop; ++l)
      C = sqrt(A);
    t1.stop();
    
    if (!equal(C.get(0), T(4)))
    {
      std::cout << "t_vsqrt1: ERROR" << std::endl;
      abort();
    }

    for (index_type i=0; i<size; ++i)
      test_assert(equal(C.get(i), sqrt(A.get(i))));
    
    time = t1.delta();
  }

  void diag()
  {
    length_type const size = 256;

    Vector<T>   A(size, T());
    Vector<T>   C(size);

    impl::assign_diagnostics(C, sqrt(A));
  }
};








void
defaults(Loop1P&)
{
}



int
test(Loop1P& loop, int what)
{
  switch (what)
  {
  case  1: loop(t_vsqrt1<float>()); break;
  case  2: loop(t_vsqrt1<complex<float> >()); break;

  case  0:
    std::cout
      << "vsqrt -- vector square-root\n"
      << "                F  - float\n"
      << "                CF - complex<float>\n"
      << "   -1 -- vector element-wise square-root -- F/F \n"
      << "   -2 -- vector element-wise square-root -- CF/CF\n"
      ;
  default:
    return 0;
  }
  return 1;
}
