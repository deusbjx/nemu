#include "cpu/exec/template-start.h"

#define instr xor

static void do_execute () {
	/* TODO: Update EFLAGS. */	
	DATA_TYPE ans = op_dest->val ^ op_src->val;
	int length = (DATA_BYTE << 3) - 1;
	cpu.SF=ans >> length;
    	cpu.ZF=!ans;
    	OPERAND_W(op_dest, ans);
	ans ^= ans >>4;
	ans ^= ans >>2;
	ans ^= ans >>1;
	cpu.PF=!(ans & 1);
	cpu.CF=0;
	cpu.OF=0;
	//panic("please implement me");
	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
