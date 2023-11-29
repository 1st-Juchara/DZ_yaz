#include <iostream>
#include "Header.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("Data_in.txt");
    Dijkstra(fin);
    fin.close();
}