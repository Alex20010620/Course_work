#pragma once
#include "list.h"

int** Matrix_Filling(LinkedList<char>* vertexes, ifstream& f);
bool BFS(int** Flow_Matrix, int s, int t, int* parent, size_t size);
int Ford_Fulkerson_Algorithm(int** Capacity_Matrix, int s, int t, size_t size);
void Result(ifstream& f);