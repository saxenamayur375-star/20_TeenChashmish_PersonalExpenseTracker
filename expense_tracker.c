/*
 * Personal Money Expense Tracker
 * B.Tech 1st Year Mini Hackathon Project (C Programming)
 *
 * Features:
 * 1. Set a monthly budget
 * 2. Record multiple expenses with category and short note
 * 3. Categorize expenses (Food, Travel, Books, Entertainment, Other)
 * 4. Calculate total spending and remaining budget
 * 5. Display category-wise totals and highest expenditure category
 * 6. Issue a warning whenever the monthly budget is exceeded
 */

#include <stdio.h>
#include <string.h>

#define MAX_EXPENSES 100
#define NUM_CATEGORIES 5

/* Structure to store a single expense record */
struct Expense {
    int category;          /* 1: Food, 2: Travel, 3: Books, 4: Entertainment, 5: Other */
    float amount;
    char note[50];
};

/* Category names for display */
const char categoryNames[NUM_CATEGORIES][20] = {
    "Food",
    "Travel",
    "Books",
    "Entertainment",
    "Other"
};

/* Function declarations */
void displayMenu(void);
void addExpense(struct Expense expenses[], int *count, float budget);
float calculateTotalSpent(struct Expense expenses[], int count);
void calculateCategoryTotals(struct Expense expenses[], int count, float catTotals[]);
int findHighestCategory(float catTotals[]);
void showSummary(struct Expense expenses[], int count, float budget);
void showAllExpenses(struct Expense expenses[], int count);

int main(void) {
    struct Expense expenses[MAX_EXPENSES];
    int expenseCount = 0;
    float monthlyBudget = 0.0f;
    int choice;

    printf("=============================================\n");
    printf("        PERSONAL MONEY EXPENSE TRACKER       \n");
    printf("=============================================\n");

    /* Step 1: Accept a valid monthly budget */
    do {
        printf("\nEnter your monthly budget (Rs.): ");
        if (scanf("%f", &monthlyBudget) != 1 || monthlyBudget <= 0) {
            printf("Invalid input! Please enter a positive amount.\n");
            while (getchar() != '\n'); /* Clear invalid input */
            monthlyBudget = 0.0f;
        }
    } while (monthlyBudget <= 0);

    printf("Monthly budget set to Rs. %.2f\n", monthlyBudget);

    /* Step 2: Menu-driven loop to record and view expenses */
    do {
        displayMenu();
        printf("Enter your choice (1-4): ");
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a number between 1 and 4.\n");
            while (getchar() != '\n');
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                addExpense(expenses, &expenseCount, monthlyBudget);
                break;

            case 2:
                showAllExpenses(expenses, expenseCount);
                break;

            case 3:
                showSummary(expenses, expenseCount, monthlyBudget);
                break;

            case 4:
                printf("\nFinal Report before exiting:\n");
                showSummary(expenses, expenseCount, monthlyBudget);
                printf("Thank you for using the Expense Tracker!\n");
                break;

            default:
                printf("\nInvalid choice! Please select between 1 and 4.\n");
        }
    } while (choice != 4);

    return 0;
}

/* Displays the main menu options */
void displayMenu(void) {
    printf("\n------------------- MENU --------------------\n");
    printf("1. Add an Expense\n");
    printf("2. View All Recorded Expenses\n");
    printf("3. View Expense Summary & Budget Status\n");
    printf("4. Exit\n");
    printf("---------------------------------------------\n");
}

/* Adds a new expense to the array and checks budget limit */
void addExpense(struct Expense expenses[], int *count, float budget) {
    int catChoice;
    float amt;
    float totalSpent;

    if (*count >= MAX_EXPENSES) {
        printf("\nExpense limit (%d) reached! Cannot add more expenses.\n", MAX_EXPENSES);
        return;
    }

    printf("\nSelect Expense Category:\n");
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        printf("  %d. %s\n", i + 1, categoryNames[i]);
    }

    do {
        printf("Enter category number (1-%d): ", NUM_CATEGORIES);
        if (scanf("%d", &catChoice) != 1 || catChoice < 1 || catChoice > NUM_CATEGORIES) {
            printf("Invalid category! Please choose between 1 and %d.\n", NUM_CATEGORIES);
            while (getchar() != '\n');
            catChoice = 0;
        }
    } while (catChoice < 1 || catChoice > NUM_CATEGORIES);

    do {
        printf("Enter expense amount (Rs.): ");
        if (scanf("%f", &amt) != 1 || amt <= 0) {
            printf("Invalid amount! Please enter a positive value.\n");
            while (getchar() != '\n');
            amt = 0.0f;
        }
    } while (amt <= 0);

    printf("Enter short description (e.g., Lunch, Bus fare): ");
    scanf(" %49[^\n]", expenses[*count].note);

    expenses[*count].category = catChoice;
    expenses[*count].amount = amt;
    (*count)++;

    printf("\nExpense recorded: %s - Rs. %.2f (%s)\n",
           categoryNames[catChoice - 1], amt, expenses[*count - 1].note);

    /* Immediate warning if budget is exceeded */
    totalSpent = calculateTotalSpent(expenses, *count);
    if (totalSpent > budget) {
        printf("\n*** WARNING: Monthly budget exceeded by Rs. %.2f! ***\n",
               totalSpent - budget);
    }
}

