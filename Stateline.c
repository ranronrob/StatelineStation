#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

void serv_cust(){
    int cust_type;
    char f_type[];
    float f_needed;
    char lubricant_request;
    int lub_qty;
    int pay_opt;

    printf("Select customer type(1. Cash on Delivery and 2. Charge)");
    scanf("%d", &cust_type);

    if(cust_type == 1){
        printf("Please enter the type of fuel being purchased.");
        scanf("%s", f_type);

        printf("Please enter the amount of fuel needed (In litres).");
        scanf("%d", &f_needed);

        srand(time(0)); // Seed for random number generation
        lubricant_request = (rand() % 2) ? 'Y' : 'N'; // Randomly choose 'Y' or 'N'
        
        printf("Lubricant Request: %c\n", lubricant_request);

        float final_cost = 0;

        if (lubricant_request == 'Y') {
            printf("Enter lubricant quantity: ");
            scanf("%d", &lub_qty);
        }

        bool x = true;

        while (x)
        {
            printf("Payment option(1 for cash or 2 for card: )");
            scanf("%d", &pay_opt);

            if(f_needed < 2 && pay_opt == 1){
                printf("The minimum purchase is two litres for cash payments. ")
                continue;
            }else if(final_cost<1000 && pay_opt == 2){
                printf("The minimum amount is $1000 for card transactions. ")
            }
        }
        

}


int main(){

}