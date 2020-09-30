#include "cpu/exec/template-start.h"

#define instr sar

static void do_execute () {
	DATA_TYPE src = op_src->val;
	DATA_TYPE_S dest = op_dest->val;
	//DATA_TYPE_S ans = op_dest->val;
	
	/* TODO: Update EFLAGS. */
	
	uint8_t count = src & 0x1f;
	dest >>= count;
	OPERAND_W(op_dest, dest);
	
	DATA_TYPE ans = dest;
	cpu.ZF=!ans;
	cpu.CF=0;
	cpu.OF=0;
	int length = (DATA_BYTE << 3)-1;
	cpu.SF = ans >> length; 
	ans ^= ans >>4;
	ans ^= ans >>2;
	ans ^= ans >>1;
	cpu.PF=!(ans & 1);
	//panic("please implement me");
	print_asm_template2();
}

make_instr_helper(rm_1)
make_instr_helper(rm_cl)
make_instr_helper(rm_imm)

#include "cpu/exec/template-end.h"
