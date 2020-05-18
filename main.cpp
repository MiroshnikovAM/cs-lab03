#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg_module.h"
#include <cstdio>

using namespace std;

vector<double> input_numbers(size_t count);

int main() {

    const char* name = "Lieutenant Victor";
    int year = 5;
    printf("%s has %d years of service.\n", name, year);
    printf("n = %10x\n", 0x13456789); // __13456789 _ = space
    return 0;

    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    if (number_count == 0) {
        cerr << "ERROR: Empty vector";
    } else {

    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;

    double min, max;
    find_minmax(numbers, min, max);

    const auto bins = make_histogram(numbers, bin_count, min, max);
    cout << show_histogram_svg(bins);

    }
    return 0;
}

vector<double> input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

