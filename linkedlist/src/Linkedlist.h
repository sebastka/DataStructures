#ifndef linkedlist_h
#define linkedlist_h

#include "helpers.h"
#include "Node.h"

struct Linkedlist {
	struct Node* head;
};

/*
 *	CRUD methods
 */

/* Create */
void* linkedlist_add_at(struct Linkedlist* const linkedlist, const int pos, void* const data);
void* linkedlist_add(struct Linkedlist* const linkedlist, void* const data);

/* Read */
void* linkedlist_get_at(const struct Linkedlist* const linkedlist, const int pos);
int linkedlist_count(const struct Linkedlist* const linkedlist);
BOOL linkedlist_printf(const struct Linkedlist* const linkedlist, const char* const fstring);

/* Update */
void* linkedlist_set_at(const struct Linkedlist* const linkedlist, const int pos, void* const data);

/* Delete */
void* linkedlist_remove_at(struct Linkedlist* const linkedlist, const int pos);
void* linkedlist_remove(struct Linkedlist* const linkedlist);
BOOL linkedlist_free(struct Linkedlist* const linkedlist);

/*
 *	Helpers - would be private in languages supporting oop
 */

struct Node* linkedlist_get_node_at(const struct Linkedlist* const linkedlist, const int pos);

#endif