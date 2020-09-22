#include "cpu/exec/template-start.h"

#define instr jno

static void do_execute() {
	DATA_TYPE_S value = op_src->val;	
	print_asm("jno %x",cpu.eip+1+DATA_BYTE+value);
	if (cpu.OF == 0)cpu.eip+=value;
}

make_instr_helper(i)

#include "cpu/exec/template-end.h"
