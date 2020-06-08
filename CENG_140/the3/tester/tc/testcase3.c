#include <stdio.h>
#include <stdlib.h>
#include "../the3.h"
int main(){
	Node *meals = NULL;
    Node *philosophers = NULL;
    Node *table = NULL;
    add_meal(&meals, "Banana Leaf Rice", 9);
    add_meal(&meals, "Corn Bread", 0);
    add_meal(&meals, "Borscht", 7);
    add_meal(&meals, "Sunday Roast", 1);
    add_meal(&meals, "Poutine", 2);
    add_meal(&meals, "Kumpir", 5);
    add_meal(&meals, "Kung Pao", 3);
    add_meal(&meals, "Tofu", 1);
    add_meal(&meals, "Wonton", 2);
    add_meal(&meals, "Fried Rice", 3);
    add_philosopher(&philosophers, "Hess", "Fried Rice", 208);
    add_philosopher(&philosophers, "Huxley", "Tofu", 195);
    add_philosopher(&philosophers, "Damascius", "Banana Leaf Rice", 1558);
   
    print_list(meals, &print_meal_node);
    printf("----------------------------\n\n");
    print_list(philosophers, &print_philosopher_node);
   
    place_philosophers(&table, philosophers);
    printf("----------------------------\n\n");
    print_table(table);
    
    serve_meals(table, meals);
    printf("----------------------------\n\n");
    print_list(meals, &print_meal_node);
    
    

    return 0;
}
