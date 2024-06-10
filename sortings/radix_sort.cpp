#include <vector>
#include <iostream>

template <typename T = int>
class RadixSort {
private:
    void stable_counting_sort(std::vector<T>& array, int exp) {
        const int size = array.size();
        int base = 10;

        std::vector<int> count(base, 0);
        std::vector<T> sortedArray(size, 0);

        for (size_t i = 0; i < size; ++i) {
            ++count[(array[i] / exp) % base];
        }

        for (size_t i = 1; i < count.size(); ++i) {
            count[i] += count[i - 1];
        }

        for (int i = size - 1; i >= 0; --i) {
            sortedArray[count[(array[i] / exp) % base] - 1] = array[i];
            --count[(array[i] / exp) % base];
        }

        std::copy(sortedArray.begin(), sortedArray.end(), array.begin());
    }

    void radix_sort(std::vector<T>& array) {
        int exp = 1;
        const int max_element = *std::max_element(array.begin(), array.end());

        while (max_element / exp > 0) {
            stable_counting_sort(array, exp);
            exp *= 10;
        }
    }

    void printArray(std::vector<T>& array) {
        for (auto elem : array) {
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }
public:
    void radix_sortArray(std::vector<int>& nums) {
        radix_sort(nums, 0, nums.size() - 1);
        printArray(nums);
    }
};

//int main() {
//    std::vector<int> arr = { 170, 45, 75, 90, 802, 24, 2, 66 };
//    radix_sort(arr);
//    printArray(arr);
//}