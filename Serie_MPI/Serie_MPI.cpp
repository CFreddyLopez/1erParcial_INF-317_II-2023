#include <iostream>
#include <vector>
#include <mpi.h>

int calcularParPosicion(int position) {
    return position+1;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, num_procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    int n = 20; // Número de términos de Fibonacci a calcular
    std::vector<int> serie_local;

    for (int i = rank * 2; i < n; i += num_procs * 2) {
        // Agregar número par
        serie_local.push_back(i);
        // Agregar número Fibonacci
        int fib = calcularParPosicion(i + 1);
        serie_local.push_back(fib);
    }

    // Reunir todas las partes de la serie en el proceso raíz
    std::vector<int> serie_total;
    if (rank == 0) {
        serie_total.resize(n);
    }

    MPI_Gather(serie_local.data(), serie_local.size(), MPI_INT, serie_total.data(), serie_local.size(), MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Imprimir la serie intercalada
        std::cout << "Serie intercalada: ";
        for (int i = 0; i < n; i++) {
            std::cout << serie_total[i] << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}
