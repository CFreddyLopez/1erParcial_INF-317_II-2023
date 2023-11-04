using System;
using System.Collections.Generic;
using System.Threading;

class Program
{
    static int calcular_ParPosicion(int i)
    {
        return i + 1;
    }

    static int calcular_Cuadrado(int i)
    {
        int index = i / 2 + 1;
        return index * index + 1;
    }

    static List<int> generar_serie(int start, int end)
    {
        List<int> serie_parte = new List<int>();
        for (int i = start; i < end; i++)
        {
            if (i % 2 == 0)
            {
                serie_parte.Add(calcular_Cuadrado(i));
            }
            else
            {
                serie_parte.Add(calcular_ParPosicion(i));
            }
        }
        return serie_parte;
    }

    static void Main()
    {
        int n = 1000;
        int num_processes = 4;  
        int elements_per_process = n / num_processes;

        List<int>[] results = new List<int>[num_processes];
        Thread[] threads = new Thread[num_processes];

        for (int i = 0; i < num_processes; i++)
        {
            int processNumber = i;
            threads[i] = new Thread(() =>
            {
                int start = processNumber * elements_per_process;
                int end = start + elements_per_process;

                results[processNumber] = generar_serie(start, end);
            });
            threads[i].Start();
        }

        foreach (Thread thread in threads)
        {
            thread.Join();
        }

        List<int> all_series = new List<int>();
        for (int i = 0; i < num_processes; i++)
        {
            all_series.AddRange(results[i]);
        }

        Console.Write("Serie: ");
        foreach (int num in all_series)
        {
            Console.Write(num + " ");
        }
        Console.WriteLine();
    }
}
