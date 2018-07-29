#include<stdlib.h>

void string_copy(char* source, char* dest)
{
	int iter = 0;
	while (source[iter] != '\0')
	{
		dest[iter] = source[iter];
		iter++;
	}
}

int is_delimeter(char character, char* delimeter)
{
	int iter = 0;
	while (delimeter[iter] != '\0')
	{
		if (character == delimeter[iter])
			return 1;
		iter++;
	}
	return 0;
}

char** split(char* query, char* delimiter)
{
	char** tokens = (char**)calloc(50, sizeof(char*));
	for (int iter = 0; iter < 50; iter++)
	{
		tokens[iter] = (char*)calloc(20, sizeof(char));
	}
	int tokens_iter = 0;
	char* token = (char*)calloc(20, sizeof(char));
	int token_iter = 0;
	int query_iter = 0;
	while (query[query_iter] != '\0' && query[query_iter] != '\n')
	{
		if (is_delimeter(query[query_iter], delimiter))
		{
			if (token[0] == '\0')
			{
				query_iter++;
				continue;
			}
			string_copy(token, tokens[tokens_iter]);
			token = (char*)calloc(20, sizeof(char));
			token_iter = 0;
			tokens_iter++;
			query_iter++;
		}
		else
		{
			token[token_iter] = query[query_iter];
			token_iter++;
			query_iter++;

		}
	}
	string_copy(token, tokens[tokens_iter]);
	return tokens;
}

int str_length(char* string)
{
	int iter = 0;
	while (string[iter] != '\0')
		iter++;
	return iter;
}

int string_compare(char* str1, char* str2)
{
	int iter = 0;
	if (str_length(str1) != str_length(str2))
		return 0;
	else
	{
		while (str1[iter] != '\0')
		{
			if (str1[iter] != str2[iter])
				return 0;
			iter++;
		}
	}
	return 1;
}

int str_to_int(char* str_number)
{
	int iter = 0;
	int number = 0;
	while (str_number[iter] != '\0')
	{
		number = number * 10 + (str_number[iter] - '0');
		iter++;
	}
	return number;
}

int get_register(char* register_name)
{
	return register_name[0] - 'A';
}
