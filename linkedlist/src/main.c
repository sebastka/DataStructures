#include <stdlib.h>
#include <stdio.h>
#include "Linkedlist.h"

void test_linkedlist_str(void);
void test_linkedlist_int(void);
void test_linkedlist_double(void);
void test_linkedlist_char(void);

int main(void)
{
	test_linkedlist_str();
	test_linkedlist_int();
	test_linkedlist_double();
	test_linkedlist_char();

	return EXIT_SUCCESS;
}

void test_linkedlist_str(void)
{
	struct Linkedlist linkedlist = { NULL };

	printf("Add three elements...\n");
	linkedlist_add(&linkedlist, "A");
	linkedlist_add(&linkedlist, "B");
	linkedlist_add(&linkedlist, "C");
	linkedlist_printf(&linkedlist, "%s");

	printf("\nRemove element with index 1...\n");
	linkedlist_remove_at(&linkedlist, 1);
	linkedlist_printf(&linkedlist, "%s");

	printf("\nChange element with index 1...\n");
	linkedlist_set_at(&linkedlist, 1, "D");
	linkedlist_printf(&linkedlist, "%s");

	linkedlist_free(&linkedlist);
}

void test_linkedlist_int(void)
{
	struct Linkedlist linkedlist = { NULL };

	int a = 0;
	int b = 1;
	int c = 2;
	int d = 3;

	printf("Add three elements...\n");
	linkedlist_add(&linkedlist, &a);
	linkedlist_add(&linkedlist, &b);
	linkedlist_add(&linkedlist, &c);
	linkedlist_printf(&linkedlist, "%i");

	printf("\nRemove element with index 1...\n");
	linkedlist_remove_at(&linkedlist, 1);
	linkedlist_printf(&linkedlist, "%i");

	printf("\nChange element with index 1...\n");
	linkedlist_set_at(&linkedlist, 1, &d);
	linkedlist_printf(&linkedlist, "%i");

	linkedlist_free(&linkedlist);
}

void test_linkedlist_double(void)
{
	struct Linkedlist linkedlist = { NULL };

	double a = 0;
	double b = 1;
	double c = 2;
	double d = 3;

	printf("Add three elements...\n");
	linkedlist_add(&linkedlist, &a);
	linkedlist_add(&linkedlist, &b);
	linkedlist_add(&linkedlist, &c);
	linkedlist_printf(&linkedlist, "%f");

	printf("\nRemove element with index 1...\n");
	linkedlist_remove_at(&linkedlist, 1);
	linkedlist_printf(&linkedlist, "%f");

	printf("\nChange element with index 1...\n");
	linkedlist_set_at(&linkedlist, 1, &d);
	linkedlist_printf(&linkedlist, "%f");

	linkedlist_free(&linkedlist);
}

void test_linkedlist_char(void)
{
	struct Linkedlist linkedlist = { NULL };

	char a = 'a';
	char b = 'b';
	char c = 'c';
	char d = 'c';

	printf("Add three elements...\n");
	linkedlist_add(&linkedlist, &a);
	linkedlist_add(&linkedlist, &b);
	linkedlist_add(&linkedlist, &c);
	linkedlist_printf(&linkedlist, "%c");

	printf("\nRemove element with index 1...\n");
	linkedlist_remove_at(&linkedlist, 1);
	linkedlist_printf(&linkedlist, "%c");

	printf("\nChange element with index 1...\n");
	linkedlist_set_at(&linkedlist, 1, &d);
	linkedlist_printf(&linkedlist, "%c");

	linkedlist_free(&linkedlist);
}
