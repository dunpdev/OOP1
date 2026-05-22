#include <iostream>
void printArray(int* arr, int size) {
    std::cout << "Array elements: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
int sumArray(int* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}
int main() {
    int size;
    std::cout << "Enter the size of the array: ";
    std::cin >> size;
    int* arr = new int[size];
    std::cout << "Enter " << size << " integers:" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }
    printArray(arr, size);
    int sum = sumArray(arr, size);
    std::cout << "Sum of array elements: " << sum << std::endl;
    delete[] arr; // Oslobađanje alocirane memorije
    return 0;
}