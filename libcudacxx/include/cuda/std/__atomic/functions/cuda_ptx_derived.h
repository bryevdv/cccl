//===----------------------------------------------------------------------===//
//
// Part of libcu++, the C++ Standard Library for your entire system,
// under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES.
//
//===----------------------------------------------------------------------===//

#ifndef __LIBCUDACXX___ATOMIC_FUNCTIONS_DERIVED_H
#define __LIBCUDACXX___ATOMIC_FUNCTIONS_DERIVED_H

#include <cuda/std/detail/__config>

#include "cuda_ptx_generated.h"

#if defined(_CCCL_IMPLICIT_SYSTEM_HEADER_GCC)
#  pragma GCC system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_CLANG)
#  pragma clang system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_MSVC)
#  pragma system_header
#endif // no system header

#include <cuda/std/__atomic/functions/cuda_ptx_generated.h>
#include <cuda/std/__type_traits/conditional.h>
#include <cuda/std/__type_traits/enable_if.h>
#include <cuda/std/__type_traits/is_scalar.h>
#include <cuda/std/cstdint>

_LIBCUDACXX_BEGIN_NAMESPACE_STD

#if defined(_CCCL_CUDA_COMPILER)

template <class... _Types, class _Scope>
static inline _CCCL_DEVICE void __cuda_atomic_dispatch_rmw(_Types... _args, _Scope)
{
  constexpr __atomic_scope_constraint<_Scope> __sco{};
  constexpr __atomic_membar_scope_constraint<_Scope> __membar_sco{};
  constexpr _Tag __tag{};
  NV_DISPATCH_TARGET(
    NV_PROVIDES_SM_70,
    (switch (__stronger_order_cuda(__success_memorder, __failure_memorder)) {
      case __ATOMIC_SEQ_CST:
        __cuda_fence(__sco, __atomic_memorder_constraint_seq_cst{});
        _CCCL_FALLTHROUGH();
      case __ATOMIC_CONSUME:
        _CCCL_FALLTHROUGH();
      case __ATOMIC_ACQUIRE:
        __cuda_atomic_compare_exchange(
          __ptr, *__expected, __old, __desired, __tag, __sco, __atomic_memorder_constraint_acquire{});
        break;
      case __ATOMIC_ACQ_REL:
        __cuda_atomic_compare_exchange(
          __ptr, *__expected, __old, __desired, __tag, __sco, __atomic_memorder_constraint_acq_rel{});
        break;
      case __ATOMIC_RELEASE:
        __cuda_atomic_compare_exchange(
          __ptr, *__expected, __old, __desired, __tag, __sco, __atomic_memorder_constraint_release{});
        break;
      case __ATOMIC_RELAXED:
        __cuda_atomic_compare_exchange(
          __ptr, *__expected, __old, __desired, __tag, __sco, __atomic_memorder_constraint_relaxed{});
        break;
      default:
        assert(0);
    }),
    NV_IS_DEVICE,
    (switch (__stronger_order_cuda(__success_memorder, __failure_memorder)) {
      case __ATOMIC_SEQ_CST:
        _CCCL_FALLTHROUGH();
      case __ATOMIC_ACQ_REL:
        __cuda_membar(__membar_sco);
        _CCCL_FALLTHROUGH();
      case __ATOMIC_CONSUME:
        _CCCL_FALLTHROUGH();
      case __ATOMIC_ACQUIRE:
        __cuda_atomic_compare_exchange(
          __ptr, *__expected, __old, __desired, __tag, __sco, __atomic_memorder_constraint_volatile{});
        __cuda_membar_block();
        break;
      case __ATOMIC_RELEASE:
        __cuda_membar_block();
        __cuda_atomic_compare_exchange(
          __ptr, *__expected, __old, __desired, __tag, __sco, __atomic_memorder_constraint_volatile{});
        break;
      case __ATOMIC_RELAXED:
        __cuda_atomic_compare_exchange(
          __ptr, *__expected, __old, __desired, __tag, __sco, __atomic_memorder_constraint_volatile{});
        break;
      default:
        assert(0);
    }))

  return (__old == *__expected);
}

