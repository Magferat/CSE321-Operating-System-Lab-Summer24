#include <stdio.h>

struct orders{
    int quantity;
    float unit_price;
};


int main() {
    struct orders paratha;
    struct orders vegetable;
    struct orders water;
    int num_people;
    float total_bill, per_person;


    printf("Enter quantity and unit price for Paratha:\n");
    scanf("%d %f", &paratha.quantity, &paratha.unit_price);


    printf("Enter quantity and unit price for Vegetable:\n");
    scanf("%d %f", &vegetable.quantity, &vegetable.unit_price);


    printf("Enter quantity and unit price for Mineral Water:\n");
    scanf("%d %f", &water.quantity, &water.unit_price);


    total_bill = (paratha.quantity * paratha.unit_price) +
                  (vegetable.quantity * vegetable.unit_price) +
                  (water.quantity * water.unit_price);


    printf("Enter the number of people:\n");
    scanf("%d", &num_people);


    
    per_person = total_bill / num_people;

    printf("Individual people will pay: %.2f tk\n", per_person);
 

    return 0;
}

