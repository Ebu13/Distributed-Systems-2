#!/bin/bash

# SSH anahtarlarını ayarla
mkdir -p /root/.ssh
chmod 700 /root/.ssh
cp /root/.ssh/authorized_keys /root/.ssh/authorized_keys
chmod 600 /root/.ssh/authorized_keys
service ssh restart

echo "Compiling MPI program..."
mpicxx -o /app/build/word_count_mpi /app/src/word_count_mpi.cpp

echo "Running MPI word count..."
mpirun --allow-run-as-root --oversubscribe -np 4 /app/build/word_count_mpi /app/data/text.txt
