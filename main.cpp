#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg_module.h"
#include <curl/curl.h>

using namespace std;

vector<double> input_numbers(istream& in, size_t count);
Input read_input(istream& in, bool prompt);

int main() {
    curl_global_init(CURL_GLOBAL_ALL);
    const auto input = read_input(cin, true);
    const auto bins = make_histogram(input);
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

Input read_input(istream& in, bool prompt) {

    Input data;

    if (prompt) {
        cerr << "Enter number count: ";
    }
    size_t number_count;
    in >> number_count; // cin ?

    if (prompt) {
        cerr << "Enter numbers: ";
    }
    data.numbers = input_numbers(in, number_count);

    if (prompt) {
        cerr << "Enter column count: ";
    }
    in >> data.bin_count; // cin ?

    return data;
}
