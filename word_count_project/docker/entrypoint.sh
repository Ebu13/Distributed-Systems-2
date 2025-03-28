#!/bin/bash
# SSH servisini başlat
service ssh start

# SSH yapılandırmasını yap
/setup_ssh.sh

# MPI veya OpenMP scriptlerini çalıştır
if [ "$HOSTNAME" == "master" ]; then
    echo "Starting MPI execution on Master node..."
    /app/scripts/run_mpi.sh
else
    echo "Worker node ready..."
    tail -f /dev/null
fi
