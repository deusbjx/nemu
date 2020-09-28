#include "cpu/exec/template-start.h"

#define instr dec

static void do_execute () {
	DATA_TYPE result = op_src->val - 1;
	OPERAND_W(op_src, result);
	int length = (DATA_BYTE << 3) - 1;
	cpu.CF = result < 0;
	cpu.SF=result >> length;
    	int src = op_src->val >> length;
    	cpu.OF=(src != 0 && cpu.SF == 0) ;
	cpu.ZF=!result;
	result ^= result >>4;
	result ^= result >>2;
	result ^= result >>1;
	cpu.PF=!(result & 1);	

	/* TODO: Update EFLAGS. */
	//panic("please implement me");

	print_asm_template1();
}

make_instr_helper(rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
#endif

#include "cpu/exec/template-end.h"
