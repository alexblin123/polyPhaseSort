#pragma once
#include <iostream>

using namespace std;

struct Series {

    int* elements;
    int lenght;

    void PrintSeriers() {

        if (lenght <= 0) return;

        cout << elements[0];

        for (int i = 1; i < lenght; i++)
            cout << " " << elements[i];

        cout << endl;
    }
};

void HoareQuickSorting(int* Arr, int startIndex, int endIndex) {

    if (startIndex <= endIndex) {

        int middleElement = Arr[(startIndex + endIndex) / 2]; 

        
        int LeftIndex = startIndex;
        int RightIndex = endIndex;

        while (LeftIndex <= RightIndex) {

            while (Arr[LeftIndex] < middleElement) 
                LeftIndex++; 

            while (Arr[RightIndex] > middleElement) 
                RightIndex--; 

            if (LeftIndex <= RightIndex) {
                
                int tmp = Arr[LeftIndex];
                Arr[LeftIndex] = Arr[RightIndex];
                Arr[RightIndex] = tmp;

                LeftIndex++; 
                RightIndex--; 
            }
        }

        HoareQuickSorting(Arr, startIndex, RightIndex); 
        HoareQuickSorting(Arr, LeftIndex, endIndex); 
    }
}

void HoareQuickSorting(int* Arr, int Lenght) { if (Lenght > 1) HoareQuickSorting(Arr, 0, Lenght - 1); }

Series MergeSeries(Series& SeriesOne, Series& SeriesTwo) {

    Series NewSeries;

    NewSeries.elements = new int[SeriesOne.lenght + SeriesTwo.lenght];

    for (int i = 0; i < SeriesOne.lenght; i++)
        NewSeries.elements[i] = SeriesOne.elements[i];

    int counter = SeriesOne.lenght;

    for (int i = 0; i < SeriesTwo.lenght; i++) {

        NewSeries.elements[counter] = SeriesTwo.elements[i];
        counter++;
    }

    NewSeries.lenght = SeriesOne.lenght + SeriesTwo.lenght;

    HoareQuickSorting(NewSeries.elements, NewSeries.lenght);

    return NewSeries;
}

void RemoveElement(Series* Arr, int Index, int Lenght) {

    delete[] Arr[Index].elements;

    for (int i = Index; i < Lenght - 1; i++)
        Arr[i] = Arr[i + 1];
}