#include "cpu/exec/template-start.h"

#define instr scas

make_helper(concat(scas_, SUFFIX)) {
	swaddr_t se = REG(R_EAX);
	swaddr_t sd = swaddr_read(reg_l(R_EDI), DATA_BYTE);
	int ans = se - sd;
	cpu.CF = se < sd;
	if (cpu.DF == 0) reg_l(R_EDI) += DATA_BYTE;
	else reg_l(R_EDI) -= DATA_BYTE;
	ans ^= ans >> 4;
	ans ^= ans >> 2;
	ans ^= ans >> 1;
	cpu.PF = !(ans & 0x1);
	int length = (DATA_BYTE << 3) - 1;
	int s1 = se >> length;
	int s2 = sd >> length;
    	cpu.OF = ((s1 != s2) && (s2 == cpu.SF));
	print_asm("scas%s", str(SUFFIX));
	return 1;
}

#include "cpu/exec/template-end.h"
