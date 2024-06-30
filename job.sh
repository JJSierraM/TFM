#!/bin/sh
#SBATCH -t 06:00:00
#SBATCH --mem 128GB
#SBATCH -c 64
#SBATCH -o "test2-%J.out"

bash test.sh