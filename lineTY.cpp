#include "lineTY.h"
#include <iostream>
#include <limits>

using namespace std;

//  lineTY � Rule of Three

lineTY::lineTY() {
    coeff = new double[3];
    coeff[0] = 0.0; // a
    coeff[1] = 1.0; // b
    coeff[2] = 0.0; // c   -> 0x + 1y = 0 => y = 0
}

lineTY::lineTY(double A, double B, double C) {
    coeff = new double[3];
    coeff[0] = A;
    coeff[1] = B;
    coeff[2] = C;
}

lineTY::lineTY(const lineTY& other) {
    coeff = new double[3];
    coeff[0] = other.coeff[0];
    coeff[1] = other.coeff[1];
    coeff[2] = other.coeff[2];
}

lineTY& lineTY::operator=(const lineTY& other) {
    if (this != &other) {
        coeff[0] = other.coeff[0];
        coeff[1] = other.coeff[1];
        coeff[2] = other.coeff[2];
    }
    return *this;
}

lineTY::~lineTY() {
    delete[] coeff;
}

//  getters

double lineTY::getA() const { return coeff[0]; }
double lineTY::getB() const { return coeff[1]; }
double lineTY::getC() const { return coeff[2]; }

//  A. Slope
//  line: a x + b y = c
//  if b == 0 -> vertical, slope undefined

double lineTY::slope() const {
    double a = coeff[0], b = coeff[1];
    if (b == 0.0) {
                    //  slope undefined-treat as vertical
        return 0.0; //  don't actually use this value if b==0
    }
    return -a / b;
}

//  B. Equal
//  a1x + b1y = c1 and a2x + b2y = c2 are equal if
//  (a1,b1,c1) = (a2,b2,c2) OR there exists k with
//  a1 = k a2, b1 = k b2, c1 = k c2

bool lineTY::isEqual(const lineTY& other) const {
    double a1 = coeff[0], b1 = coeff[1], c1 = coeff[2];
    double a2 = other.coeff[0], b2 = other.coeff[1], c2 = other.coeff[2];

    if (a1 == a2 && b1 == b2 && c1 == c2) {
        return true;
    }

    //  avoid division by 0; check possible k using whichever is non-zero
    if (a2 != 0.0) {
        double k = a1 / a2;
        return (b1 == k * b2 && c1 == k * c2);
    }
    else if (b2 != 0.0) {
        double k = b1 / b2;
        return (a1 == k * a2 && c1 == k * c2);
    }
    else if (c2 != 0.0) {
        double k = c1 / c2;
        return (a1 == k * a2 && b1 == k * b2);
    }

    //  if a2 == b2 == c2 == 0, extremely degenerate; treat as not equal
    return false;
}

//  C. Parallel
//  parallel if both vertical (b1==0 && b2==0) OR slopes equal

bool lineTY::isParallel(const lineTY& other) const {
    double a1 = coeff[0], b1 = coeff[1];
    double a2 = other.coeff[0], b2 = other.coeff[1];

    if (b1 == 0.0 && b2 == 0.0) {
        return true; // both vertical
    }
    if ((b1 == 0.0 && b2 != 0.0) || (b1 != 0.0 && b2 == 0.0)) {
        return false; //    one vertical, one not
    }
    //  both non-vertical: compare slopes via cross-multiply
    //  -a1/b1 == -a2/b2  <=>  a1*b2 == a2*b1
    return (a1 * b2 == a2 * b1);
}

//  D. Perpendicular
//  perpendicular if:
//  - one is horizontal (a=0, b!=0) and the other is vertical (b=0, a!=0)
//  OR slopes m1*m2 = -1 for non-vertical lines

bool lineTY::isPerpendicular(const lineTY& other) const {
    double a1 = coeff[0], b1 = coeff[1];
    double a2 = other.coeff[0], b2 = other.coeff[1];

    bool thisHorizontal = (a1 == 0.0 && b1 != 0.0);
    bool thisVertical = (b1 == 0.0 && a1 != 0.0);
    bool otherHorizontal = (a2 == 0.0 && b2 != 0.0);
    bool otherVertical = (b2 == 0.0 && a2 != 0.0);

    //  case 1: one horizontal, one vertical
    if ((thisHorizontal && otherVertical) || (thisVertical && otherHorizontal)) {
        return true;
    }

    //  case 2: general case m1 * m2 = -1, both non-vertical
    if (b1 == 0.0 || b2 == 0.0) {
        return false; //    at least one vertical but we already handled vert/horiz case
    }

    //  m1 = -a1/b1, m2 = -a2/b2
    //  m1*m2 = (a1*a2)/(b1*b2); want == -1 => a1*a2 == -b1*b2
    return (a1 * a2 == -b1 * b2);
}

