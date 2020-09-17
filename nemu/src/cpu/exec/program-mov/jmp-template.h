#include "cpu/exec/template-start.h"

#define instr jmp

static void do_execute() {
	DATA_TYPE_S value = op_src->val;
	if (op_src->type == OP_TYPE_REG || op_src->type == OP_TYPE_MEM){
		cpu.eip = value-concat(decode_rm_,SUFFIX)(cpu.eip+1)-1;
		print_asm_template1();
	}
	else {
		print_asm("jmp %x",cpu.eip+1+DATA_BYTE+value);
		cpu.eip+=value;
	}	
}

make_instr_helper(i)
make_instr_helper(rm)

#include "cpu/exec/template-end.h"