template <class _Type, class _Scope, class _Tag>
static inline _CCCL_DEVICE void
__cuda_atomic_compare_exchange(_Type* __ptr, _Type& __dst, _Type __cmp, _Type __op, _Tag, _Scope)
{
  constexpr __atomic_scope_constraint<_Scope> __sco{};
  constexpr __atomic_membar_scope_constraint<_Scope> __membar_sco{};
  constexpr _Tag __tag{};
  NV_DISPATCH_TARGET(
    NV_PROVIDES_SM_70,
    (switch (__stronger_order_cuda(__success_memorder, __failure_memorder)) {
      case __ATOMIC_SEQ_CST:
        __cuda_fence(__sco, __atomic_memorder_constraint_seq_cst{});
        _CCCL_FALLTHROUGH();
      case __ATOMIC_CONSUME:
        _CCCL_FALLTHROUGH();
      case __ATOMIC_ACQUIRE:
        __cuda_atomic_compare_exchange(
          __ptr, *__expected, __old, __desired, __tag, __sco, __atomic_memorder_constraint_acquire{});
        break;
      case __ATOMIC_ACQ_REL:
        __cuda_atomic_compare_exchange(
          __ptr, *__expected, __old, __desired, __tag, __sco, __atomic_memorder_constraint_acq_rel{});
        break;
      case __ATOMIC_RELEASE:
        __cuda_atomic_compare_exchange(
          __ptr, *__expected, __old, __desired, __tag, __sco, __atomic_memorder_constraint_release{});
        break;
      case __ATOMIC_RELAXED:
        __cuda_atomic_compare_exchange(
          __ptr, *__expected, __old, __desired, __tag, __sco, __atomic_memorder_constraint_relaxed{});
        break;
      default:
        assert(0);
    }),
    NV_IS_DEVICE,
    (switch (__stronger_order_cuda(__success_memorder, __failure_memorder)) {
      case __ATOMIC_SEQ_CST:
        _CCCL_FALLTHROUGH();
      case __ATOMIC_ACQ_REL:
        __cuda_membar(__membar_sco);
        _CCCL_FALLTHROUGH();
      case __ATOMIC_CONSUME:
        _CCCL_FALLTHROUGH();
      case __ATOMIC_ACQUIRE:
        __cuda_atomic_compare_exchange(
          __ptr, *__expected, __old, __desired, __tag, __sco, __atomic_memorder_constraint_volatile{});
        __cuda_membar_block();
        break;
      case __ATOMIC_RELEASE:
        __cuda_membar_block();
        __cuda_atomic_compare_exchange(
          __ptr, *__expected, __old, __desired, __tag, __sco, __atomic_memorder_constraint_volatile{});
        break;
      case __ATOMIC_RELAXED:
        __cuda_atomic_compare_exchange(
          __ptr, *__expected, __old, __desired, __tag, __sco, __atomic_memorder_constraint_volatile{});
        break;
      default:
        assert(0);
    }))

  return (__old == *__expected);
}

template <typename _Tp, typename _Sco>
_CCCL_DEVICE bool __atomic_compare_exchange_cuda(
  _Tp volatile* __ptr,
  _Tp* __expected,
  const _Tp __desired,
  bool __weak,
  int __success_memorder,
  int __failure_memorder,
  _Sco)
{
  using __proxy_t  = _If<sizeof(_Tp) == 4, uint32_t, uint64_t>;
  using __op_tag_t = __atomic_operand_tag<__atomic_operand_type::_b, sizeof(__proxy_t) * 8>;

  volatile __proxy_t* __atom = reinterpret_cast<volatile __proxy_t*>(__ptr);
  __proxy_t* __old           = reinterpret_cast<__proxy_t*>(__expected);
  __proxy_t __new            = *reinterpret_cast<__proxy_t*>(&__desired);

  bool __result = __cuda_atomic_compare_exchange(
    __atom, *__old, *__old, __new, __weak, __success_memorder, __failure_memorder, _Sco{});
  return __result;
}

