CC     = nvcc
DEBUG  = -g
CUDA_DIR = /gpfs/software/cuda/9.1/toolkit/lib64 
MAGMA_DIR = /gpfs/home/shyyuan/local/magma-2.4.0/lib/
LAPACK_DIR=/gpfs/home/shyyuan/local/lapack-3.8.0
LIBS = -L $(CUDA_DIR) -L $(MAGMA_DIR) -L $(LAPACK_DIR)

INCS = -I /usr/local/cuda-8.0/include -I /gpfs/home/shyyuan/local/magma-2.4.0/include/
CFLAGS = $(DEBUG) $(INCS) $(LIBS) -DADD_ 

all: qr
qr: qr_solver.cu
	$(CC) $(CFLAGS) -o qr qr_solver.cu  -lcudart -lcublas -lcusolver -lmagma -llapacke -llapack -lrefblas -lgfortran 

