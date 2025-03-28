#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <omp.h>

void count_words(const std::string& filename) {
    std::ifstream file(filename);
    std::unordered_map<std::string, int> word_count;
    std::vector<std::string> words;
    std::string word;

    while (file >> word) {
        words.push_back(word);
    }

    // OpenMP ile paralel kelime sayımı
    #pragma omp parallel for
    for (size_t i = 0; i < words.size(); i++) {
        #pragma omp critical
        word_count[words[i]]++;
    }

    // Sonuçları yazdır
    for (const auto& pair : word_count) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

int main() {
    count_words("/app/data/text.txt");
    return 0;
}
