#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <numeric>
#include <iomanip>

enum A {
	RQS,
	DQS
};

class RandomNumber {
public:
	RandomNumber() {
		unsigned seed = static_cast<unsigned>(std::chrono
												 ::high_resolution_clock
												 ::now().time_since_epoch().count());
		generator.seed(seed);
		srand(seed);
	}

	int generateWithMT(int size) {
		std::uniform_int_distribution<int> distribution(0, size - 1);
		return distribution(generator);
	}

	/*int generateWithRand() {
		return std::rand();
	}*/

private:
	std::mt19937 generator;
};

class QuickSort {
private:
	RandomNumber rn;
	template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
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

	template<
		typename T,
		typename = std::enable_if_t<std::is_arithmetic_v<T>>
	> int 
	partition(std::vector<T>& array, int begin, int end, A a) {
		int pivotIndex = 0;
		if constexpr (RQS) {
			pivotIndex = rn.generateWithMT(array.size()) % (end + 1 - begin) + begin;
		}
		/*else if (RND) {
			pivotIndex = rn.generateWithRand() % (end + 1 - begin) + begin;
		}*/
		else {
			pivotIndex = medianOfFive(array, begin, end);
		}
		std::swap(array[pivotIndex], array[end]);
		T pivot = array[end];
		int l = begin - 1;

		for (size_t i = begin; i < end; ++i) {
			if (array[i] >= pivot) continue;
			if (array[i] < pivot) {
				++l;
				std::swap(array[l], array[i]);
			}
		}
		std::swap(array[l + 1], array[end]);
		return l + 1;
	}

	template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	void quick_sort(std::vector<T>& array, int begin, int end) {
		if (begin >= end) return;
		int pivotIndex = partition(array, begin, end, DQS);
		quick_sort(array, begin, pivotIndex);
		quick_sort(array, pivotIndex + 1, end);
	}

public:
	template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	void printArray(const std::vector<T>& nums) {
		std::copy(nums.begin(), nums.end(), std::ostream_iterator<T>(std::cout, " "));
		std::cout << '\n';
	}

	template<typename T>
	void quick_sortArray(std::vector<T>& nums) {
		auto start_time = std::chrono::high_resolution_clock::now();
		quick_sort(nums, 0, nums.size() - 1);
		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

		std::cout << "Sorted array: ";
		printArray(nums);

		std::cout << "Time taken for QuickSort: " << duration.count() << " microseconds\n";
	}
};

int main() {
	QuickSort qs;

	const int ARRAY_SIZE = 1000000;
	const int DSTR = 100000;

	std::vector<int> largeArray(ARRAY_SIZE);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(0, DSTR);
	for (int& num : largeArray) {
		num = distribution(gen);
	}

	std::cout << "Unsorted array: ";
	qs.printArray(largeArray);

	qs.quick_sortArray(largeArray);
}