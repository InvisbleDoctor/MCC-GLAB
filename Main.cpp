#include <iostream>
#include <vector>
#include "lineTY.h"
#include "Shapemaker.h"

using namespace std;

//Testing git tracking

int main() {
    vector<lineTY*> lines;
    int choice = -1;

    do {
        cout << "\nMenu\n\n";
        cout << "1. Add a new line\n";
        cout << "2. List all lines (with slopes)\n";
        cout << "3. Compare two lines (equal/parallel/perpendicular)\n";
        cout << "4. Find intersection point of two lines\n";
        cout << "5. Detect shapes from CSV file\n";
        cout << "0. Exit\n\n";

        cout << "Enter your choice: ";
        // read menu choice, but if stdin is closed (EOF) exit cleanly
        if (!(cin >> choice)) {
            if (cin.eof()) {
                cout << "\nEnd-of-input detected, exiting program.\n";
                break; // EOF -> stop program
            }
            // non-numeric input or other error: recover and reprompt
            InputFailSafe(choice);
            if (choice == -1) continue;
        }

        switch (choice) {
        case 1:
            addLine(lines);
            //WaitForEnter();
            break;
        case 2:
            listLines(lines, true);
            WaitForEnter();
            break;
        case 3:
            compareTwoLines(lines);
            //WaitForEnter();
            break;
        case 4:
            intersectTwoLines(lines);
            //WaitForEnter();
            break;
        case 5: {
            const std::string filename = "lineData.csv";
            std::cout << "\n[Option 5] Reading file: " << filename << "\n";
            Shape loader;
            if (!loader.parseThroughCsvFile(filename)) {
                std::cout << "File read failed or empty: " << filename << "\n";
                break;
            }
            // Build shapes (groups of 4 lines). Provide diagnostic counts.
            std::vector<Shape> shapes = loader.buildShapes();
            std::cout << "Loaded total lines: " << loader.buildShapes().size()*4 << " (grouped into " << shapes.size() << " shapes)\n";
            if (shapes.empty()) {
                std::cout << "No complete groups of 4 lines. Nothing to classify.\n";
                break;
            }
            auto shapeTypeToString = [](ShapeType t){
                switch (t) {
                case ShapeType::Unknown: return std::string("Unknown");
                case ShapeType::Triangle: return std::string("Triangle");
                case ShapeType::Quadrilateral: return std::string("Quadrilateral");
                case ShapeType::Parallelogram: return std::string("Parallelogram");
                case ShapeType::Trapezoid: return std::string("Trapezoid");
                case ShapeType::Rhombus: return std::string("Rhombus");
                case ShapeType::Rectangle: return std::string("Rectangle");
                case ShapeType::Square: return std::string("Square");
                case ShapeType::Line: return std::string("Line");
                }
                return std::string("(invalid)");
            };
            std::size_t trapezoidCount=0, paraCount=0, rectCount=0, rhombCount=0, squareCount=0, unknownCount=0;
            std::cout << "\nClassifications:\n";
            for (size_t i = 0; i < shapes.size(); ++i) {
                auto linesForShape = shapes[i].getLines();
                std::cout << "\nShape #" << (i+1) << " lines:\n";
                for (size_t j = 0; j < linesForShape.size(); ++j) {
                    const lineTY &L = linesForShape[j];
                    std::cout << "  (" << (j+1) << ") " << L.getA() << "x + " << L.getB() << "y = " << L.getC() << "\n";
                }
                ShapeType t = shapes[i].detectShapeType();
                switch(t){
                    case ShapeType::Trapezoid: trapezoidCount++; break;
                    case ShapeType::Parallelogram: paraCount++; break;
                    case ShapeType::Rectangle: rectCount++; break;
                    case ShapeType::Rhombus: rhombCount++; break;
                    case ShapeType::Square: squareCount++; break;
                    case ShapeType::Unknown: unknownCount++; break;
                    default: break; // ignore other enums not needed here
                }
                std::cout << "=> Type: " << shapeTypeToString(t) << "\n";
            }
            std::cout << "\nSummary: "
                      << "Trapezoid=" << trapezoidCount << ", Parallelogram=" << paraCount
                      << ", Rectangle=" << rectCount << ", Rhombus=" << rhombCount
                      << ", Square=" << squareCount << ", Unknown=" << unknownCount << "\n";
            WaitForEnter();
            break;
        }
        case 0:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice.\n";
            WaitForEnter();
            break;
        }
    } while (choice != 0);

    clearLines(lines); //   free all before exit
    return 0;
}
