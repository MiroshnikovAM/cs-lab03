#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg_module.h"

using namespace std;

int main() {

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

    show_histogram_svg(bins);

    }
    return 0;
}


