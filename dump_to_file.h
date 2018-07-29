#include<stdio.h>
void dumping()
{
	FILE* fp = fopen("dump.txt", "w");
	for (int iter = 0; iter < 8; iter++)
	{
		fprintf(fp, "%d", registers[iter]);
	}
	/*int symbol_table_count = 0;//this count is for knowing how many nodes are there in symbol table 
	for (int iter = 0; iter < symbol_table_hash->size; iter++)
	{
		hash* node = symbol_table_hash->table[iter];
		while (node != NULL)
			symbol_table_count++;
	}
	fprintf(fp, "%d", symbol_table_count);
	for (int iter = 0; iter < symbol_table_hash->size; iter++)
	{
		hash* node = symbol_table_hash->table[iter];
		while (node != NULL)
			fwrite(node, sizeof(symbol_table_row), 1, fp);
	}*/
	fwrite((void*)memory_block, 1000 * sizeof(int), 1, fp);
	for (int iter = 0; iter < intermediate_inst_num - 1; iter++)
	{
		fwrite((void*)inter_lang_table[iter], sizeof(inter_lang_row), 1, fp);
	}
	fclose(fp);
}