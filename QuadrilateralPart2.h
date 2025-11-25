#pragma once
#include <vector>
#include <string>
#include "lineTY.h"

struct PointTY {
    double x;
    double y;
};

enum class QuadType {
    None,
    Parallelogram,
    Trapezoid,
    Rhombus,
    Rectangle,
    Square
};

std::vector<lineTY> infData(const std::string& filename);
bool isParallel(const lineTY& l1, const lineTY& l2, double eps = 1e-9);
bool isPerpendicular(const lineTY& l1, const lineTY& l2, double eps = 1e-9);
bool intersectionPoint(const lineTY& l1, const lineTY& l2, PointTY& p);
double pointDistance(const PointTY& p1, const PointTY& p2);

bool isParallelogram(const std::vector<lineTY>& L);
bool isTrapezoid(const std::vector<lineTY>& L);
bool isRhombus(const std::vector<lineTY>& L);
bool isRectangle(const std::vector<lineTY>& L);
bool isSquare(const std::vector<lineTY>& L);

QuadType classifyQuadrilateral(const std::vector<lineTY>& L);
const char* quadTypeToString(QuadType q);