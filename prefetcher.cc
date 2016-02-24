/*
 * A sample prefetcher which does sequential one-block lookahead.
 * This means that the prefetcher fetches the next block _after_ the one that
 * was just accessed. It also ignores requests to blocks already in the cache.
 */

#include "interface.hh"

int W = 1;
int Th = 1;
int L = 0;
double acc = (double)Th/W;
void prefetch_init(void)
{
    /* Called before any calls to prefetch_access. */
    /* This is the place to initialize data structures. */
    DPRINTF(HWPrefetch, "Initialized sequential-on-access prefetcher\n");
}

void prefetch_access(AccessStat stat)
{
    /* pf_addr is now an address within the _next_ cache block */
    Addr pf_addr = stat.mem_addr;
    int hits = 0;
    //Addr pf_addr1 = stat.mem_addr + delta + BLOCK_SIZE;
    for (int i = 0; i < W; i++){
        Addr pf_addr1 = pf_addr + i*BLOCK_SIZE;
        stat.mem_addr = pf_addr1;
	int hit = stat.miss;
        if (!hit){
		if(get_prefetch_bit(pf_addr1)){hits++;}
		}
	}

    /*
     * Issue a prefetch request if a demand miss occured,
     * and the block is not already in cache.
     */
    stat.mem_addr = pf_addr;
    for (int i = 0; i < W; i++){
        Addr pf_addr2= pf_addr + i*BLOCK_SIZE;
        stat.mem_addr = pf_addr2;
    	if (stat.miss && !in_cache(pf_addr + i*BLOCK_SIZE)) {
        	issue_prefetch(pf_addr + i*BLOCK_SIZE);
        	set_prefetch_bit(pf_addr + i*BLOCK_SIZE);

    		}
	}
    double pfacc = (double)hits/W;
    if (pfacc < acc && W > 1){W--; Th--;}
    else {W++; Th = W-1;}
    if (W == 1){Th = 1;}
}

void prefetch_complete(Addr addr) {
    /*
     * Called when a block requested by the prefetcher has been loaded.
     */
}
