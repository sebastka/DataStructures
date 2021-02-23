#include <stdlib.h>
#include <stdio.h>
#include "Linkedlist.h"
#include "Node.h"

/*
 *	"Constructor" and "Destructor"
 */

struct Linkedlist* ll_create(void)
{
	struct Linkedlist* linkedlist = NULL;

	if (!(linkedlist = calloc(1, sizeof(struct Linkedlist))))
		_ERR("Error in node_create(): could not allocate memory\n", NULL);

	linkedlist->head = NULL;
	
	return linkedlist;
}

BOOL ll_free(struct Linkedlist* const linkedlist)
{
	struct Node *temp = NULL;
	struct Node *current = NULL;

	if (!linkedlist)
		_ERR("Error in ll_count(): nullptr passed as argument\n", FALSE);

	current = linkedlist->head;
	for (; current != NULL; temp = NULL) {
		temp = current->next;
		free(current);
		current = temp;
	}
	
	free(linkedlist);

	return TRUE;
}

/*
 *	CRUD methods
 */

/* Create */

void* ll_add_at(struct Linkedlist* const linkedlist, const int pos, void* const data)
{
	struct Node* prev = NULL;
	struct Node* current = NULL;
	struct Node* new_node = NULL;
	int n = 0;
	
	if (!linkedlist)
		_ERR("Error in ll_add_at(): nullptr passed as linkedlist argument\n", NULL);

	if (!data)
		_ERR("Error in ll_add_at(): nullptr passed as data argument\n", NULL);

	if (pos < 0)
		_ERR("Error in ll_add_at(): invalid position passed as argument\n", NULL);
	
	if (!(new_node = node_create(data)))
		_ERR("Error in ll_add_at(): could not create node\n", NULL);

	/* Set new head if pos = 0 */
	if (pos == 0) {
		new_node->next = linkedlist->head; /* Does not matter if NULL */
		linkedlist->head = new_node;
		return new_node->data;
	}

	/* head should not be NULL anymore */
	if (!linkedlist->head)
		_ERR("Error in ll_add_at(): head is nullptr\n", NULL);

	/* Get previous */
	if (!(prev = ll_get_node_at(linkedlist, pos-1)))
		_ERR("Error in ll_add_at(): could not get previous node\n", NULL);

	/* Get size */
	if ((n = ll_count(linkedlist)) < 0)
		_ERR("Error in ll_add_at(): linkedlist has an invalid size\n", NULL);

	/* Append element at the end */
	if (n == pos) {
		prev->next = new_node;
		return data;
	}

	/* Otherwise, put new_node between previous and current */
	if (!(current = prev->next))
		_ERR("Error in ll_add_at(): could not get previous's next node\n", NULL);
	
	/* It's already guaranteed that neither prev or new_node can't be NULL */
	prev->next = new_node;
	new_node->next = current;
	
	return new_node->data;
}

void* ll_add(struct Linkedlist* const linkedlist, void* const data)
{
	int n = 0;

	if (!linkedlist)
		_ERR("Error in ll_add(): nullptr passed as linkedlist argument\n", NULL);

	if (!data)
		_ERR("Error in ll_add(): nullptr passed as data argument\n", NULL);
	
	if ((n = ll_count(linkedlist)) < 0)
		_ERR("Error in ll_add(): could not get count\n", NULL);

	return ll_add_at(linkedlist, n, data);
}

/* Read */

void* ll_get_at(const struct Linkedlist* const linkedlist, const int pos)
{
	struct Node* node = NULL;

	if (!linkedlist)
		_ERR("Error in ll_get_at(): nullptr passed as argument\n", NULL);
	
	if (pos < 0)
		_ERR("Error in ll_get_at(): invalid position passed as argument\n", NULL);
	
	if (!(node = ll_get_node_at(linkedlist, pos)))
		_ERR("Error in ll_get_at(): could not get node\n", NULL);
	
	return node->data;
}

int ll_count(const struct Linkedlist* const linkedlist)
{
	int n = 0;
	struct Node *current = NULL;

	if (!linkedlist)
		_ERR("Error in ll_count(): nullptr passed as argument\n", ERR);

	current = linkedlist->head;

	for (n = 0; current != NULL; ++n)
		current = current->next;
	
	if (n < 0)
		_ERR("Error in ll_count(): overflow!\n", ERR);

	return n;
}

