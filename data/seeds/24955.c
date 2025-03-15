// RUN: %clang_cc1 -fsyntax-only %s -Winvalid-utf8 -verify
// expected-no-diagnostics

// § § § 😀 你好 ©

/*§ § § 😀 你好 ©*/

/*
§ § § 😀 你好 ©©©
*/

/* § § § 😀 你好 © */
/*
    a longer comment to exerce the vectorized code path
    ----------------------------------------------------
    αααααααααααααααααααααα      // here is some unicode
    ----------------------------------------------------
    ----------------------------------------------------
*/

// The following test checks that a short comment is not merged
// with a subsequent long comment containing utf-8
enum a {
  x /* 01234567890ABCDEF*/
};
/*ααααααααα*/
