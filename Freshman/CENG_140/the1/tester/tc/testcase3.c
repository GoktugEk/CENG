#include <stdio.h>
#include "../the1.h"

int binary_tree[MAX_LENGTH];

int main() {
	int depth;
	initialize_the_tree(binary_tree,1);
	
    printf("Initial values\n");
	print_binary_tree_values(binary_tree);

	insert_node(binary_tree, 0, 'i', 35);
	
	depth = find_height_of_tree_rec(binary_tree,0);

	draw_binary_tree_rec(binary_tree, 0, depth);
	delete_node_rec(binary_tree,2);
	draw_binary_tree_rec(binary_tree, 0, depth);
	
	insert_node(binary_tree,0,'r',5);
	draw_binary_tree_rec(binary_tree, 2, depth);
	
	printf("Breadth first search results:\n");
    printf("%d is at %d in tree with root[%d].\n", 3, breadth_first_search_itr(binary_tree, 0,3), 0);
    printf("%d is at %d in tree with root[%d].\n", 9, breadth_first_search_itr(binary_tree, 0,9), 0);
	printf("%d is at %d in tree with root[%d].\n", 3, breadth_first_search_itr(binary_tree, 1,3), 1);
	printf("%d is at %d in tree with root[%d].\n", 2, breadth_first_search_itr(binary_tree, 0,2), 0);
	printf("%d is at %d in tree with root[%d].\n", 4, breadth_first_search_itr(binary_tree, 0,4), 0);
	printf("%d is at %d in tree with root[%d].\n", 5, breadth_first_search_itr(binary_tree, 0,5), 1);
	
	
	
	printf("Depth first search results:\n");
    printf("%d is at %d in tree with root[%d].\n", 3, depth_first_search_rec(binary_tree, 0,3), 0);
    printf("%d is at %d in tree with root[%d].\n", 9, depth_first_search_rec(binary_tree, 0,9), 0);
	printf("%d is at %d in tree with root[%d].\n", 3, depth_first_search_rec(binary_tree, 1,3), 1);
	printf("%d is at %d in tree with root[%d].\n", 2, depth_first_search_rec(binary_tree, 0,2), 0);
	printf("%d is at %d in tree with root[%d].\n", 4, depth_first_search_rec(binary_tree, 0,4), 0);
	printf("%d is at %d in tree with root[%d].\n", 5, depth_first_search_rec(binary_tree, 0,5), 1);
	
	printf("Find the height of the tree results:\n");
	printf("The height of the tree is %d\n",find_height_of_tree_rec(binary_tree,0));
	printf("The height of the tree is %d\n",find_height_of_tree_rec(binary_tree,1));
	

	return 0;
}
