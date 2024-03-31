#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void serv_cust(){
    int cust_type;
    char f_type[];
    float f_needed;
    char lubricant_request;


    printf("Select customer type(1. Cash on Delivery and 2. Charge)");
    scanf("%d", &cust_type);

    if(cust_type == 1){
        printf("Please enter the type of fuel being purchased.");
        scanf("%s", f_type);

        printf("Please enter the amount of fuel needed (In litres).")
        scanf("%d", &f_needed)

        srand(time(0)); // Seed for random number generation
        lubricant_request = (rand() % 2) ? 'Y' : 'N'; // Randomly choose 'Y' or 'N'
        
        printf("Lubricant Request: %c\n", lubricant_request);

        if (lubricant_request == 'Y') {
            printf("Enter lubricant quantity: ")
            scanf("%d", lub_qty)
        }

    }else if (cust_type == 2){

    }
}


int main(){

}