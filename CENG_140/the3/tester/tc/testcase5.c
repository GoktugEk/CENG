#include <stdio.h>
#include <stdlib.h>
#include "../the3.h"


int main() {
    Node *meals = NULL;
    Node *philosophers = NULL;
    Node *table = NULL;

    add_meal(&meals, "Patates Kızartması", 98);
    add_meal(&meals, "Pilav", 9);
    add_meal(&meals, "Salata", 99);
    add_meal(&meals, "Köfte", 9);

    add_philosopher(&philosophers, "phil1", "Patates Kızartması", 1424);
    add_philosopher(&philosophers, "phil2", "Pilav", 1145);
    add_philosopher(&philosophers, "phil3", "Köfte", 1976);
    add_philosopher(&philosophers, "phil4", "Patates Kızartması", 1555);
    add_philosopher(&philosophers, "phil5", "Pilav", 10);
    add_philosopher(&philosophers, "phil6", "Pilav", 8);
    add_philosopher(&philosophers, "phil7", "Salata", 9998);
    add_philosopher(&philosophers, "phil8", "Pilav", 456);
    add_philosopher(&philosophers, "phil9", "Pilav", 450);
    add_philosopher(&philosophers, "phil10", "Pilav", 8753);
    add_philosopher(&philosophers, "phil11", "Salata", 5333);


    print_list(meals, &print_meal_node);

    print_list(philosophers, &print_philosopher_node);


    place_philosophers(&table, philosophers);

    print_table(table);


    serve_meals(table, meals);

    print_list(meals, &print_meal_node);


    remove_philosopher(&table, 2, 11);
    remove_philosopher(&table, 5, 10);
    remove_philosopher(&table, 0, 9);
    remove_philosopher(&table, 0, 8);
    remove_philosopher(&table, 6, 7);

    print_table(table);


    return 0;
}
