#include "cpu/exec/template-start.h"

#define instr jbe

static void do_execute() {
	DATA_TYPE_S value = op_src->val;	
	print_asm("jbe %x",cpu.eip+1+DATA_BYTE+value);
	if (cpu.CF == 1 || cpu.ZF == 1)cpu.eip+=value;
}

/*make_helper(concat(jbe_i_, SUFFIX)) {
	int len = concat(decode_i_, SUFFIX) (eip + 1);
	print_asm("jbe 0x%x", (DATA_TYPE_S)op_src->imm + cpu.eip + len + 1);
	if(cpu.ZF == 1 || cpu.CF == 1) cpu.eip += (DATA_TYPE_S)op_src->imm;
	return len + 1;
}*/

make_instr_helper(i)

#include "cpu/exec/template-end.h"
