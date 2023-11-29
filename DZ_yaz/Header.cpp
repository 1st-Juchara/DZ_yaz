#include "Header.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

void Dijkstra(ifstream& fin)
{
    int size;
    fin >> size;

    int** a = (int**)malloc(size * sizeof(int*)); // матрица связей
    for (int i = 0; i < size; i++) {
        a[i] = (int*)malloc(size * sizeof(int));
    }

    int** d = (int**)malloc(size * sizeof(int*)); // минимальное расстояние
    for (int i = 0; i < size; i++) {
        d[i] = (int*)malloc(size * sizeof(int));
    }

    int** v = (int**)malloc(size * sizeof(int*)); // посещенные вершины
    for (int i = 0; i < size; i++) {
        v[i] = (int*)malloc(size * sizeof(int));
    }

    int temp, minindex, min;

    // Инициализация матрицы связей
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                a[i][j] = 0;
            }
            else {
                a[i][j] = INT_MAX/2;
            }
        }
    }

    // Ввод связей между вершинами
    int ways_cnt;
    fin >> ways_cnt;
    for (int i = 0; i < ways_cnt; i++)
    {
        int index1, index2;
        fin >> index1;
        fin >> index2;
        fin >> a[index1-1][index2-1];
    }

    // Вывод матрицы связей

    // Ввод начальной и конечной вершин
    //fin >> begin_index;
    //fin >> end_index;

    //Инициализация вершин и расстояний
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            d[i][j] = INT_MAX/2;
            v[i][j] = 0;
        }
    //d[begin_index - 1] = 0;

    // Шаг алгоритма
    for (int index_ = 0; index_ < size; index_++)
    {
        d[index_][index_] = 0;
        for (int count = 0; count < size; count++)
        {
            min = INT_MAX/2;
            for (int i = 0; i < size; i++)
            {
                if (v[index_][i] == 0 && d[index_][i] <= min)
                {
                    min = d[index_][i];
                    minindex = i;
                }
            }

            v[index_][minindex] = 1;

            for (int i = 0; i < size; i++)
            {
                if (!v[index_][i] && a[minindex][i] != INT_MAX/2 && d[index_][minindex] != INT_MAX/2 && d[index_][minindex] + a[minindex][i] < d[index_][i])
                {
                    d[index_][i] = d[index_][minindex] + a[minindex][i];
                }
            }
        }
    }

    // Восстановление пути
    int* ver = (int*)malloc(size * sizeof(int)); // массив посещенных вершин
    //int end = end_index - 1; // индекс конечной вершины
    //ver[0] = end + 1; // начальный элемент

    // Освобождение памяти
    for (int i = 0; i < size; i++) {
        free(a[i]);
    }
    for (int i = 0; i < size; i++) {
        free(d[i]);
    }
    for (int i = 0; i < size; i++) {
        free(v[i]);
    }
    free(a);
    free(d);
    free(v);
}