BOOL ll_print_str(const struct Linkedlist* const linkedlist)
{
	int i = 0;
	struct Node* current = NULL;

	if (!linkedlist)
		_ERR("Error in ll_get_node_at(): nullptr passed as argument\n", FALSE);

	current = linkedlist->head;
	for (i = 0; current != NULL; current = current->next, ++i)
		printf("Node #%i : %s\n", i, (char *) current->data);

	return TRUE;
}

BOOL ll_print_int(const struct Linkedlist* const linkedlist)
{
	int i = 0;
	struct Node* current = NULL;

	if (!linkedlist)
		_ERR("Error in ll_get_node_at(): nullptr passed as argument\n", FALSE);

	current = linkedlist->head;
	for (i = 0; current != NULL; current = current->next, ++i)
		printf("Node #%i : %i\n", i, *( (int *) current->data ));

	return TRUE;
}

BOOL ll_print_double(const struct Linkedlist* const linkedlist)
{
	int i = 0;
	struct Node* current = NULL;

	if (!linkedlist)
		_ERR("Error in ll_get_node_at(): nullptr passed as argument\n", FALSE);

	current = linkedlist->head;
	for (i = 0; current != NULL; current = current->next, ++i)
		printf("Node #%i : %f\n", i, *( (double *) current->data ));

	return TRUE;
}

BOOL ll_print_char(const struct Linkedlist* const linkedlist)
{
	int i = 0;
	struct Node* current = NULL;

	if (!linkedlist)
		_ERR("Error in ll_get_node_at(): nullptr passed as argument\n", FALSE);

	current = linkedlist->head;
	for (i = 0; current != NULL; current = current->next, ++i)
		printf("Node #%i : %c\n", i, *( (char *) current->data ));

	return TRUE;
}

/* Update */

void* ll_set_at(const struct Linkedlist* const linkedlist, const int pos, void* const data)
{
	struct Node* node = NULL;

	if (!linkedlist || !data)
		_ERR("Error in ll_set_at(): nullptr passed as argument\n", NULL);
	
	if (pos < 0)
		_ERR("Error in ll_set_at(): invalid position passed as argument\n", NULL);

	if (!(node = ll_get_node_at(linkedlist, pos)))
		_ERR("Error in ll_set_at(): could not get node\n", NULL);

	return (node->data = data);
}

/* Delete */

void* ll_remove_at(struct Linkedlist* const linkedlist, const int pos)
{
	struct Node* current = NULL;
	struct Node* prev = NULL;
	struct Node* next = NULL;
	void* data = NULL;

	if (!linkedlist)
		_ERR("Error in ll_remove_at(): nullptr passed as argument\n", NULL);

	if (!(current = ll_get_node_at(linkedlist, pos)))
		_ERR("Error in ll_remove_at(): could not get current\n", NULL);
	
	/* Can be NULL */
	next = current->next;

	/* If removing the head, set the it to the current head's next */
	if (pos == 0) {
		linkedlist->head = next;
	} else {
		if (!(prev = ll_get_node_at(linkedlist, pos-1)))
			_ERR("Error in ll_remove_at(): could not get previous node\n", NULL);
		
		prev->next = next;
	}

	data = current->data;
	free(current);

	return data;
}

void* ll_remove(struct Linkedlist* const linkedlist)
{
	if (!linkedlist)
		_ERR("Error in ll_remove(): nullptr passed as argument\n", NULL);
	
	return ll_remove_at(linkedlist, 0);
}

/*
 *	Helpers
 */

struct Node* ll_get_node_at(const struct Linkedlist* const linkedlist, const int pos)
{
	struct Node* node = NULL;
	int i = 0;
	
	if (!linkedlist)
		_ERR("Error in ll_get_node_at(): nullptr passed as argument\n", NULL);
	
	if (pos < 0)
		_ERR("Error in ll_get_node_at(): invalid position passed as argument\n", NULL);
	
	node = linkedlist->head;
	for (i = 0; node != NULL && pos != i; ++i)
		node = node->next;
	
	if (!node)
		_ERR("Error in ll_get_node_at(): could not find node\n", NULL);
	
	return node;
}
