#include <iostream>
#include <vector>
#include <chrono>
#include <random>

class MersenneTwister {
public:
	MersenneTwister() {
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		generator.seed(static_cast<unsigned>(seed));
	}

	int generateRandomIndex(int size) {
		std::uniform_int_distribution<int> distribution(0, size - 1);
		return distribution(generator);
	}

private:
	std::mt19937 generator;
};

class QuickSelect {
private:
	MersenneTwister mt;

	template<typename T>
	int partition(std::vector<T>& array, int begin, int end) {
		int pivotIndex = mt.generateRandomIndex(end - begin + 1) + begin;
		std::swap(array[pivotIndex], array[end]);
		int pivot = array[end];
		int l = begin - 1;

		for (size_t i = begin; i < end; ++i) {
			if (array[i] >= array[pivot]) continue;
			if (array[i] < array[pivot]) {
				++l;
				std::swap(array[l], array[i]);
			}
		}
		std::swap(array[l + 1], array[end]);
		return l + 1;
	}

	template<typename T>
	T quick_select(std::vector<T>& array, int begin, int end, int k) {
		while (begin <= end) {
			int pivotIndex = partition(array, begin, end);

			if (pivotIndex == k) return array[pivotIndex];
			else if (pivotIndex < k) begin = pivotIndex + 1;
			else end = pivotIndex - 1;
		}
	}

public:
	template<typename T>
	T quick_selectElem(std::vector<int>& nums, int k) {
		T kth_element = quick_select(nums, 0, nums.size() - 1, k - 1);
		return kth_element;
	}
};

//int main() {
//	std::vector<int> v{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
//	QuickSelect select;
//	int kth_element = select.quick_selectElem<int>(v, 3);
//	std::cout << "The 3rd smallest element is: " << kth_element << std::endl;
//}