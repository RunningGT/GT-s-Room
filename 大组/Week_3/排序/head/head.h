#ifndef QG_SORT_HEAD_H
#define QG_SORT_HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

void showDesk();
void generateTestData(const char* filename, int length);
void performTest(const char* testDescription, int length, int saveResult, int repeatCount) ;
void bubbleSort(int arr[], int length);
void bubbleSortOptimized1(int arr[], int length);
void bubbleSortOptimized2(int arr[], int length);
void bubbleSortOptimized3(int arr[], int length);
void insertSort(int arr[], int length);
void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);
int partition(int arr[], int l, int r);
void quickSort(int arr[], int l, int r);
void mergeSortAdapter(int arr[], int length);
void quickSortAdapter(int arr[], int length);
void countSort(int arr[], int length);
void countingSortForRadix(int arr[], int length, int exp);
int getMax(int arr[], int length);
void radixCountSort(int arr[], int length);
int isSorted(int arr[], int length);
double testSort(void (*sortFunc)(int*, int), int data[], int length, const char* sortName);
void writeArrayToFile(const char* filename, int arr[], int length);
void readArrayFromFile(const char* filename, int arr[], int length);

#endif //QG_SORT_HEAD_H
