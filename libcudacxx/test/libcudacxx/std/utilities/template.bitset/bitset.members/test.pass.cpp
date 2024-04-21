//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// bool test(size_t pos) const; // constexpr since C++23

#include <cuda/std/bitset>
#include <cuda/std/cassert>
#include <cuda/std/cstddef>

#include "../bitset_test_cases.h"
#include "test_macros.h"

_CCCL_NV_DIAG_SUPPRESS(186)

template <cuda::std::size_t N>
__host__ __device__ BITSET_TEST_CONSTEXPR void test_test()
{
  span_stub<const char*> const cases = get_test_cases<N>();
  for (cuda::std::size_t c = 0; c != cases.size(); ++c)
  {
    cuda::std::bitset<N> const v(cases[c]);
    if (v.size() > 0)
    {
      cuda::std::size_t middle = v.size() / 2;
      bool b                   = v.test(middle);
      assert(b == v[middle]);
    }
  }
}

__host__ __device__ BITSET_TEST_CONSTEXPR bool test()
{
  test_test<0>();
  test_test<1>();
  test_test<31>();
  test_test<32>();
  test_test<33>();
  test_test<63>();
  test_test<64>();
  test_test<65>();

  return true;
}

int main(int, char**)
{
  test();
  test_test<1000>(); // not in constexpr because of constexpr evaluation step limits
#if TEST_STD_VER > 2011 && !defined(_CCCL_CUDACC_BELOW_11_4) // 11.4 added support for constexpr device vars
                                                             // needed here
  static_assert(test(), "");
#endif

  return 0;
}