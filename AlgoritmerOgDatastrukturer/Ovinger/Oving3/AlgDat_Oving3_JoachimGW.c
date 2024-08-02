#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fills the array with unsorted numbers.
void fill_table_with_random_numbers(int *table, int table_length, int floor, int ceiling) {
    srand(1);
    for (int i = 0; i < table_length; i++) {
        table[i] = (rand() % ceiling) + floor;
    }
}

// Fills the array with unsorted numbers.
void fill_table_with_random_numbers_with_duplicates(int *table, int table_length, int floor, int ceiling, int duplicate) {
    srand(1);
    for (int i = 0; i < table_length; i++) {
        if (i % 2 == 0) table[i] = duplicate;
        else table[i] = (rand() % ceiling) + floor;
    }
}

// Calculates the sum of the numbers in the given array
long get_sum(int *table, int table_length) {
    long sum = 0;
    for (int i = 0; i < table_length; i++) {
        sum += table[i];
    }
    return sum;
}

// Swaps the values of two elements in the array
void swap_pos(int *i, int *j) {
    int k = *j;
    *j = *i;
    *i = k;
}

// Calculates the median value of three numbers in the given array
int median3sort(int *table, int left, int right) {
    int mid = (left+right) / 2;

    if (table[left] > table[mid]) swap_pos(&table[left], &table[mid]);

    if (table[mid] > table[right]) {
        swap_pos(&table[mid], &table[right]);
        if (table[left] > table[mid]) swap_pos(&table[left], &table[mid]);
    }
    return mid;
}

// Split function to split a given array into two
int split(int *table, int left, int right) {
    int i_left, i_right;
    int mid = median3sort(table, left, right);
    int split_value = table[mid];
    swap_pos(&table[mid], &table[right-1]);

    for (i_left = left, i_right = right-1;;) {
        while (table[++i_left] < split_value);
        while (table[--i_right] > split_value);

        if (i_left >= i_right) break;
        swap_pos(&table[i_left], &table[i_right]);
    }

    swap_pos(&table[i_left], &table[right-1]);
    return i_left;
}

// Insertion sort
void insertion_sort(int n, int t[n]) {
    for (int j = 1; j < n; ++j) {
        int swap = t[j];
        int i = j-1;
        while (i >= 0 && t[i] > swap) {
            t[i+1] = t[i];
            --i;
        }
        t[i+1] = swap;
    }
}

// Bubble sort method
void bubble_sort(int n, int t[n]) {
    for (int i = n-1; i; --i) {
        for (int j = 0; j < i; ++j) {
            if (t[j] > t [j+1])
                swap_pos(&t[j], &t[j+1]);
        }
    }
}

// Quicksort with median3sort
void quicksort_with_median(int *table, int left, int right) {
    if (right - left > 2) {
        int split_pos = split(table, left, right);
        quicksort_with_median(table, left, split_pos-1);
        quicksort_with_median(table, split_pos+1, right);
    } else median3sort(table, left, right);
}

// Quicksort with insertion sort as a help algorithm
void quicksort_with_insertion(int *table, int left, int right) {
    if (right - left > 26) {
        int split_pos = split(table, left, right);
        quicksort_with_insertion(table, left, split_pos-1);
        quicksort_with_insertion(table, split_pos+1, right);
    }
    else insertion_sort(right-left+1, table+left);
}

// Quicksort with bubble sort as a help algorithm
void quicksort_with_bubble(int *table, int left, int right) {
    if (right - left > 6) {
        int split_pos = split(table, left, right);
        quicksort_with_bubble(table, left, split_pos-1);
        quicksort_with_bubble(table, split_pos+1, right);
    }
    else bubble_sort(right-left+1, table+left);
}

