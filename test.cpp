#include <iostream>

// Compile-time constant
constexpr int kArraySize = 20;

// Function prototype for Fibonacci sequence calculation
inline int fibonacci(int n);

// Function overloading for array manipulation
void manipulateArray(int arr[], int size);
void manipulateArray(double arr[], int size);

int main() {
    // Run-time constant
    const int kFibonacciNumber = 10;

    // Fibonacci sequence using recursion
    int fibRecursive = fibonacci(kFibonacciNumber);
    std::cout << "Fibonacci Recursive(" << kFibonacciNumber << "): " << fibRecursive << std::endl;

    // Array manipulation using function overloading
    int intArray[kArraySize] = {1, 2, 3, 4, 5};
    manipulateArray(intArray, kArraySize);

    double doubleArray[kArraySize] = {1.1, 2.2, 3.3, 4.4, 5.5};
    manipulateArray(doubleArray, kArraySize);

    return 0;
}

// Fibonacci sequence using recursion
inline int fibonacci(int n) {
    return (n <= 1) ? n : (fibonacci(n - 1) + fibonacci(n - 2));
}

// Array manipulation using function overloading
void manipulateArray(int arr[], int size) {
    std::cout << "Manipulating int array: ";
    for (int i = 0; i < size; ++i) {
        arr[i] *= 2;
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void manipulateArray(double arr[], int size) {
    std::cout << "Manipulating double array: ";
    for (int i = 0; i < size; ++i) {
        arr[i] *= 1.5;
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
