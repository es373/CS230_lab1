#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*	
Allocate a linked list node with a given key
Allocate a node using malloc(),
initialize the pointers to NULL,
set the key value to the key provided by the argument
 */
struct list_node *allocate_node_with_key(int key)
{
	struct list_node *list;
	list=(struct list_node*)malloc(sizeof(struct list_node));
	
	list->prev=NULL;
	list->next=NULL;
	list->key=key;

	return list;
}

/*	
Initialize the key values of the head/tail list nodes (I used -1 key values)
Also, link the head and tail to point to each other
 */
void initialize_list_head_tail(struct list_node *head, struct list_node *tail)
{
	head->key=-1;
	tail->key=-1;    // these two lines are temporary
	head->prev=tail;
	head->next=tail;
	tail->prev=head;
	tail->next=head;

	return;
}

/*	
Insert the *new_node* after the *node*
 */
void insert_node_after (struct list_node *node, struct list_node *new_node)
{
	struct list_node *ori=node->next;
	node->next = new_node;
	new_node->prev = node;
	ori->prev = new_node;
	new_node->next = ori;

	return;
}

/*	
Remove the *node* from the list
 */
void del_node (struct list_node *node)
{
	struct list_node *ori_prev = node->prev;
	struct list_node *ori_next = node->next;

	ori_prev->next = ori_next;
	node->prev = NULL;
	node->next = NULL;
	ori_next->prev = ori_prev;

	return;
}

/*	
Search from the head to the tail (excluding both head and tail,
as they do not hold valid keys), for the node with a given *search_key*
and return the node.
You may assume that the list will only hold nodes with unique key values
(No duplicate keys in the list)
 */
struct list_node *search_list (struct list_node *head, int search_key)
{
	struct list_node *objnode = head;

	do
	{
		if (objnode->key==search_key)
		{
			break;
		}
		
		objnode = objnode->next;		

	}while (objnode->next != head);

	if (objnode->key != search_key)		//can't find the node having that key
	{
		return NULL;
	}
	return objnode;
}

/*	
Count the number of nodes in the list (excluding head and tail), 
and return the counted value
 */
int count_list_length (struct list_node *head)
{	
	struct list_node *cntnode=head;
	int num=0;

	while(cntnode->next != head)
	{
		cntnode=cntnode->next;
		if (cntnode->next !=head)	//if cntnode is not a  tail node
		{	
			num+=1;
		}
	}

	return num;
}

/*	
Check if the list is empty (only head and tail exist in the list)
Return 1 if empty. Return 0 if list is not empty.
 */
int is_list_empty (struct list_node *head)
{
	if (count_list_length(head) ==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}	
	

/*	
Loop through the list and print the key values
This function will not be tested, but it will aid you in debugging your list.
You may add calls to the *iterate_print_keys* function in the test.c
at points where you need to debug your list.
But make sure to test your final version with the original test.c code.
 */
void iterate_print_keys (struct list_node *head)
{	
	//my code will print key values of nodes including head node and tail node.

	struct list_node *objnode = head;

	do
	{
		printf("%d\t", objnode->key);
		
		objnode = objnode->next;
	
	}while(objnode->next !=head);
	
	printf("%d\n",objnode->key);	//this is for tail node.

	return;
}	

/*	
Insert a *new_node* at the sorted position so that the keys of the nodes of the
list (including the key of the *new_node*) is always sorted (increasing order)
 */
int insert_sorted_by_key (struct list_node *head, struct list_node *new_node)
{	
	struct list_node *objnode = head;
	struct list_node *tmpnode = NULL;		

	if (is_list_empty(head))
	{
		insert_node_after(objnode,new_node);
		return 0;	// return what?
	}

	while(objnode->next!=head)
	{	
		tmpnode = objnode->next;
		if ((tmpnode->key >  new_node->key) || (tmpnode->next==head))	//proper position or the biggest key-val case 
		{
			insert_node_after(objnode,new_node);
			break;
		}

		objnode = objnode->next;
	}	

	return 0;
}
