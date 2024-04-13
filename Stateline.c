#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <time.h> 
#include <stdbool.h> 

#define SIZE 100

float total_lubcost = 0, max_cap87 = 75708.23, max_cap90 = 113562.35, max_capDiesel = 94635;
char cust_type[8];

typedef struct charge_customer {
    int idnum; // customer's ID number or business name
    char lic_plnum[9]; // license plate number (e.g., 5786KW). 
    float deposit_am;
    float f_needed; // Variable to store fuel needed
    int f_type; // Variable to store fuel type
    char bus_name[50];

} cus_mers;

void fuel_menu() {
    printf("Fuel  Type          Price Per litre($)\n"); // Display fuel types and prices
    printf("1. E10-87                 184.90\n");
    printf("2. E10-90                 193.60\n");
    printf("3. Diesel                 182.30\n");
}

void lubricant_menu() {
    printf("Lubricant Type             Price($)\n"); // Display lubricant types and prices
    printf("1. 5w-30                    2900.00\n ");
    printf("2. 5w-40                    3500.00\n ");
    printf("3. 15w-40                   3600.00\n ");
    printf("4. SAE-40                   2100.00\n ");
}

void gen_receipt(char* cust_type, float final_cost, float cash_tendered, float total_lubcost) {
    printf("\nReceipt:\n");
    printf("Date of Transaction: %s\n", __DATE__); // Current date
    printf("Type of Customer: %s\n", cust_type);
    printf("Item(s) Purchased: Fuel\n");
    printf("GCT Amount (calculated at 16%% for all lubricants): %.2f\n", total_lubcost * 0.16); // Assuming 16% GCT for all items
    printf("Total Amount (including GCT): %.2f\n", final_cost);
    if (strcmp(cust_type, "COD") == 0) {
        printf("Cash Tendered: %.2f\n", cash_tendered);
        printf("Change Given: %.2f\n", cash_tendered - final_cost);
    }
}

void ranlubri(float* total_lubcost) {
    int lub_qty; // Variable to store lubricant quantity
    int lub_type; // Variable to store lubricant type
    char lubricant_request;

    srand(time(0)); // Seed for random number generation
    lubricant_request = (rand() % 2) ? 'Y' : 'N'; // Randomly choose 'Y' or 'N' for lubricant request
        
    printf("Lubricant Request: %c\n", lubricant_request); // Display lubricant request
    if (lubricant_request == 'Y') { // If lubricant is requested
        lubricant_menu();
        printf("Enter the number that represents the lubricant type purchasing: "); // Prompt user to enter lubricant type
        scanf("%d", &lub_type); // Read lubricant type from user input
        
        printf("Enter lubricant quantity: "); // Prompt user to enter lubricant quantity
        scanf("%d", &lub_qty); // Read lubricant quantity from user input

        switch (lub_type) { // Calculate total lubricant cost based on lubricant type and quantity
            case 1:
                *total_lubcost += 2900.00 * lub_qty;
                break;
            case 2:
                *total_lubcost += 3500.00 * lub_qty;
                break;
            case 3:
                *total_lubcost += 3600.00 * lub_qty;
                break;
            case 4:
                *total_lubcost += 2100.00 * lub_qty;
                break;
            default:
                break;
        }
    }
}

