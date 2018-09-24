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
 
    magma_init();
    double A[12] = {1,2,3,4,5,6,7,6,5,4,3,2};
    //matrix initializing
    double *B = new double[12];
    double *C = new double[12];
    magma_int_t m = 4;
    magma_int_t n = 3;
    magma_int_t lda = 4;
    magma_int_t lddb = 4;
    magma_int_t device = 0;

    magma_queue_t queue_setmatrix;
    //set up magma queue
    magma_queue_create(device, &queue_setmatrix);
    magma_setmatrix(m,n,sizeof(double),A,lda,B,lddb,queue_setmatrix); 
    double **B_array = &B;

    //cout<<C[2]<<endl;
 
    
   //----------------qr----------------------------
    
    double **TAU;
    magma_int_t *info;
    magma_int_t batchid = 0;
    
    magma_queue_t queue_qr;
    magma_queue_create(device,&queue_qr);
    magma_dgeqrf_batched(m,n,B_array,lda,TAU,info,batchid,queue_qr);
    magma_getmatrix(m,n,sizeof(double),B,lddb,C,lda,queue_setmatrix);
   
    for(int i=0;i<12;i++){

	cout<<C[i]<<endl;

}

    magma_finalize();

    return 0;



}



