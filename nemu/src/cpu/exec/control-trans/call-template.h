#include "cpu/exec/template-start.h"

#define instr call

make_helper(concat(call_i_, SUFFIX)) {
	int length = concat(decode_i_,SUFFIX)(eip+1);
	reg_l(R_ESP) -= DATA_BYTE;
	swaddr_write(reg_l(R_ESP),4,cpu.eip+length);
	DATA_TYPE_S value = op_src->val;
	print_asm("call $0x%x",cpu.eip+1+length+value);
	//print_asm("eip $0x%x,%d",cpu.eip,length);
	cpu.eip+=value;
	return length+1;
}

make_helper(concat(call_rm_, SUFFIX)) {
	DATA_TYPE_S value = op_src->val;
	uint32_t length = concat(decode_rm_,SUFFIX)(eip+1);
	reg_l(R_ESP) -= DATA_BYTE;
	swaddr_write(reg_l(R_ESP),4,cpu.eip+length);
	print_asm("call2 $0x%x",value);
	cpu.eip=value-length-1;
	return length+1;
}

#include "cpu/exec/template-end.h"
