#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cstdio>
#include <windows.h>

using namespace std;

string make_info_text() {
    stringstream buffer;

    DWORD mask = 0x0000ffff;
    DWORD mask_major = 0b00000000'00000000'00000000'11111111;
    DWORD info = GetVersion();
    DWORD platform = info >> 16;
    DWORD version = info & mask;
    DWORD version_major = version & mask_major;
    DWORD version_minor = version >> 8;

    if ((info & 0x40000000) == 0) {
        DWORD build = platform;
        buffer << "Windows v" << version_major << "." << version_minor << "(build " << build << ")\n";
    }

    char computer_name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computer_name);
    GetComputerNameA(computer_name, &size);
    buffer << "Name: " << computer_name << "\n";

    return buffer.str();
}

string svg_system_info(double x, double y) {
    ostringstream strs;
    strs << "<text x='" << x << "' y='" << y << "'>" << make_info_text()<< "</text>";
    string output = strs.str();
    return output;
}

string svg_begin(double width, double height) {
    ostringstream strs;
    strs << "<?xml version='1.0' encoding='UTF-8'?>\n";
    strs << "<svg ";
    strs << "width='" << width << "' ";
    strs << "height='" << height << "' ";
    strs << "viewBox='0 0 " << width << " " << height << "' ";
    strs << "xmlns='http://www.w3.org/2000/svg'>\n";
    string output = strs.str();
    return output;
}

string svg_end() {
    ostringstream strs;
    strs << "</svg>\n";
    string output = strs.str();
    return output;
}

string svg_rect(double x, double y, double width, double height, string stroke, string fill) {
    ostringstream strs;
    strs << "\t";
    strs << "<rect x='" << x << "' y='" << y
         << "' width='" << width << "' height='" << height
         << "' stroke='" << stroke << "' fill='" << fill
         << "' />";
    strs << endl;
    string output = strs.str();
    return output;
}

string svg_text(double left, double baseline, string text) {
    ostringstream strs;
    strs << "\t";
    strs << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
    strs << endl;
    string output = strs.str();
    return output;
}

string show_histogram_svg(const vector<size_t> & bins) {
    const auto IMAGE_WIDTH = 500;
    const auto IMAGE_HEIGHT = 500;
    const auto TEXT_TOP = 20;
    const auto TEXT_HEIGHT = 30;
    const auto BIN_WIDTH = 30;
    const auto TEXT_BASELINE = BIN_WIDTH / 2;
    string output;
    output = svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double left = 0;
    string stroke = "black";
    string fill = "blue";
    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    for (size_t bin : bins) {
        const double scaling_factor = (double)(IMAGE_HEIGHT - TEXT_HEIGHT) / max_count;
        const double bin_height = bin * scaling_factor;
        output += svg_text(left + TEXT_BASELINE, TEXT_TOP + TEXT_TOP, to_string(bin));
        output += svg_rect(left, TEXT_HEIGHT + TEXT_TOP, BIN_WIDTH, bin_height, stroke, fill);
        left += BIN_WIDTH;
    }
    output += svg_system_info(TEXT_TOP, TEXT_TOP);
    output += svg_end();
    return output;
}
