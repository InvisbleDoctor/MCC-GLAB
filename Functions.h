#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>

class lineTY {
public:
    // Rule of Three
    lineTY();                               // default constructor
    lineTY(double A, double B, double C);   // parameter constructor
    lineTY(const lineTY& other);            // copy constructor
    lineTY& operator=(const lineTY& other); // copy assignment
    ~lineTY();                              // destructor

    // getters
    double getA() const;
    double getB() const;
    double getC() const;

    // A. slope (if not vertical)
    double slope() const;

    // B–E relationships
    bool isEqual(const lineTY& other) const;
    bool isParallel(const lineTY& other) const;
    bool isPerpendicular(const lineTY& other) const;
    bool intersectionPoint(const lineTY& other, double& x, double& y) const;

private:
    double* coeff; // coeff[0] = a, coeff[1] = b, coeff[2] = c
};

// generic helpers
void WaitForEnter();
void InputFailSafe(int& choice);

// menu helpers working on vector of pointers
void addLine(std::vector<lineTY*>& lines);
void listLines(const std::vector<lineTY*>& lines, bool showSlopes = false);
void compareTwoLines(const std::vector<lineTY*>& lines);
void intersectTwoLines(const std::vector<lineTY*>& lines);
void clearLines(std::vector<lineTY*>& lines);

#endif
