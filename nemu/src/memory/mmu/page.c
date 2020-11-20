#include "memory/page.h"

#include "nemu.h"

uint32_t hwaddr_read(hwaddr_t, size_t);
uint32_t tlb_read(lnaddr_t);

typedef union {
	struct {
		uint32_t pf_off		:12;
		uint32_t pt_idx		:10;
		uint32_t pdir_idx	:10;
	};
	uint32_t addr;
} PageAddr;

hwaddr_t page_walk(lnaddr_t lnaddr) {
	PageAddr *addr = (void *)&lnaddr;
	hwaddr_t pdir_base = cpu.cr3.val & ~PAGE_MASK;

	PDE pde;
	pde.val	= hwaddr_read(pdir_base + addr->pdir_idx * 4, 4);
	//set_bp();
	//Log("test");
	
	if(!pde.present) {
		void do_int3();
		do_int3();
		Log("eip = %x, lnaddr = %x, pdir_base = %x, pde = %x", cpu.eip, lnaddr, pdir_base, pde.val);
		Log("Error1!");
		//assert(0);
	}

	hwaddr_t pt_base = pde.val & ~PAGE_MASK;
	PTE pte;
	pte.val = hwaddr_read(pt_base + addr->pt_idx * 4, 4);
	
	if(!pte.present) {
		Log("eip = %x, lnaddr = %x, pt_base = %x, pte = %x", cpu.eip, lnaddr, pt_base, pte.val);
		Log("Error2!");
		assert(0);
	}
	return pte.val;
}

hwaddr_t page_translate(lnaddr_t addr) {	
	return tlb_read(addr) | (addr & PAGE_MASK);
}
