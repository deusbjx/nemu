#include "cpu/exec/template-start.h"

#define instr call

make_helper(concat(call_i_, SUFFIX)) {
	DATA_TYPE_S value = op_src->val;
	uint32_t length = concat(decode_i_,SUFFIX)(eip+1);
	reg_l(R_ESP) -= DATA_BYTE;
	swaddr_write(reg_l(R_ESP),4,cpu.eip+length);
	print_asm("call %x",cpu.eip+1+value+length);
	cpu.eip+=value;
	return length+1;
}

make_helper(concat(call_rm_, SUFFIX)) {
	DATA_TYPE_S value = op_src->val;
	uint32_t length = concat(decode_rm_,SUFFIX)(eip+1);
	reg_l(R_ESP) -= DATA_BYTE;
	swaddr_write(reg_l(R_ESP),4,cpu.eip+length);
	print_asm("call %x",value);
	cpu.eip=value-length-1;
	return length+1;
}

#include "cpu/exec/template-end.h"
