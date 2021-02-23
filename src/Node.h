#ifndef node_h
#define node_h

#include "helpers.h"

struct Node {
	void *data;
	struct Node *next;
};

struct Node* node_create(void* const data);

#endif