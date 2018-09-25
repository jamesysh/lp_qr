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
    double D[12] = {5,4,7,8,0,1,4,2,6,8,4,1};
    //matrix initializing
    double *C_out1 ;
    double *C_out2;
    double* B_array[2];
    magma_int_t m = 4;
    magma_int_t n = 3;

    magma_dmalloc(&B_array[0],m*n);
    magma_dmalloc(&B_array[1],m*n);
   
    magma_int_t lda = 4;
    magma_int_t lddb = 4;
    magma_int_t device = 0;
    cout<<"init success"<<endl;
    ;
    cout<<"B success"<<endl; 
    magma_dmalloc_cpu(&C_out1,m*n);
    magma_dmalloc_cpu(&C_out2,m*n);
    cout<<"C success"<<endl;
    magma_queue_t queue_setmatrix = NULL;
    cout<<"allocate success"<<endl;
    //set up magma queue
    magma_queue_create(device, &queue_setmatrix);
    magma_setmatrix(m,n,sizeof(double),A,lda,B_array[0],lddb,queue_setmatrix); 
    magma_setmatrix(m,n,sizeof(double),D,lda,B_array[1],lddb,queue_setmatrix);
    cout<<"B value success"<<endl;
   
    magma_getmatrix(m,n,sizeof(double),B_array[1],lddb,C_out1,lda,queue_setmatrix);
   magma_queue_sync(queue_setmatrix );

 for(int i=0;i<12;i++){

	cout<<C_out1[i]<<endl;

}

   
    
    //cout<<C[2]<<endl;
 
    
   //----------------qr----------------------------
    
    double *TAU[2];
    magma_dmalloc_cpu(&TAU[1],3);
    magma_dmalloc_cpu(&TAU[0],3);
    magma_int_t info[2];
    magma_int_t batchid = 2;
    
    cout<<"QRi computation "<<endl;
    magma_dgeqrf_batched(m,n,B_array,4,TAU,info,batchid,queue_setmatrix);
    cout<<info[0]<<endl;
    magma_queue_sync(queue_setmatrix );
    magma_getmatrix(m,n,sizeof(double),B_array[1],lddb,C_out1,lda,queue_setmatrix);
     magma_queue_sync(queue_setmatrix );
    for(int i=0;i<12;i++){

	cout<<C_out1[i]<<endl;


    }

    free(C_out1);
    free(C_out2);
    for (int i=0;i<2;i++){
    magma_free(B_array[i]);
    }
    magma_queue_destroy(queue_setmatrix);

    magma_finalize();

    return 0;



}



