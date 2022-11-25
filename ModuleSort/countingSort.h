#ifndef MODULESORT_QUICKSORT_H
#define MODULESORT_QUICKSORT_H
    int readFromFile(FILE *file, int *data, int *size);
    void insertionSort(int *data, int start, int end);
    void smartQuickSort(int *data, int start, int end);
    bool testQuickSort(void);
    int mostFrequentElement(FILE *file);
    bool test(void);
#endif //MODULESORT_QUICKSORT_H
