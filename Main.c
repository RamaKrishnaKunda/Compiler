#include<stdlib.h>
#include<stdio.h>

#include"Hash.h"
int* memory_block;
int memory_current_address;
int* registers;
hash_table* symbol_table_hash;
hash_table* label_table_hash;
hash_table* opp_code_hash;
int intermediate_inst_num;
#include "helper_function.h"
#include "intializations.h"
if_stack* stack;
void perform_initializations()
{
	memory_block = (int*)calloc(1000, sizeof(int));
	memory_current_address = 0;
	registers = (int*)calloc(8, sizeof(int));
	symbol_table_hash = create_symbol_table_hash();
	label_table_hash = create_lable_table_hash();
	opp_code_hash = create_oppcode_hash();
	stack = create_stack();
	intermediate_inst_num = 1;
}

inter_lang_row** inter_lang_table;


#include "Memory_handling.h"
#include "Symbol_table_gen.h"
#include "Intermediate_code_gen.h"
#include "parser.h"
//#include "C_converter.h"


int main()
{
	perform_initializations();
	inter_lang_table = create_inter_lang_table();
	//implemet this function
	parse_data("program.txt");
	
	/*symbol_table_row* symb = (symbol_table_row*)get_value_from_hash(symbol_table_hash, (void*)"B");
	printf("%s\n", symb->var_name);
	printf("%d\n", symb->offset);
	printf("%d\n", memory_block[symb->offset]);
	printf("\n");*/
	for (int iter = 0; iter < intermediate_inst_num - 1; iter++)
	{
		printf("%d ", inter_lang_table[iter]->inst_no);
		printf("%d ", inter_lang_table[iter]->op_code);
		for (int i = 0; i < inter_lang_table[iter]->num_of_parameter; i++)
		{
			printf("%d ", inter_lang_table[iter]->parameters[i]);
		}
		printf("\n");
	}
	//execute_intermediate_code();
	//convert_itermediate_code_to_c();
	getchar();
	return 0;
}