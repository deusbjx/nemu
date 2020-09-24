#include "cpu/exec/template-start.h"

#define instr test

static void do_execute() {
	DATA_TYPE ans = op_dest->val && op_src->val;
	cpu.ZF = !ans;
	uint32_t length = (DATA_BYTE << 3)-1;
	cpu.SF = ans >> length;
	cpu.CF = 0;
	//cpu.AF = 0;
	uint32_t an = ans >> 4;
	ans ^= an;
	uint32_t res = ans >> 2;
	ans ^= res;
	ans ^= ans >> 1;
	cpu.PF = !(ans & 0x1);
	cpu.OF = 0;
	print_asm_template2();
}

//make_instr_helper(i2r)
make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"
