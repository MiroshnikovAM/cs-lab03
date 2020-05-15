#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg_module.h"
#include <curl/curl.h>
#include <sstream>
#include <string>

using namespace std;

vector<double> input_numbers(istream& in, size_t count);
Input read_input(istream& in, bool prompt);
Input download(const string& address);
size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx);

int main(int argc, char* argv[]) {
    Input input;
    if (argc > 1) {
        input = download(argv[1]);
    } else {
        input = read_input(cin, true);
    }

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

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    // TODO: дописывать данные к буферу.
    return 0;
}

Input download(const string& address) {
    stringstream buffer;
    // TODO: заполнить буфер.
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        res = curl_easy_perform(curl);
        if (res) {
            cerr << curl_easy_strerror(res) << endl;
            exit(1);
        }
    }
    curl_easy_cleanup(curl);
    return read_input(buffer, false);
}
