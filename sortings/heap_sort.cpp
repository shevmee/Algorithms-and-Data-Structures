#include <iostream>
#include <vector>

template<typename T>
class HeapSort {
private:
    void siftDown(std::vector<T>& array, int i, int size) {
        int maxIndex = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && array[left] > array[maxIndex]) {
            maxIndex = left;
        }

        if (right < size && array[right] > array[maxIndex]) {
            maxIndex = right;
        }

        if (i != maxIndex) {
            std::swap(array[i], array[maxIndex]);
            siftDown(array, maxIndex, size);
        }
    }

    void heapify(std::vector<T>& array) {
        int size = array.size();
        for (int i = size / 2 - 1; i >= 0; --i) {
            siftDown(array, i, size);
        }
    }

public:
    void sort(std::vector<T>& array) {
        int size = array.size();

        heapify(array);

        for (int i = size - 1; i > 0; --i) {
            std::swap(array[0], array[i]);
            siftDown(array, 0, i);
        }
    }
};

//int main() {
//    std::vector<int> array = { 12, 4, 5, 6, 7, 2, 3, 1, 15 };
//
//    HeapSort<int> heapSort;
//    heapSort.sort(array);
//
//    std::cout << "Sorted array: ";
//    for (int num : array) {
//        std::cout << num << " ";
//    }
//    std::cout << std::endl;
//}
