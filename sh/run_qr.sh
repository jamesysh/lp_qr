#!/bin/bash
#PBS -l nodes=1:ppn=2
#PBS -l walltime=00:02:00
#PBS -q gpu
#PBS -N QR_BATCHED
module load shared
module load pgi
module load cuda91
module load intel/mkl
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/Desktop/local/magma-2.4.0/lib/
cd ~/Desktop/lp_qr/
./qr
