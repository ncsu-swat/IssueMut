// RUN: %clang_cc1 -fsyntax-only -verify -std=c23 %s

[[gnu::no_stack_protector]] void test1(void) {}
[[clang::no_stack_protector]] void test2(void) {}
