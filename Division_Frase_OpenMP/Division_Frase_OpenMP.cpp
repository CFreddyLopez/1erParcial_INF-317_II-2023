#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <omp.h>

int main() {
    std::string frase = "tres tristes tigres trigaban trigo por culpa del bolivar";
    int num_threads = 2; 

    std::vector<std::string> frases(num_threads);

    std::vector<std::string> palabras;
    std::stringstream ss(frase);
    std::string palabra;

    while (ss >> palabra) {
        palabras.push_back(palabra);
    }
    for (int i = 0; i < palabras.size(); i++) {
        std::cout << "Palabra " << i + 1 << ": " << palabras[i] << std::endl;
    }
    

#pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < palabras.size(); i++) {
        int thread_id = omp_get_thread_num();
        if (i % 2 == 0) {
            frases[0] += palabras[i] + " ";
        }
        else
        {
            frases[1] += palabras[i] + " ";
        }
    }
    for (int i = 0; i < 2; i++) {
        std::cout << "Frase " << i + 1 << ": " << frases[i] << std::endl;
    }

    return 0;
}
