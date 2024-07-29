#include "Image_Class.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>
#include <fstream>

// Comprehensive ASCII characters from darkest to lightest
const std::string ASCII_CHARS =
"@#W$9876543210?!abc;:+=-,._ "
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int nearestAnsiColor(int r, int g, int b) {
    return 16 + 36 * (r / 51) + 6 * (g / 51) + (b / 51);
}

std::string convertToColoredASCII(Image& img, int width, int console_width) {
    std::string ascii_art;
    int height = img.height * width / img.width; // Maintain aspect ratio

    int margin = (console_width - width) / 2; // Calculate left margin for centering
    std::string margin_spaces(margin > 0 ? margin : 0, ' '); // Create margin string

    for (int y = 0; y < height; ++y) {
        ascii_art += margin_spaces; // Add margin at the beginning of each line
        for (int x = 0; x < width; ++x) {
            int originalX = x * img.width / width;
            int originalY = y * img.height / height;

            unsigned char r = img.getPixel(originalX, originalY, 0);
            unsigned char g = img.getPixel(originalX, originalY, 1);
            unsigned char b = img.getPixel(originalX, originalY, 2);

            unsigned char gray = static_cast<unsigned char>(0.2989 * r + 0.5870 * g + 0.1140 * b);
            char ascii_char = ASCII_CHARS[(gray * (ASCII_CHARS.size() - 1)) / 255];

            int color_code = nearestAnsiColor(r, g, b);

            ascii_art += "\033[38;5;" + std::to_string(color_code) + "m" + ascii_char + "\033[0m";
        }
        ascii_art += '\n';
    }
    return ascii_art;
}

int main() {
    std::string image_path;
    std::cout << "Enter the path to the image file: ";
    std::cin >> image_path;

    try {
        Image img(image_path);

        int new_width = 200; // Increased width for more detail
        int console_width = 200; // Assumed console width, adjust as needed

        std::string ascii_art = convertToColoredASCII(img, new_width, console_width);

        std::cout << ascii_art << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}
