#include "cpu/exec/template-start.h"

#define instr js

static void do_execute() {
	DATA_TYPE_S value = op_src->val;	
	print_asm("js %x",cpu.eip+1+DATA_BYTE+value);
	printf("%d,%d,%d\n",cpu.ZF,cpu.SF,cpu.OF);
	if (cpu.SF == 1)cpu.eip+=value;
}

make_instr_helper(i)

#include "cpu/exec/template-end.h"
