#include <stdio.h>

typedef	struct
{
	int* a;
	int length;
	int capacity;
}vector;

void vec_create(vector* v, int size)
{
	v->a = (int*)malloc(size * sizeof(int));

	if (!v->a)
	{
		printf("Fail to create vector. Memory not allocated!");
		return;
	}

	v->capacity = size;
	v->length = 0;
}

void vec_push_back(vector* v, int value)
{
	if (v->length + 1 < v->capacity)
		v->a[++v->length];
	else
		increase_capacity(v, v->capacity + 3);
}

void vec_empty(vector* v)
{
	free(v->a);
	v->length = 0;
}

void vec_increase_capacity(vector* v, int new_size)
{
	int* aux = realloc(v->a, new_size * sizeof(int));
	if (aux)
	{
		v->a = aux;
		v->capacity = new_size;
	}
	else
	{
		printf("Fail to Increase the vector size. Memory reallocation failure!");
		return;
	}
}

int vec_get(vector* v, int i)
{
	if (i + 1 >= v->length)
	{
		printf("index out of bounds!");
		return 0;
	}
	else
		return v->a[i];
}

void vec_set(vector* v, int i, int value)
{
	if (i + 1 >= v->capacity)
	{
		printf("index out of bounds!");
		return 0;
	}
	else
		v->a[i] = value;
}