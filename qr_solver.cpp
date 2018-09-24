/*************************************************************************
	> File Name: qr_solver.cpp
	> Author:James 
	> Mail: 
	> Created Time: Mon 24 Sep 2018 09:39:53 AM EDT
 ************************************************************************/

#include<iostream>
#include <cuda.h>
#include <cublas_v2.h>
#include <magma.h>
#include <magma_lapack.h>
#include <magma_v2.h>
using namespace std;


int main(){
    double A[12] = {1,2,3,4,5,6,7,6,5,4,3,2};
    //matrix initializing
    double *B;
    int m = 4;
    int n = 3;
    int lda = 4;
    int lddb = 4;

    int device = 0;
    magma_queue_t queue_setmatrix;
    magma_queue_create(device, &queue_setmatrix);
   
    
    
    
    return 0



}



