#include <stdlib.h>
#include <stdio.h>
#include "test_linkedlist.h"
#include "Linkedlist.h"

void test_linkedlist(void)
{
	test_linkedlist_str();
	test_linkedlist_int();
	test_linkedlist_double();
	test_linkedlist_char();
}

void test_linkedlist_str(void)
{
	struct Linkedlist* linkedlist = ll_create();

	printf("Add three elements...\n");
	ll_add(linkedlist, "A");
	ll_add(linkedlist, "B");
	ll_add(linkedlist, "C");
	ll_print_str(linkedlist);
	
	printf("\nRemove element with index 1...\n");
	ll_remove_at(linkedlist, 1);
	ll_print_str(linkedlist);

	printf("\nChange element with index 1...\n");
	ll_set_at(linkedlist, 1, "D");
	ll_print_str(linkedlist);

	ll_free(linkedlist);
}

void test_linkedlist_int(void)
{
	struct Linkedlist* linkedlist = ll_create();
	
	int a = 0;
	int b = 1;
	int c = 2;
	int d = 3;

	printf("Add three elements...\n");
	ll_add(linkedlist, &a);
	ll_add(linkedlist, &b);
	ll_add(linkedlist, &c);
	ll_print_int(linkedlist);
	
	printf("\nRemove element with index 1...\n");
	ll_remove_at(linkedlist, 1);
	ll_print_int(linkedlist);

	printf("\nChange element with index 1...\n");
	ll_set_at(linkedlist, 1, &d);
	ll_print_int(linkedlist);

	ll_free(linkedlist);
}

void test_linkedlist_double(void)
{
	struct Linkedlist* linkedlist = ll_create();
	
	double a = 0;
	double b = 1;
	double c = 2;
	double d = 3;

	printf("Add three elements...\n");
	ll_add(linkedlist, &a);
	ll_add(linkedlist, &b);
	ll_add(linkedlist, &c);
	ll_print_double(linkedlist);
	
	printf("\nRemove element with index 1...\n");
	ll_remove_at(linkedlist, 1);
	ll_print_double(linkedlist);

	printf("\nChange element with index 1...\n");
	ll_set_at(linkedlist, 1, &d);
	ll_print_double(linkedlist);

	ll_free(linkedlist);
}

void test_linkedlist_char(void)
{
	struct Linkedlist* linkedlist = ll_create();
	
	char a = 'a';
	char b = 'b';
	char c = 'c';
	char d = 'c';

	printf("Add three elements...\n");
	ll_add(linkedlist, &a);
	ll_add(linkedlist, &b);
	ll_add(linkedlist, &c);
	ll_print_char(linkedlist);
	
	printf("\nRemove element with index 1...\n");
	ll_remove_at(linkedlist, 1);
	ll_print_char(linkedlist);

	printf("\nChange element with index 1...\n");
	ll_set_at(linkedlist, 1, &d);
	ll_print_char(linkedlist);

	ll_free(linkedlist);
}