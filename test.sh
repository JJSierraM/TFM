make build

printf "Multiple threads no optimizations:\n"
for p in 2 4 8 16 24 32
do
    for n in 128 256 512 1024 2048 
    do
        printf "Num points: ${n}, num threads: ${p}\n"
        export OMP_NUM_THREADS=${p}
        time ./main $n
    done
done