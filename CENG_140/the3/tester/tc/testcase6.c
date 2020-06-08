#include <stdio.h>
#include <stdlib.h>
#include "../the3.h"


int main() {
    Node *meals = NULL;
    Node *philosophers = NULL;
    Node *table = NULL;

    add_meal(&meals, "Patates Kızartması", 1);
    add_meal(&meals, "Pilav", 1);
    add_meal(&meals, "Salata", 1);
    

    add_philosopher(&philosophers, "phil1", "Patates Kızartması", 9998);
    add_philosopher(&philosophers, "phil2", "Pilav", 2);
    add_philosopher(&philosophers, "phil3", "Salata", 3125);
    


    print_list(meals, &print_meal_node);

    print_list(philosophers, &print_philosopher_node);


    place_philosophers(&table, philosophers);

    print_table(table);


    serve_meals(table, meals);

    print_list(meals, &print_meal_node);

    return 0;
}
