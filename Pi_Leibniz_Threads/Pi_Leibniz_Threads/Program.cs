using System;
using System.Threading;

class Program
{
    static void Main()
    {
        int numIteraciones = 1000000;
        int numProcesadores = 3;
        int iteracionesPorProcesador = numIteraciones / numProcesadores;

        double[] resultados = new double[numProcesadores];
        Thread[] hilos = new Thread[numProcesadores];

        for (int i = 0; i < numProcesadores; i++)
        {
            int procesador = i;
            hilos[i] = new Thread(() =>
            {
                resultados[procesador] = Pi_Leibniz(iteracionesPorProcesador, procesador, numProcesadores);
            });
            hilos[i].Start();
        }
        
        foreach (var hilo in hilos)
        {
            hilo.Join();
        }

        double piEstimado = 0.0;
        foreach (var resultado in resultados)
        {
            piEstimado += resultado;
        }

        Console.WriteLine("Valor estimado de Pi es: " + piEstimado);
    }

    static double Pi_Leibniz(int numIteraciones, int inicio, int salto)
    {
        double suma = 0.0;

        for (int i = inicio; i < numIteraciones; i += salto)
        {
            double termino = 1.0 / (2 * i + 1);
            if (i % 2 == 0)
            {
                suma += termino;
            }
            else
            {
                suma -= termino;
            }
        }
        return 4.0 * suma;
    }
}
