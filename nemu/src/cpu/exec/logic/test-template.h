#include "cpu/exec/template-start.h"

#define instr test

static void do_execute() {
	DATA_TYPE ans = op_dest->val & op_src->val;
	cpu.ZF = !ans;
	if (cpu.ZF == 1)print_asm("test success,value:%d",ans);
	else print_asm("test fail,dest:%d,src:%d,ans:%d",op_dest->val,op_src->val,ans);
	uint32_t length = (DATA_BYTE << 3)-1;
	cpu.SF = ans >> length;
	cpu.CF = 0;
	//cpu.AF = 0;
	ans ^= ans >> 4;
	ans ^= ans >> 2;
	ans ^= ans >> 1;
	cpu.PF = !(ans & 1);
	cpu.OF = 0;
	//print_asm_template2();
}

//make_instr_helper(i2r)
make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"
