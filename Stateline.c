#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <time.h> 
#include <stdbool.h> 


typedef struct charge_customer
{
    int idnum;
    char lic_plnum[5];
    char fuel_type[9];
    float fuel_amount;
    float deposit_am;
}chg_cus;

void fuel_menu(){
    printf("Fuel  Type          Price Per litre($)"); // Display fuel types and prices
    printf("1. E10-87                 184.90\n");
    printf("2. E10-90                 193.60\n");
    printf("3. Diesel                 182.30\n");
}

void lubricant_menu(){
    printf("Lubricant Type             Price($)\n"); // Display lubricant types and prices
    printf("1. 5w-30                    2900.00\n ");
    printf("2. 5w-40                    3500.00\n ");
    printf("3. 15w-40                   3600.00\n ");
    printf("4. SAE-40                   2100.OO\n ");
}

void gen_receipt(char* cust_type, float final_cost, float cash_tendered, int total_lubcost){
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

void serv_cust(){ // Function definition to serve the customer
    char cust_type[10]; // Variable to store customer type
    int f_type; // Variable to store fuel type
    float f_needed; // Variable to store fuel needed
    char lubricant_request; // Variable to store lubricant request
    int lub_qty; // Variable to store lubricant quantity
    int pay_opt; // Variable to store payment option
    float price_pl; // Variable to store price per litre of fuel
    float tot_lcost; // Variable to store total fuel cost
    float final_cost; // Variable to store final cost
    int lub_type; // Variable to store lubricant type
    int total_lubcost; // Variable to store total lubricant cost
    float cash_tendered;

    printf("Select customer type(COD or Charge)"); // Prompt user to select customer type
    scanf("%s", cust_type); // Read customer type from user input



    if(strcmp(cust_type, "COD") == 0){ // If customer type is Cash on Delivery (COD)

        fuel_menu();
        printf("Enter the number that represent the fuel type purchasing"); // Prompt user to enter fuel type
        scanf("%d", &f_type); // Read fuel type from user input


        printf("Please enter the amount of fuel needed (In litres)."); // Prompt user to enter fuel amount
        scanf("%f", &f_needed); // Read fuel amount from user input


        srand(time(0)); // Seed for random number generation
        lubricant_request = (rand() % 2) ? 'Y' : 'N'; // Randomly choose 'Y' or 'N' for lubricant request
        
        printf("Lubricant Request: %c\n", lubricant_request); // Display lubricant request

        if (lubricant_request == 'Y') { // If lubricant is requested

            lubricant_menu();
            printf("Enter the number that represent the lubricant type purchasing."); // Prompt user to enter lubricant type
            scanf("%d", &lub_type); // Read lubricant type from user input
        
            printf("Enter lubricant quantity: "); // Prompt user to enter lubricant quantity
            scanf("%d", &lub_qty); // Read lubricant quantity from user input

            switch (lub_type) { // Calculate total lubricant cost based on lubricant type and quantity
                case 1:
                    total_lubcost = 2900.00 * lub_qty;
                    break;
                case 2:
                    total_lubcost = 3500.00 * lub_qty;
                    break;
                case 3:
                    total_lubcost = 3600.00 * lub_qty;
                    break;
                case 4:
                    total_lubcost = 2100.00 * lub_qty;
                    break;
                default:
                    break;
            }
        }

        switch (f_type) // Calculate total fuel cost based on fuel type and amount
        {
            case 1:
                price_pl = 184.90;
                tot_lcost = price_pl * f_needed;
                final_cost = tot_lcost + total_lubcost;
                break;
            case 2:
                price_pl = 193.60;
                tot_lcost = price_pl * f_needed;
                final_cost = tot_lcost + total_lubcost;
                break;
            case 3:
                price_pl = 182.30;
                tot_lcost = price_pl * f_needed;
                final_cost = tot_lcost + total_lubcost;
                break;
            default:
                break;
        }

        while (true) // Loop until valid payment option is selected
        {
            printf("Payment option(1 for cash or 2 for card: )"); // Prompt user to select payment option
            scanf("%d", &pay_opt); // Read payment option from user input
         

            if(f_needed < 2 && pay_opt == 1){ // Check if minimum purchase condition for cash payment is met
                printf("The minimum purchase is two litres for cash payments. "); // Display error message
                continue; // Continue to next iteration of the loop
            }else if(final_cost<1000 && pay_opt == 2){ // Check if minimum amount condition for card payment is met
                printf("The minimum amount is $1000 for card transactions. "); // Display error message
                continue; // Continue to next iteration of the loop
            }else{
                break; // Exit the loop if payment option is valid
                }
            }

            if (pay_opt == 1)
            {
                printf("Please enter cash tendered: ");
                scanf("%f", &cash_tendered);
            }
                
                gen_receipt(cust_type, final_cost, cash_tendered, total_lubcost);
        

    }else if(strcmp(cust_type, "charge")==0){ // If customer type is Charge

    }

}





int main(){

}