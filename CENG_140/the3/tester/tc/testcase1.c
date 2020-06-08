#include <stdio.h>
#include <stdlib.h>
#include "../the3.h"
int main(){
    Node *meals = NULL;
    Node *philosophers = NULL;
    Node *table = NULL;
    add_meal(&meals, "Banana Leaf Rice", 58);
    add_meal(&meals, "Corn Bread", 44);
    add_meal(&meals, "Borscht", 44);
    add_meal(&meals, "Sunday Roast", 44);
    add_meal(&meals, "Poutine",44);
    add_meal(&meals, "Kumpir", 44);
    add_meal(&meals, "Kung Pao", 44);
    add_meal(&meals, "Tofu", 44);
    add_meal(&meals, "Wonton", 44);
    add_meal(&meals, "Fried Rice", 44);
    add_philosopher(&philosophers, "Lao Tzu", "Banana Leaf Rice", 1424);
    add_philosopher(&philosophers, "Confucius", "Banana Leaf Rice", 1145);
    add_philosopher(&philosophers, "Mozi", "Banana Leaf Rice", 1976);
    add_philosopher(&philosophers, "Shang Yang", "Banana Leaf Rice", 1555);
    add_philosopher(&philosophers, "Darwin", "Banana Leaf Rice", 211);
    add_philosopher(&philosophers, "De Moragan", "Banana Leaf Rice", 214);
    add_philosopher(&philosophers, "Descates", "Banana Leaf Rice", 424);
    add_philosopher(&philosophers, "Erasmus", "Banana Leaf Rice", 554);
    add_philosopher(&philosophers, "Faraday", "Banana Leaf Rice", 229);
    add_philosopher(&philosophers, "Gaius", "Banana Leaf Rice", 1910);
    add_philosopher(&philosophers, "Gorgias", "Banana Leaf Rice", 2503);
    add_philosopher(&philosophers, "Hess", "Banana Leaf Rice", 208);
    add_philosopher(&philosophers, "Huxley", "Banana Leaf Rice", 195);
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
    
	remove_philosopher(&table, 13, 14);
    printf("----------------------------\n\n");
    print_table(table);    

    return 0;
}
