// Primer vezbanja CPP kroz par primera i osnovni zadaci sa tipovima podataka i operacijama.
// zadatak sa nizovima i funkcijama
#include <iostream>
#include <string>
void printArray(int arr[], int size) {
    std::cout << "Array elements: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
int sumArray(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}
int main() {
    const int SIZE = 5;
    int arr[SIZE] = {1, 2, 3, 4, 5};
    printArray(arr, SIZE);
    int sum = sumArray(arr, SIZE);
    std::cout << "Sum of array elements: " << sum << std::endl;
    return 0;
}