/* Calculates total amount spent across all recorded expenses */
float calculateTotalSpent(struct Expense expenses[], int count) {
    float total = 0.0f;
    for (int i = 0; i < count; i++) {
        total += expenses[i].amount;
    }
    return total;
}

/* Calculates spending total for each category */
void calculateCategoryTotals(struct Expense expenses[], int count, float catTotals[]) {
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        catTotals[i] = 0.0f;
    }

    for (int i = 0; i < count; i++) {
        int index = expenses[i].category - 1;
        if (index >= 0 && index < NUM_CATEGORIES) {
            catTotals[index] += expenses[i].amount;
        }
    }
}

/* Returns the index of the category with the highest spending, or -1 if none */
int findHighestCategory(float catTotals[]) {
    int maxIndex = -1;
    float maxAmount = 0.0f;

    for (int i = 0; i < NUM_CATEGORIES; i++) {
        if (catTotals[i] > maxAmount) {
            maxAmount = catTotals[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}

/* Displays a table of all individual recorded expenses */
void showAllExpenses(struct Expense expenses[], int count) {
    printf("\n============= RECORDED EXPENSES =============\n");
    if (count == 0) {
        printf("No expenses recorded yet.\n");
        printf("=============================================\n");
        return;
    }

    printf("%-4s %-15s %-12s %s\n", "No.", "Category", "Amount(Rs.)", "Description");
    printf("---------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-4d %-15s %-12.2f %s\n",
               i + 1,
               categoryNames[expenses[i].category - 1],
               expenses[i].amount,
               expenses[i].note);
    }
    printf("=============================================\n");
}

/* Displays complete expense summary, category-wise totals, highest category, and budget status */
void showSummary(struct Expense expenses[], int count, float budget) {
    float catTotals[NUM_CATEGORIES];
    float totalSpent = calculateTotalSpent(expenses, count);
    float remaining = budget - totalSpent;
    int highestIndex;

    calculateCategoryTotals(expenses, count, catTotals);
    highestIndex = findHighestCategory(catTotals);

    printf("\n============== EXPENSE SUMMARY ==============\n");
    printf("Total Expenses Recorded : %d\n", count);
    printf("Monthly Budget          : Rs. %.2f\n", budget);
    printf("Total Spending          : Rs. %.2f\n", totalSpent);

    if (remaining >= 0) {
        printf("Remaining Budget        : Rs. %.2f\n", remaining);
    } else {
        printf("Remaining Budget        : Rs. 0.00 (Over by Rs. %.2f)\n", -remaining);
    }

    printf("\n----------- CATEGORY-WISE TOTALS ------------\n");
    printf("%-16s %-14s %s\n", "Category", "Total (Rs.)", "Share");
    printf("---------------------------------------------\n");
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        float percent = (totalSpent > 0) ? (catTotals[i] / totalSpent) * 100.0f : 0.0f;
        printf("%-16s %-14.2f %.1f%%\n", categoryNames[i], catTotals[i], percent);
    }

    printf("\n----------- HIGHEST EXPENDITURE -------------\n");
    if (highestIndex != -1) {
        printf("Highest Spending Category: %s (Rs. %.2f)\n",
               categoryNames[highestIndex], catTotals[highestIndex]);
    } else {
        printf("No expenses recorded yet.\n");
    }

    printf("\n--------------- BUDGET STATUS ---------------\n");
    if (totalSpent > budget) {
        printf("STATUS: WARNING! Budget exceeded by Rs. %.2f!\n", totalSpent - budget);
    } else if (totalSpent == budget) {
        printf("STATUS: Budget fully used (Rs. 0.00 remaining).\n");
    } else {
        float usedPercent = (totalSpent / budget) * 100.0f;
        printf("STATUS: Within budget (%.1f%% used, Rs. %.2f left).\n",
               usedPercent, remaining);
    }
    printf("=============================================\n");
}