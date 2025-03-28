# Base image
FROM ubuntu:latest

# Gerekli paketleri yükle
RUN apt-get update && apt-get install -y \
    build-essential \
    libopenmpi-dev \
    openmpi-bin \
    cmake \
    nano \
    iputils-ping \
    openssh-server

# SSH yapılandırması
RUN mkdir -p /run/sshd
RUN echo "PermitRootLogin yes" >> /etc/ssh/sshd_config
RUN echo "StrictHostKeyChecking no" >> /etc/ssh/ssh_config

# SSH anahtarlarını oluştur ve yetkilendir
RUN ssh-keygen -t rsa -N "" -f /root/.ssh/id_rsa
RUN cat /root/.ssh/id_rsa.pub >> /root/.ssh/authorized_keys

# Çalışma dizini oluştur
WORKDIR /app

# Klasörleri kopyala
COPY src/ ./src/
COPY data/ ./data/
COPY scripts/ ./scripts/

# build klasörünü oluştur
RUN mkdir -p /app/build

# Script dosyalarına çalıştırma izni ver
RUN chmod +x /app/scripts/*.sh

# Varsayılan komut (SSH sunucusunu başlat)
CMD ["/usr/sbin/sshd", "-D"]
