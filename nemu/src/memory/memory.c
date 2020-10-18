#include "common.h"
#include "stdlib.h"
#include "burst.h"
#include "memory/cache.h"

uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);

/* Memory accessing interfaces */

uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
	int fir_id = cache_read(addr);	//get cache id
	//printf("id:%d\n",fir_id);
	uint32_t in_addr = addr & (CACHE_BLOCK_SIZE - 1); //inside addr
	uint8_t tmp[2 * BURST_LEN];
	if(in_addr + len >= CACHE_BLOCK_SIZE) {
		// it's time to use unalign_rw 
		int sec_id = cache_read(addr + len);
		memcpy(tmp, cache[fir_id].data + in_addr, CACHE_BLOCK_SIZE - in_addr);
		memcpy(tmp + CACHE_BLOCK_SIZE - in_addr, cache[sec_id].data, len - (CACHE_BLOCK_SIZE - in_addr));
	} else {
		memcpy(tmp, cache[fir_id].data + in_addr, len);
	}
	int zero = 0;
	uint32_t ans = unalign_rw(tmp + zero, 4) & (~0u >> ((4 - len) << 3));
	return ans;
	//return dram_read(addr, len) & (~0u >> ((4 - len) << 3));
}

/*uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
	return dram_read(addr, len) & (~0u >> ((4 - len) << 3));
}*/

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
	//dram_write(addr, len, data);	
	cache_write(addr,len,data);
}

uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	return hwaddr_read(addr, len);
}

void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	hwaddr_write(addr, len, data);
}

uint32_t swaddr_read(swaddr_t addr, size_t len) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	return lnaddr_read(addr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	lnaddr_write(addr, len, data);
}

