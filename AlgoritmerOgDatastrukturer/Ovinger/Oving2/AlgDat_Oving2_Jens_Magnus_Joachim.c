#include <stdio.h>
#include <time.h>

//Øving 2: Magnus Rindal, Joachim Grimen Westgaard og Jens Martin Jahle

/**
 * Method 1 for multiplication.
 * @param n whole and positive number.
 * @param x decimal number.
 * @return The decimal number if n equals 1, and otherwise recursively calls itself.
 */
double method_1(int n, double x) {
    if (n == 1) return x;

    else {
        return x + (method_1(n-1, x));
    }
}

/**
 * Method 2 for multiplication.
 * @param n whole and positive number.
 * @param x decimal number.
 * @return The decimal number if n equals 1, recursively calls itself in two different
 * ways, depending on whether the n is an even or odd number when the method is called.
 */
double method_2(int n, double x) {
    if (n == 1) return x;

    else if (n & 1) {
        return x + method_2((n-1)/2, x+x);
    }

    else {
        return method_2(n/2, x+x);
    }
}

/**
 * Main function.
 * @return 0 if the program executes successfully, otherwise it returns the encountered error code.
 */
int main() {

    // Initialize the variables used to test the methods
    int n = 10000;
    double x = 250.5;
    int number_of_runs = 1000;
    double result_method_1 = 0;
    double result_method_2 = 0;

    // Run method 1 for number_of_runs times and measured the spent time
    clock_t start_time_1 = clock();
    for (int i = 0; i<number_of_runs; i++) {
        result_method_1 = method_1(n, x);
    }
    clock_t end_time_1 = clock();

    // Run method 2 for number_of_runs times and measured the spent time
    clock_t start_time_2 = clock();
    for (int i = 0; i<number_of_runs; i++) {
        result_method_2 = method_2(n, x);
    }
    clock_t end_time_2 = clock();

    double elapsed_time_method_1 = (double)(end_time_1 - start_time_1) / (CLOCKS_PER_SEC * number_of_runs);
    double elapsed_time_method_2 = (double)(end_time_2 - start_time_2) / (CLOCKS_PER_SEC * number_of_runs);


    // Print test multiplications for the two methods
    printf("\nTest for method 1 (13 * 2.5 = 32.5): %.1f", method_1(13, 2.5));
    printf("\nTest for method 2 (13 * 2.5 = 32.5): %.1f", method_2(13, 2.5));
    printf("\n\nTest for method 1 (14 * 10.1 = 141.4): %.1f", method_1(14, 10.1));
    printf("\nTest for method 2 (14 * 10.1 = 141.4): %.1f", method_2(14, 10.1));

    // Print the result of the methods and the measured in seconds
    printf("\n\nMethod 1: %d * %.3f = %.3f", n, x, result_method_1);
    printf("\nMethod 2: %d * %.3f = %.3f", n, x, result_method_2);
    printf("\n\n##Runs the multiplication methods above %d times##", number_of_runs);
    printf("\n##With a time of...##");

    // Print the time measured in microseconds
    printf("\nTime method 1: %.5f microseconds", 1000000 * elapsed_time_method_1);
    printf("\nTime method 2: %.5f miroseconds", 1000000 * elapsed_time_method_2);

    // Print the time measured in microseconds using method_2 for multiplication
    printf("\nTime method 1: %.5f microseconds", method_2(1000000, elapsed_time_method_1));
    printf("\nTime method 2: %.5f miroseconds", method_2(1000000, elapsed_time_method_2));

    return 0;
}