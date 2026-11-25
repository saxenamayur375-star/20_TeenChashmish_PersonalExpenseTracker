# Personal Money Expense Tracker: Algorithm & Pseudocode

This document matches the exact logic of `expense_tracker.c` and is structured for B.Tech 1st-year mini hackathon documentation, presentations, and viva explanations.

## Overview

- **Inputs:** Monthly budget (`monthlyBudget`), menu choice (`choice`), and multiple expense records consisting of category (`1–5`), amount (`amount`), and short description (`note`).
- **Categories:** `1. Food`, `2. Travel`, `3. Books`, `4. Entertainment`, `5. Other`.
- **Outputs:** List of recorded expenses, total spending, remaining budget (or over-budget amount), category-wise totals with percentage share, highest expenditure category, and budget status warning.

## Algorithm

1. **Start.**
2. **Initialize** an array `expenses[100]` of structures (each storing `category`, `amount`, and `note`), set `expenseCount = 0`, and define `categoryNames` for Food, Travel, Books, Entertainment, and Other.
3. **Read and validate monthly budget:**
   - Prompt the user to enter `monthlyBudget`.
   - If the input is invalid or `monthlyBudget <= 0`, display an error message and prompt again until a positive value is entered.
4. **Display the main menu** in a loop until the user selects **Exit (`4`)**:
   - Option 1: Add an Expense
   - Option 2: View All Recorded Expenses
   - Option 3: View Expense Summary & Budget Status
   - Option 4: Exit
5. **If `choice == 1` (Add an Expense):**
   - If `expenseCount >= 100`, display a limit-reached message and return to the menu.
   - Display the 5 categories and read a valid `catChoice` between `1` and `5`.
   - Read a valid positive expense amount `amt > 0`.
   - Read a short description `note`.
   - Store `catChoice`, `amt`, and `note` at `expenses[expenseCount]` and increment `expenseCount` by `1`.
   - Compute `totalSpent` by summing `amount` across all recorded expenses.
   - If `totalSpent > monthlyBudget`, display an immediate over-budget warning showing `totalSpent - monthlyBudget`.
6. **If `choice == 2` (View All Recorded Expenses):**
   - If `expenseCount == 0`, display `"No expenses recorded yet."`
   - Otherwise, loop from `i = 0` to `expenseCount - 1` and print the serial number, category name, amount, and description of each expense.
7. **If `choice == 3` (View Expense Summary & Budget Status):**
   - Compute `totalSpent` across all recorded expenses and `remaining = monthlyBudget - totalSpent`.
   - Initialize an array `catTotals[5]` to `0` and accumulate each expense's `amount` into `catTotals[category - 1]`.
   - Find `highestIndex`, the index of the category with the maximum value in `catTotals` (or `-1` if no expenses exist).
   - Display total expenses recorded, monthly budget, total spending, and remaining budget (or `0.00` along with the over-budget amount if `remaining < 0`).
   - Loop through all 5 categories and display each category's total and percentage share `(catTotals[i] / totalSpent) * 100`.
   - Display the highest spending category and its total (or `"No expenses recorded yet."` if none).
   - Display the budget status:
     - If `totalSpent > monthlyBudget`: print **WARNING** with the exceeded amount.
     - Else if `totalSpent == monthlyBudget`: print that the budget is fully used.
     - Else: print **Within budget** along with percentage used and remaining amount.
8. **If `choice == 4` (Exit):**
   - Display the final summary and budget status (same as Step 7) and exit the loop.
9. **If `choice` is invalid:** Display an error message and show the menu again.
10. **Stop.**

## Pseudocode

