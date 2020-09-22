#include "cpu/exec/template-start.h"

#define instr movs

static void do_execute() {
	if (ops_decoded.is_operand_size_16){
		swaddr_write(reg_w(R_DI),2,swaddr_read(R_SI,4));
		if (!cpu.DF){
			reg_w(R_DI)+=DATA_BYTE;
			reg_w(R_SI)+=DATA_BYTE;
		}
		else {
			reg_w(R_DI)-=DATA_BYTE;
			reg_w(R_SI)-=DATA_BYTE;
		}
	}
	else {
		swaddr_write(reg_l(R_EDI),4,swaddr_read(R_ESI,4));
		if (!cpu.DF){
			reg_l(R_EDI)+=DATA_BYTE;
			reg_l(R_ESI)+=DATA_BYTE;
		}
		else {
			reg_l(R_EDI)-=DATA_BYTE;
			reg_l(R_ESI)-=DATA_BYTE;
		}
	}
	print_asm("movs");
}

make_instr_helper(i)

#include "cpu/exec/template-end.h"
