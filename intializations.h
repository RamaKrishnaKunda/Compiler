#include<stdio.h>
#include<stdlib.h>
typedef struct symbol_table_row
{
	char* var_name;
	int offset;
	int size;
	int is_const;
}symbol_table_row;

typedef struct label_table_row
{
	char* label_name;
	int nxt_inst_no;
}label_table_row;

typedef struct inter_lang_row{
	int inst_no;
	int op_code;
	int num_of_parameter;
	int* parameters;
}inter_lang_row;

typedef struct if_stack
{
	int* stack;
	int top;
}if_stack;

typedef struct opcode_row{
	char* name;
	int value;
}oppcode_row;

/*symbol_table_hash** create_symbol_table_hash()//assumed some 100 symbols can be created
{
symbol_table_hash** symbol_table = (symbol_table_hash**)calloc(10, sizeof(symbol_table_hash*));
for (int iter = 0; iter < 10; iter++)
{
symbol_table[iter] = (symbol_table_hash*)calloc(1, sizeof(symbol_table_hash));
symbol_table[iter]->symbol_row = (symbol_table_row*)calloc(1, sizeof(symbol_table_row));
}
return symbol_table;
}

label_table_hash** create_label_hash()//returns a label table of 100 size
{
label_table_hash** label_table = (label_table_hash**)calloc(100, sizeof(label_table_hash*));
for (int iter = 0; iter < 10; iter++)
{
label_table[iter] = (label_table_hash*)calloc(1, sizeof(label_table_hash));
label_table[iter]->label_row = (label_table_row*)calloc(1, sizeof(label_table_row));
}
return label_table;
}*/


inter_lang_row** create_inter_lang_table()//returns a lang table of 500 size
{
	inter_lang_row** inter_lang = (inter_lang_row**)calloc(500, sizeof(inter_lang_row*));
	for (int iter = 0; iter < 500; iter++)
	{
		inter_lang[iter] = (inter_lang_row*)calloc(1, sizeof(inter_lang_row));
		inter_lang[iter]->parameters = (int*)calloc(4, sizeof(int));
	}
	return inter_lang;
}


hash_table* create_symbol_table_hash()
{
	hash_table* symbol_table_hash = create_hash_table(20);
	//symbol_table_hash->size = 20;
	return symbol_table_hash;
}

hash_table* create_lable_table_hash()
{
	hash_table* lable_table_hash = create_hash_table(20);
	//label_table_hash->size = 20;
	return lable_table_hash;
}
oppcode_row* create_opcode_row(char* name, int value)
{
	oppcode_row* opcode = (oppcode_row*)calloc(1, sizeof(oppcode_row));
	opcode->name = (char*)calloc(50, sizeof(char));
	string_copy(name, opcode->name);
	opcode->value = value;
	return opcode;
}


hash_table* create_oppcode_hash()
{
	hash_table* oppcode_hash = create_hash_table(20);
	insert_value_into_hash(oppcode_hash, "ELSE", (void*)create_opcode_row("ELSE", 0));
	insert_value_into_hash(oppcode_hash, "MOVrm", (void*)create_opcode_row("MOVrm", 1));
	insert_value_into_hash(oppcode_hash, "MOVmr", (void*)create_opcode_row("MOVmr", 2));
	insert_value_into_hash(oppcode_hash, "ADD", (void*)create_opcode_row("ADD", 3));
	insert_value_into_hash(oppcode_hash, "SUB", (void*)create_opcode_row("SUB", 4));
	insert_value_into_hash(oppcode_hash, "MUL", (void*)create_opcode_row("MUL", 5));
	insert_value_into_hash(oppcode_hash, "JMP", (void*)create_opcode_row("JMP", 6));
	insert_value_into_hash(oppcode_hash, "IF", (void*)create_opcode_row("IF", 7));
	insert_value_into_hash(oppcode_hash, "EQ", (void*)create_opcode_row("EQ", 8));
	insert_value_into_hash(oppcode_hash, "LT", (void*)create_opcode_row("LT", 9));
	insert_value_into_hash(oppcode_hash, "GT", (void*)create_opcode_row("GT", 10));
	insert_value_into_hash(oppcode_hash, "LTEQ", (void*)create_opcode_row("LTEQ", 11));
	insert_value_into_hash(oppcode_hash, "GTEQ", (void*)create_opcode_row("GTEQ", 12));
	insert_value_into_hash(oppcode_hash, "PRINT", (void*)create_opcode_row("PRINT", 13));
	insert_value_into_hash(oppcode_hash, "READ", (void*)create_opcode_row("READ", 14));
	insert_value_into_hash(oppcode_hash, "ENDIF", (void*)create_opcode_row("ENDIF", 15));
	return oppcode_hash;
}
int pop(if_stack* stack)
{
	stack->top--;
	return stack->stack[stack->top];
}

void push(if_stack* stack, int value)
{
	stack->stack[stack->top] = value;
	stack->top++;
}

if_stack* create_stack()
{
	if_stack* stack = (if_stack*)calloc(1, sizeof(int));
	stack->stack = (int*)calloc(50, sizeof(int));
	stack->top = 0;
	return stack;
}




