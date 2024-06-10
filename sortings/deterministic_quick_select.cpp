#include <iostream>
#include <vector>
#include <chrono>
#include <random>

template<typename T>
class DeterministicQuickSelect {
private:
    int partition(std::vector<T>& array, int begin, int end) {
        T pivotIndex = medianOfFive(array, begin, end);
        std::swap(array[pivotIndex], array[end]);
        T pivot = array[end];
        int l = begin - 1;

        for (int i = begin; i < end; ++i) {
            if (array[i] < pivot) {
                ++l;
                std::swap(array[l], array[i]);
            }
        }
        std::swap(array[l + 1], array[end]);
        return l + 1;
    }

    T medianOfFive(std::vector<T>& arr, int begin, int end) {
        int mid = begin + (end - begin) / 2;
        int quarter1 = begin + (mid - begin) / 2;
        int quarter3 = mid + (end - mid) / 2;

        if (arr[begin] > arr[quarter1]) {
            std::swap(arr[begin], arr[quarter1]);
        }

        if (arr[begin] > arr[mid]) {
            std::swap(arr[begin], arr[mid]);
        }

        if (arr[begin] > arr[quarter3]) {
            std::swap(arr[begin], arr[quarter3]);
        }

        if (arr[quarter1] > arr[mid]) {
            std::swap(arr[quarter1], arr[mid]);
        }

        if (arr[quarter1] > arr[quarter3]) {
            std::swap(arr[quarter1], arr[quarter3]);
        }

        if (arr[mid] > arr[quarter3]) {
            std::swap(arr[mid], arr[quarter3]);
        }
        return quarter3;
    }

	T deterministic_quick_select(std::vector<T>& array, int begin, int end, int k) {
		while (begin <= end) {
			int pivotIndex = partition(array, begin, end);

			if (pivotIndex == k) return array[pivotIndex];
			else if (pivotIndex < k) begin = pivotIndex + 1;
			else end = pivotIndex - 1;
		}
	}
public:
	T deterministic_quick_selectElem(std::vector<int>& nums, int k) {
		T kth_element = deterministic_quick_select(nums, 0, nums.size() - 1, k - 1);
		return kth_element;
	}
};

//int main() {
//	std::vector<int> v{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
//    DeterministicQuickSelect<int> select;
//	int kth_element = select.deterministic_quick_selectElem(v, 3);
//	std::cout << "The 3rd smallest element is: " << kth_element << std::endl;
//}