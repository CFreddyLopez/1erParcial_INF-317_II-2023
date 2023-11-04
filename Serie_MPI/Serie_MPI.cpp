#include <iostream>
#include <vector>
#include <mpi.h>

int calcular_ParPosicion(int i) {
    return i + 1;
}

int calcular_Cuadrado(int i) {
    int index = i / 2 + 1;
    return index * index + 1;
}

std::vector<int> generar_serie(int start, int end) {
    std::vector<int> serie_parte;
    for (int i = start; i < end; i++) {
        if (i % 2 == 0) {
            serie_parte.push_back(calcular_Cuadrado(i));
        }
        else {
            serie_parte.push_back(calcular_ParPosicion(i));
        }
    }
    return serie_parte;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, num_processes;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

    int n = 1000;
    int elements_per_process = n / num_processes;

    int start = rank * elements_per_process;
    int end = start + elements_per_process;

    std::vector<int> local_series = generar_serie(start, end);

    std::vector<int> all_series;
    if (rank == 0) {
        all_series.resize(n);
    }

    MPI_Gather(local_series.data(), elements_per_process, MPI_INT, all_series.data(), elements_per_process, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        
        std::cout << "Serie: ";
        for (int num : all_series) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}
