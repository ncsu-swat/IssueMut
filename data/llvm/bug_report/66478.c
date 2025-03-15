#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "callbacks.h"
#include "register_emi.h"

int main( void )
{
    int numDevices = omp_get_num_devices();
    assert( numDevices > 0 );
    int srcDevice = 0;
    int dstDevice = numDevices > 1 ? 1 : 0;

    printf( "Allocating memory on device\n" );
    int* devicePtr = (int*) omp_target_alloc( sizeof(int), srcDevice );
    int* devicePtrRecv = (int*) omp_target_alloc( sizeof(int), dstDevice );
    int* hostPtr = (int*) malloc( sizeof(int) );
    *hostPtr = 42;

    printf( "Testing host to device\n" );
    omp_target_memcpy( devicePtr, hostPtr, sizeof(int), 0, 0, srcDevice, omp_get_initial_device() );

    printf( "Testing device to device\n" );
    omp_target_memcpy( devicePtrRecv, devicePtr, sizeof(int), 0, 0, dstDevice, srcDevice );

    printf( "Testing device to host\n" );
    omp_target_memcpy( hostPtr, devicePtrRecv, sizeof(int), 0, 0, omp_get_initial_device(), dstDevice );

    printf( "Checking correctness\n" );
    assert( *hostPtr == 42 );

    printf( "Freeing memory on device\n" );
    free( hostPtr );
    omp_target_free( devicePtr, srcDevice );
    omp_target_free( devicePtrRecv, dstDevice );
}
