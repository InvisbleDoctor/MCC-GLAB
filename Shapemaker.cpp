#include "Shapemaker.h"
#include <cmath>

//Default Constructor
Shape::Shape():
    M_line1(), M_line2(), M_line3(), M_line4(){} // Each lineTY default constructor called

//Parameter Constructor
Shape::Shape(const lineTY& line1,const lineTY& line2,const lineTY& line3,const lineTY& line4):
    M_line1(line1), M_line2(line2), M_line3(line3), M_line4(line4) {}

//Copy Constructor and Assignment Operator are defined in header file

//Data Parsing from CSV File
bool Shape::parseThroughCsvFile(const std::string& filename){
    std::ifstream inputFile(filename);
    if(!inputFile.is_open()){
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line; // to capture each line
    if(!std::getline(inputFile, line)) { // header (optional) consume first line
        return false; // empty file
    }

    while(std::getline(inputFile, line)) {
        // trim whitespace
        size_t start = line.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) continue; // blank line
        size_t end = line.find_last_not_of(" \t\r\n");
        std::string trimmed = line.substr(start, end - start + 1);

        std::stringstream ss(trimmed);
        std::string tokA, tokB, tokC;
        if(!std::getline(ss, tokA, ',')) continue;
        if(!std::getline(ss, tokB, ',')) continue;
        if(!std::getline(ss, tokC, ',')) continue;

        // trim tokens
        auto trimTok = [](std::string &t){
            size_t s = t.find_first_not_of(" \t\r\n");
            if (s == std::string::npos) { t.clear(); return; }
            size_t e = t.find_last_not_of(" \t\r\n");
            t = t.substr(s, e - s + 1);
        };
        trimTok(tokA); trimTok(tokB); trimTok(tokC);
        if (tokA.empty() || tokB.empty() || tokC.empty()) continue; // incomplete row

        double a=0.0, b=0.0, c=0.0;
        try {
            a = std::stod(tokA);
            b = std::stod(tokB);
            c = std::stod(tokC);
        } catch (const std::exception&) {
            // malformed numeric value; skip row
            continue;
        }

        lineTY tempLine(a,b,c);
        vM_lines.push_back(tempLine);
    }
    return true;
}


std::vector<Shape> Shape::buildShapes() const{
    std::vector<Shape> shapes;
    for(size_t i = 0; i + 3 < vM_lines.size(); i += 4){
        Shape tempShape(vM_lines[i], vM_lines[i+1], vM_lines[i+2], vM_lines[i+3]);
        shapes.emplace_back(tempShape);
    }

    return shapes;
}

ShapeType Shape::detectShapeType(){
    // Assumption for Part 2: (line1,line2) are opposite sides, (line3,line4) are opposite sides.
    // Opposite sides may be parallel; adjacent sides must come from different pairs.
    bool opp12 = M_line1.isParallel(M_line2);
    bool opp34 = M_line3.isParallel(M_line4);

    // If neither pair is parallel we cannot classify under required set.
    if (!opp12 && !opp34) { M_shapeType = ShapeType::Unknown; return M_shapeType; }

    // Exactly one parallel pair => trapezoid per assignment definition.
    if ((opp12 && !opp34) || (!opp12 && opp34)) { M_shapeType = ShapeType::Trapezoid; return M_shapeType; }

    // Both pairs parallel -> candidate for parallelogram family.
    // Need intersections of adjacent sides: adjacency pairs (1,3), (3,2), (2,4), (4,1).
    double xA,yA,xB,yB,xC,yC,xD,yD; // vertices in order A,B,C,D
    bool okA = M_line1.intersectionPoint(M_line3,xA,yA); // A = L1 & L3
    bool okB = M_line3.intersectionPoint(M_line2,xB,yB); // B = L3 & L2
    bool okC = M_line2.intersectionPoint(M_line4,xC,yC); // C = L2 & L4
    bool okD = M_line4.intersectionPoint(M_line1,xD,yD); // D = L4 & L1

    // Even if intersection fails (degenerate or parallel misuse), still at least a parallelogram.
    auto dist = [](double ax,double ay,double bx,double by){ double dx=ax-bx, dy=ay-by; return std::sqrt(dx*dx+dy*dy); };
    auto approxEqual = [](double a,double b,double eps=1e-6){ double diff=std::fabs(a-b); if(diff<=eps) return true; double m=std::fmax(std::fabs(a),std::fabs(b)); return diff <= eps*m; };

    bool rightAngle = false;
    bool allSidesEqual = false;

    if (okA && okB && okC && okD) {
        double s1 = dist(xA,yA,xB,yB); // along line3
        double s2 = dist(xB,yB,xC,yC); // along line2
        double s3 = dist(xC,yC,xD,yD); // along line4
        double s4 = dist(xD,yD,xA,yA); // along line1
        allSidesEqual = approxEqual(s1,s2) && approxEqual(s2,s3) && approxEqual(s3,s4);
        // Adjacent perpendicular checks
        bool perp13 = M_line1.isPerpendicular(M_line3);
        bool perp32 = M_line3.isPerpendicular(M_line2);
        bool perp24 = M_line2.isPerpendicular(M_line4);
        bool perp41 = M_line4.isPerpendicular(M_line1);
        rightAngle = (perp13 || perp32 || perp24 || perp41);
    } else {
        // Without reliable vertices we can still test perpendicular adjacency directly
        bool perp13 = M_line1.isPerpendicular(M_line3);
        bool perp32 = M_line3.isPerpendicular(M_line2);
        bool perp24 = M_line2.isPerpendicular(M_line4);
        bool perp41 = M_line4.isPerpendicular(M_line1);
        rightAngle = (perp13 || perp32 || perp24 || perp41);
        // Cannot measure side equality -> leave allSidesEqual false.
    }

    if (allSidesEqual && rightAngle) { M_shapeType = ShapeType::Square; return M_shapeType; }
    if (allSidesEqual) { M_shapeType = ShapeType::Rhombus; return M_shapeType; }
    if (rightAngle) { M_shapeType = ShapeType::Rectangle; return M_shapeType; }
    M_shapeType = ShapeType::Parallelogram; return M_shapeType;
}

std::array<lineTY,4> Shape::getLines() const {
    return { M_line1, M_line2, M_line3, M_line4 };
}

