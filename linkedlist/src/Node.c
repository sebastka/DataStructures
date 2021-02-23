#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "Node.h"

struct Node* node_create(void* const data)
{
	struct Node* new_node = NULL;

	if (!data)
		_ERR("Error in node_create(): nullptr passed as argument\n", NULL);
	
	if (!(new_node = calloc(1, sizeof(struct Node))))
		_ERR_P("Error in node_create()", NULL);

	new_node->data = data;
	new_node->next = NULL;
	
	return new_node;
}