//  E. Intersection Point
// 
//   a1 x + b1 y = c1
//   a2 x + b2 y = c2
//   D = a1*b2 - a2*b1
//   if D == 0 its parallel or equal, no single point

bool lineTY::intersectionPoint(const lineTY& other, double& x, double& y) const {
    double a1 = coeff[0], b1 = coeff[1], c1 = coeff[2];
    double a2 = other.coeff[0], b2 = other.coeff[1], c2 = other.coeff[2];

    double D = a1 * b2 - a2 * b1;
    if (D == 0.0) {
        return false;
    }

    double Dx = c1 * b2 - c2 * b1;
    double Dy = a1 * c2 - a2 * c1;

    x = Dx / D;
    y = Dy / D;
    return true;
}

//  Generic helpers

void WaitForEnter() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Press Enter To Return\n";
    cin.get();
}

void InputFailSafe(int& choice) {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid\n\n";
        choice = -1;
    }
}

//  Menu helpers

void listLines(const vector<lineTY*>& lines, bool showSlopes) {
    if (lines.empty()) {
        cout << "No lines stored.\n";
        return;
    }

    cout << "\nCurrent lines:\n";
    for (size_t i = 0; i < lines.size(); ++i) {
        const lineTY* L = lines[i];
        double a = L->getA();
        double b = L->getB();
        double c = L->getC();

        cout << (i + 1) << ") "
            << a << "x + " << b << "y = " << c;

        if (showSlopes) {
            if (b == 0.0) {
                cout << "   --> slope: undefined (vertical)";
            }
            else {
                cout << "   --> slope: " << L->slope();
            }
        }
        cout << "\n";
    }
}

void addLine(vector<lineTY*>& lines) {
    double A, B, C;
    cout << "\nEnter coefficients for new line (ax + by = c)\n";
    cout << "a = ";
    cin >> A;
    cout << "b = ";
    cin >> B;
    cout << "c = ";
    cin >> C;

    lineTY* ptr = new lineTY(A, B, C);
    lines.push_back(ptr);

    cout << "\nAdded line #" << lines.size() << ": "
        << A << "x + " << B << "y = " << C << "\n";
}

bool chooseIndex(const vector<lineTY*>& lines, int& idx, const char* prompt) {
    cout << prompt;
    cin >> idx;
    InputFailSafe(idx);
    if (idx == -1) return false;

    if (idx < 1 || idx > static_cast<int>(lines.size())) {
        cout << "Invalid index.\n";
        return false;
    }
    return true;
}

void compareTwoLines(const vector<lineTY*>& lines) {
    if (lines.size() < 2) {
        cout << "\nNeed at least 2 lines.\n";
        return;
    }

    cout << "\nCompare Two Lines\n";
    listLines(lines, false);

    int i1, i2;
    if (!chooseIndex(lines, i1, "\nEnter FIRST line number: "))  return;
    if (!chooseIndex(lines, i2, "Enter SECOND line number: "))   return;

    const lineTY* L1 = lines[i1 - 1];
    const lineTY* L2 = lines[i2 - 1];

    cout << "\nLine #" << i1 << ": "
        << L1->getA() << "x + " << L1->getB() << "y = " << L1->getC() << "\n";
    cout << "Line #" << i2 << ": "
        << L2->getA() << "x + " << L2->getB() << "y = " << L2->getC() << "\n\n";

    cout << "Equal?          " << (L1->isEqual(*L2) ? "YES" : "NO") << "\n";
    cout << "Parallel?       " << (L1->isParallel(*L2) ? "YES" : "NO") << "\n";
    cout << "Perpendicular?  " << (L1->isPerpendicular(*L2) ? "YES" : "NO") << "\n";
}

void intersectTwoLines(const vector<lineTY*>& lines) {
    if (lines.size() < 2) {
        cout << "\nNeed at least 2 lines.\n";
        return;
    }

    cout << "\nIntersection of Two Lines\n";
    listLines(lines, false);

    int i1, i2;
    if (!chooseIndex(lines, i1, "\nEnter FIRST line number: "))  return;
    if (!chooseIndex(lines, i2, "Enter SECOND line number: "))   return;

    const lineTY* L1 = lines[i1 - 1];
    const lineTY* L2 = lines[i2 - 1];

    if (L1->isEqual(*L2)) {
        cout << "Lines are equal: Many intersection points.\n";
        return;
    }
    if (L1->isParallel(*L2)) {
        cout << "Lines are parallel: no intersection point.\n";
        return;
    }

    double x, y;
    if (L1->intersectionPoint(*L2, x, y)) {
        cout << "Intersection at (" << x << ", " << y << ")\n";
    }
    else {
        cout << "No single intersection point.\n";
    }
}

void clearLines(vector<lineTY*>& lines) {
    for (lineTY* p : lines) {
        delete p;
    }
    lines.clear();
}