template <typename _Tp,
          typename _Sco,
          __enable_if_t<!is_scalar<_Tp>::value && (sizeof(_Tp) == 4 || sizeof(_Tp) == 8), int> = 0>
_CCCL_DEVICE bool __atomic_compare_exchange_cuda(
  void volatile* __ptr,
  _Tp* __expected,
  const _Tp __desired,
  bool __weak,
  int __success_memorder,
  int __failure_memorder,
  _Sco)
{
  using __proxy_t = _If<sizeof(_Tp) == 4, uint32_t, uint64_t>;
  __proxy_t __old = 0;
  __proxy_t __new = 0;
  memcpy(&__old, __expected, sizeof(__proxy_t));
  memcpy(&__new, &__desired, sizeof(__proxy_t));
  bool __result =
    __atomic_compare_exchange_cuda(__ptr, &__old, __new, __weak, __success_memorder, __failure_memorder, _Sco{});
  memcpy(__expected, &__old, sizeof(__proxy_t));
  return __result;
}
template <typename _Tp,
          typename _Sco,
          __enable_if_t<!is_scalar<_Tp>::value && (sizeof(_Tp) == 4 || sizeof(_Tp) == 8), int> = 0>
_CCCL_DEVICE bool __atomic_compare_exchange_cuda(
  void* __ptr, _Tp* __expected, const _Tp __desired, bool __weak, int __success_memorder, int __failure_memorder, _Sco)
{
  using __proxy_t = _If<sizeof(_Tp) == 4, uint32_t, uint64_t>;
  __proxy_t __old = 0;
  __proxy_t __new = 0;
  memcpy(&__old, __expected, sizeof(__proxy_t));
  memcpy(&__new, &__desired, sizeof(__proxy_t));
  bool __result =
    __atomic_compare_exchange_cuda(__ptr, &__old, __new, __weak, __success_memorder, __failure_memorder, _Sco{});
  memcpy(__expected, &__old, sizeof(__proxy_t));
  return __result;
}
template <typename _Tp,
          typename _Sco,
          __enable_if_t<!is_scalar<_Tp>::value && (sizeof(_Tp) == 4 || sizeof(_Tp) == 8), int> = 0>
_CCCL_DEVICE void __atomic_exchange_cuda(void volatile* __ptr, _Tp* __val, _Tp* __ret, int __memorder, _Sco)
{
  using __proxy_t = _If<sizeof(_Tp) == 4, uint32_t, uint64_t>;
  __proxy_t __old = 0;
  __proxy_t __new = 0;
  memcpy(&__new, __val, sizeof(__proxy_t));
  __atomic_exchange_cuda(__ptr, &__new, &__old, __memorder, _Sco{});
  memcpy(__ret, &__old, sizeof(__proxy_t));
}
template <typename _Tp,
          typename _Sco,
          __enable_if_t<!is_scalar<_Tp>::value && (sizeof(_Tp) == 4 || sizeof(_Tp) == 8), int> = 0>
_CCCL_DEVICE void __atomic_exchange_cuda(void* __ptr, _Tp* __val, _Tp* __ret, int __memorder, _Sco)
{
  using __proxy_t = _If<sizeof(_Tp) == 4, uint32_t, uint64_t>;
  __proxy_t __old = 0;
  __proxy_t __new = 0;
  memcpy(&__new, __val, sizeof(__proxy_t));
  __atomic_exchange_cuda(__ptr, &__new, &__old, __memorder, _Sco{});
  memcpy(__ret, &__old, sizeof(__proxy_t));
}

