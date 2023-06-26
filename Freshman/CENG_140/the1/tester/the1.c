#include <stdio.h>
#include <math.h>
#include "the1.h"

/*
 * This function gets a parameter that indicateswhether user will give initial values or not. If it evaluates false,
 * you will simply set all values of thearray -1. Otherwise, you will scan an integer from the user stating the number
 * of values that s/he willenter. User will enter that many integer index and value pairs. If the value for that index
 * is insertedbefore, or the index or the value is out of the range, you will simply ignore it.
*/

void initialize_the_tree(int binary_tree[MAX_LENGTH], int get_values_from_user) {
    int value_count,index,number,i;
	if(!get_values_from_user){
    	for(i=0;i<MAX_LENGTH;i++){
    		binary_tree[i] = -1;}
		}
	else{
    	for(i=0;i<MAX_LENGTH;i++){
    		binary_tree[i] = -1;}
		scanf("%d",&value_count);
		for(i=0;i<value_count;i++){
			scanf("%d %d",&index,&number);
		    if(index<MAX_LENGTH && binary_tree[index] == -1){
		        binary_tree[index] = number;

		    }
		}
	}
}
/*
 * This function gets index of parent node, 'l'eft, 'r'ight or 'i'tself for where to insert and integer value.
 * If the value for the inserted node already exists, it ignores and does nothing.
 */
void insert_node(int binary_tree[MAX_LENGTH], int node, char where, int value) {
    if(node < MAX_LENGTH && where == 'i' && binary_tree[node] == -1){
        if(node%2 == 1 && binary_tree[(node-1)/2] != -1){
    	    binary_tree[node] = value;}
        else if(node%2 == 0 && binary_tree[(node-2)/2] != -1){
    	    binary_tree[node] = value;}
	}
	else if(2*node+1 < MAX_LENGTH && where == 'l' && binary_tree[2*node+1] == -1 && binary_tree[node] != -1){
		 binary_tree[2*node+1] = value; 
	}
	else if(2*node+2 < MAX_LENGTH && where == 'r' && binary_tree[2*node+2] == -1 && binary_tree[node] != -1){
		binary_tree[2*node+2] = value; 
	}
}


/*
 * This method  gets  the  index  of  the  node  to  be  deleted.   If  a  node  is  to  be deleted, all of its
 * descendants will be also purged.  Deleting means putting -1 value to the proper area in the array.
 */
void delete_node_rec(int binary_tree[MAX_LENGTH], int node) {
	if(node >= MAX_LENGTH || binary_tree[node] == -1){
		return;
	}
	else{
		delete_node_rec(binary_tree,2*node+1);
		delete_node_rec(binary_tree,2*node+2);
		binary_tree[node] = -1;
	}

}


/*
 * This is  a recursive function that prints the tree in in-order fashion. In other words, it will print the nodes 
 * starting from the left-most child and traverse the rest of the tree in that manner. Printing order will be 
 * <left-child, root, right-child>. It gets the index of the root and the depth value as control variable. Initial 
 * value of the depth will be the height of the tree. Be careful, any sub-tree can be given to the function.
 */
void recursive_loop(int loop_down,int loop_up){
    if(loop_up <= loop_down){
        return;
    }
    printf("\t");
    recursive_loop(loop_down+1,loop_up);
}

void draw_binary_tree_rec(int binary_tree[MAX_LENGTH], int root, int depth) {
    if(root >= MAX_LENGTH || binary_tree[root] == -1){
        return;
    }
    draw_binary_tree_rec(binary_tree,2*root+1,depth-1);
    recursive_loop(0,depth);
    printf("%d\n",binary_tree[root]);
    draw_binary_tree_rec(binary_tree,2*root+2,depth-1);
}
/*
 * This is a recursive function that returns the height of the tree.  If given root does not have any child, its height
 * is 0.  Be careful, any sub-tree can be given to the function
 */
int find_height_of_tree_rec(int binary_tree[MAX_LENGTH], int root) {
    int left,right;
    if(2*root+2 >= MAX_LENGTH ){
        return 0;
    }
	else if(binary_tree[2*root+1] == -1 && binary_tree[2*root+2] == -1){
		return 0;
	}
	else if(binary_tree[root] == -1){
	    return 0;
	}
	else{
		left = find_height_of_tree_rec(binary_tree,2*root+1);
	    right = find_height_of_tree_rec(binary_tree,2*root+2);
	}
	return MAX(left+1,right+1);
}

