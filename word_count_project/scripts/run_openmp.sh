#!/bin/bash
cd /app/src
g++ -fopenmp word_count_openmp.cpp -o /app/build/word_count_openmp
echo "Running OpenMP word count..."
/app/build/word_count_openmp
