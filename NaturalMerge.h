#pragma once

#include <iostream>
#include <fstream>

#include "CommonFunctions.h"

using namespace std;

void SortUsingNaturalMerge(ifstream* file, int Lenght)
{

	Series* SeriesArr = new Series[Lenght]; 
	int AmountOfSeries = 1;

	int indexOfCurSeries = 0;
	SeriesArr[0].elements = new int[Lenght];
	SeriesArr[0].lenght = 1;

	file->read((char*)&SeriesArr[0].elements[0], sizeof(int));

	for (int i = 1; i < Lenght; i++) {

		int curElement;
		file->read((char*)&curElement, sizeof(curElement));

		if (curElement >= SeriesArr[indexOfCurSeries].elements[SeriesArr[indexOfCurSeries].lenght - 1]) {

			SeriesArr[indexOfCurSeries].elements[SeriesArr[indexOfCurSeries].lenght] = curElement;
			SeriesArr[indexOfCurSeries].lenght++;
		}

		else {

			indexOfCurSeries++;
			AmountOfSeries++;

			SeriesArr[indexOfCurSeries].elements = new int[Lenght];
			SeriesArr[indexOfCurSeries].lenght = 1;
			SeriesArr[indexOfCurSeries].elements[0] = curElement;
		}
	}

	while (AmountOfSeries > 1) {

		for (int i = 0; i < AmountOfSeries - 1; i++) {

			Series MergedSeries = MergeSeries(SeriesArr[i], SeriesArr[i + 1]);

			delete[] SeriesArr[i].elements;
			SeriesArr[i] = MergedSeries;
			RemoveElement(SeriesArr, i + 1, AmountOfSeries);
			AmountOfSeries--;
		}
	}

	Series sortedContent = SeriesArr[0];

	ofstream Output("F2.txt");

	Output << sortedContent.elements[0];
	cout << sortedContent.elements[0];

	for (int i = 1; i < sortedContent.lenght; i++) {

		cout << " " << sortedContent.elements[i];
		Output << " " << sortedContent.elements[i];
	}

	Output.close();

	delete[] sortedContent.elements;
	delete[] SeriesArr;
}