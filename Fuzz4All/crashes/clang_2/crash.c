#include <stdlib.h>

#include <stdio.h>
#include <stdalign.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <stdatomic.h>
#include <threads.h>
#include <wchar.h>
#include <math.h>

struct someStruct
{
    aligned_alloc(16, 64) char arr[32];
    int i;
    char c;
} __attribute__((packed));

thread_local int count = 0;
thread_local int i;

void someCallbackFunction() __attribute__((callback_func));
void someCallbackFunction()
{
    unsigned int *count_ = (unsigned int *)&count;

    __atomic_add_fetch(count_, 7, __ATOMIC_RELAXED);
}

struct someStruct *function1() __attribute__((alloc_size(1, 2), regparm(3))) __attribute__((returns_twice));
struct someStruct *function1()
{
    return NULL;
}

struct someStruct *__attribute__((malloc, alloc_size(1, 2), regparm(3))) __attribute__((alloc_align(16)))
malloc_f1(int a, ...)
{
    va_list argumentPointer;
    va_start(argumentPointer, a);
    void *mem = malloc(a + 32);
    memset(mem, 0, a + 32);
    printf("%p\n", va_arg(argumentPointer, int *));
    int j = 2;
    va_end(argumentPointer);
    return mem;
}

void __attribute__((no_instrument_function)) noInstrumentFunction();

void __attribute__((noreturn)) voidFunction(void *a)
{
    exit(0);
}

typedef void (*t_void)(void *a);
t_void functionPointer(void (*callbackFunction)(void *callbackParameter), void *callbackParameter)
{
    return (t_void)callbackFunction;
}

typedef struct
{
    int someNumber;
} someStruct2;

bool someCondition() __attribute__((format_arg(3)));
bool someCondition()
{
    return true;
}

void checkCondition()
{
    someCondition();
}

struct someStruct *malloc(int size);

int main()
{
    const wchar_t *someCharacters = L"This is some characters";
    wchar_t c = 0;

    printf("%s\n", someCharacters);
    printf("%zx\n", sizeof("This is a char array"));
    printf("%c\n", 'A' - 1);
    printf("%c\n", __WCHAR_MIN__);
    printf("%c\n", c);

    printf("%d\n", a - b / c * d % e + f);
    printf("%ld\n", sizeof("0xffffffff"));
    printf("%d\n", isprint(' '));
    printf("%zu\n", strlen((const char *)(someCharacters + 1)));
    printf("%zu\n", sizeof("test") - 1);
    printf("%d\n", M_PI);
    wprintf(L"%d\n", M_E);

    printf("%lli\n", strtoll("0xffffffffffffffff", NULL, 10));
    printf("%llu\n", strtoull("0xffffffffffffffff", NULL, 10));
