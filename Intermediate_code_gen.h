int execute_intermediate_code()
{
	int iter = 0;
	for (iter = 0; inter_lang_table[iter]->inst_no != 0; iter++)
	{
		int opcode = inter_lang_table[iter]->op_code;
		int operand1, operand2, condition_operator;
		switch (opcode)
		{
			case 1:
				if (inter_lang_table[iter]->num_of_parameter == 2)
				{
					memory_block[inter_lang_table[iter]->parameters[0]] = registers[inter_lang_table[iter]->parameters[1]];
					break;
				}
				else
				{
					memory_block[inter_lang_table[iter]->parameters[0] + inter_lang_table[iter]->parameters[1]] = registers[inter_lang_table[iter]->parameters[2]];
				}
				break;
			case 2:
				if (inter_lang_table[iter]->num_of_parameter == 2)
				{
					registers[inter_lang_table[iter]->parameters[0]] = memory_block[inter_lang_table[iter]->parameters[1]];
					break;
				}
				else
				{
					registers[inter_lang_table[iter]->parameters[0]] = memory_block[inter_lang_table[iter]->parameters[1] + inter_lang_table[iter]->parameters[2]];
				}
				break;
			case 3:
				registers[inter_lang_table[iter]->parameters[0]] = registers[inter_lang_table[iter]->parameters[1]] + registers[inter_lang_table[iter]->parameters[2]];
				//printf("%d", registers[inter_lang_table[iter]->parameters[0]]);
				break;
			
			case 4:
				registers[inter_lang_table[iter]->parameters[0]] = registers[inter_lang_table[iter]->parameters[1]] - registers[inter_lang_table[iter]->parameters[2]];
				break;
			
			case 5:
				registers[inter_lang_table[iter]->parameters[0]] = registers[inter_lang_table[iter]->parameters[1]] * registers[inter_lang_table[iter]->parameters[2]];
				break;

			case 6:
				iter = inter_lang_table[iter]->parameters[0] - 2;//because once loop is completed iter++ happens
				break;

			case 7:
				operand1 = registers[inter_lang_table[iter]->parameters[0]];
				operand2 = registers[inter_lang_table[iter]->parameters[1]];
				condition_operator = inter_lang_table[iter]->parameters[2];
				switch (condition_operator)
				{
					case 8:
						if (operand1 != operand2)
						{
							iter = inter_lang_table[iter]->parameters[3] - 2;
						}
						break;
					case 9:
						if (operand1 > operand2)
						{
							iter = inter_lang_table[iter]->parameters[3] - 2;
						}
						break;
					case 10:
						if (operand1 < operand2)
						{
							iter = inter_lang_table[iter]->parameters[3] - 2;
						}
						break;
					case 11:
						if (operand1 >= operand2)
						{
							iter = inter_lang_table[iter]->parameters[3] - 2;
						}
						break;
					case 12:
						if (operand1 <= operand2)
						{
							iter = inter_lang_table[iter]->parameters[3] - 2;
						}
						break;

				}
				break;

			case 0:
				iter = inter_lang_table[iter]->parameters[0] - 2;
				break;

			case 15:
				continue;
				break;
			case 13:
				if (inter_lang_table[iter]->num_of_parameter == 1)
					printf("%d\n", registers[inter_lang_table[iter]->parameters[0]]);
				else
				{
					printf("%d\n", memory_block[inter_lang_table[iter]->parameters[0] + inter_lang_table[iter]->parameters[1]]);
				}
				break;
			case 14:
				scanf("%d", &registers[inter_lang_table[iter]->parameters[0]]);
				fflush(stdin);
				break;
		}
	}
	return 0;
}