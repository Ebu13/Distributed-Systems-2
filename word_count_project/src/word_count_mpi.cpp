#include <mpi.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>

void count_words(const std::vector<std::string>& words, std::unordered_map<std::string, int>& word_count) {
    for (const auto& word : words) {
        word_count[word]++;
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<std::string> words;
    std::unordered_map<std::string, int> local_word_count;

    if (rank == 0) {
        std::ifstream file("/app/data/text.txt");
        std::string word;
        while (file >> word) {
            words.push_back(word);
        }
    }

    // Düğüme özgü veri miktarını hesapla
    int chunk_size = words.size() / size;
    std::vector<std::string> local_words(chunk_size);

    // Veriyi dağıt (MPI_BYTE kullanıldı)
    MPI_Scatter(words.data(), chunk_size, MPI_BYTE, local_words.data(), chunk_size, MPI_BYTE, 0, MPI_COMM_WORLD);

    // Her düğümde kelime sayımını yap
    count_words(local_words, local_word_count);

    // Sonuçları topla
    std::unordered_map<std::string, int> global_word_count;
    for (auto& pair : local_word_count) {
        int global_count = 0;
        MPI_Reduce(&pair.second, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        if (rank == 0) {
            global_word_count[pair.first] = global_count;
        }
    }

    // Sonuçları yazdır
    if (rank == 0) {
        for (const auto& pair : global_word_count) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}
