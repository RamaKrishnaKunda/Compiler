#include<stdio.h>
#include<stdlib.h>

//() - indicates compulsory
//{} - indicates optional
char grammar[14][10][20] = { 
{ "DATA", "(variable)", "{size}" },
{ "CONST", "(variable)", "=", "(value)" },
{ "MOV", "(register)", "(variable)", "{index}" },
{ "MOV", "(variable)", "{index}", "(register)" },
{ "ADD", "(answer)", "(operand1)", "(operand2)" },
{ "SUB", "(answer)", "(operand1)", "(operand2)" },
{ "MUL", "(answer)", "(operand1)", "(operand2)" },
{ "READ", "(register)" },
{ "PRINT", "(variable/register)", "{size}" }, 
{ "(name)", ":" },
{"JMP", "(lable)"},
{"IF", "(operand1)", "(condition)", "(operand2)"},
{"ELSE"},
{"ENDIF"} };//increse 9 to 10 if "if_else" is added

char* get_first_word(char* line)
{
	char* first_word = (char*)calloc(20, sizeof(char));
	int iter = 0;
	int line_iter = 0;
	while (line[line_iter] != ' ' && line[line_iter] != '\n' && line[line_iter] != '\0')
	{
		if (line[line_iter] == '\t')
		{
			line_iter++;
			continue;
		}
		first_word[iter] = line[line_iter];
		iter++;
		line_iter++;
	}
	return first_word;
}
int identify_instruction(char* line)
{
	char* first_word = get_first_word(line);
	for (int iter = 0; iter < 14; iter++)//here iter < 11  should be 11 if "if_else" is added
	{
		if (string_compare(first_word, grammar[iter][0]))
			return iter + 1;
	}
}

