#include "Triangle.h"
#include <iostream>
#include <cmath>

using namespace std;

Triangle::Triangle(
    double _x1, double _y1,
    double _x2, double _y2,
    double _x3, double _y3) : x1(_x1), y1(_y1), x2(_x2), y2(_y2), x3(_x3), y3(_y3){}

double Triangle::distance(double xA, double yA, double xB, double yB) const {
    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

double Triangle::getInRadius() const {
    double a = distance(x1, y1, x2, y2);
    double b = distance(x2, y2, x3, y3);
    double c = distance(x3, y3, x1, y1);
    double s = (a + b + c) / 2.0;
    double area = std::sqrt(s * (s - a) * (s - b) * (s - c));
    return area / s;
}

void Triangle::print() const {
    std::cout << "Треугольник с вершинами: А("
    << x1 << ", " << y1 << "), B(" << x2 << ", " << y2 << "), C(" << x3 << ", " << y3 << ")" << std::endl;


}

Triangle::~Triangle() {
    std::cout << "Bye!";
}