/*
 * This is a recursive function that returns the minimum value given tree contains.
 * Be careful, any sub-tree can be given to the function.
 */
int find_min_of_tree_rec(int binary_tree[MAX_LENGTH], int root) {
	int left,right,min,res;
    if(root >= MAX_LENGTH || binary_tree[root] == -1){
        return MAX_VAL;
    }
	else{
	left = find_min_of_tree_rec(binary_tree,2*root + 1);
	right = find_min_of_tree_rec(binary_tree,2*root + 2);
	min = MIN(left,right);
	res = MIN(min,binary_tree[root]);
    return res;
	}
}


/*
 * This is an iterative function that performs breadth-first search on the given tree.  If the value does not appear
 * in the given tree,  it returns -1.  Otherwise,  it returns the index of the first observation of the value.
 * It gets the index of the root and the integer value that is to be searched.  Be careful, any sub-tree can be given to
 * the function and you will apply level-wise search in the tree
 */
int breadth_first_search_itr(int binary_tree[MAX_LENGTH], int root, int value) {
	int i,f,r;
	int queue[MAX_LENGTH];
	int index_array[MAX_LENGTH];
	
	if(root >= MAX_LENGTH || binary_tree[root] == -1){
	    return -1;
	}
	
	for(i=0;i<MAX_LENGTH;i++){ /*Making arrays full of -1*/
		queue[i] = -1;
		index_array[i] = -1;
	}
	
	queue[0] = root;
	index_array[0] = root;
	f = r = 0;
	
	for(i=0;i<MAX_LENGTH;i++){ /*Checking if root has childs or not,if yes adding them to the queue*/
	    if(queue[f] == -1){
	        continue;
	    }
	    
		if(2*queue[f]+1 < MAX_LENGTH && 2*queue[f]+1 < MAX_LENGTH && binary_tree[2*queue[f]+1] != -1){
			queue[r+1] = 2*queue[f]+1;
			index_array[r+1] = 2*queue[f]+1;
			r++;
		}
		
		if(2*queue[f]+2< MAX_LENGTH && 2*queue[f]+1 < MAX_LENGTH && binary_tree[2*queue[f]+2] != -1){
			queue[r+1] = 2*queue[f]+2;
			index_array[r+1] = 2*queue[f]+2;
			r++;
		}
		
		queue[f] = -1;
		f++;
	}
	
	for(i=0;i<MAX_LENGTH;i++){/*We have all the indexes of our tree/subtree checking if they are matching with the value*/
	    if(index_array[i] == -1){}
		else if(binary_tree[index_array[i]] == value){
			return index_array[i];
		}
	}
	
    return -1;
}
/*
 * This is  a  recursive  function  that  performs  depth-first search on the given tree.  If the value does not appear
 * in the given tree,  it returns -1.  Otherwise,  itreturns the index of the first observation of the value.  It gets
 * the index of the root and the integer valuethat is to be searched.
 * Be careful, any sub-tree can be given to the function.
 */
int depth_first_search_rec(int binary_tree[MAX_LENGTH], int root, int value) {

    if(root >= MAX_LENGTH || binary_tree[root] == -1){
        return -1;
    }

    if(binary_tree[depth_first_search_rec(binary_tree,2*root+1,value)] == value){
        return depth_first_search_rec(binary_tree,2*root+1,value);
    }
    if(binary_tree[depth_first_search_rec(binary_tree,2*root+2,value)] == value){
        return depth_first_search_rec(binary_tree,2*root+2,value);
    }
    if(binary_tree[root] == value){
        return root;
    }    

    return -1;

}

/*
 * This is already given to you.
 */
void print_binary_tree_values(int binary_tree[MAX_LENGTH]) {
    int i;
    for (i = 0; i < MAX_LENGTH; i++) {
        if (binary_tree[i] != -1) {
            printf("%d - %d\n", i, binary_tree[i]);
        }
    }

}
