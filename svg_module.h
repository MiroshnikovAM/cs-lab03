#pragma once

#include <vector>
#include <string>

using namespace std;

string svg_begin(double width, double height);
string svg_end();
string svg_rect(double x, double y, double width, double height, string stroke, string fill);
string svg_text(double left, double baseline, string text);
string show_histogram_svg(const vector<size_t>& bins);
string svg_system_info(double x, double y);
string make_info_text();
