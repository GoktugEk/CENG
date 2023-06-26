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
	delete_node_rec(binary_tree,499);
	draw_binary_tree_rec(binary_tree, 0, depth);
	
	insert_node(binary_tree,0,'r',5);
	draw_binary_tree_rec(binary_tree, 50, depth);
	
	printf("Breadth first search results:\n");
    printf("%d is at %d in tree with root[%d].\n", 140, breadth_first_search_itr(binary_tree, 0,140), 0);
    printf("%d is at %d in tree with root[%d].\n", 1, breadth_first_search_itr(binary_tree, 0,1), 0);
	printf("%d is at %d in tree with root[%d].\n", 53, breadth_first_search_itr(binary_tree, 1,53), 0);
	printf("%d is at %d in tree with root[%d].\n", 111, breadth_first_search_itr(binary_tree, 0,111), 0);
	printf("%d is at %d in tree with root[%d].\n", 4, breadth_first_search_itr(binary_tree, 2,4), 2);
	printf("%d is at %d in tree with root[%d].\n", 5, breadth_first_search_itr(binary_tree, 1,5), 1);
	
	
	
	printf("Depth first search results:\n");
    printf("%d is at %d in tree with root[%d].\n", 140, depth_first_search_rec(binary_tree, 0,140), 0);
    printf("%d is at %d in tree with root[%d].\n", 1, depth_first_search_rec(binary_tree, 0,1), 0);
	printf("%d is at %d in tree with root[%d].\n", 53, depth_first_search_rec(binary_tree, 0,53), 0);
	printf("%d is at %d in tree with root[%d].\n", 111, depth_first_search_rec(binary_tree, 0,111), 0);
	printf("%d is at %d in tree with root[%d].\n", 4, depth_first_search_rec(binary_tree, 2,4),2);
	printf("%d is at %d in tree with root[%d].\n", 5, depth_first_search_rec(binary_tree, 1,5), 1);
	
	printf("Find the height of the tree results:\n");
	printf("The height of the tree is %d\n",find_height_of_tree_rec(binary_tree,0));
	printf("The height of the tree is %d\n",find_height_of_tree_rec(binary_tree,200));
	printf("The height of the tree is %d\n",find_height_of_tree_rec(binary_tree,50));
	printf("The height of the tree is %d\n",find_height_of_tree_rec(binary_tree,30));
	printf("The height of the tree is %d\n",find_height_of_tree_rec(binary_tree,2));
	printf("The height of the tree is %d\n",find_height_of_tree_rec(binary_tree,1));

	printf("The minimum of the tree is %d for the root %d\n",find_min_of_tree_rec(binary_tree,0),0);
	printf("The minimum of the tree is %d for the root %d\n",find_min_of_tree_rec(binary_tree,1),1);
	printf("The minimum of the tree is %d for the root %d\n",find_min_of_tree_rec(binary_tree,2),2);
	

	return 0;
}
