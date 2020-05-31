#include <stdio.h>
#include <stdlib.h>
#include "../the3.h"
int main(){
	Node *meals = NULL;
    Node *philosophers = NULL;
    Node *table = NULL;
    add_meal(&meals, "Banana Leaf Rice", 93);
    add_meal(&meals, "Corn Bread", 5);
    add_meal(&meals, "Borscht", 2);
    add_meal(&meals, "Sunday Roast", 1);
    add_meal(&meals, "Poutine", 2);
    add_meal(&meals, "Kumpir", 1);
    add_meal(&meals, "Kung Pao", 3);
    add_meal(&meals, "Tofu", 21);
    add_meal(&meals, "Wonton", 1);
    add_meal(&meals, "Fried Rice", 12);
    add_philosopher(&philosophers, "Lao Tzu", "Wonton", 1424);
    add_philosopher(&philosophers, "Confucius", "Banana Leaf Rice", 1145);
    add_philosopher(&philosophers, "Mozi", "Fried Rice", 1976);
    add_philosopher(&philosophers, "Shang Yang", "Banana Leaf Rice", 1555);
    add_philosopher(&philosophers, "Darwin", "Sunday Roast", 211);
    add_philosopher(&philosophers, "De Moragan", "Poutine", 214);
    add_philosopher(&philosophers, "Descates", "Borscht", 424);
    add_philosopher(&philosophers, "Erasmus", "Borscht", 554);
    add_philosopher(&philosophers, "Faraday", "Poutine", 229);
    add_philosopher(&philosophers, "Gaius", "Corn Bread", 1910);
    add_philosopher(&philosophers, "Gorgias", "Kumpir", 2503);
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
    
	remove_philosopher(&table, 0, 14);
    printf("----------------------------\n\n");
    print_table(table); 
	   
	remove_philosopher(&table, 5, 13);
    printf("----------------------------\n");
    print_table(table); 
    
    remove_philosopher(&table, 10, 12);
    printf("----------------------------\n");
    print_table(table); 
    
    
    remove_philosopher(&table, 10, 11);
    printf("----------------------------\n");
    print_table(table); 
    
    
    remove_philosopher(&table, 9, 10);
    printf("----------------------------\n");
    print_table(table); 
    
    
    remove_philosopher(&table, 5, 9);
    printf("----------------------------\n");
    print_table(table); 
    
    
    remove_philosopher(&table, 2, 8);
    printf("----------------------------\n");
    print_table(table); 
    
    
    remove_philosopher(&table, 3, 7);
    printf("----------------------------\n");
    print_table(table); 
    
    
    remove_philosopher(&table, 4, 6);
    printf("----------------------------\n");
    print_table(table); 
    
    
    remove_philosopher(&table, 1, 5);
    printf("----------------------------\n");
    print_table(table); 
    
    
    remove_philosopher(&table, 2, 4);
    printf("----------------------------\n");
    print_table(table); 
    
    return 0;
}
