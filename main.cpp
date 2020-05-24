#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg_module.h"
#include <curl/curl.h>
#include <sstream>
#include <string>
#include <cstdio>
#include <windows.h>

using namespace std;

struct Options {
    bool useDebugVerbose;
    bool useHelp;
    char* url;
};

vector<double> input_numbers(istream& in, size_t count);
Input read_input(istream& in, bool prompt);
Input download(const string& address, bool useDebugVerbose);
size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx);
Options parse_args(int argc, char** argv);

int main(int argc, char* argv[]) {
    Options options = parse_args(argc, argv);
    if (options.useHelp) {
        cerr << "ToDo: Help & Usage" << endl;
        exit(2);
    }
    Input input;
    if (options.url) {
        input = download(options.url, options.useDebugVerbose);
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
    in >> number_count;

    if (prompt) {
        cerr << "Enter numbers: ";
    }
    data.numbers = input_numbers(in, number_count);

    if (prompt) {
        cerr << "Enter column count: ";
    }
    in >> data.bin_count;

    return data;
}

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    size_t data_size = item_size * item_count;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    (*buffer).write(reinterpret_cast<const char*>(items), data_size);
    return data_size;
}

Input download(const string& address, bool useDebugVerbose) {
    stringstream buffer;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        if (useDebugVerbose) {
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        }
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (res) {
            cerr << curl_easy_strerror(res) << endl;
            exit(1);
        }
    }
    curl_easy_cleanup(curl);
    return read_input(buffer, false);
}

Options parse_args(int argc, char** argv) {
    Options opt;
    opt.url = 0;
    opt.useHelp = false;
    opt.useDebugVerbose = false;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-verbose") == 0) {
                opt.useDebugVerbose = true;
            } else {
                opt.useHelp = true;
            }
        } else {
            opt.url = argv[i];
        }
    }
    // Uncomment for NoURL behavior
    /*
    if (opt.url == 0) {
        opt.useHelp = true;
    }
    */
    return opt;
}