```text
CONST MAX_EXPENSES = 100
CONST NUM_CATEGORIES = 5

STRUCT Expense
    category : INTEGER      // 1: Food, 2: Travel, 3: Books, 4: Entertainment, 5: Other
    amount   : FLOAT
    note     : STRING
END STRUCT

ARRAY categoryNames = ["Food", "Travel", "Books", "Entertainment", "Other"]

PROCEDURE MAIN()
    DECLARE expenses[MAX_EXPENSES] OF Expense
    SET expenseCount = 0
    SET monthlyBudget = 0.0

    // Step 1: Input and validate monthly budget
    REPEAT
        PRINT "Enter your monthly budget (Rs.): "
        READ monthlyBudget
        IF monthlyBudget <= 0 THEN
            PRINT "Invalid input! Please enter a positive amount."
        END IF
    UNTIL monthlyBudget > 0

    // Step 2: Menu-driven loop
    REPEAT
        CALL displayMenu()
        PRINT "Enter your choice (1-4): "
        READ choice

        SWITCH choice
            CASE 1:
                CALL addExpense(expenses, expenseCount, monthlyBudget)
            CASE 2:
                CALL showAllExpenses(expenses, expenseCount)
            CASE 3:
                CALL showSummary(expenses, expenseCount, monthlyBudget)
            CASE 4:
                PRINT "Final Report before exiting:"
                CALL showSummary(expenses, expenseCount, monthlyBudget)
                PRINT "Thank you for using the Expense Tracker!"
            DEFAULT:
                PRINT "Invalid choice! Please select between 1 and 4."
        END SWITCH
    UNTIL choice == 4
END PROCEDURE

PROCEDURE addExpense(expenses, BYREF count, budget)
    IF count >= MAX_EXPENSES THEN
        PRINT "Expense limit reached! Cannot add more expenses."
        RETURN
    END IF

    FOR i = 0 TO NUM_CATEGORIES - 1 DO
        PRINT (i + 1), ". ", categoryNames[i]
    END FOR

    REPEAT
        READ catChoice
    UNTIL catChoice >= 1 AND catChoice <= NUM_CATEGORIES

    REPEAT
        READ amt
    UNTIL amt > 0

    READ note

    SET expenses[count].category = catChoice
    SET expenses[count].amount = amt
    SET expenses[count].note = note
    SET count = count + 1

    SET totalSpent = calculateTotalSpent(expenses, count)
    IF totalSpent > budget THEN
        PRINT "WARNING: Monthly budget exceeded by Rs. ", (totalSpent - budget)
    END IF
END PROCEDURE

FUNCTION calculateTotalSpent(expenses, count) RETURNS FLOAT
    SET total = 0.0
    FOR i = 0 TO count - 1 DO
        SET total = total + expenses[i].amount
    END FOR
    RETURN total
END FUNCTION

PROCEDURE calculateCategoryTotals(expenses, count, catTotals)
    FOR i = 0 TO NUM_CATEGORIES - 1 DO
        SET catTotals[i] = 0.0
    END FOR

    FOR i = 0 TO count - 1 DO
        SET index = expenses[i].category - 1
        SET catTotals[index] = catTotals[index] + expenses[i].amount
    END FOR
END PROCEDURE

FUNCTION findHighestCategory(catTotals) RETURNS INTEGER
    SET maxIndex = -1
    SET maxAmount = 0.0
    FOR i = 0 TO NUM_CATEGORIES - 1 DO
        IF catTotals[i] > maxAmount THEN
            SET maxAmount = catTotals[i]
            SET maxIndex = i
        END IF
    END FOR
    RETURN maxIndex
END FUNCTION

PROCEDURE showAllExpenses(expenses, count)
    IF count == 0 THEN
        PRINT "No expenses recorded yet."
        RETURN
    END IF

    FOR i = 0 TO count - 1 DO
        PRINT (i + 1), categoryNames[expenses[i].category - 1], expenses[i].amount, expenses[i].note
    END FOR
END PROCEDURE

PROCEDURE showSummary(expenses, count, budget)
    DECLARE catTotals[NUM_CATEGORIES] OF FLOAT
    SET totalSpent = calculateTotalSpent(expenses, count)
    SET remaining = budget - totalSpent

    CALL calculateCategoryTotals(expenses, count, catTotals)
    SET highestIndex = findHighestCategory(catTotals)

    PRINT "Total Expenses Recorded: ", count
    PRINT "Monthly Budget: ", budget
    PRINT "Total Spending: ", totalSpent

    IF remaining >= 0 THEN
        PRINT "Remaining Budget: ", remaining
    ELSE
        PRINT "Remaining Budget: 0.00 (Over by ", (-remaining), ")"
    END IF

    FOR i = 0 TO NUM_CATEGORIES - 1 DO
        IF totalSpent > 0 THEN
            SET percent = (catTotals[i] / totalSpent) * 100
        ELSE
            SET percent = 0.0
        END IF
        PRINT categoryNames[i], catTotals[i], percent, "%"
    END FOR

    IF highestIndex != -1 THEN
        PRINT "Highest Spending Category: ", categoryNames[highestIndex], catTotals[highestIndex]
    ELSE
        PRINT "No expenses recorded yet."
    END IF

    IF totalSpent > budget THEN
        PRINT "STATUS: WARNING! Budget exceeded by Rs. ", (totalSpent - budget)
    ELSE IF totalSpent == budget THEN
        PRINT "STATUS: Budget fully used (Rs. 0.00 remaining)."
    ELSE
        SET usedPercent = (totalSpent / budget) * 100
        PRINT "STATUS: Within budget (", usedPercent, "% used, Rs. ", remaining, " left)."
    END IF
END PROCEDURE
```
