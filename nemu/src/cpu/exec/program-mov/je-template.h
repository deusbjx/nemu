#include "cpu/exec/template-start.h"

#define instr je

static void do_execute() {
	DATA_TYPE value = op_src->val;	
	print_asm("je %x",cpu.eip+1+DATA_BYTE+value);
	if (cpu.ZF == 1)cpu.eip+=value;
}

make_instr_helper(i)

#include "cpu/exec/template-end.h"
