#pragma once

#include <iostream>
#include <fstream>

#include "CommonFunctions.h"

using namespace std;

struct Bucket {

	Series* seriesArr;
	int lenght;
};

pair<int, int> GetFibonnachiNumbers(int numberToCompareTo, pair<int, int> PreviousTwoNumbers) {

	int currentNumber = PreviousTwoNumbers.first + PreviousTwoNumbers.second;
	pair <int, int> PairToReturn;

	if (currentNumber < numberToCompareTo)
		PairToReturn = GetFibonnachiNumbers(numberToCompareTo, { PreviousTwoNumbers.second, currentNumber });

	else
		PairToReturn = PreviousTwoNumbers;

	return PairToReturn;
}

pair<int, int> GetFibonnachiNumbers(int numberToCompareTo) { return GetFibonnachiNumbers(numberToCompareTo, { 0, 1 }); }

void SortUsingManyPhaseMerging(ifstream* file, int Lenght) {

	Series* SeriesArr = new Series[Lenght]; 
	int AmountOfSeries = 1;

	int indexOfCurSeries = 0;
	SeriesArr[0].elements = new int[Lenght];
	SeriesArr[0].lenght = 1;

	file->read((char*)&SeriesArr[0].elements[0], sizeof(int));

	for (int i = 1; i < Lenght; i++) {

		int curElement;
		file->read((char*)&curElement, sizeof(int));

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

	pair<int, int> PerfectFibonachiNumbers = GetFibonnachiNumbers(Lenght);

	Bucket* Buckets = new Bucket[3];

	Buckets[0].lenght = PerfectFibonachiNumbers.second;
	Buckets[1].lenght = PerfectFibonachiNumbers.first;
	Buckets[2].lenght = 0;

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < Lenght; j++)
			Buckets[i].seriesArr = new Series[Lenght];
	}

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < Lenght; j++) {

			Buckets[i].seriesArr[j].elements = new int[Lenght];
			Buckets[i].seriesArr[j].lenght = 0;
		}
	}

	indexOfCurSeries = 0;

	for (int i = 0; i < 2 && indexOfCurSeries < AmountOfSeries; i++) {

		for (int j = 0; j < Buckets[i].lenght && indexOfCurSeries < AmountOfSeries; j++) {

			Buckets[i].seriesArr[j] = SeriesArr[indexOfCurSeries];
			indexOfCurSeries++;
		}
	}

	AmountOfSeries = PerfectFibonachiNumbers.first + PerfectFibonachiNumbers.second;

	int IndexOfTheBiggerBucket = 0;
	int IndexOfTheSmallerBucket = 1;
	int IndexOfTheHelpingBucket = 2;

	while (AmountOfSeries > 1) {

		int NewLenght = Buckets[IndexOfTheBiggerBucket].lenght - Buckets[IndexOfTheSmallerBucket].lenght;

		int curIndexOfTheHelpingBucket = 0;
		int lastIndexOfSmallerBucket = Buckets[IndexOfTheSmallerBucket].lenght - 1;

		for (int i = Buckets[IndexOfTheBiggerBucket].lenght - 1; i > NewLenght - 1; i--) {

			Series NewSeries = MergeSeries(Buckets[IndexOfTheBiggerBucket].seriesArr[i], Buckets[IndexOfTheSmallerBucket].seriesArr[lastIndexOfSmallerBucket]);

			Buckets[IndexOfTheHelpingBucket].seriesArr[curIndexOfTheHelpingBucket] = NewSeries;

			Buckets[IndexOfTheHelpingBucket].lenght++;

			curIndexOfTheHelpingBucket++;
			lastIndexOfSmallerBucket--;

			AmountOfSeries--;
		}

		Buckets[IndexOfTheBiggerBucket].lenght -= Buckets[IndexOfTheSmallerBucket].lenght;

		for (int i = 0; i < Buckets[IndexOfTheSmallerBucket].lenght; i++)
			delete[] Buckets[IndexOfTheSmallerBucket].seriesArr[i].elements;

		delete[] Buckets[IndexOfTheSmallerBucket].seriesArr;

		Buckets[IndexOfTheSmallerBucket].seriesArr = new Series[Lenght];

		for (int i = 0; i < Lenght; i++) {

			Buckets[IndexOfTheSmallerBucket].seriesArr[i].elements = new int[Lenght];
			Buckets[IndexOfTheSmallerBucket].seriesArr[i].lenght = 0;
		}

		Buckets[IndexOfTheSmallerBucket].lenght = 0;

		int tmp = IndexOfTheBiggerBucket;
		IndexOfTheBiggerBucket = IndexOfTheHelpingBucket;
		IndexOfTheHelpingBucket = IndexOfTheSmallerBucket;
		IndexOfTheSmallerBucket = tmp;
	}

	Series sortedContent = Buckets[IndexOfTheBiggerBucket].seriesArr[0];

	ofstream Output("F2.txt");

	Output << sortedContent.elements[0];
	cout << sortedContent.elements[0];

	for (int i = 1; i < sortedContent.lenght; i++) {

		cout << " " << sortedContent.elements[i];
		Output << " " << sortedContent.elements[i];
	}

	Output.close();

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < Lenght; j++)
			delete[] Buckets[i].seriesArr[j].elements;

		delete[] Buckets[i].seriesArr;
	}

	delete[] Buckets;

	delete[] SeriesArr;
}