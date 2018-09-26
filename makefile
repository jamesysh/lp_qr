CC     = pgc++
DEBUG  = -g
CUDA_DIR = /gpfs/software/cuda/9.1/toolkit/lib64 
MAGMA_DIR = /gpfs/home/shyyuan/Desktop/local/magma-2.4.0/lib/
INCS = -I /usr/local/cuda-8.0/include -I /gpfs/home/shyyuan/Desktop/local/magma-2.4.0/include/
LIBS = -L $(CUDA_DIR) -L $(MAGMA_DIR)
CFLAGS = $(DEBUG) $(INCS) $(LIBS) -DADD_ 

all: qr
qr: qr_solver.cpp
	$(CC) $(CFLAGS) -o qr qr_solver.cpp  -lcudart -lcublas -lcusolver -lmagma
