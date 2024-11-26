#include <iostream>
#include "halftone.h"

int main(void) {

    Halftone<bool> image(8, 8, true);
    bool fill = 0;
    size_t x1 = 2, y1 = 6;
    size_t x2 = 6, y2 = 2;

    std::cout << "\nEnter value to fill: ";
    std::cin >> fill;

    paint_square(image, x1, y1, x2, y2, fill);

    std::cout << image << "\n";

    return 0;
}
