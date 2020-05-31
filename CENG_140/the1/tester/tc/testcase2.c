#include <stdio.h>
#include "../the1.h"

int binary_tree[MAX_LENGTH];

int main() {
	initialize_the_tree(binary_tree,1);
	
    printf("Initial values\n");
	print_binary_tree_values(binary_tree);

	insert_node(binary_tree, 0, 'i', 35);

	draw_binary_tree_rec(binary_tree, 0, 0);
	delete_node_rec(binary_tree,0);
	draw_binary_tree_rec(binary_tree, 0, 0);
	
	insert_node(binary_tree,0,'i',10);
	draw_binary_tree_rec(binary_tree, 0, 0);
	
	printf("Breadth first search results:\n");
    printf("%d is at %d in tree with root[%d].\n", 10, breadth_first_search_itr(binary_tree, 0,10), 0);
    printf("%d is at %d in tree with root[%d].\n", 9, breadth_first_search_itr(binary_tree, 0,9), 0);
	printf("%d is at %d in tree with root[%d].\n", 10, breadth_first_search_itr(binary_tree, 1,10), 1);
	
	
	
	printf("Depth first search results:\n");
	printf("%d is at %d in tree with root[%d].\n", 10, depth_first_search_rec(binary_tree, 0,10), 0);
    printf("%d is at %d in tree with root[%d].\n", 9, depth_first_search_rec(binary_tree, 0,9), 0);
	printf("%d is at %d in tree with root[%d].\n", 10, depth_first_search_rec(binary_tree, 1,10), 1);
	
	printf("Find the height of the tree results:\n");
	printf("The min of the tree is %d\n",find_min_of_tree_rec(binary_tree,0));
	

	return 0;
}
