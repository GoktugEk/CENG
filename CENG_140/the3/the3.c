#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the3.h"

int get_table_length(Node *list);

Node* copy_list(Node* list){
    Node* newlist = NULL,*backup;
    Philosopher* phil;
    backup = list;

    while(backup){
        phil = (Philosopher*)backup->node;
        add_philosopher(&newlist, phil->name, phil->favorite_meal, phil->age);
        backup = backup->next;
    }
    return newlist;
}

    /*GETS LIST, RETURNS THE NODE IN GIVEN INDEX*/
Node* indexing(Node* list, int index){
    int i;
    Node* res;
    res = list;
    for(i=0;i<index;i++){
        res = res->next;
    }
    return res;
}

int compare(Node* list,int in1,int in2){ /*COMPARES THE PHILOSOPHER'S AGES WITH GIVEN INDEXES*/
    Philosopher* phil1,*phil2;
    Node* node1,*node2;
    void* void1, *void2;
    
    node1 = indexing(list,in1);
    node2 = indexing(list,in2);
    
    void1 = node1->node;
    void2 = node2->node;
    
    phil1 = (Philosopher *)void1;
    phil2 = (Philosopher *)void2;
    
    return phil1->age > phil2->age;
}

void swap(Node* swap1, Node* swap2){/*SWAPS GIVEN PHILOSOPHERS*/
    Philosopher* phil1,*phil2,*temp;
    temp = malloc(sizeof(struct Philosopher));
    
    phil1 = (Philosopher *)swap1->node;
    phil2 = (Philosopher *)swap2->node;
    
    temp->name = phil1->name;
    temp->favorite_meal =phil1->favorite_meal;
    temp->age = phil1->age ; 
    temp->sitting = phil1->sitting;
    
    phil1->name = phil2->name;
    phil1->favorite_meal = phil2->favorite_meal;
    phil1->age = phil2->age;
    phil1->sitting = phil2->sitting;
    
    phil2->name = temp->name;
    phil2->favorite_meal = temp->favorite_meal;
    phil2->age = temp->age;
    phil2->sitting = temp->sitting;
    
    
    
}

/*
INPUT:
    Node **meals_head: reference of the meal's linked list
    char *name: name of the meal
    int count: number of the meals

METHOD:
    Creates a meal and a node containing that meal. Append it to meal's linked list end.
*/
void add_meal(Node **meals_head, char *name, int count){
    
    Node* result;/*Creating a backup pointer*/
    Meal* new_meal  = malloc(sizeof(struct Meal));/*Allocating memory for new meal*/
    Node* new_node = (Node *)malloc(sizeof(struct Node));/*Allocating memory for new node*/
    new_node->node = (Meal *)malloc(sizeof(struct Meal));/*Allocating new node's "node" member so that we can put our new meal to new node*/

    result = *meals_head;/*Assigning our real lists pointer to backup pointer*/
    


    new_meal->name = name; /*Getting values an assigning them to the new meal*/
    new_meal->count = count;   

    new_node->node = new_meal;/*Adding new meal to the new node*/
    new_node->next = NULL;
    
 
    if(*meals_head == NULL){
        *meals_head = new_node;
        return;
    }
    while((*meals_head)->next != NULL){/*Setting our list's pointer until NULL*/
        *meals_head = (*meals_head)->next;
    }

    (*meals_head)->next = new_node;/*Changing NULL with our new node*/
    
    *meals_head = result;/*Getting list's first element by using backup pointer*/
    

}

/*
INPUT:
    Node **philosophers_head: reference of the philosopher's linked list
    char *name: name of the philosopher
    char *favorite_meal: favorite meal
    int age: age of the philosopher

METHOD:
    Creates a philosopher and a node containing that philosopher. 
    Append it to philosopher's linked list end.
*/
void add_philosopher(Node **philosophers_head, char *name, char *favorite_meal, int age){
    Node* result;
    Philosopher* new_philosopher  = malloc(sizeof(struct Philosopher));
    Node* new_node = (Node *)malloc(sizeof(struct Node));
    new_node->node = (Philosopher *)malloc(sizeof(struct Philosopher));

    
    
    result = *philosophers_head;

    new_philosopher->name = name;
    new_philosopher->favorite_meal = favorite_meal;
    new_philosopher->age = age; 
    new_philosopher->sitting = 0;
    

    new_node->node = new_philosopher;
    new_node->next = NULL;
    
 
    if(*philosophers_head == NULL){
        *philosophers_head = new_node;
        return;
    }
    while((*philosophers_head)->next != NULL){
        *philosophers_head = (*philosophers_head)->next;
    }

    (*philosophers_head)->next = new_node;
    
    *philosophers_head = result;
    

}

