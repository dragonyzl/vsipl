/* Copyright (c) 2007 by CodeSourcery, LLC.  All rights reserved. */

/** @file    tests/vmul_sizes.cpp
    @author  Jules Bergmann
    @date    2007-03-16
    @brief   VSIPL++ Library: Check that range of vmul sizes are handled.
*/

/***********************************************************************
  Included Files
***********************************************************************/

#define VERBOSE 0

#if VERBOSE
#  include <iostream>
#endif

#include <vsip/initfin.hpp>
#include <vsip/support.hpp>
#include <vsip/vector.hpp>
#include <vsip/matrix.hpp>
#include <vsip/domain.hpp>
#include <vsip/random.hpp>

#include <vsip_csl/test.hpp>

using namespace vsip;
using vsip_csl::Almost_equal;

/***********************************************************************
  Definitions - Utility Functions
***********************************************************************/

template <typename T, storage_format_type C>
void
test_vmul(length_type len)
{
  typedef Layout<1, row1_type, dense, C> LP;
  typedef impl::Strided<1, T, LP> block_type;

  Rand<T> gen(0, 0);

  Vector<T, block_type> A(len);
  Vector<T, block_type> B(len);
  Vector<T, block_type> Z(len);

  A = gen.randu(len);
  B = gen.randu(len);

  Z = A * B;

  for (index_type i=0; i<len; ++i)
  {
#if VERBOSE
    if (!equal(Z.get(i), A.get(i) * B.get(i)))
    {
      std::cout << "Z(" << i << ")        = " << Z(i) << std::endl;
      std::cout << "A(" << i << ") * B(" << i << ") = "
		<< A(i) * B(i) << std::endl;
    }
#endif
    test_assert(Almost_equal<T>::eq(Z.get(i), A.get(i) * B.get(i)));
  }
}




template <typename T, storage_format_type C>
void
test_sweep()
{
  for (index_type i=1; i<=128; ++i)
    test_vmul<T, C>(i);
}

int
main(int argc, char** argv)
{
  vsipl init(argc, argv);

  test_sweep<float,          interleaved_complex>();
  test_sweep<complex<float>, interleaved_complex>();
  test_sweep<complex<float>, split_complex>();
}
