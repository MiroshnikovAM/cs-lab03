#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg_module.h"

using namespace std;

struct Input {
    vector<double> numbers;
    size_t bin_count;
};

vector<double> input_numbers(istream& in, size_t count);
Input read_input(istream& in);

int main() {

    const auto input = read_input(cin);

    double min, max;
    find_minmax(input.numbers, min, max);

    const auto bins = make_histogram(input.numbers, input.bin_count, min, max);
    cout << show_histogram_svg(bins);

    return 0;
}

vector<double> input_numbers(istream& in, size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }
    return result;
}

Input read_input(istream& in) {

    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count; // cin ?

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter column count: ";
    in >> data.bin_count; // cin ?

    return data;
}