int main() {
    int table_length = 2000000;
    int *table = malloc(sizeof(int) * table_length);
    long sum_before_sort;
    long sum_after_sort;

    if (table == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Fill the table with random numbers between the 'floor' and 'ceiling',
    // optionally along with duplicates of number 'duplicate'
    int floor = 1;
    int ceiling = table_length;
    int duplicate = 42;
//    fill_table_with_random_numbers(table, table_length, floor, ceiling);
    fill_table_with_random_numbers_with_duplicates(table, table_length, floor, ceiling, duplicate);

    // Calculate and print the sum of the table before the sort
    for (int i = 0; i < 10; i++) {
        printf("%i,", table[i]);
    }
    sum_before_sort = get_sum(table, table_length);
    printf("...\nSum before sort: %li\n\n", sum_before_sort);

    // Run and measure quicksort with median3sort
    clock_t start_qwm3s = clock();
    quicksort_with_median(table, 0, table_length-1);
    clock_t end_qwm3s = clock();
    double measured_time_quick_with_median3 = (double) (end_qwm3s-start_qwm3s) / CLOCKS_PER_SEC;
    clock_t start_qwm3sas = clock();
    quicksort_with_median(table, 0, table_length-1);
    clock_t end_qwm3sas = clock();
    double measured_time_quick_with_median3_sorted = (double) (end_qwm3sas-start_qwm3sas) / CLOCKS_PER_SEC;

    // Refill the table with the original random numbers (same random generator seed in the method),
    // either with or without duplicates
//        fill_table_with_random_numbers(table, table_length, floor, ceiling);
    fill_table_with_random_numbers_with_duplicates(table, table_length, floor, ceiling, duplicate);

    // Run and measure quicksort with insertion_sort
    clock_t start_insertion = clock();
    quicksort_with_insertion(table, 0, table_length - 1);
    clock_t end_insertion = clock();
    double measured_time_quick_with_insertion = (double) (end_insertion - start_insertion) / CLOCKS_PER_SEC;
    clock_t start_insertion_sorted = clock();
    quicksort_with_insertion(table, 0, table_length - 1);
    clock_t end_insertion_sorted = clock();
    double measured_time_quick_with_insertion_sorted = (double) (end_insertion_sorted - start_insertion_sorted) / CLOCKS_PER_SEC;

    // Refill the table with the original random numbers (same random generator seed in the method),
    // either with or without duplicates
//        fill_table_with_random_numbers(table, table_length, floor, ceiling);
    fill_table_with_random_numbers_with_duplicates(table, table_length, floor, ceiling, duplicate);


    // Run and measure quicksort with bubble_sort
    clock_t start_bubble = clock();
    quicksort_with_bubble(table, 0, table_length - 1);
    clock_t end_bubble = clock();
    double measured_time_quick_with_bubble = (double) (end_bubble - start_bubble) / CLOCKS_PER_SEC;
    clock_t start_bubble_sorted = clock();
    quicksort_with_bubble(table, 0, table_length - 1);
    clock_t end_bubble_sorted = clock();
    double measured_time_quick_with_bubble_sorted =
            (double) (end_bubble_sorted - start_bubble_sorted) / CLOCKS_PER_SEC;

    // Calculate and print the sum of the table after the sort
    for (int i = 0; i < 10; i++) {
        printf("%i,", table[i]);
    }
    sum_after_sort = get_sum(table, table_length);
    printf("...\nSum after sort: %li\n\n", sum_after_sort);

    // Check whether all numbers have been sorted correctly, and if the sum before equals the sum after
    int boolean = 1;
    for (int i = 1; i < table_length-1; i++) {
        if (table[i] < table[i-1]) {
            printf("The table has NOT been sorted correctly!\n");
            boolean = 0;
            break;
        }
    }
    if (boolean == 1) {
        printf("### The table was sorted successfully! ###\n");
    }
    if (sum_before_sort == sum_after_sort) {
        printf("### The sum before equals the sum after sorting! ###\n\n");
    }

    // Print the results for comparison
    printf("Time spent (quicksort with median3sort): %.10f seconds\n", measured_time_quick_with_median3);
    printf("Time spent (quicksort with median3sort, sorted): %.10f seconds\n", measured_time_quick_with_median3_sorted);
    printf("Time spent (quicksort with insertion): %.10f seconds\n", measured_time_quick_with_insertion);
    printf("Time spent (quicksort with insertion, sorted): %.10f seconds\n", measured_time_quick_with_insertion_sorted);
    printf("Time spent (quicksort with bubble): %.10f seconds\n", measured_time_quick_with_bubble);
    printf("Time spent (quicksort with bubble, sorted): %.10f seconds\n", measured_time_quick_with_bubble_sorted);

    free(table);

    return 0;
}