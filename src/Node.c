#include <stdlib.h>
#include <stdio.h>
#include "Node.h"

struct Node* node_create(void* const data)
{
	struct Node* new_node = NULL;

	if (!data)
		_ERR("Error in node_create(): nullptr passed as argument\n", NULL);
	
	if (!(new_node = calloc(1, sizeof(struct Node))))
		_ERR("Error in node_create(): could not allocate memory\n", NULL);

	new_node->data = data;
	new_node->next = NULL;
	
	return new_node;
}
