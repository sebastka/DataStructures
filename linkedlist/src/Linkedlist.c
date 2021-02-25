#include <stdlib.h>
#include <stdio.h>
#include "Linkedlist.h"
#include "Node.h"

/*
 *	CRUD methods
 */

/* Create */

void* linkedlist_add_at(struct Linkedlist* const linkedlist, const int pos, void* const data)
{
	struct Node* prev = NULL;
	struct Node* current = NULL;
	struct Node* new_node = NULL;
	int n = 0;

	if (!linkedlist)
		_ERR("Error in linkedlist_add_at(): nullptr passed as linkedlist argument\n", NULL);

	if (!data)
		_ERR("Error in linkedlist_add_at(): nullptr passed as data argument\n", NULL);

	if (pos < 0)
		_ERR("Error in linkedlist_add_at(): invalid position passed as argument\n", NULL);

	if (!(new_node = node_create(data)))
		_ERR("Error in linkedlist_add_at(): could not create node\n", NULL);

	/* Set new head if pos = 0 */
	if (pos == 0) {
		new_node->next = linkedlist->head; /* Does not matter if NULL */
		linkedlist->head = new_node;
		return new_node->data;
	}

	/* head should not be NULL anymore */
	if (!linkedlist->head)
		_ERR("Error in linkedlist_add_at(): head is nullptr\n", NULL);

	/* Get previous */
	if (!(prev = linkedlist_get_node_at(linkedlist, pos-1)))
		_ERR("Error in linkedlist_add_at(): could not get previous node\n", NULL);

	/* Get size */
	if ((n = linkedlist_count(linkedlist)) < 0)
		_ERR("Error in linkedlist_add_at(): linkedlist has an invalid size\n", NULL);

	/* Append element at the end */
	if (n == pos)
		return (prev->next = new_node)->data;

	/* Otherwise, put new_node between previous and current */
	if (!(current = prev->next))
		_ERR("Error in linkedlist_add_at(): could not get previous's next node\n", NULL);

	/* It's already guaranteed that neither prev or new_node can be NULL */
	prev->next = new_node;
	new_node->next = current;

	return new_node->data;
}

void* linkedlist_add(struct Linkedlist* const linkedlist, void* const data)
{
	int n = 0;

	if (!linkedlist)
		_ERR("Error in linkedlist_add(): nullptr passed as linkedlist argument\n", NULL);

	if (!data)
		_ERR("Error in linkedlist_add(): nullptr passed as data argument\n", NULL);

	if ((n = linkedlist_count(linkedlist)) < 0)
		_ERR("Error in linkedlist_add(): could not get count\n", NULL);

	return linkedlist_add_at(linkedlist, n, data);
}

/* Read */

void* linkedlist_get_at(const struct Linkedlist* const linkedlist, const int pos)
{
	struct Node* node = NULL;

	if (!linkedlist)
		_ERR("Error in linkedlist_get_at(): nullptr passed as argument\n", NULL);

	if (pos < 0)
		_ERR("Error in linkedlist_get_at(): invalid position passed as argument\n", NULL);

	if (!(node = linkedlist_get_node_at(linkedlist, pos)))
		_ERR("Error in linkedlist_get_at(): could not get node\n", NULL);

	return node->data;
}

int linkedlist_count(const struct Linkedlist* const linkedlist)
{
	int n = 0;
	struct Node *current = NULL;

	if (!linkedlist)
		_ERR("Error in linkedlist_count(): nullptr passed as argument\n", ERR);

	current = linkedlist->head;

	for (n = 0; current != NULL; ++n)
		current = current->next;

	if (n < 0)
		_ERR("Error in linkedlist_count(): overflow!\n", ERR);

	return n;
}

int linkedlist_printf(const struct Linkedlist* const linkedlist, const char* const fstring)
{
	int i = 0;
	int strlen = 0;
	struct Node* current = NULL;

	if (!linkedlist || !fstring)
		_ERR("Error in linkedlist_get_node_at(): nullptr passed as argument\n", ERR);

	/* Find fstring length */
	for (strlen = 0; fstring[strlen] != '\0'; ++strlen);

	if (strlen != 2 || fstring[0] != '%')
		_ERR("Error in linkedlist_get_node_at(): invalid fstring\n", ERR);

	current = linkedlist->head;
	for (i = 0; current != NULL; current = current->next, ++i) {
		printf("Node #%i: ", i);

		if (fstring[1] == 's')
			printf(fstring, (char *) current->data);
		else if (fstring[1] == 'i')
			printf(fstring, *((int *) current->data));
		else if (fstring[1] == 'f')
			printf(fstring, *((double *) current->data));
		else if (fstring[1] == 'c')
			printf(fstring, *((char *) current->data));
		else
			printf("Datatype not supported");

		printf("\n");
	}

	return 1;
}

/* Update */

void* linkedlist_set_at(const struct Linkedlist* const linkedlist, const int pos, void* const data)
{
	struct Node* node = NULL;

	if (!linkedlist || !data)
		_ERR("Error in linkedlist_set_at(): nullptr passed as argument\n", NULL);

	if (pos < 0)
		_ERR("Error in linkedlist_set_at(): invalid position passed as argument\n", NULL);

	if (!(node = linkedlist_get_node_at(linkedlist, pos)))
		_ERR("Error in linkedlist_set_at(): could not get node\n", NULL);

	return (node->data = data);
}

/* Delete */

void* linkedlist_remove_at(struct Linkedlist* const linkedlist, const int pos)
{
	struct Node* current = NULL;
	struct Node* prev = NULL;
	struct Node* next = NULL;
	void* data = NULL;

	if (!linkedlist)
		_ERR("Error in linkedlist_remove_at(): nullptr passed as argument\n", NULL);

	if (!(current = linkedlist_get_node_at(linkedlist, pos)))
		_ERR("Error in linkedlist_remove_at(): could not get current\n", NULL);

	/* Can be NULL */
	next = current->next;

	/* If removing the head, set the it to the current head's next */
	if (pos == 0) {
		linkedlist->head = next;
	} else {
		if (!(prev = linkedlist_get_node_at(linkedlist, pos-1)))
			_ERR("Error in linkedlist_remove_at(): could not get previous node\n", NULL);

		prev->next = next;
	}

	data = current->data;
	free(current);

	return data;
}

void* linkedlist_remove(struct Linkedlist* const linkedlist)
{
	if (!linkedlist)
		_ERR("Error in linkedlist_remove(): nullptr passed as argument\n", NULL);

	return linkedlist_remove_at(linkedlist, 0);
}

int linkedlist_free(struct Linkedlist* const linkedlist)
{
	struct Node *temp = NULL;
	struct Node *current = NULL;

	if (!linkedlist)
		_ERR("Error in linkedlist_count(): nullptr passed as argument\n", ERR);

	for (current = linkedlist->head; current != NULL; temp = NULL) {
		temp = current->next;
		free(current);
		current = temp;
	}

	return 1;
}

/*
 *	Helpers
 */

struct Node* linkedlist_get_node_at(const struct Linkedlist* const linkedlist, const int pos)
{
	struct Node* node = NULL;
	int i = 0;

	if (!linkedlist)
		_ERR("Error in linkedlist_get_node_at(): nullptr passed as argument\n", NULL);

	if (pos < 0)
		_ERR("Error in linkedlist_get_node_at(): invalid position passed as argument\n", NULL);

	node = linkedlist->head;
	for (i = 0; node != NULL && pos != i; ++i)
		node = node->next;

	if (!node)
		_ERR("Error in linkedlist_get_node_at(): could not find node\n", NULL);

	return node;
}
