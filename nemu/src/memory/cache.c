#include "common.h"
#include "memory/cache.h"
#include <stdlib.h>
#include "burst.h"

void ddr3_read_public(hwaddr_t addr, void *data);
void ddr3_write_public(hwaddr_t addr, void *data, uint8_t *mask);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);

/*cache function*/

int cache_read(hwaddr_t addr) 
{
	uint32_t g_num = (addr>>6) & 0x7f; //group number
	//uint32_t block = (addr >> 6)<<6;
	int i;
	bool flag = false;
	for (i = g_num * WAY_8 ; i < (g_num + 1) * WAY_8 ;i++){
		if (cache[i].tag == (addr >> 13) && cache[i].valid){
				flag = true;
				break;
		}
	}
	if (!flag)
	{
		//int j = secondarycache_read (addr);
		for (i = g_num * WAY_8 ; i < (g_num+1) * WAY_8 ;i++){
			if (!cache[i].valid)break;
		}
		//use random way for replace
		if (i == (g_num + 1) * WAY_8){
			srand (0);
			i = g_num * WAY_8 + rand() % WAY_8;
		}
		cache[i].valid = true;
		cache[i].tag = addr >> 13;
		//memcpy (cache[i].data,cache2[j].data,BLOCK_SIZE);
	}
	return i;
}

void cache_write(hwaddr_t addr, size_t len,uint32_t data) {
	uint32_t g_num = (addr>>6) & 0x7f; //group number
	uint32_t in_addr = addr & (CACHE_SIZE - 1); // inside addr
	//bool flag = false;
	int i;
	for (i = g_num * WAY_8 ; i < (g_num + 1) * WAY_8 ;i ++){
		if (cache[i].tag == (addr >> 13)&& cache[i].valid){
			if(in_addr + len > CACHE_SIZE) {//across
				dram_write(addr, CACHE_SIZE - in_addr, data);	//write through
				memcpy(cache[i].data + in_addr, &data, CACHE_SIZE - in_addr);
				//writeCache2(addr, CACHE_BLOCK_SIZE - offset, data);//update cache2
				cache_write(addr + CACHE_SIZE - in_addr, len - CACHE_SIZE + in_addr, data >> (CACHE_SIZE - in_addr));
			} 
			else {
				dram_write(addr, len, data);
				memcpy(cache[i].data + in_addr, &data, len);
				//writeCache2(addr, len, data);
			}
			return;
		}
	}
}

