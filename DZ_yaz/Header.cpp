#include "Header.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

const int INF = INT_MAX / 2;

void Varligin(ifstream& fin)
{

    auto start = chrono::system_clock::now();

    int size = tryChoose(fin, 0, 9999);

    vector<vector<int>> a(size, vector<int>(size)); // матрица связей

    vector<vector<int>> d(size, vector<int>(size)); // минимальное расстояние

    vector<vector<int>> v(size, vector<int>(size)); // посещенные вершины

    int temp, minindex, min;

    // Инициализация матрицы связей
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                a[i][j] = 0;
            }
            else {
                a[i][j] = INT_MAX / 2;
            }
        }
    }

    // Ввод связей между вершинами
    int ways_cnt = tryChoose(fin, 0, 9999);

    for (int i = 0; i < ways_cnt; i++)
    {
        int index_1 = tryChoose(fin, 0, size - 1);
        int index_2 = tryChoose(fin, 0, size - 1);
        a[index_1][index_2] = tryChoose(fin, -9999, 9999);
    }

    // Вывод матрицы связей

    // Ввод начальной и конечной вершин
    //fin >> begin_index;
    //fin >> end_index;

    //Инициализация вершин и расстояний
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            d[i][j] = INT_MAX / 2;
            v[i][j] = 0;
        }
    //d[begin_index - 1] = 0;

    // Шаг алгоритма
    for (int index_ = 0; index_ < size; index_++)
    {
        d[index_][index_] = 0;
        for (int count = 0; count < size; count++)
        {
            min = INT_MAX / 2;
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
                if (!v[index_][i] && a[minindex][i] != INT_MAX / 2 && d[index_][minindex] != INT_MAX / 2 && d[index_][minindex] + a[minindex][i] < d[index_][i])
                {
                    d[index_][i] = d[index_][minindex] + a[minindex][i];
                }
            }
        }
    }

    auto finish = chrono::system_clock::now();
    auto time = chrono::duration_cast<chrono::microseconds>(finish - start).count();
    cout << "Time for method: " << time << " microseconds" << endl;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (d[i][j] == INF) {
                cout << "      INF";
            }
            else {
                cout << format("{:9}", d[i][j]);
            }
        }
        cout << endl;
    }
}