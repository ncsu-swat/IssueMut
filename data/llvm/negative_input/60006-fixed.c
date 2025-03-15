#include <immintrin.h>


__m128i expensive_call();
int pr60006() {
    __m128i call = expensive_call();
    return _mm_test_all_ones(call);
}