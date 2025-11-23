# QA Report: Branch lineTY-Slope-Function-Adjustment

## Summary of Changes

### 1. Validation for Degenerate Lines
* In the `lineTY` constructor, a check was added to detect when both coefficients `a` and `b` are zero (i.e., the line equation is not valid).
* If both are zero, a warning is printed, and the line is set to the default `y = 0`.

### 2. User Input Validation in `addLine`
* The `addLine` function was updated to prevent users from entering both `a = 0` and `b = 0` for a new line.
* The function now prompts the user to re-enter values if both are zero, ensuring only valid lines are created.

### 3. Slope Calculation Clarification
* The `slope()` member function returns `numeric_limits<double>::infinity()` for vertical lines (when `b == 0`), clearly indicating an undefined slope.
* A message is printed to inform the user when the slope is undefined.

---

## Testing Performed

| Test Case | Description | Result |
| :--- | :--- | :--- |
| **Constructor Validation** | Attempted to create a line with `a=0`, `b=0`. | Program outputs warning & defaults to `y=0`. |
| **User Input** | Tried to add line with `a` and `b` as zero. | Program prompts for re-entry until valid. |
| **Slope Function** | Checked horizontal (`0.0`), vertical (`inf`), and normal lines. | Returns correct/handled values. |

---

## Results
* The program no longer allows degenerate lines to be created by user input or by the constructor.
* Slope calculations are robust and user-friendly, with clear messaging for undefined slopes.
* All other line operations (equality, parallelism, perpendicularity, intersection) function as expected with the improved validation.

---

## Recommendations
* [ ] **Add Continuous Functionality for Menu Options:**
    * In **Option 1**, after the user enters the first line, prompt the user with a sub-menu:
        * `1`: Add another line
        * `2`: Return to main menu
    * *Current behavior:* Forces a return to the main menu via "Press Enter."
    * *Functionality should also be added to option 3 and 4 in case the user wants to compare multiple sets of lines