void serv_cust(cus_mers servchargcustomer[], int size) {
    cus_mers CODcus;
    cus_mers charge_1;

    float E87_tot = 0;
    float E90_tot = 0;
    float d_tot = 0;
    float chargeE87_tot = 0;
    float chargeE90_tot = 0;
    float charge_d_tot = 0;
    int pay_opt = 0; // Variable to store payment option
    float price_pl = 0; // Variable to store price per litre of fuel
    float tot_lcost = 0; // Variable to store total fuel cost
    float final_cost = 0; // Variable to store final cost
    float total_lubcost = 0; // Variable to store total lubricant cost
    float cash_tendered = 0;
    int choice = 0;

    printf("Select customer type (COD or Charge): "); // Prompt user to select customer type
    scanf("%s", cust_type); // Read customer type from user input

    if (strcmp(cust_type, "COD") == 0) { // If customer type is Cash on Delivery (COD)

        fuel_menu();
        printf("Enter the number that represents the fuel type purchasing: "); // Prompt user to enter fuel type
        scanf("%d", &CODcus.f_type); // Read fuel type from user input

        printf("Please enter the amount of fuel needed (In litres): "); // Prompt user to enter fuel amount
        scanf("%f", &CODcus.f_needed); // Read fuel amount from user input

        ranlubri(&total_lubcost);        

        switch (CODcus.f_type) { // Calculate total fuel cost based on fuel type and amount
            case 1:
                price_pl = 184.90;      
                E87_tot = price_pl * CODcus.f_needed;
                tot_lcost += E87_tot;
                final_cost = tot_lcost + total_lubcost;
                max_cap87 -= CODcus.f_needed;
                break;
            case 2:
                price_pl = 193.60;
                E90_tot = price_pl * CODcus.f_needed;
                tot_lcost += E90_tot;
                final_cost = tot_lcost + total_lubcost;
                max_cap90 -= CODcus.f_needed;
                break;
            case 3:
                price_pl = 182.30;
                d_tot = price_pl * CODcus.f_needed;
                tot_lcost += d_tot;
                final_cost = tot_lcost + total_lubcost;
                max_capDiesel -= CODcus.f_needed;
                break;
            default:
                break;
        }

        while (true) { // Loop until valid payment option is selected
            printf("Payment option (1 for cash or 2 for card): "); // Prompt user to select payment option
            scanf("%d", &pay_opt); // Read payment option from user input

            if (CODcus.f_needed < 2 && pay_opt == 1) { // Check if minimum purchase condition for cash payment is met
                printf("The minimum purchase is two litres for cash payments.\n"); // Display error message
                continue; // Continue to next iteration of the loop
            } else if (final_cost < 1000 && pay_opt == 2) { // Check if minimum amount condition for card payment is met
                printf("The minimum amount is $1000 for card transactions.\n"); // Display error message
                continue; // Continue to next iteration of the loop
            } else {
                break; // Exit the loop if payment option is valid
            }
        }

        if (pay_opt == 1) {
            printf("Please enter cash tendered: ");
            scanf("%f", &cash_tendered);
        }

        gen_receipt(cust_type, final_cost, cash_tendered, total_lubcost);

    } else if (strcmp(cust_type, "charge") == 0) { // If customer type is Charge

        int count = 0, flag, countinner = 0;
        char lic_num[9];
        float max_cash_deposit = 10000.00;

        for (count = 0; count < size; count++) {
            printf("Will you be entering your Customer ID number or Business name (1 for Customer ID and 2 for Business name): ");
            scanf("%d", &choice);

            if (choice == 1) {
                printf("Please enter Customer's ID number: ");
                scanf("%d", &servchargcustomer[count].idnum);
            } else {
                printf("Please enter Customer's ID number or business name: ");
                scanf("%s", servchargcustomer[count].bus_name);
            }

            while (true) {
                printf("Please enter license plate number: ");
                scanf("%8s", lic_num); // Ensure buffer size is correct

                flag = 0;
                for (countinner = 0; countinner < size; countinner++) {
                    if (strcmp(lic_num, servchargcustomer[countinner].lic_plnum) == 0) {
                        printf("That license plate number already exists!\n");
                        flag = 1;
                        break; // Exit the inner loop if a duplicate is found
                    }
                }
                if (flag == 0) {
                    // No duplicates found, copy the license number and break the loop
                    strcpy(servchargcustomer[count].lic_plnum, lic_num);
                    break;
                }
            }   

            fuel_menu();
            printf("Enter the number that represents the fuel type purchasing: "); // Prompt user to enter fuel type
            scanf("%d", &servchargcustomer[count].f_type); // Read fuel type from user input

            printf("Please enter the amount of fuel needed (In litres): "); // Prompt user to enter fuel amount
            scanf("%f", &servchargcustomer[count].f_needed); // Read fuel amount from user input

            ranlubri(&total_lubcost);
        }

        for (count = 0; count < size; count++) {
            switch (servchargcustomer[count].f_type) {
                case 1: // E10-87
                    price_pl = 184.90;
                    chargeE87_tot = price_pl * servchargcustomer[count].f_needed;
                    if (servchargcustomer[count].f_needed <= max_cap87) {
                        if (pay_opt == 1) {
                            printf("Please enter cash tendered: ");
                            scanf("%f", &cash_tendered);
                            if (cash_tendered > max_cash_deposit) {
                                printf("Error: Cash tendered exceeds maximum allowed deposit of $%.2f. Transaction not processed.\n", max_cash_deposit);
                            } else {
                                tot_lcost += chargeE87_tot;
                                final_cost = tot_lcost + total_lubcost;
                                max_cap87 -= servchargcustomer[count].f_needed;  // Deduct the amount from the remaining capacity
                            }
                        } else {
                            tot_lcost += chargeE87_tot;
                            final_cost = tot_lcost + total_lubcost;
                            max_cap87 -= servchargcustomer[count].f_needed;  // Deduct the amount from the remaining capacity
                        }
                    } else {
                        printf("Error: Request exceeds fuel capacity for E10-87. Transaction not processed.\n");
                    }
                    break;
                case 2: // E10-90
                    price_pl = 193.60;
                    chargeE90_tot = price_pl * servchargcustomer[count].f_needed;
                    if (servchargcustomer[count].f_needed <= max_cap90) {
                        if (pay_opt == 1) {
                            printf("Please enter cash tendered: ");
                            scanf("%f", &cash_tendered);
                            if (cash_tendered > max_cash_deposit) {
                                printf("Error: Cash tendered exceeds maximum allowed deposit of $%.2f. Transaction not processed.\n", max_cash_deposit);
                            } else {
                                tot_lcost += chargeE90_tot;
                                final_cost = tot_lcost + total_lubcost;
                                max_cap90 -= servchargcustomer[count].f_needed;  // Deduct the amount from the remaining capacity
                            }
                        } else {
                            tot_lcost += chargeE90_tot;
                            final_cost = tot_lcost + total_lubcost;
                            max_cap90 -= servchargcustomer[count].f_needed;  // Deduct the amount from the remaining capacity
                        }
                    } else {
                        printf("Error: Request exceeds fuel capacity for E10-90. Transaction not processed.\n");
                    }
                    break;
                case 3: // Diesel
                    price_pl = 182.30;
                    charge_d_tot = price_pl * servchargcustomer[count].f_needed;
                    if (servchargcustomer[count].f_needed <= max_capDiesel) {
                        if (pay_opt == 1) {
                            printf("Please enter cash tendered: ");
                            scanf("%f", &cash_tendered);
                            if (cash_tendered > max_cash_deposit) {
                                printf("Error: Cash tendered exceeds maximum allowed deposit of $%.2f. Transaction not processed.\n", max_cash_deposit);
                            } else {
                                tot_lcost += charge_d_tot;
                                final_cost = tot_lcost + total_lubcost;
                                max_capDiesel -= servchargcustomer[count].f_needed;  // Deduct the amount from the remaining capacity
                            }
                        } else {
                            tot_lcost += charge_d_tot;
                            final_cost = tot_lcost + total_lubcost;
                            max_capDiesel -= servchargcustomer[count].f_needed;  // Deduct the amount from the remaining capacity
                        }
                    } else {
                        printf("Error: Request exceeds fuel capacity for Diesel. Transaction not processed.\n");
                    }
                    break;
                default:
                    printf("Invalid fuel type selected.\n");
                    break;
            }
            gen_receipt(cust_type, final_cost, cash_tendered, total_lubcost);       
        }
    }
}

int main() {
    cus_mers customers[SIZE]; // Declare an array to hold customer information
    int num_customers;

    printf("Enter the number of customers: ");
    scanf("%d", &num_customers);

    // Input customer data
    for (int i = 0; i < num_customers; i++) {
        printf("Customer %d:\n", i + 1);
        // Input customer details like ID, license plate number, etc.
        // (You may need to prompt for additional information depending on your requirements)
    }

    // Process each customer
    for (int i = 0; i < num_customers; i++) {
        printf("\nProcessing customer %d:\n", i + 1);
        serv_cust(customers, SIZE); // Call the serv_cust function with the array of customers
    }

    return 0;
}