#include "FordFulkerson.h"
#include "queue.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int** Matrix_Filling(LinkedList<char>* vertexes, ifstream& f) {
	string str;
	char temp;
	int counter, index;
	// Ищем уникальные вершины
	while (!f.eof()) {
		getline(f, str);
		counter = 0;
		for (size_t i = 0; i < str.size(); i++) {
			temp = str[i++];
			index = vertexes->search(temp);
			if (index == -1) {
				vertexes->push_back(temp);
			}
			counter++;
			if (counter == 2) {
				break;
			}
			if (str[i] != ' ') {
				throw("incorrect input");
			}
		}
	}

	f.clear();
	f.seekg(0);

	size_t n = vertexes->get_size();

	int** Capacity_Matrix = new int* [n];
	for (size_t i = 0; i < n; i++) {
		Capacity_Matrix[i] = new int[n];
	}
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			Capacity_Matrix[i][j] = 0;
		}
	}

	// Заполняем матрицу потоков
	int indexI, indexJ;
	counter = 0;
	while (!f.eof()) {
		getline(f, str);
		counter = 0;
		for (size_t i = 0; i < str.size(); i++) {
			temp = str[i++];
			if (counter == 0) {
				indexI = vertexes->search(temp);
			}
			if (counter == 1) {
				indexJ = vertexes->search(temp);
			}
			if (counter == 2) {
				if (int(temp) < int('0') || int(temp) > int('9')) {
					throw("incorrect input");
				}
				else {
					Capacity_Matrix[indexI][indexJ] = int(temp) - int('0');
				}
			}
			counter++;
		}
	}

	return Capacity_Matrix;
}

bool BFS(int** Flow_Matrix, int s, int t, int* parent, size_t size) {
	// Массив посещенных вершин
	bool* visited = new bool[size];
	for (size_t i = 0; i < size; i++) {
		visited[i] = false;
	}
	Queue<int> queue;
	queue.push(s);
	visited[s] = true;
	parent[s] = -1;
	while (!queue.empty()) {
		int currentVertex = queue.first();
		queue.pop();
		for (size_t i = 0; i < size; i++) {
			if (visited[i] == false && Flow_Matrix[currentVertex][i] > 0) {
				queue.push(i);
				parent[i] = currentVertex;
				visited[i] = true;
			}
		}
	}
	return visited[t];
}

int Ford_Fulkerson_Algorithm(int** Capacity_Matrix, int s, int t, size_t size) {
	int Current_Vertex;
	int** Flow_Matrix = new int* [size];
	for (size_t i = 0; i < size; i++) {
		Flow_Matrix[i] = new int[size];
	}
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			Flow_Matrix[i][j] = Capacity_Matrix[i][j];
		}
	}

	int* parent = new int[size];
	int Max_Flow = 0;
	int Path_Flow;

	while (BFS(Flow_Matrix, s, t, parent, size)) {
		Path_Flow = INT_MAX;

		for (int i = t; i != s; i = parent[i]) {
			Current_Vertex = parent[i];
			if (Path_Flow > Flow_Matrix[Current_Vertex][i]) {
				Path_Flow = Flow_Matrix[Current_Vertex][i];
			}
		}
		for (int i = t; i != s; i = parent[i]) {
			Current_Vertex = parent[i];
			Flow_Matrix[Current_Vertex][i] -= Path_Flow;
			Flow_Matrix[i][Current_Vertex] += Path_Flow;
		}
		Max_Flow += Path_Flow;
	}
	return Max_Flow;
}

void Result(ifstream& f) {
	LinkedList<char>* vertexes = new LinkedList<char>;
	int** Capacity_Matrix = new int*[0];
	Capacity_Matrix = Matrix_Filling(vertexes, f);
	size_t n = vertexes->get_size();
	cout << "Максимальный поток графа равен: " << Ford_Fulkerson_Algorithm(Capacity_Matrix, 0, n - 1, n);
}