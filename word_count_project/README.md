# Word Count Project

Bu proje, büyük metin dosyalarındaki kelime sayısını paralel işlem teknikleri kullanarak hesaplamak amacıyla geliştirilmiştir. Proje, MPI (Message Passing Interface) ve OpenMP (Open Multi-Processing) kullanarak dağıtık ve paralel hesaplamayı gerçekleştirir. Docker ve Docker Compose kullanılarak birden fazla konteynerde çalışan bir yapı oluşturulmuştur.

## İçindekiler

- [Proje Tanıtımı](#proje-tanıtımı)
- [Kullanılan Teknolojiler](#kullanılan-teknolojiler)
- [Proje Yapısı](#proje-yapısı)
- [Kurulum ve Çalıştırma](#kurulum-ve-çalıştırma)
- [Çalıştırma Adımları](#çalıştırma-adımları)

## Proje Tanıtımı

Bu proje, büyük boyutlu metin dosyalarındaki kelimeleri sayarak, verimli bir şekilde analiz yapmayı hedefler. İki farklı paralel işleme tekniği kullanılır:
1. **MPI** (Message Passing Interface) ile çoklu düğümler üzerinden dağıtık işlem.
2. **OpenMP** (Open Multi-Processing) ile tek bir düğümde çoklu iş parçacığı kullanarak paralel işlem.

Proje Docker konteynerlerinde çalışacak şekilde yapılandırılmıştır, böylece kolayca dağıtılabilir ve ölçeklenebilir.

## Kullanılan Teknolojiler

- **MPI** (Message Passing Interface): Dağıtık işlem için kullanılır.
- **OpenMP** (Open Multi-Processing): Paralel iş parçacığı kullanarak hesaplama yapılır.
- **Docker**: Uygulamanın konteynerize edilmesini sağlar.
- **Docker Compose**: Çoklu konteynerli yapı kurulumunu yönetir.
- **C++**: Hesaplamalar için kullanılan ana programlama dili.

## Proje Yapısı
```bash
word_count_project/
│
├── data/                    # Veri dosyaları (text.txt)
│   └── data.py              # Rastgele metin üretmek için kullanılan Python script'i
│
├── docker/                  # Docker yapılandırma dosyaları
│   ├── Dockerfile           # Docker imajı için yapılandırma
│   ├── entrypoint.sh        # Başlatıcı script
│   ├── setup_ssh.sh         # SSH yapılandırma script'i
│   └── run_mpi.sh           # MPI ile çalıştırılacak script
│
├── scripts/                 # Yardımcı script'ler
│   ├── run_mpi.sh           # MPI işlemi için çalıştırma script'i
│   └── run_openmp.sh        # OpenMP işlemi için çalıştırma script'i
│
├── src/                     # Kaynak kodları
│   ├── word_count_mpi.cpp   # MPI ile kelime sayımı
│   └── word_count_openmp.cpp # OpenMP ile kelime sayımı
│
├── docker-compose.yml       # Docker Compose yapılandırma dosyası
└── README.md                # Proje dökümantasyonu
```


## Kurulum ve Çalıştırma

1. **Gerekli araçların yüklü olduğundan emin olun**:
    - Docker
    - Docker Compose

2. **Projeyi Klonlayın**:
    ```bash
    git clone https://github.com/Ebu13/Distributed-Systems-2.git
    cd word_count_project
    ```

3. **Gerekli Python paketlerini yükleyin** (metin oluşturma için öncelikle python sanal ortamında olmak lazım):
    ```bash
    pip install lorem
    ```

4. **Metin dosyasını oluşturun**:
    ```bash
    python data/data.py
    ```
    Bu komut, `data/text.txt` dosyasını oluşturacaktır.

5. **Docker konteynerlerini oluşturun ve başlatın**:
    ```bash
    docker-compose build
    docker-compose up
    ```

   Bu komut, master ve worker konteynerlerini başlatacak ve MPI işlemi master konteynerinde çalışacaktır.

## Çalıştırma Adımları

1. **Metin Üretimi**:
    - `data/data.py` script'i, `text.txt` dosyasını oluşturur. Bu dosya 150.000 kelime içerir.
  
2. **Docker Konteynerlerini Başlatma**:
    - `docker-compose up` komutu ile, Docker Compose ile konteynerler başlatılır.
    - `master` konteyneri, MPI programını çalıştıracak ve kelime sayımını gerçekleştirecektir.
    - `worker` konteynerleri, hesaplamaya yardımcı olacak ve yükü paylaşacaktır.

3. **MPI veya OpenMP Çalıştırma**:
    - Master konteyner, `run_mpi.sh` script'i aracılığıyla MPI işlemini başlatır.
    - Eğer OpenMP kullanılacaksa, `run_openmp.sh` script'i devreye girer.
