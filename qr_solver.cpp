/*************************************************************************
	> File Name: qr_solver.cpp
	> Author:James 
	> Mail: 
	> Created Time: Mon 24 Sep 2018 09:39:53 AM EDT
 ************************************************************************/

#include<iostream>
#include <cuda.h>
#include <cublas_v2.h>
#include <magma_lapack.h>
#include <magma_v2.h>
using namespace std;


int main(){
 
magma_int_t a =  magma_init();
cout<<a<<endl;
    double A[12] = {1,2,3,4,5,6,7,6,5,4,3,2};
    //matrix initializing
    double *B = new double[12];
    double *C = new double[12];
    int m = 4;
    int n = 3;
    int lda = 4;
    int lddb = 4;
    int device = 0;

    magma_queue_t queue_setmatrix;
    //set up magma queue
    magma_queue_create(device, &queue_setmatrix);
    magma_setmatrix(m,n,sizeof(double),A,lda,B,lddb,queue_setmatrix); 
    magma_getmatrix(m,n,sizeof(double),B,lddb,C,lda,queue_setmatrix);
    cout<<C[2]<<endl;
    magma_finalize();

    return 0;



}



