#include "quadrilateralPart2.h"
#include <cmath>
#include <fstream>
#include <iostream>

using std::vector;
using std::string;

vector<lineTY> infData(const string& filename)
{
    vector<lineTY> lines;
    std::ifstream file(filename);
    if (!file) return lines;

    double a, b, c;
    while (file >> a >> b >> c)
        lines.push_back(lineTY(a, b, c));

    return lines;
}

bool isParallel(const lineTY& l1, const lineTY& l2, double eps)
{
    double a1=l1.getA(), b1=l1.getB();
    double a2=l2.getA(), b2=l2.getB();

    bool v1 = std::fabs(b1) < eps;
    bool v2 = std::fabs(b2) < eps;

    if (v1 && v2) return true;
    if (v1 || v2) return false;

    return std::fabs((-a1/b1) - (-a2/b2)) < eps;
}

bool isPerpendicular(const lineTY& l1, const lineTY& l2, double eps)
{
    double a1=l1.getA(), b1=l1.getB();
    double a2=l2.getA(), b2=l2.getB();

    bool v1 = std::fabs(b1) < eps;
    bool v2 = std::fabs(b2) < eps;

    if (v1 && !v2) return std::fabs(-a2/b2) < eps;
    if (!v1 && v2) return std::fabs(-a1/b1) < eps;
    if (v1 && v2) return false;

    return std::fabs(((-a1/b1) * (-a2/b2)) + 1.0) < eps;
}

bool intersectionPoint(const lineTY& l1, const lineTY& l2, PointTY& p)
{
    double a1=l1.getA(), b1=l1.getB(), c1=l1.getC();
    double a2=l2.getA(), b2=l2.getB(), c2=l2.getC();
    double det = a1*b2 - a2*b1;

    if (std::fabs(det) < 1e-9) return false;

    p.x = (c1*b2 - c2*b1) / det;
    p.y = (a1*c2 - a2*c1) / det;
    return true;
}

double pointDistance(const PointTY& p1, const PointTY& p2)
{
    double dx=p2.x-p1.x, dy=p2.y-p1.y;
    return std::sqrt(dx*dx + dy*dy);
}

static bool valid4(const vector<lineTY>& L)
{ return L.size() == 4; }

bool isParallelogram(const vector<lineTY>& L)
{
    if (!valid4(L)) return false;
    return isParallel(L[0],L[1]) && isParallel(L[2],L[3]) &&
           !isPerpendicular(L[0],L[2]);
}

bool isTrapezoid(const vector<lineTY>& L)
{
    if (!valid4(L)) return false;
    bool p12 = isParallel(L[0],L[1]);
    bool p34 = isParallel(L[2],L[3]);
    return (p12 ^ p34);
}

static bool computeVertices(const vector<lineTY>& L,
                            PointTY& P13,PointTY& P14,
                            PointTY& P23,PointTY& P24)
{
    return intersectionPoint(L[0],L[2],P13) &&
           intersectionPoint(L[0],L[3],P14) &&
           intersectionPoint(L[1],L[2],P23) &&
           intersectionPoint(L[1],L[3],P24);
}

bool isRhombus(const vector<lineTY>& L)
{
    if (!isParallelogram(L)) return false;

    PointTY A,B,C,D;
    if (!computeVertices(L,A,B,C,D)) return false;

    double s1=pointDistance(A,B);
    double s2=pointDistance(B,D);
    double s3=pointDistance(D,C);
    double s4=pointDistance(C,A);

    const double eps=1e-6;
    return std::fabs(s1-s2)<eps && std::fabs(s1-s3)<eps && std::fabs(s1-s4)<eps;
}

bool isRectangle(const vector<lineTY>& L)
{
    if (!valid4(L)) return false;

    if (!(isParallel(L[0],L[1]) && isParallel(L[2],L[3]))) return false;
    if (!(isPerpendicular(L[0],L[2]) && isPerpendicular(L[1],L[2]))) return false;

    PointTY A,B,C,D;
    if (!computeVertices(L,A,B,C,D)) return false;

    double s1 = pointDistance(A,B);
    double s2 = pointDistance(A,C);

    return std::fabs(s1-s2) > 1e-6;
}

bool isSquare(const vector<lineTY>& L)
{
    if (!valid4(L)) return false;

    if (!(isParallel(L[0],L[1]) && isParallel(L[2],L[3]))) return false;
    if (!(isPerpendicular(L[0],L[2]) && isPerpendicular(L[1],L[2]))) return false;

    PointTY A,B,C,D;
    if (!computeVertices(L,A,B,C,D)) return false;

    double s1=pointDistance(A,B);
    double s2=pointDistance(A,C);
    double s3=pointDistance(C,D);
    double s4=pointDistance(B,D);

    const double eps=1e-6;
    return std::fabs(s1-s2)<eps &&
           std::fabs(s1-s3)<eps &&
           std::fabs(s1-s4)<eps;
}

QuadType classifyQuadrilateral(const vector<lineTY>& L)
{
    if (isSquare(L)) return QuadType::Square;
    if (isRectangle(L)) return QuadType::Rectangle;
    if (isRhombus(L)) return QuadType::Rhombus;
    if (isParallelogram(L)) return QuadType::Parallelogram;
    if (isTrapezoid(L)) return QuadType::Trapezoid;
    return QuadType::None;
}

const char* quadTypeToString(QuadType q)
{
    switch(q) {
        case QuadType::Square:        return "Square";
        case QuadType::Rectangle:     return "Rectangle";
        case QuadType::Rhombus:       return "Rhombus";
        case QuadType::Parallelogram: return "Parallelogram";
        case QuadType::Trapezoid:     return "Trapezoid";
        default:                      return "None";
    }
}