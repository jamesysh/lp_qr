/*************************************************************************
	> File Name: qr_solver.cpp
	> Author:James 
	> Mail: 
	> Created Time: Mon 24 Sep 2018 09:39:53 AM EDT
 ************************************************************************/

#include<iostream>
#include <cuda.h>
#include <cuda_runtime_api.h>
#include <cublas_v2.h>
#include <magma_lapack.h>
#include <magma_v2.h>
using namespace std;


int main(){

    magma_init();
    magma_int_t dev_t;
    magma_getdevice(&dev_t);
    magma_queue_t queue_qr = NULL;
    magma_int_t dev = dev_t;
    magma_queue_create(dev,&queue_qr);
    //set up device and queue
    magma_int_t m = 9;
    magma_int_t n = 5;
    magma_int_t mn = m*n;
    magma_int_t min_mn = min(m,n);
    magma_int_t lda = 9;
    int num  = 10;
//array of pointers on cpu
    double* a[num];
    for(int i=0;i<num;i++){
  	 a[i] = new double[mn];
    }
    //initialize matrix
    for(int j=0;j<num;j++){
         for(int i=0;i<mn;++i){
       		 a[j][i] = i+j;
    	 }
    }
//array of points in gpu
    double** B_array;
    cudaMalloc((void**)&B_array,num*sizeof(double*));
    double *tem_B[num];
    for(int i=0;i<num;i++){
	cudaMalloc((void**)&tem_B[i],sizeof(double)*mn);
    
	}
    cout<<"----------------------------Coefficient matrices-------------------------------------------"<<endl;
    for(int i=0;i<num;i++){
        cudaMemcpy(tem_B[i], a[i], mn*sizeof(double), cudaMemcpyHostToDevice);
        magma_dprint_gpu(m,n,tem_B[i],lda,queue_qr);
    }	
    cudaMemcpy(B_array, tem_B, sizeof(tem_B), cudaMemcpyHostToDevice);


    cout<<"----------------------------------init success----------------------------------------------"<<endl;

   
    
   //----------------qr----------------------------
//variables need by qr    
    double **Tau;
    cudaMalloc((void**)&Tau,num*sizeof(double*));
    double* tem_T[num];
    for(int i=0;i<num;i++){
        cudaMalloc((void**)&tem_T[i],sizeof(double)*min_mn);
    }



    cudaMemcpy(Tau, tem_T, sizeof(tem_T), cudaMemcpyHostToDevice);  
    magma_int_t* info;
    cudaMalloc((void**)&info,num*sizeof(magma_int_t));
    magma_int_t batchid = num;
   
	
    cout<<"---------------------------------QR computation results----------------------------------- "<<endl;
    magma_dgeqrf_batched(m,n,B_array,lda,Tau,info,batchid,queue_qr);
    magma_queue_sync(queue_qr);
    for(int i=0;i<num;i++){
        magma_dprint_gpu(m,n,tem_B[i],lda,queue_qr);
    }
    for(int i=0;i<num;i++){
       free(a[i]);
        }

    for(int i=0;i<num;i++){
        cudaFree(tem_B[i]);
        }
    cudaFree(B_array);

    for(int i=0;i<num;i++){
        cudaFree(tem_T[i]);
        }
    cudaFree(Tau);
    cudaFree(info);

  



    magma_queue_destroy(queue_qr);
    magma_finalize();


    return EXIT_SUCCESS;

}