template <typename _Tp, typename _Sco, __enable_if_t<sizeof(_Tp) <= 2, int> = 0>
_CCCL_DEVICE bool __atomic_compare_exchange_cuda(
  _Tp volatile* __ptr, _Tp* __expected, const _Tp __desired, bool, int __success_memorder, int __failure_memorder, _Sco)
{
  auto const __aligned = (uint32_t*) ((intptr_t) __ptr & ~(sizeof(uint32_t) - 1));
  auto const __offset  = uint32_t((intptr_t) __ptr & (sizeof(uint32_t) - 1)) * 8;
  auto const __mask    = ((1 << sizeof(_Tp) * 8) - 1) << __offset;

  uint32_t __old = *__expected << __offset;
  uint32_t __old_value;
  while (1)
  {
    __old_value = (__old & __mask) >> __offset;
    if (__old_value != *__expected)
    {
      break;
    }
    uint32_t const __attempt = (__old & ~__mask) | (*__desired << __offset);
    if (__atomic_compare_exchange_cuda(
          __aligned, &__old, &__attempt, true, __success_memorder, __failure_memorder, _Sco{}))
    {
      return true;
    }
  }
  *__expected = __old_value;
  return false;
}

template <typename _Tp, typename _Sco, __enable_if_t<sizeof(_Tp) <= 2, int> = 0>
_CCCL_DEVICE void __atomic_exchange_cuda(_Tp volatile* __ptr, _Tp* __val, _Tp* __ret, int __memorder, _Sco)
{
  _Tp __expected = __atomic_load_n_cuda(__ptr, __ATOMIC_RELAXED, _Sco{});
  while (!__atomic_compare_exchange_cuda(__ptr, &__expected, __val, true, __memorder, __memorder, _Sco{}))
    ;
  *__ret = __expected;
}

template <typename _Tp, typename _Up, typename _Sco, __enable_if_t<sizeof(_Tp) <= 2, int> = 0>
_CCCL_DEVICE _Tp __atomic_fetch_add_cuda(_Tp volatile* __ptr, _Up __val, int __memorder, _Sco)
{
  _Tp __expected = __atomic_load_n_cuda(__ptr, __ATOMIC_RELAXED, _Sco{});
  _Tp __desired  = __expected + __val;
  while (!__atomic_compare_exchange_cuda(__ptr, &__expected, __desired, true, __memorder, __memorder, _Sco{}))
  {
    __desired = __expected + __val;
  }
  return __expected;
}

template <typename _Tp,
          typename _Up,
          typename _Sco,
          __enable_if_t<sizeof(_Tp) <= 2 || _CUDA_VSTD::is_floating_point<_Tp>::value, int> = 0>
_CCCL_DEVICE _Tp __atomic_fetch_max_cuda(_Tp volatile* __ptr, _Up __val, int __memorder, _Sco)
{
  _Tp __expected = __atomic_load_n_cuda(__ptr, __ATOMIC_RELAXED, _Sco{});
  _Tp __desired  = __expected > __val ? __expected : __val;

  while (__desired == __val
         && !__atomic_compare_exchange_cuda(__ptr, &__expected, __desired, true, __memorder, __memorder, _Sco{}))
  {
    __desired = __expected > __val ? __expected : __val;
  }

  return __expected;
}

template <typename _Tp,
          typename _Up,
          typename _Sco,
          __enable_if_t<sizeof(_Tp) <= 2 || _CUDA_VSTD::is_floating_point<_Tp>::value, int> = 0>
_CCCL_DEVICE _Tp __atomic_fetch_min_cuda(_Tp volatile* __ptr, _Up __val, int __memorder, _Sco)
{
  _Tp __expected = __atomic_load_n_cuda(__ptr, __ATOMIC_RELAXED, _Sco{});
  _Tp __desired  = __expected < __val ? __expected : __val;

  while (__desired == __val
         && !__atomic_compare_exchange_cuda(__ptr, &__expected, __desired, true, __memorder, __memorder, _Sco{}))
  {
    __desired = __expected < __val ? __expected : __val;
  }

  return __expected;
}

template <typename _Tp, typename _Up, typename _Sco, __enable_if_t<sizeof(_Tp) <= 2, int> = 0>
_CCCL_DEVICE _Tp __atomic_fetch_sub_cuda(_Tp volatile* __ptr, _Up __val, int __memorder, _Sco)
{
  _Tp __expected = __atomic_load_n_cuda(__ptr, __ATOMIC_RELAXED, _Sco{});
  _Tp __desired  = __expected - __val;
  while (!__atomic_compare_exchange_cuda(__ptr, &__expected, __desired, true, __memorder, __memorder, _Sco{}))
  {
    __desired = __expected - __val;
  }
  return __expected;
}

