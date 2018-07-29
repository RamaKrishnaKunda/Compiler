void add_to_symbol_table(char** tokens)
{
	symbol_table_row* value = (symbol_table_row*)calloc(1, sizeof(symbol_table_row));
	value->var_name = (char*)calloc(10, sizeof(char));
	if (string_compare(tokens[0], "DATA"))
	{
		string_copy(tokens[1], value->var_name);
		value->offset = memory_current_address;
		if (tokens[2][0] != '\0')
		{
			value->size = str_to_int(tokens[2]);
		}
		else
		{
			value->size = 1;
		}
		memory_current_address += value->size;
		value->is_const = 0;
	}
	else if (string_compare(tokens[0], "CONST"))
	{
		string_copy(tokens[1], value->var_name);
		value->offset = memory_current_address;
		value->size = 1;
		memory_current_address += value->size;
		value->is_const = 1;
		add_to_memory(value->offset, str_to_int(tokens[3]));
	}
	insert_value_into_hash(symbol_table_hash, (void*)tokens[1], (void*)value);
}