#include <iostream>
#include <fstream>

#include "NaturalMerge.h"
#include "ManyPhaseMerge.h"

using namespace std;

typedef void(*functionPointer)(ifstream*, int);

int main()
{
	srand(time(0));
	system("chcp 1251 > Null");

	functionPointer functions[] = { &SortUsingNaturalMerge, &SortUsingManyPhaseMerging };
	int Lenght;

	for (functionPointer function : functions) {

		do
		{
			cout << "\nВведите кол-во элементов массива: "; cin >> Lenght;
		} while (Lenght <= 1);

		ofstream Output("F1.bin", ios_base::binary);


		cout << "\nИсходный массив: ";
		for (int i = 0; i < Lenght; i++) {

			int element = rand() % 101 - 50;

			cout << element << " ";

			Output.write(reinterpret_cast<const char*>(&element), sizeof(element));
		}

		cout << endl;

		Output.close();

		cout << "\nОтсортированный массив: ";

		ifstream Input("F1.bin", ios_base::binary);

		function(&Input, Lenght);

		Input.close();

		cout << endl << endl;

		return 0;
	}
}