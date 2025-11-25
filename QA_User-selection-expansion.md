# **QA Report — Branch: `User-Selection-expansion`**

**Scope:**  
Runtime input/validation and line behavior updates only.  
*No `tasks.json` or build configuration changes included.*

---

## **Summary of Changes**

### **1. Constructor Validation**
**File:** `lineTY`  
- Updated constructor `lineTY(double A, double B, double C)` detects the **degenerate line case** where:
  ```cpp
  a == 0 && b == 0
  ```
- When this occurs:
  - A warning is printed.
  - The object is reset to the **default line: `y = 0`**.

---

### **2. User Input Validation for Adding Lines**
**Function:** `addLine(...)`
- Fully reworked to:
  - Repeatedly prompt until valid inputs are entered.
  - Validate coefficients:
    - Requires valid `a`, `b`.
    - Validates `c`.
  - Correctly handles `cin` failures (e.g., non-numeric input).
  - Allows user to:
    - Add multiple lines consecutively.
    - Safely return to the main menu.

---

### **3. Slope Handling**
**Function:** `slope()`
- Returns:
  - `0.0` for **horizontal lines** (`a ≠ 0, b = 0 → y = constant`).
  - `std::numeric_limits<double>::infinity()` for **vertical lines** (`b == 0`).
- Prints a clear status message indicating the type of line.

---

### **4. Interactive Comparisons & Intersections**
**Functions:**
- `compareTwoLines(...)`
- `intersectTwoLines(...)`

Both now:
- Use a **loop** to enable repeated user operations.
- Support:
  - Retrying invalid selections.
  - Performing comparisons/intersections for multiple pairs in a single session.
  - Explicitly returning to the main menu via user choice.

---
