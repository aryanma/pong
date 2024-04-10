#include <cmath>
#include <iostream>

void calculateStringLengths(double W, double H, double x, double y) {
    double bottomLeft = sqrt(x*x + y*y);
    double bottomRight = sqrt((W-x)*(W-x) + y*y);
    double topRight = sqrt((W-x)*(W-x) + (H-y)*(H-y));
    double topLeft = sqrt(x*x + (H-y)*(H-y));

    std::cout << "Bottom-left string length: " << bottomLeft << std::endl;
    std::cout << "Bottom-right string length: " << bottomRight << std::endl;
    std::cout << "Top-right string length: " << topRight << std::endl;
    std::cout << "Top-left string length: " << topLeft << std::endl;
}

int main() {
    // Example usage
    double W = 100.0; // Width of the field
    double H = 100.0; // Height of the field
    double x = 50.0; // X position
    double y = 50.0; // Y position

    calculateStringLengths(W, H, x, y);

    return 0;
}
