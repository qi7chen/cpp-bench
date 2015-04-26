// Copyright (C) 2014 ichenq@gmail.com. All rights reserved.
// Distributed under the terms and conditions of the Apache License.
// See accompanying files LICENSE.

#pragma once

// portable version check
#ifndef __GNUC_PREREQ
# if defined __GNUC__ && defined __GNUC_MINOR__
#  define __GNUC_PREREQ(maj, min) ((__GNUC__ << 16) + __GNUC_MINOR__ >= \
                                   ((maj) << 16) + (min))
# else
#  define __GNUC_PREREQ(maj, min) 0
# endif
#endif

// 64 bit detection
#if defined(__x86_64__) || defined(_M_X64)
# define PLAT_X64  1
#else
# define PLAT_X64  0
#endif

// macro wrappers for C++11's "final" and "override" keywords
#if !defined(QSF_FINAL) && !defined(QSF_OVERRIDE)
# if defined(__clang__) || __GNUC_PREREQ(4, 7)
#  define FINAL     final
#  define OVERRIDE  override
# else
#  define FINAL
#  define OVERRIDE
# endif
#endif

#if defined(__GNUC__) && __GNUC__ >= 4
# define LIKELY(x)   (__builtin_expect((x), 1))
# define UNLIKELY(x) (__builtin_expect((x), 0))
#else
# define LIKELY(x)   (x)
# define UNLIKELY(x) (x)
#endif

#ifdef _MSC_VER
# define ATTR_ALIGN(x)        __declspec(align(x))
#include <cstddef>
typedef std::max_align_t MaxAlign;
#elif defined(__GNUC__)
# define ATTR_ALIGN(x)        __attribute__((aligned(x)))
struct MaxAlign { char c; } __attribute__((aligned));
#endif

// compiler specific attribute translation
// msvc should come first, so if clang is in msvc mode it gets the right defines

// NOTE: this will only do checking in msvc with versions that support /analyze
#if _MSC_VER
# ifdef _USE_ATTRIBUTES_FOR_SAL
#   undef _USE_ATTRIBUTES_FOR_SAL
# endif
# define _USE_ATTRIBUTES_FOR_SAL 1
# include <sal.h>
# define PRINTF_FORMAT _Printf_format_string_
# define PRINTF_FORMAT_ATTR(format_param, dots_param) /**/
#else
# define PRINTF_FORMAT /**/
# define PRINTF_FORMAT_ATTR(format_param, dots_param) \
  __attribute__((format(printf, format_param, dots_param)))
#endif

/* Platform specific TLS support
 * gcc implements __thread
 * msvc implements __declspec(thread)
 * the semantics are the same (but remember __thread is broken on apple)
 */
#if defined(_MSC_VER)
# define THREAD_LOCAL __declspec(thread)
#elif defined(__GNUC__) || defined(__clang__)
# define THREAD_LOCAL __thread
#else
# error cannot define platform specific thread local storage
#endif



// MSVC specific defines, mainly for posix compatibility
#ifdef _MSC_VER

// this definition is in a really silly place with a silly name
// and ifdefing it every time we want it is painful
#include <basetsd.h>
typedef SSIZE_T ssize_t;


// sprintf semantics are not exactly identical
// but current usage is not a problem
#define snprintf   sprintf_s

// semantics here are identical
#define strerror_r(errno,buf,len) strerror_s(buf,len,errno)

// compiler specific to compiler specific
#define __PRETTY_FUNCTION__    __FUNCSIG__

#define alignof     __alignof

// noexcept operator was not supported in MSVC 2013
#define noexcept       _NOEXCEPT

#endif // _MSC_VER
