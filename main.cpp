#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg_module.h"
#include <cstdio>
#include <windows.h>

using namespace std;

vector<double> input_numbers(size_t count);

int main() {
    /*
    const char* name = "Commander Shepard";
    int year = 2154;
    printf("%s was born in %d.\n", name, year);
    // Commander Shepard was born in 2154.
    printf("n = %08x\n", 0x1234567); // 01234567
    */
    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD info = GetVersion();
    DWORD version = info & mask;
    printf("Windows (decimal) version is %u.\n", version);
    printf("Windows (16x) version is %x.\n", version);
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