template <typename _Tp, typename _Up, typename _Sco, __enable_if_t<sizeof(_Tp) <= 2, int> = 0>
_CCCL_DEVICE _Tp __atomic_fetch_and_cuda(_Tp volatile* __ptr, _Up __val, int __memorder, _Sco)
{
  _Tp __expected = __atomic_load_n_cuda(__ptr, __ATOMIC_RELAXED, _Sco{});
  _Tp __desired  = __expected & __val;
  while (!__atomic_compare_exchange_cuda(__ptr, &__expected, __desired, true, __memorder, __memorder, _Sco{}))
  {
    __desired = __expected & __val;
  }
  return __expected;
}

template <typename _Tp, typename _Up, typename _Sco, __enable_if_t<sizeof(_Tp) <= 2, int> = 0>
_CCCL_DEVICE _Tp __atomic_fetch_xor_cuda(_Tp volatile* __ptr, _Up __val, int __memorder, _Sco)
{
  _Tp __expected = __atomic_load_n_cuda(__ptr, __ATOMIC_RELAXED, _Sco{});
  _Tp __desired  = __expected ^ __val;
  while (!__atomic_compare_exchange_cuda(__ptr, &__expected, __desired, true, __memorder, __memorder, _Sco{}))
  {
    __desired = __expected ^ __val;
  }
  return __expected;
}

template <typename _Tp, typename _Up, typename _Sco, __enable_if_t<sizeof(_Tp) <= 2, int> = 0>
_CCCL_DEVICE _Tp __atomic_fetch_or_cuda(_Tp volatile* __ptr, _Up __val, int __memorder, _Sco)
{
  _Tp __expected = __atomic_load_n_cuda(__ptr, __ATOMIC_RELAXED, _Sco{});
  _Tp __desired  = __expected | __val;
  while (!__atomic_compare_exchange_cuda(__ptr, &__expected, __desired, true, __memorder, __memorder, _Sco{}))
  {
    __desired = __expected | __val;
  }
  return __expected;
}

template <typename _Tp, typename _Sco>
_CCCL_DEVICE _Tp __atomic_load_n_cuda(const _Tp volatile* __ptr, int __memorder, _Sco)
{
  _Tp __ret;
  __atomic_load_cuda(__ptr, &__ret, __memorder, _Sco{});
  return __ret;
}

template <typename _Tp, typename _Sco>
_CCCL_DEVICE void __atomic_store_n_cuda(_Tp volatile* __ptr, _Tp __val, int __memorder, _Sco)
{
  __atomic_store_cuda(__ptr, &__val, __memorder, _Sco{});
}

template <typename _Tp, typename _Sco>
_CCCL_DEVICE bool __atomic_compare_exchange_n_cuda(
  _Tp volatile* __ptr, _Tp* __expected, _Tp __desired, bool __weak, int __success_memorder, int __failure_memorder, _Sco)
{
  return __atomic_compare_exchange_cuda(
    __ptr, __expected, __desired, __weak, __success_memorder, __failure_memorder, _Sco{});
}

template <typename _Tp, typename _Sco>
_CCCL_DEVICE _Tp __atomic_exchange_n_cuda(_Tp volatile* __ptr, _Tp __val, int __memorder, _Sco)
{
  _Tp __ret;
  __atomic_exchange_cuda(__ptr, &__val, &__ret, __memorder, _Sco{});
  return __ret;
}

_CCCL_DEVICE static inline void __atomic_signal_fence_cuda(int)
{
  asm volatile("" ::: "memory");
}

#endif // defined(_CCCL_CUDA_COMPILER)

_LIBCUDACXX_END_NAMESPACE_STD

#endif // __LIBCUDACXX___ATOMIC_FUNCTIONS_DERIVED_H
