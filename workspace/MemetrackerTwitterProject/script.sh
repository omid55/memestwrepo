#!/bin/bash
#$ -cwd
#$ -S /bin/bash
#$ -o /agbs/cluster/oaskaris/workspace/MemetrackerTwitterProject/myoutputs
#$ -j y
#$ -p 100
#$ -l h_vmem=500G

export PATH=$PATH:/agbs/cluster/oaskaris/bin
make mpi;
./"$1"

#matlab -nodisplay nodesktop -nosplash -r "PackGeneration,exit"

