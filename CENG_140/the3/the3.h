#ifndef THE3_H
#define THE3_H

#define MAX_VAL 9999

typedef struct Node
{
    void *node;
    struct Node *next;
} Node;

typedef struct Meal
{
    char *name;
    int count;
} Meal;

typedef struct Philosopher
{
    char *name;
    char *favorite_meal;
    int age;
    int sitting;
} Philosopher;

void add_meal(Node **meals_head, char *name, int count);
void add_philosopher(Node **philosophers_head, char *name, char *favorite_meal, int age);
void place_philosophers(Node **table_head, Node *philosophers);
void remove_philosopher(Node **table_head, int index, int size_of_table);
void serve_meals(Node *table, Node *meals);

void print_list(Node *list, void (*helper_print)(void *));
void print_meal_node(void *meal);
void print_philosopher_node(void *philosopher);
void print_table(Node *table);

int get_length(Node *list);
Philosopher *get_philosopher(Node *philosophers, int index);

#endif
