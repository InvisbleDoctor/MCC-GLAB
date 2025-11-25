#include "Shapemaker.h"

//Default Constructor
Shape::Shape():
    M_line1(), M_line2(), M_line3(), M_line4(){} // Each lineTY default constructor called

//Parameter Constructor
Shape::Shape(const lineTY& line1,const lineTY& line2,const lineTY& line3,const lineTY& line4):
    M_line1(line1), M_line2(line2), M_line3(line3), M_line4(line4) {}

//Copy Constructor and Assignment Operator are defined in header file

//Data Parsing from CSV File
bool Shape::parseThroughCsvFile(const std::string& filename){
    std::ifstream inputFile;
    inputFile.open(filename);
    if(!inputFile.is_open()){
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }
    std::string line = ""; //Empty String to capture each line

    getline(inputFile, line); //Captures Headerline in csv file
    line = ""; //clear line

    while(getline(inputFile,line))
    {
        std::string tempStringForValues = "";
        double a=0.0, b=0.0, c=0.0;

        std::stringstream inputString(line); //Create stringstream object to parse line

        getline(inputString, tempStringForValues, ','); //Get 'a' value, comma is set as delimiter
        a = std::stod(tempStringForValues); //Convert string to double


    }


}