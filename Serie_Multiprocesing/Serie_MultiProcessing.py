# -*- coding: utf-8 -*-
"""
Created on Tue Oct 31 06:18:35 2023

@author: fredd
"""

import multiprocessing

def calcular_ParPosicion(i):
    return i+1

def calcular_Cuadrado(i):
    index=int(i/2)
    index+=1
    return index*index + 1

def generar_serie(start, end):
    serie_parte = []
    for i in range(start, end):
        if i % 2 == 0:
            serie_parte.append(calcular_Cuadrado(i))
        else:
            serie_parte.append(calcular_ParPosicion(i))
    return serie_parte

if __name__ == '__main__':
    n = 10000  
    num_processes = 2  
    pool = multiprocessing.Pool(processes=num_processes)
    ranges = [(i, i + n // num_processes) for i in range(0, n, n // num_processes)]
    results = pool.starmap(generar_serie, ranges)
    serie_intercalada = [num for sublist in results for num in sublist]
    
    print("Serie :", serie_intercalada)
