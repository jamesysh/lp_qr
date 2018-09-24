CC     = pgc++
DEBUG  = -g
CUDA_DIR=/usr/local/cuda-8.0/lib64
MAGMA_DIR=/hpcgpfs01/software/magma/2.2.0-mkl-gnu/lib
INCS = -I /usr/local/cuda-8.0/include -I /hpcgpfs01/software/magma/2.2.0-mkl-gnu/include
LIBS = -L $(CUDA_DIR) -L $(MAGMA_DIR)
CFLAGS = $(DEBUG) $(INCS) $(LIBS) -DADD_ 

all: qr
qr: qr_solver.cpp
	$(CC) $(CFLAGS) -o qr qr_solver.cpp  -lcudart -lcublas -lcusolver -lmagma
