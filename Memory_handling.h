void add_to_memory(int offset, int value)
{
	//*(memory_block + (offset * 4)) = value;
	memory_block[offset] = value;
}