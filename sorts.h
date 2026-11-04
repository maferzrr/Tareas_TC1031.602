/*
 * sorts.h
 *
 *  Created on: 07/09/2026
 *      Autor: María Fernanda Zetina Reyes
 *      Matrícula: A01709799
 * 
 */

#ifndef SORTS
#define SORTS

#include <vector>

using namespace std;

template <class T>
class Sorts {
private:
    void swap(vector<T>&, int, int);
    void copyArray(vector<T>&, vector<T>&, int, int);
    void mergeArray(vector<T>&, vector<T>&, int, int, int);
    void mergeSplit(vector<T>&, vector<T>&, int, int);

public:
    void ordenaSeleccion(vector<T>&);
    void ordenaBurbuja(vector<T>&);
    void ordenaMerge(vector<T>&);
    int busqSecuencial(const vector<T>& v, T val);
    int busqBinaria(const vector<T>& v, T val);
};

template <class T>
void Sorts<T>::swap(vector<T> &v, int i, int j) {
    T aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

template <class T>
void Sorts<T>::ordenaSeleccion(vector<T> &v) {
    int indx;

    for (int i = v.size() - 1; i > 0; i--) {
        indx = 0;

        for (int j = 1; j <= i; j++) {
            if (v[j] > v[indx]) {
                indx = j;
            }
        }

        if (indx != i) { 
            swap(v, i, indx);
        }
    }
}

template <class T>
void Sorts<T>::ordenaBurbuja(vector<T> &v) {
    for (int i = v.size() - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (v[j] > v[j + 1]) {
                swap(v, j, j + 1);
            }
        }
    }
}

template <class T>
void Sorts<T>::copyArray(vector<T> &A, vector<T> &B, int low, int high) {
    for (int i = low; i <= high; i++) {
        A[i] = B[i];
    }
}

template <class T>
void Sorts<T>::mergeArray(vector<T> &A, vector<T> &B, int low, int mid, int high) {
    int i, j, k;

    i = low;
    j = mid + 1;
    k = low;

    while (i <= mid && j <= high) {
        if (A[i] < A[j]) {
            B[k] = A[i];
            i++;
        } else {
            B[k] = A[j];
            j++;
        }
        k++;
    }
    if (i > mid) {
        for (; j <= high; j++) {
            B[k++] = A[j];
        }
    } else {
        for (; i <= mid; i++) {
            B[k++] = A[i];
        }
    }
}

template <class T>
void Sorts<T>::mergeSplit(vector<T> &A, vector<T> &B, int low, int high) {
    int mid;

    if ((high - low) < 1) {
        return;
    }

    mid = (high + low) / 2;
    mergeSplit(A, B, low, mid);
    mergeSplit(A, B, mid + 1, high);
    mergeArray(A, B, low, mid, high);
    copyArray(A, B, low, high);
}

template <class T>
void Sorts<T>::ordenaMerge(vector<T> &v) {
    vector<T> tmp(v.size());
    mergeSplit(v, tmp, 0, v.size() - 1);
}

template <class T>
int Sorts<T>::busqSecuencial(const vector<T> &v, T val) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == val) {
            return i;
        }
    }
    return -1;
}

template <class T>
int Sorts<T>::busqBinaria(const vector<T> &v, T val) {
    int low = 0;
    int high = v.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (v[mid] == val) {
            return mid;
        } else if (val < v[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

#endif