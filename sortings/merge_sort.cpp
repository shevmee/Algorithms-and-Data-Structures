#include <iostream>
#include <vector>

//template <typename T> 
//void binary_search(const std::vector<T>& v, const T& target,
//				size_t low = 0, size_t high = v.size() - 1) {
//	if (low > high) return;
//
//	size_t mid = low + (high - low) / 2;
//
//	if (v.at(mid) == target) return mid;
//
//	if (v.at(mid) > target)) binary_search(v, target, low, mid - 1);
//
//	if (v.at(mid) < target)) binary_search(v, target, mid + 1, high);
//
//	// TODO: print
//}

//struct Sorting {
//	template<typename T>
//	std::vector<T> bubble_sort(std::vector<T>& v) {
//		for (size_t i = 0; i < v.size() - 1; ++i) {
//			size_t min = i;
//			for (size_t j = i + 1; j < v.size(), ++j) {
//				if (v.at(min) > v.at(j)) {
//					min = j;
//				}
//			}
//			std::swap(v.at(min), v.at(j));
//		}
//		return v;
//	}
//
//	//кол-во обменов О(n)
//	std::vector<int> selection_sort(std::vector<int>& v) {
//		for (size_t i = 0; i < v.size() - 1; ++i) {
//			size_t idx_min = i;
//			for (size_t j = i + 1; j < v.size(); ++j) {
//				if (v[idx_min] > v[j]) idx_min = j;
//			}
//			std::swap(v[idx_min], v[i]); 
//		}
//		return v;
//	}
//
//	//кол-во обменов О(n^2 )
//	std::vector<int> insertion_sort(std::vector<int>& v) {
//		for (size_t i = 1; i < v.size(); ++i) {
//			size_t j = i - 1;
//			while (v[j] >= 0 && v[j] > v[j + 1]) {
//				std::swap(v[j], v[j + 1]);
//				j -= 1;
//			}
//		}
//		return v;
//	}

	/*

	std::vector<int> count_sort(std::vector<int>& v) {
		std::vector<int> c(v.size());
		for (size_t i = 1; i < v.size(); ++i) {
			
			while (v[j] >= 0 && v[j] > v[j + 1]) {
				std::swap(v[j], v[j + 1]);
				j -= 1;
			}
		}
		return v;
	}*/
//};

class MergeSort {
private:
	template<typename T>
	void merge(std::vector<T>& array, int left, int right) {
		int mid = left + (right - left) / 2;
		int i = left;
		int j = mid + 1;
		int k = 0;
		std::vector<T> sorted(right - left + 1);

		while (i <= mid && j <= right) {
			if (array[i] <= array[j]) {
				sorted[k++] = array[i++];
			}
			else {
				sorted[k++] = array[j++];
			}
		}

		while (i <= mid) sorted[k++] = array[i++];
		while (j <= right) sorted[k++] = array[j++];

		for (i = 0; i < sorted.size(); i++) {
			array[left + i] = sorted[i];
		}
	}

	template<typename T>
	void merge_sort(std::vector<T>& array, int begin, int end) {
		int mid = begin + (end - begin) / 2;
		if (begin >= end) return;
		merge_sort(array, begin, mid);
		merge_sort(array, mid + 1, end);
		merge(array, begin, end);
	}

	template<typename T>
	void printArray(const std::vector<T>& nums) const {
		for (const T& num : nums)
			std::cout << num << ' ';
		std::cout << '\n';
	}
public:
	void merge_sortArray(std::vector<int>& nums) {
		merge_sort(nums, 0, nums.size() - 1);
		printArray(nums);
	}
};
//
//int main() {
//	std::vector<int> v{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
//	MergeSort merge;
//	merge.merge_sortArray(v);
//}