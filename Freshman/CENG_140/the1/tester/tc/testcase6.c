#include <stdio.h>
#include "../the1.h"

int binary_tree[MAX_LENGTH];

int main() {
	int depth;
	initialize_the_tree(binary_tree,1);
	
        printf("Initial values\n");
	print_binary_tree_values(binary_tree);

	
	depth = find_height_of_tree_rec(binary_tree,0);

	draw_binary_tree_rec(binary_tree, 0, depth);
	
	printf("Breadth first search results:\n");
        printf("%d is at %d in tree with root[%d].\n", 1, breadth_first_search_itr(binary_tree, 0,1), 0);
        printf("%d is at %d in tree with root[%d].\n", 1, breadth_first_search_itr(binary_tree, 1,1), 1);
	printf("%d is at %d in tree with root[%d].\n", 1, breadth_first_search_itr(binary_tree, 2,1), 2);
	printf("%d is at %d in tree with root[%d].\n", 10, breadth_first_search_itr(binary_tree, 0,10), 0);
	printf("%d is at %d in tree with root[%d].\n", 10, breadth_first_search_itr(binary_tree, 2,10), 2);
	printf("%d is at %d in tree with root[%d].\n", 10, breadth_first_search_itr(binary_tree, 1,10), 1);


	printf("Depth first search results:\n");
        printf("%d is at %d in tree with root[%d].\n", 1, depth_first_search_rec(binary_tree, 0,1), 0);
	printf("%d is at %d in tree with root[%d].\n", 1, depth_first_search_rec(binary_tree, 1,1), 1);
	printf("%d is at %d in tree with root[%d].\n", 1, depth_first_search_rec(binary_tree, 2,1), 2);
	printf("%d is at %d in tree with root[%d].\n", 10, depth_first_search_rec(binary_tree, 0,10), 0);
	printf("%d is at %d in tree with root[%d].\n", 10, depth_first_search_rec(binary_tree, 2,10), 2);
	printf("%d is at %d in tree with root[%d].\n", 10, depth_first_search_rec(binary_tree, 1,10), 1);	
	
	
	
	printf("Find the height of the tree results:\n");
	printf("The height of the tree is %d for root %d\n",find_height_of_tree_rec(binary_tree,0),0);
	printf("The height of the tree is %d for root %d\n",find_height_of_tree_rec(binary_tree,2),2);
	printf("The height of the tree is %d for root %d\n",find_height_of_tree_rec(binary_tree,1),1);
	

	return 0;
}
