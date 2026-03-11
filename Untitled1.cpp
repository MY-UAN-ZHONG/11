#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// 輔助函式：列印目前陣列狀態
void printStep(const vector<int>& arr, string msg) {
    cout << setw(20) << left << msg << ": ";
    for (int x : arr) cout << x << " ";
    cout << endl;
}

// 1. Bubble Sort (冒泡排序) - O(n^2)
void bubbleSort(vector<int> arr, bool verbose) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
        }
        if (verbose) printStep(arr, "Round " + to_string(i + 1));
    }
}

// 2. Insertion Sort (插入排序) - O(n^2)
void insertionSort(vector<int> arr, bool verbose) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        if (verbose) printStep(arr, "Insert " + to_string(key));
    }
}

// 3. Quick Sort (快速排序) - O(n log n)
int partition(vector<int>& arr, int low, int high, bool verbose) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    if (verbose) printStep(arr, "Pivot " + to_string(pivot));
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high, bool verbose) {
    if (low < high) {
        int pi = partition(arr, low, high, verbose);
        quickSort(arr, low, pi - 1, verbose);
        quickSort(arr, pi + 1, high, verbose);
    }
}

// 4. Merge Sort (歸併排序) - O(n log n)
void merge(vector<int>& arr, int l, int m, int r, bool verbose) {
    int n1 = m - l + 1, n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    if (verbose) printStep(arr, "Merged [" + to_string(l) + "," + to_string(r) + "]");
}

void mergeSort(vector<int>& arr, int l, int r, bool verbose) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, verbose);
        mergeSort(arr, m + 1, r, verbose);
        merge(arr, l, m, r, verbose);
    }
}

int main() {
    // --- 部分一：步驟演示 (小規模) ---
    vector<int> demo = {35, 12, 48, 9, 21};
    cout << "=== Sorting Steps Demonstration (n=5) ===" << endl;
    
    cout << "\n[Bubble Sort]" << endl;
    bubbleSort(demo, true);

    cout << "\n[Insertion Sort]" << endl;
    insertionSort(demo, true);

    cout << "\n[Quick Sort]" << endl;
    vector<int> qDemo = demo;
    quickSort(qDemo, 0, 4, true);

    cout << "\n[Merge Sort]" << endl;
    vector<int> mDemo = demo;
    mergeSort(mDemo, 0, 4, true);

    // --- 部分二：時間複雜度經驗觀察 (大規模) ---
    int N = 5000;
    vector<int> largeData(N);
    for (int i = 0; i < N; i++) largeData[i] = rand() % 10000;

    cout << "\n=== Empirical Observation (n=" << N << ") ===" << endl;

    auto benchmark = [&](string name, vector<int> d, char type) {
        auto start = high_resolution_clock::now();
        if (type == 'B') bubbleSort(d, false);
        else if (type == 'I') insertionSort(d, false);
        else if (type == 'Q') quickSort(d, 0, N - 1, false);
        else if (type == 'M') mergeSort(d, 0, N - 1, false);
        auto stop = high_resolution_clock::now();
        cout << left << setw(15) << name << ": " 
             << duration_cast<milliseconds>(stop - start).count() << " ms" << endl;
    };

    benchmark("Bubble Sort", largeData, 'B');
    benchmark("Insertion Sort", largeData, 'I');
    benchmark("Quick Sort", largeData, 'Q');
    benchmark("Merge Sort", largeData, 'M');

    return 0;
}
