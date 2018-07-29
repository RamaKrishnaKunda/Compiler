#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>

int generate_index(void * key);
bool compare(void * key1, void * key2);

typedef struct hash
{
	void * key;
	void * value;
	struct hash * next;
}hash;

typedef struct hash_table
{
	int size;
	hash ** table;
}hash_table;

hash_table * create_hash_table(int size)
{
	hash_table * t = (hash_table *)malloc(sizeof(hash_table));
	t->size = size;
	t->table = (hash **)calloc(t->size, sizeof(hash *));
	return t;
}

void insert_value_into_hash(hash_table * t, void * key, void * value)
{
	int index = generate_index(key) % t->size;
	hash * node = (hash *)calloc(1, sizeof(hash));
	node->key = key;
	node->value = value;
	node->next = NULL;

	if (t->table[index] == NULL)
	{
		t->table[index] = node;
	}
	else
	{
		hash * temp = t->table[index];
		bool flag = false;
		if (compare(temp->key, node->key))
		{
			flag = true;
		}
		else
		{
			while (temp->next != NULL)
			{
				flag = compare(temp->key, node->key);
				temp = temp->next;
			}
		}
		if (flag)
		{
			temp->value = node->value;
		}
		temp->next = node;
	}
}

void * get_value_from_hash(hash_table * t, void * key)
{
	int index = generate_index(key) % t->size;
	hash * temp = t->table[index];

	while (temp != NULL)
	{
		if (compare(temp->key, key))
		{
			return temp->value;
		}
		temp = temp->next;
	}
	return NULL;
}

bool compare(void * key1, void * key2)
{
	if (strcmp((char *)key1, (char *)key2) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int generate_index(void * key)
{
	int sum = 0;

	char * temp_key = (char *)key;
	for (int index = 0; temp_key[index] != '\0'; index++)
	{
		sum = sum + (int)temp_key[index];
	}
	return sum;
}
