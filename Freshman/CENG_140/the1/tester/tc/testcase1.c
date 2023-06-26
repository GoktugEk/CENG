#include <stdio.h>
#include "../the1.h"

int binary_tree[MAX_LENGTH];

int main() {
	int get_values_from_user;
	scanf("%d", &get_values_from_user);
	initialize_the_tree(binary_tree, get_values_from_user);
	
	
    printf("Initial values\n");
	print_binary_tree_values(binary_tree);
	
	insert_node(binary_tree, 1, 'i', 35); /* It will be ignored */
	
	draw_binary_tree_rec(binary_tree, 0, 5);
	insert_node(binary_tree, 12, 'l', 4);
	
	draw_binary_tree_rec(binary_tree, 0, 6);
    
    printf("After custom insertions\n");
	print_binary_tree_values(binary_tree);	
	
    delete_node_rec(binary_tree, 1);
	
    printf("Values after node 1 is deleted\n");
	print_binary_tree_values(binary_tree);
	
	draw_binary_tree_rec(binary_tree, 0, 6);
	
	
	printf("Breadth first search results:\n");
    printf("%d is at %d in tree with root[%d].\n", 8, breadth_first_search_itr(binary_tree, 0,8), 0);
    printf("%d is at %d in tree with root[%d].\n", 8, breadth_first_search_itr(binary_tree, 1,8), 1);
    printf("%d is at %d in tree with root[%d].\n", 7, breadth_first_search_itr(binary_tree, 0,7), 0);
    printf("%d is at %d in tree with root[%d].\n", 1, breadth_first_search_itr(binary_tree, 6,1), 1);
    printf("%d is at %d in tree with root[%d].\n", 7, breadth_first_search_itr(binary_tree, 10,7), 10);
    printf("%d is at %d in tree with root[%d].\n", 4, breadth_first_search_itr(binary_tree, 0,4), 0);
	
	printf("Depth first search results:\n");
    printf("%d is at %d in tree with root[%d].\n", 8, depth_first_search_rec(binary_tree, 0,8), 0);
    printf("%d is at %d in tree with root[%d].\n", 8, depth_first_search_rec(binary_tree, 1,8), 1);
    printf("%d is at %d in tree with root[%d].\n", 7, depth_first_search_rec(binary_tree, 0,7), 0);
    printf("%d is at %d in tree with root[%d].\n", 1, depth_first_search_rec(binary_tree, 6,1), 1);
    printf("%d is at %d in tree with root[%d].\n", 7, depth_first_search_rec(binary_tree, 10,7), 10);
    printf("%d is at %d in tree with root[%d].\n", 4, depth_first_search_rec(binary_tree, 0,4), 0);
    	
	return 0;
}
