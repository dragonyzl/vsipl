/* Copyright (c) 2009 by CodeSourcery.  All rights reserved. */

/** @file    vsip/core/c++0x.hpp
    @author  Stefan Seefeld
    @date    2009-07-06
    @brief   VSIPL++ Library: C++0x bits that we can't use from libstdc++ just yet.
*/

#ifndef VSIP_CORE_CXX0X_HPP
#define VSIP_CORE_CXX0X_HPP

namespace vsip
{
namespace impl
{

template <typename T, T v>
struct integral_constant
{
  static const T value = v;
  typedef T value_type;
  typedef integral_constant<T, v> type;
};

template <typename T, T v>
const T integral_constant<T, v>::value;

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template <bool B, typename T = void>
struct enable_if_c { typedef T type;};

template <typename T>
struct enable_if_c<false, T> {};

/// Define a nested type if some predicate holds.
template <typename C, typename T = void>
struct enable_if : public enable_if_c<C::value, T> {};

/// A conditional expression, but for types. If true, first, if false, second.
template<bool B, typename Iftrue, typename Iffalse>
struct conditional
{
  typedef Iftrue type;
};

template<typename Iftrue, typename Iffalse>
struct conditional<false, Iftrue, Iffalse>
{
  typedef Iffalse type;
};

template <typename T1, typename T2> struct is_same : false_type {};
template <typename T> struct is_same<T, T> : true_type {};

template <typename> struct is_const : public false_type {};
template <typename T> struct is_const<T const> : public true_type {};

template <typename> struct is_volatile : public false_type {};
template <typename T> struct is_volatile<T volatile> : public true_type {};

template <typename T> struct remove_const { typedef T type;};
template <typename T> struct remove_const<T const> { typedef T type;};

template <typename T> struct remove_volatile { typedef T type;};
template <typename T> struct remove_volatile<T volatile> { typedef T type;};

template <typename T> struct remove_cv 
{
  typedef typename remove_const<typename remove_volatile<T>::type>::type type;
};
  
template <typename T> struct add_const { typedef T const type;};
template <typename T> struct add_volatile { typedef T volatile type;};
template <typename T> struct add_cv 
{
  typedef typename
  add_const<typename add_volatile<T>::type>::type type;
};


} // namespace vsip::impl
} // namespace vsip

#endif