/*
INPUT:
    Node **table_head: reference of the circular linked list (table)
    Node *philosophers: philosopher's linked list

METHOD:
    Places philosophers into a circular linked list in ascending order of ages.
*/
void place_philosophers(Node **table_head, Node *philosophers){
    int length,changed = 1,i;
    Node* first,*last,*node1;   
    Node *backup;
    Philosopher *phil;
    backup = copy_list(philosophers);
    

    
    
    length = get_length(backup);
    
    first = backup;
    last = indexing(backup,length-1);


    while(changed){/*BUBBLE SORT*/
        changed = 0;

        for(i=0;i<length-1;i++){
            node1 = indexing(backup,i);
            phil = (Philosopher *) (node1->node);
            phil->sitting =1;
            if(compare(backup,i,i+1)){
                swap(indexing(backup,i),indexing(backup,i+1));
                changed =1;
            }
            
        }
    }
    

    
    last->next = first;
    (*table_head) = backup;
}

/*
INPUT:
    Node **table_head: reference of the circular linked list (table)
    int index: index of the philosopher to be removed
    int size_of_table: number of philosophers in the table

METHOD:
    Removes a philosopher from table.
*/
void remove_philosopher(Node **table_head, int index, int size_of_table){
    Node* prev,*current,*last;
    int length;

    length = size_of_table;
    last = indexing(*table_head,length-1);
    current = indexing(*table_head,index);

    
    if(index == 0){
        last->next = current->next;
        *table_head = current->next;
    }
    else{
        prev = indexing(*table_head,index-1);
        prev->next = current->next;
    }

    size_of_table--;
    
}

/*
INPUT:
    Node *table: Circular linked list
    Node *meals: Meal's linked list

METHOD:
    Serves favorite meals and reduce their counts. Use strcmp function from string.h
*/
void serve_meals(Node *table, Node *meals){
    int length_p,length_m,i,j;
    Node* table_h,*meals_h;
    Philosopher *phil;
    Meal* meal_node;
    char* meal_name,*phils_meal;
    
    table_h = table;
    meals_h = meals;
    
    length_p = get_table_length(table);
    length_m = get_length(meals_h);
    

    
    for(i=0;i<length_m;i++){
        meal_node = (Meal *)meals_h->node;
        meal_name = meal_node->name;
        for(j=0;j<length_p;j++){
            phil = (Philosopher *)table_h->node;
            phils_meal = phil->favorite_meal;
            if(!strcmp(phils_meal,meal_name)){
                meal_node->count--;
            }
            table_h = table_h->next;
        }
        meals_h = meals_h->next;
    }
}

/*
INPUT:
    Node *list: A linked list
    void (*helper_print)(void *): Reference of a helper print function

METHOD:
    Prints items in the linked list using helper print function
*/
void print_list(Node *list, void (*helper_print)(void *)){
    Node *backup;
    backup = list;
    while(list != NULL){
        (*helper_print)(list->node);
        list = list->next;
    }
    list = backup;
}

/*
INPUT:
    void *meal: void meal pointer

METHOD:
    Cast void pointer to a meal pointer and prints it's content
*/
void print_meal_node(void *meal){
    Meal* the_meal;
    the_meal = (Meal *)meal;
    printf("Name: %s, count: %d\n",the_meal->name,the_meal->count);
}

/*
INPUT:
    void *philosopher: void philosopher pointer

METHOD:
    Cast void pointer to a philosopher pointer and prints it's content
*/
void print_philosopher_node(void *philosopher){
    Philosopher* phil;
    phil = (Philosopher *)philosopher;
    printf("Name: %s, favorite meal: %s, age: %d\n",phil->name,phil->favorite_meal,phil->age);
}

/*
INPUT:
    Node *table: Circular linked list

METHOD:
    Prints the formation as <prev> <current> <next>
*/
void print_table(Node *table){
    Node *backup,*prev;
    Philosopher *phil1,*phil2,*phil3;
    int length,i;
    
    backup = table;
    
    length = get_table_length(backup);

    prev = indexing(backup,length-1);

    for(i=0;i<length;i++){
        phil1 = (Philosopher *)prev->node;
        phil2 = (Philosopher *)backup->node;
        phil3 = (Philosopher *)((backup->next)->node);
        printf("%s -> %s -> %s\n",phil1->name,phil2->name,phil3->name);
        prev = backup;
        backup = backup->next;
    }
}

/*
INPUT:
    Node *list: A linked list

OUTPUT:
    Size of the linked list in an integer format

METHOD:
    Calculates the size of the linked list and returns it.
*/
int get_length(Node *list){
    int length =0;
    Node *backup;
    backup = list;
    if(list == NULL){
        return length;
    }

    while(list){
        length++;
        list = list->next;
    }
    list = backup;
    return length;
}

int get_table_length(Node *list){
    int length = 1 ;
    Node* backup;
    
    backup = list;
    list = list->next;
    while(list != backup){
        length++;
        list = list->next;
    }
    list = backup;
    return length;
}

/*
INPUT:
    Node *philosophers: Philosopher's linked list

OUTPUT:
    Philosopher pointer at given index.

METHOD:
    Finds the philosopher at given index and returns it's reference.
*/
Philosopher *get_philosopher(Node *philosophers, int index){ 
    Philosopher* phil;
    Node* the_node;
    the_node = indexing(philosophers,index);
    phil = (Philosopher *)the_node->node;
    
    return phil; 
}
