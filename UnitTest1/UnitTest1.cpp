#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <iostream>
#include <string>
#include "D:\Прога 4 сем лабы\Project2\Project2\FordFulkerson.h"
#include "D:\Прога 4 сем лабы\Project2\Project2\FordFulkerson.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Matrix_Filling_Test_1)
		{
			ifstream f;
			f.open("D:\\Прога 4 сем лабы\\Project2\\UnitTest1\\test.txt", ios::in);
			LinkedList<char>* test = new LinkedList<char>;

			int** Capacity_Matrix = new int* [0];
			Capacity_Matrix = Matrix_Filling(test, f);

			int n = test->get_size();

			int Test_Matrix[4][4] = { {0, 3, 3, 0}, {0, 0, 0, 3}, {0, 0, 0, 2}, {0, 0, 0, 0} };

			for (size_t i = 0; i < n; i++) {
				for (size_t j = 0; j < n; j++) {
					Assert::IsTrue(Capacity_Matrix[i][j] == Test_Matrix[i][j]);
				}
			}
		}

		TEST_METHOD(Matrix_Filling_Test_2)
		{
			ifstream f;
			f.open("D:\\Прога 4 сем лабы\\Project2\\UnitTest1\\Incorrect1.txt", ios::in);
			LinkedList<char>* test = new LinkedList<char>;

			int** Capacity_Matrix = new int* [0];

			try
			{
				Capacity_Matrix = Matrix_Filling(test, f);
			}
			catch (const char* exception)
			{
				Assert::AreEqual(exception, "incorrect input");
			}
		}

		TEST_METHOD(Matrix_Filling_Test_3)
		{
			ifstream f;
			f.open("D:\\Прога 4 сем лабы\\Project2\\UnitTest1\\Incorrect1.txt", ios::in);
			LinkedList<char>* test = new LinkedList<char>;

			int** Capacity_Matrix = new int* [0];

			try
			{
				Capacity_Matrix = Matrix_Filling(test, f);
			}
			catch (const char* exception)
			{
				Assert::AreEqual(exception, "incorrect input");
			}
		}

		TEST_METHOD(Ford_Fulkerson_Test)
		{
			ifstream f;
			f.open("D:\\Прога 4 сем лабы\\Project2\\UnitTest1\\test.txt", ios::in);
			LinkedList<char>* test = new LinkedList<char>;

			int** Capacity_Matrix = new int* [0];
			Capacity_Matrix = Matrix_Filling(test, f);
			int n = test->get_size();
			int Max_Flow = Ford_Fulkerson_Algorithm(Capacity_Matrix, 0, n - 1, n);
			Assert::IsTrue(Max_Flow == 5);
		}
	};
}
