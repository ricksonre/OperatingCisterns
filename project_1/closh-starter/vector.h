#include <stdio.h>

typedef	struct
{
	int* a;
	int length;
	int capacity;
}vector;

void vec_create(vector* v, int size);

void vec_push_back(vector* v, int value);

void vec_empty(vector* v);

void vec_increase_capacity(vector* v, int new_size);

int vec_get(vector* v, int i);

void vec_set(vector* v, int i, int value);