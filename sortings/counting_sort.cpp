#include <iostream>
#include <vector>

//unstable counting sort
void unstable_counting_sort(std::vector<int>& array, int begin, int end) {
    std::vector<int> count(end - begin + 1, 0);

    // Count the occurrences of each element
    for (size_t i = 0; i < array.size(); ++i) {
        ++count[array[i] - begin];
    }

    // Update the array with sorted values
    int b = 0;
    for (int i = begin; i <= end; ++i) {
        for (int j = 0; j < count[i - begin]; ++j) {
            array[b++] = i;
        }
    }
}

void stable_counting_sort(std::vector<int>& array, int begin, int end) {
    std::vector<int> count(end - begin + 1, 0);
    std::vector<int> sortedArray(array.size());

    for (size_t i = 0; i < array.size(); ++i) {
        ++count[array[i] - begin];
    }

    for (size_t i = 1; i < count.size(); ++i) {
        count[i] += count[i - 1];
    }

    for (int i = array.size() - 1; i >= 0; --i) {
        sortedArray[count[array[i] - begin] - 1] = array[i];
        --count[array[i] - begin];
    }

    std::copy(sortedArray.begin(), sortedArray.end(), array.begin());
}


void print(std::vector<int>& array) {
    for (auto elem : array) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
}

//int main() {
//    std::vector<int> v = { 9, 7, 23, 67, 0, 3 };
//    std::vector<int> v1{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
//    unstable_counting_sort(v, 0, 67);
//    stable_counting_sort(v1, 0, 9);
//    print(v);
//    print(v1);
//}
