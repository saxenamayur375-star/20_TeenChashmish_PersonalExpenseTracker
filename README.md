# Personal Money Expense Tracker

A menu-driven console application developed in **C** for a B.Tech 1st Year Mini Hackathon to track personal monthly expenses. The program allows users to set a monthly budget, record categorized expenses with short descriptions, view all logged expenses, inspect category-wise spending summaries and the highest expenditure category, and receive warnings whenever the monthly budget is exceeded.

## Features

- Set a monthly budget in Rupees (Rs.) with validation for positive values.
- Record up to 100 expenses, each with a category, positive amount, and a short description (up to 49 characters).
- Categorize expenses into five built-in categories: **Food**, **Travel**, **Books**, **Entertainment**, and **Other**.
- View all recorded expenses in a formatted tabular list.
- Calculate total spending and remaining budget (or the amount exceeded).
- Display category-wise spending totals along with each category's percentage share of total spending.
- Identify and display the highest expenditure category.
- Issue an immediate warning when adding an expense pushes total spending over the monthly budget.
- Display a final expense summary report automatically before exiting.

## Budget Status & Warnings

The program uses local C `if-else` conditions to evaluate total spending against the monthly budget and display the current budget status.

| Spending Condition | Budget Status Displayed |
|---|---|
| Total Spending < Monthly Budget | `STATUS: Within budget (X.X% used, Rs. Y.YY left).` |
| Total Spending == Monthly Budget | `STATUS: Budget fully used (Rs. 0.00 remaining).` |
| Total Spending > Monthly Budget | `STATUS: WARNING! Budget exceeded by Rs. Z.ZZ!` |

In addition, whenever a newly recorded expense causes total spending to exceed the monthly budget, an immediate warning (`*** WARNING: Monthly budget exceeded by Rs. Z.ZZ! ***`) is shown right after the entry is saved.

## Program Menu

After entering a valid monthly budget, the program presents four menu options:

1. **Add an Expense** — Choose a category (1–5), enter the expense amount, and add a short description.
2. **View All Recorded Expenses** — Display all recorded entries with their serial number, category, amount, and description.
3. **View Expense Summary & Budget Status** — Show total entries, monthly budget, total spending, remaining budget, category-wise totals with percentage shares, highest spending category, and budget status.
4. **Exit** — Print the final expense summary report and exit the program.

## Technologies Used

- C programming language
- Standard C libraries (`stdio.h`, `string.h`)
- Structures (`struct Expense`), arrays, functions, loops (`do-while`, `for`), `switch-case`, and conditional statements
- Console-based input and output

## Project Structure

```text
Personal-Money-Expense-Tracker/
├── expense_tracker.c
└── README.md
```

## Requirements

- GCC compiler (MinGW GCC on Windows, or GCC on Linux/macOS)
- A terminal or command prompt

## How to Compile and Run

### Windows (MinGW)

Open Command Prompt in the project folder and run:

```cmd
gcc expense_tracker.c -o expense_tracker.exe
expense_tracker.exe
```

### Linux / macOS

```bash
gcc expense_tracker.c -o expense_tracker
./expense_tracker
```

## Data Storage Note

Expense records are stored in an in-memory array (`MAX_EXPENSES = 100`) while the program is running. They are not saved permanently, so all entries are cleared when the program exits. File handling can be added in a future version to provide persistent storage.

## BY

- Mayur
- Kritvi
- Bhumika
