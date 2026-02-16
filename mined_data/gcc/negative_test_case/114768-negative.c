void test_no_bug(int *p) {
    *(volatile int *)p = *p;
}