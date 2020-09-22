#include "cpu/exec/template-start.h"

#define instr sbb

static void do_execute() {
	DATA_TYPE value = op_src->val;
	if (op_src->size == 1 && op_dest->size != 1){
		op_src->val = (int8_t)op_src->val;
	}
	value += cpu.CF;
	DATA_TYPE ans =  op_dest->val - value;
	cpu.ZF = !ans;
	uint32_t length = (DATA_BYTE << 3)-1;
	cpu.SF = ans >> length;
	cpu.CF = op_dest->val < value;
	cpu.OF = 0;
	int dest = op_dest->val >> length;
	int src = op_src->val >> length;
	if (dest != src && src == cpu.SF){
		cpu.OF = 1;
	}
	//cpu.AF = 0;
	OPERAND_W(op_dest,ans);
	uint32_t an = ans >> 4;
	ans ^= an;
	uint32_t res = ans >> 2;
	ans ^= res;
	ans ^= ans >> 1;
	cpu.PF = !(ans & 0x1);
	print_asm_template2();
}

#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif

make_instr_helper(i2a)
make_instr_helper(i2r)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)



#include "cpu/exec/template-end.h"
