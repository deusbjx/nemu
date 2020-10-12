#ifndef __CACHE_H__
#define __CACHE_H_

#define CACHE_SIZE 64 //64b
#define CACHE_BLOCK_SIZE 64*1024 //64kb
#define WAY_8 8 //8-way set associative

#define CACHE2_BLOCK_SIZE_BIT 6
#define CACHE2_WAY_BIT 4
#define CACHE2_SET_BIT 12
#define CACHE2_BLOCK_SIZE (1 << CACHE2_BLOCK_SIZE_BIT)
#define CACHE2_WAY_SIZE (1 << CACHE2_WAY_BIT)
#define CACHE2_SET_SIZE (1 << CACHE2_SET_BIT)

//uint64_t MEMORY_TIME;

typedef struct {
	bool valid; //valid bit
	int tag;
	uint8_t data[CACHE_SIZE];
}Cache;

/*typedef struct {
	uint8_t data[CACHE2_BLOCK_SIZE];
	int tag;
	bool valid, dirty;
} CacheBlock2;*/

Cache cache[CACHE_BLOCK_SIZE/CACHE_SIZE];
//CacheBlock2 cache2[CACHE2_SET_SIZE * CACHE2_WAY_SIZE];

void init_cache();
int cache_read(hwaddr_t addr);
void cache_write(hwaddr_t addr, size_t len, uint32_t data);
//void addMemoryTime(uint32_t t);
//int readCache2(hwaddr_t addr);
//void writeCache2(hwaddr_t addr, size_t len, uint32_t data);

#endif
