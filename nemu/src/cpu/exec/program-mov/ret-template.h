#include "cpu/exec/template-start.h"

#define instr ret

make_helper(concat(ret_i_, SUFFIX)) {
	int value = instr_fetch(eip+1,2);
	//current_sreg = R_SS;
	cpu.eip = MEM_R(REG(R_ESP));
	REG(R_ESP)+=DATA_BYTE;
	int i;
	for (i = 0;i < value;i+=DATA_BYTE){
		MEM_W(REG(R_ESP)+i,0);
	}
	if (DATA_BYTE == 2){
		cpu.eip &= 0xffff;
	}
	MEM_W(REG(R_ESP)+i,0);
	REG(R_ESP)+=value;
	print_asm("ret 0x%x",value);
	return 0;
}



#include "cpu/exec/template-end.h"
