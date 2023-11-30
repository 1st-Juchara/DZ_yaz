#include <iostream>
#include <fstream>
#include <vector>
#include "TimirbaevErik.h"

using namespace std;

vector<int> get_path(vector<vector<int>>& from, int start, int finish) {
	vector<int> path;
	for (int v = finish; v != -1; v = from[start][v])
		path.push_back(v);
	reverse(path.begin(), path.end());
	return path;
}

void floyd_warshall(vector<Edge>& edges, int vertex_count, int edge_count, const int INF) {

	vector<vector<int>> matrix(vertex_count, vector<int>(vertex_count, INF));

	vector<vector<int>> from(vertex_count, vector<int>(vertex_count, -1));

	for (int v = 0; v < vertex_count; v++) {
		matrix[v][v] = 0;
	}

	for (int i = 0; i < edge_count; i++) {
		int a, b, weight;
		a = edges[i].source;
		b = edges[i].dest;
		weight = edges[i].weight;

		if (matrix[a][b] > weight) {
			matrix[a][b] = weight;
			from[a][b] = a;
		}
	}

	for (int v = 0; v < vertex_count; v++) {
		for (int a = 0; a < vertex_count; a++) {
			if (matrix[a][v] != INF) {
				for (int b = 0; b < vertex_count; b++) {
					if (matrix[v][b] != INF && matrix[a][b] > matrix[a][v] + matrix[v][b]) {
						matrix[a][b] = matrix[a][v] + matrix[v][b];
						from[a][b] = from[v][b];
					}
				}
			}
		}
	}

	ofstream output_file;
	output_file.open("output.txt", ios::out);
	if (output_file.is_open()) {
		for (int a = 0; a < vertex_count; a++) {
			for (int b = 0; b < vertex_count; b++) {
				output_file << matrix[a][b] << "\t";
			}
			output_file << "\n";
		}

		output_file << endl << "The shortest path from 0 to 2" << endl << endl;

		for (int v : get_path(from, 0, 2))
			output_file << v << "\t";

		output_file.close();
	}
	else cout << "Error! File does not exist.";
}