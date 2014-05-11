#!/bin/bash
#$ -cwd
#$ -S /bin/bash
#$ -o /agbs/cluster/oaskaris/workspace/MemetrackerTwitterProject/myoutputs
#$ -j y
#$ -p 100
#$ -l h_vmem=500G

echo ./"$1"
#matlab -nodisplay nodesktop -nosplash -r "PackGeneration,exit"

