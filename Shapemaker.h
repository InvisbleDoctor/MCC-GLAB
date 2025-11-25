#include "lineTY.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>

class Shape{
    std::string M_shapeType;
    lineTY M_line1, M_line2, M_line3, M_line4; // up to 4 lines for shapes like rectangle

    std::vector<lineTY> vM_lines; // vector to hold multiple lines if needed
public:
    //Constructors and Destructors
    Shape(); // default constructor
    Shape(const lineTY& line1,const lineTY& line2,const lineTY& line3,const lineTY& line4); // parameter constructor
    
    Shape(const Shape& other) : M_line1(other.M_line1),  // copy constructor
    M_line2(other.M_line2), M_line3(other.M_line3), M_line4(other.M_line4) {}
    
    //Assignment Operator
    Shape& operator=(const Shape& rhs) {
        if (this != &rhs) {
            return *this;
        }
        M_line1 = rhs.M_line1;
        M_line2 = rhs.M_line2;
        M_line3 = rhs.M_line3;
        M_line4 = rhs.M_line4;
        return *this;
    }

    
    bool parseThroughCsvFile(const std::string& filename);

    //Destructor
    ~Shape() {}  
};