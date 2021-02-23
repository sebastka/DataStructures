#ifndef linkedlist_h
#define linkedlist_h

#include "Node.h"

struct Linkedlist {
	struct Node* head;
};

/*
 *	"Constructor" and "Destructor"
 */
struct Linkedlist* ll_create(void);
BOOL ll_free(struct Linkedlist* const linkedlist);

/*
 *	CRUD methods
 */

/* Create */
void* ll_add_at(struct Linkedlist* const linkedlist, const int pos, void* const data);
void* ll_add(struct Linkedlist* const linkedlist, void* const data);

/* Read */
void* ll_get_at(const struct Linkedlist* const linkedlist, const int pos);
int ll_count(const struct Linkedlist* const linkedlist);
BOOL ll_print_str(const struct Linkedlist* const linkedlist);
BOOL ll_print_int(const struct Linkedlist* const linkedlist);
BOOL ll_print_double(const struct Linkedlist* const linkedlist);
BOOL ll_print_char(const struct Linkedlist* const linkedlist);

/* Update */
void* ll_set_at(const struct Linkedlist* const linkedlist, const int pos, void* const data);

/* Delete */
void* ll_remove_at(struct Linkedlist* const linkedlist, const int pos);
void* ll_remove(struct Linkedlist* const linkedlist);

/*
 *	Helpers
 */

struct Node* ll_get_node_at(const struct Linkedlist* const linkedlist, const int pos);

#endif