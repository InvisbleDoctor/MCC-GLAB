#include <iostream>
#include <vector>
#include "lineTY.h"

using namespace std;

//Testing git tracking

// charlene is testing  push

int main() {
    vector<lineTY*> lines;
    int choice = -1;

    do {
        cout << "\nMenu\n\n";
        cout << "1. Add a new line\n";
        cout << "2. List all lines (with slopes)\n";
        cout << "3. Compare two lines (equal/parallel/perpendicular)\n";
        cout << "4. Find intersection point of two lines\n";
        cout << "0. Exit\n\n";

        cout << "Enter your choice: ";
        cin >> choice;
        InputFailSafe(choice);
        if (choice == -1) continue;

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