void parse_data(char* file_name)
{
	FILE* fp = fopen(file_name, "r");
	while (!feof(fp))
	{
		char* line = (char*)calloc(200, sizeof(char));
		if (fgets(line, 199, fp))
		{
			int flag = 0;
			char** tokens;
			if (line[str_length(line) - 2] == ':')//stringlength-2 because \n will be last caharacter
			{
				tokens = split(line, ":");
				label_table_row* row = (label_table_row*)calloc(1, sizeof(label_table_row));
				row->label_name = tokens[0];
				row->nxt_inst_no = intermediate_inst_num;
				insert_value_into_hash(label_table_hash, tokens[0], (void*)row);
				continue;
			}
			int inst_index = identify_instruction(line);
			if (inst_index == 1)
			{
				tokens = split(line, " []\t");
				add_to_symbol_table(tokens);
			}
			if (inst_index == 2)
			{
				tokens = split(line, " \t");
				add_to_symbol_table(tokens);
			}
			if (inst_index == 3)
			{
				tokens = split(line, " [],\t");
				if (str_length(tokens[1]) == 2 && tokens[1][1] == 'X')
				{
					if (tokens[3][0] == '\0')
					{
						flag = 1;
						symbol_table_row* symb = (symbol_table_row*)get_value_from_hash(symbol_table_hash, (void*)tokens[2]);
						/*registers[get_register(tokens[1])] = memory_block[symb->offset];*/
						
						inter_lang_row* row = (inter_lang_row*)calloc(1, sizeof(inter_lang_row));
						row->inst_no = intermediate_inst_num;
						oppcode_row* op_row = (oppcode_row*)get_value_from_hash(opp_code_hash, (void*)"MOVmr");
						row->num_of_parameter = 2;
						row->parameters = (int*)calloc(row->num_of_parameter, sizeof(int));
						row->op_code = op_row->value;
						row->parameters[0] = get_register(tokens[1]);
						row->parameters[1] = symb->offset;
						inter_lang_table[intermediate_inst_num - 1] = row;
						intermediate_inst_num++;
					}
					else
					{
						flag = 1;
						symbol_table_row* symb = (symbol_table_row*)get_value_from_hash(symbol_table_hash, (void*)tokens[2]);
						//registers[get_register(tokens[1])] = memory_block[symb->offset + symb->size];

						inter_lang_row* row = (inter_lang_row*)calloc(1, sizeof(inter_lang_row));
						row->inst_no = intermediate_inst_num;
						oppcode_row* op_row = (oppcode_row*)get_value_from_hash(opp_code_hash, (void*)"MOVmr");
						row->num_of_parameter = 3;
						row->parameters = (int*)calloc(row->num_of_parameter, sizeof(int));
						row->op_code = op_row->value;
						row->parameters[0] = get_register(tokens[1]);
						row->parameters[1] = symb->offset;
						row->parameters[2] = str_to_int(tokens[3]);
						inter_lang_table[intermediate_inst_num - 1] = row;
						intermediate_inst_num++;
						// write intermediate code for a[0] case using 3rd parameter
					}
				}
			}
			if (inst_index == 3 && flag == 0)
			{
				tokens = split(line, " [],\t");
				if (str_length(tokens[2]) == 2 && tokens[2][1] == 'X')
				{
					symbol_table_row* symb = (symbol_table_row*)get_value_from_hash(symbol_table_hash, (void*)tokens[1]);
					/*registers[get_register(tokens[1])] = memory_block[symb->offset];*/

					inter_lang_row* row = (inter_lang_row*)calloc(1, sizeof(inter_lang_row));
					row->inst_no = intermediate_inst_num;
					oppcode_row* op_row = (oppcode_row*)get_value_from_hash(opp_code_hash, (void*)"MOVrm");
					row->num_of_parameter = 2;
					row->parameters = (int*)calloc(row->num_of_parameter, sizeof(int));
					row->op_code = op_row->value;
					row->parameters[0] = symb->offset;;
					row->parameters[1] = get_register(tokens[2]);
					inter_lang_table[intermediate_inst_num - 1] = row;
					intermediate_inst_num++;
				}
				else
				{
					symbol_table_row* symb = (symbol_table_row*)get_value_from_hash(symbol_table_hash, (void*)tokens[1]);
					//registers[get_register(tokens[1])] = memory_block[symb->offset + symb->size];

					inter_lang_row* row = (inter_lang_row*)calloc(1, sizeof(inter_lang_row));
					row->inst_no = intermediate_inst_num;
					oppcode_row* op_row = (oppcode_row*)get_value_from_hash(opp_code_hash, (void*)"MOVrm");
					row->num_of_parameter = 3;
					row->parameters = (int*)calloc(row->num_of_parameter, sizeof(int));
					row->op_code = op_row->value;
					row->parameters[0] = symb->offset;
					row->parameters[1] = str_to_int(tokens[2]);
					row->parameters[2] = get_register(tokens[3]);
					inter_lang_table[intermediate_inst_num - 1] = row;
					intermediate_inst_num++;
				}

			}
			if (inst_index == 4)
			{

			}
			if (inst_index == 5)
			{
				tokens = split(line, ", \t");
				inter_lang_row* row = (inter_lang_row*)calloc(1, sizeof(inter_lang_row));
				row->inst_no = intermediate_inst_num;
				oppcode_row* symb = (oppcode_row*)get_value_from_hash(opp_code_hash, (void*)tokens[0]);
				row->num_of_parameter = 3;
				row->parameters = (int*)calloc(row->num_of_parameter, sizeof(int));
				row->op_code = symb->value;
				row->parameters[0] = get_register(tokens[1]);
				row->parameters[1] = get_register(tokens[2]);
				row->parameters[2] = get_register(tokens[3]);
				inter_lang_table[intermediate_inst_num - 1] = row;
				intermediate_inst_num++;

				//registers[get_register(tokens[1])] = registers[get_register(tokens[2])] + registers[get_register(tokens[3])];
			}
			if (inst_index == 6)
			{
				tokens = split(line, ", \t");
				inter_lang_row* row = (inter_lang_row*)calloc(1, sizeof(inter_lang_row));
				row->inst_no = intermediate_inst_num;
				oppcode_row* symb = (oppcode_row*)get_value_from_hash(opp_code_hash, (void*)tokens[0]);
				row->num_of_parameter = 3;
				row->parameters = (int*)calloc(row->num_of_parameter, sizeof(int));
				row->op_code = symb->value;
				row->parameters[0] = get_register(tokens[1]);
				row->parameters[1] = get_register(tokens[2]);
				row->parameters[2] = get_register(tokens[3]);
				inter_lang_table[intermediate_inst_num - 1] = row;
				intermediate_inst_num++;
				
				//registers[get_register(tokens[1])] = registers[get_register(tokens[2])] - registers[get_register(tokens[3])];
			}
			if (inst_index == 7)
			{
				tokens = split(line, ", \t");
				inter_lang_row* row = (inter_lang_row*)calloc(1, sizeof(inter_lang_row));
				row->inst_no = intermediate_inst_num;
				oppcode_row* symb = (oppcode_row*)get_value_from_hash(opp_code_hash, (void*)tokens[0]);
				row->num_of_parameter = 3;
				row->parameters = (int*)calloc(row->num_of_parameter, sizeof(int));
				row->op_code = symb->value;
				row->parameters[0] = get_register(tokens[1]);
				row->parameters[1] = get_register(tokens[2]);
				row->parameters[2] = get_register(tokens[3]);
				inter_lang_table[intermediate_inst_num - 1] = row;
				intermediate_inst_num++;

				//registers[get_register(tokens[1])] = registers[get_register(tokens[2])] * registers[get_register(tokens[3])];
			}
			if (inst_index == 8)
			{
				tokens = split(line, " \t");
				inter_lang_row* row = (inter_lang_row*)calloc(1, sizeof(inter_lang_row));
				row->inst_no = intermediate_inst_num;
				oppcode_row* symb = (oppcode_row*)get_value_from_hash(opp_code_hash, (void*)tokens[0]);
				row->num_of_parameter = 1;
				row->parameters = (int*)calloc(row->num_of_parameter, sizeof(int));
				row->op_code = symb->value;
				row->parameters[0] = get_register(tokens[1]);
				inter_lang_table[intermediate_inst_num - 1] = row;
				intermediate_inst_num++;
			}
			if (inst_index == 9)
			{
				tokens = split(line, " \t[]");
				if (str_length(tokens[1]) == 2 && tokens[1][1] == 'X')
				{
					inter_lang_row* row = (inter_lang_row*)calloc(1, sizeof(inter_lang_row));
					row->inst_no = intermediate_inst_num;
					oppcode_row* symb = (oppcode_row*)get_value_from_hash(opp_code_hash, (void*)tokens[0]);
					row->num_of_parameter = 1;
					row->parameters = (int*)calloc(row->num_of_parameter, sizeof(int));
					row->op_code = symb->value;
					row->parameters[0] = get_register(tokens[1]);
					inter_lang_table[intermediate_inst_num - 1] = row;
					intermediate_inst_num++;
				}
				else
				{
					inter_lang_row* row = (inter_lang_row*)calloc(1, sizeof(inter_lang_row));
					row->inst_no = intermediate_inst_num;
					oppcode_row* symb = (oppcode_row*)get_value_from_hash(opp_code_hash, (void*)tokens[0]);
					row->num_of_parameter = 2;
					row->parameters = (int*)calloc(row->num_of_parameter, sizeof(int));
					row->op_code = symb->value;
					symbol_table_row* symb_row = (symbol_table_row*)get_value_from_hash(symbol_table_hash, (void*)tokens[1]);
					row->parameters[0] = symb_row->offset;
					row->parameters[1] = str_to_int(tokens[2]);
					inter_lang_table[intermediate_inst_num - 1] = row;
					printf("IN PARSE %d %d %d %d", row->inst_no, row->op_code, row->parameters[0], row->parameters[1]);
					intermediate_inst_num++;
				}
			}
			if (inst_index == 11)
			{
				tokens = split(line, " \t");
				label_table_row* label_row = (label_table_row*)get_value_from_hash(label_table_hash, (void*)tokens[1]);
				inter_lang_row* row = (inter_lang_row*)calloc(1, sizeof(inter_lang_row));
				row->inst_no = intermediate_inst_num;
				oppcode_row* symb = (oppcode_row*)get_value_from_hash(opp_code_hash, (void*)tokens[0]);
				row->num_of_parameter = 1;
				row->parameters = (int*)calloc(row->num_of_parameter, sizeof(int));
				row->op_code = symb->value;
				row->parameters[0] = label_row->nxt_inst_no;
				inter_lang_table[intermediate_inst_num - 1] = row;
				intermediate_inst_num++;
			}
			if (inst_index == 12)
			{
				tokens = split(line, " \t");
				push(stack, intermediate_inst_num);

				inter_lang_row* row = (inter_lang_row*)calloc(1, sizeof(inter_lang_row));
				row->inst_no = intermediate_inst_num;
				oppcode_row* symb = (oppcode_row*)get_value_from_hash(opp_code_hash, (void*)tokens[0]);
				row->num_of_parameter = 4;
				row->op_code = symb->value;
				row->parameters = (int*)calloc(row->num_of_parameter, sizeof(int));
				row->parameters[0] = get_register(tokens[1]);
				row->parameters[1] = get_register(tokens[3]);
				symb = (oppcode_row*)get_value_from_hash(opp_code_hash, (void*)tokens[2]);
				row->parameters[2] = symb->value;
				inter_lang_table[intermediate_inst_num - 1] = row;
				intermediate_inst_num++;
			}
			if (inst_index == 13)
			{
				tokens = split(line, "\t\n");
				inter_lang_row* row = (inter_lang_row*)calloc(1, sizeof(inter_lang_row));
				row->inst_no = intermediate_inst_num;
				oppcode_row* symb = (oppcode_row*)get_value_from_hash(opp_code_hash, (void*)tokens[0]);
				row->num_of_parameter = 1;
				row->op_code = symb->value;
				row->parameters = (int*)calloc(row->num_of_parameter, sizeof(int));
				int prev_if = pop(stack);
				push(stack, intermediate_inst_num);
				inter_lang_table[prev_if - 1]->parameters[3] = intermediate_inst_num + 1;
				inter_lang_table[intermediate_inst_num - 1] = row;
				intermediate_inst_num++;
			}
			if (inst_index == 14)
			{
				tokens = split(line, "\t\n\0");
				inter_lang_row* row = (inter_lang_row*)calloc(1, sizeof(inter_lang_row));
				row->inst_no = intermediate_inst_num;
				oppcode_row* symb = (oppcode_row*)get_value_from_hash(opp_code_hash, (void*)tokens[0]);
				row->num_of_parameter = 0;
				row->op_code = symb->value;
				row->parameters = (int*)calloc(row->num_of_parameter, sizeof(int));
				int prev_if = pop(stack);
				inter_lang_table[prev_if - 1]->parameters[0] = intermediate_inst_num + 1;
				inter_lang_table[intermediate_inst_num - 1] = row;
				intermediate_inst_num++;
			}
		}
	}
}
