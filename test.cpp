#include "histogram.h"
#include "svg_module.h"
#include <cassert>
#include <string>

void test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_negative() {
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}

void test_equal() {
    double min = 0;
    double max = 0;
    find_minmax({1, 1, 1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void test_empty() {
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}

void test_scale1() {
    string h1 = show_histogram_svg({1});
    string expected_string = "<?xml version='1.0' encoding='UTF-8'?>\n";
    expected_string += "<svg width='300' height='300' viewBox='0 0 300 300' xmlns='http://www.w3.org/2000/svg'>\n";
    expected_string += "\t<text x='15' y='20'>1</text>\n";
    expected_string += "\t<rect x='0' y='30' width='30' height='270' stroke='black' fill='blue' />\n";
    expected_string += "</svg>\n";
    assert(h1 == expected_string);
}

void test_scale2() {
    string h1 = show_histogram_svg({1, 2});
    string expected_string = "<?xml version='1.0' encoding='UTF-8'?>\n";
    expected_string += "<svg width='300' height='300' viewBox='0 0 300 300' xmlns='http://www.w3.org/2000/svg'>\n";
    expected_string += "\t<text x='15' y='20'>1</text>\n";
    expected_string += "\t<rect x='0' y='30' width='30' height='135' stroke='black' fill='blue' />\n";
    expected_string += "\t<text x='45' y='20'>2</text>\n";
    expected_string += "\t<rect x='30' y='30' width='30' height='270' stroke='black' fill='blue' />\n";
    expected_string += "</svg>\n";
    assert(h1 == expected_string);
}

int main() {
    test_positive();
    test_negative();
    test_equal();
    test_empty();
    test_scale1();
    test_scale2();
}
