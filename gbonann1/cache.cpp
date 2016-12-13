#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<vector>



unsigned long long addr;
char behavior[10];
int total = 0;
int directMapped1 = 0;
int directMapped4 = 0;
int directMapped16 = 0;
int directMapped32 = 0;
unsigned long long directMappedCache1[32];
unsigned long long directMappedCache4[128];
unsigned long long directMappedCache16[512];
unsigned long long directMappedCache32[1024];
int setAsso2 = 0;
int setAsso4 = 0;
int setAsso8 = 0;
int setAsso16 = 0;
std::vector<std::vector<long>> setAssoCache2 (256, std::vector<long> (2, -1));
std::vector<std::vector<long>> setAssoCache4 (128, std::vector<long> (4, -1));
std::vector<std::vector<long>> setAssoCache8 (64, std::vector<long> (8, -1));
std::vector<std::vector<long>> setAssoCache16 (32, std::vector<long> (16, -1));
int fullAsso = 0;
int fullAssoHC = 0;
std::vector<long> fullAssoCache(512, -1);
std::vector<long> fullAssoHCCache(512, -1);
int noAlloc2 = 0;
int noAlloc4 = 0;
int noAlloc8 = 0;
int noAlloc16 = 0;
std::vector<std::vector<long>> noAllocCache2 (256, std::vector<long> (2, -1));
std::vector<std::vector<long>> noAllocCache4 (128, std::vector<long> (4, -1));
std::vector<std::vector<long>> noAllocCache8 (64, std::vector<long> (8, -1));
std::vector<std::vector<long>> noAllocCache16 (32, std::vector<long> (16, -1));
int prefetch2 = 0;
int prefetch4 = 0;
int prefetch8 = 0;
int prefetch16 = 0;
std::vector<std::vector<long>> prefetchCache2 (256, std::vector<long> (2, -1));
std::vector<std::vector<long>> prefetchCache4 (128, std::vector<long> (4, -1));
std::vector<std::vector<long>> prefetchCache8 (64, std::vector<long> (8, -1));
std::vector<std::vector<long>> prefetchCache16 (32, std::vector<long> (16, -1));
int prefetchMiss2 = 0;
int prefetchMiss4 = 0;
int prefetchMiss8 = 0;
int prefetchMiss16 = 0;
std::vector<std::vector<long>> prefetchMissCache2 (256, std::vector<long> (2, -1));
std::vector<std::vector<long>> prefetchMissCache4 (128, std::vector<long> (4, -1));
std::vector<std::vector<long>> prefetchMissCache8 (64, std::vector<long> (8, -1));
std::vector<std::vector<long>> prefetchMissCache16 (32, std::vector<long> (16, -1));
int extraCred = 0;
std::vector<std::vector<long>> extraCredCache (64, std::vector<long> (16, -1));



void directMapped(){
	unsigned long long block = (addr/32);
	if (directMappedCache1[block%32] == block){
		directMapped1++;
	}
	directMappedCache1[block%32] = block;

	if (directMappedCache4[block%128] == block){
		directMapped4++;
	}
	directMappedCache4[block%128] = block;

	if (directMappedCache16[block%512] == block){
		directMapped16++;
	}
	directMappedCache16[block%512] = block;

	if (directMappedCache32[block%1024] == block){
		directMapped32++;
	}
	directMappedCache32[block%1024] = block;
	
}

void setAssociative(){
	//vector to implement LRU replacement
	int block = (addr/32);
	if (setAssoCache2[block%256].front() == block || setAssoCache2[block%256].back() == block){
		setAsso2++;	
	}
	if (setAssoCache2[block%256].back() != block){
		setAssoCache2[block%256].erase(setAssoCache2[block%256].begin());
		setAssoCache2[block%256].push_back(block);
	}


	if (setAssoCache4[block%128][0] == block){
		setAsso4++;
		setAssoCache4[block%128].erase(setAssoCache4[block%128].begin());
		setAssoCache4[block%128].push_back(block);
	}
	else if (setAssoCache4[block%128][1] == block){
		setAsso4++;
		setAssoCache4[block%128].erase(setAssoCache4[block%128].begin() + 1);
		setAssoCache4[block%128].push_back(block);
	}
	else if (setAssoCache4[block%128][2] == block){
		setAsso4++;
		setAssoCache4[block%128].erase(setAssoCache4[block%128].begin() + 2);
		setAssoCache4[block%128].push_back(block);
	}
	else if (setAssoCache4[block%128][3] == block){
		setAsso4++;
	}

	else {
		setAssoCache4[block%128].erase(setAssoCache4[block%128].begin());
		setAssoCache4[block%128].push_back(block);
	}

	if (setAssoCache8[block%64][0] == block){
		setAsso8++;
		setAssoCache8[block%64].erase(setAssoCache8[block%64].begin());
		setAssoCache8[block%64].push_back(block);
	}
	else if (setAssoCache8[block%64][1] == block){
		setAsso8++;
		setAssoCache8[block%64].erase(setAssoCache8[block%64].begin() + 1);
		setAssoCache8[block%64].push_back(block);
	}
	else if (setAssoCache8[block%64][2] == block){
		setAsso8++;
		setAssoCache8[block%64].erase(setAssoCache8[block%64].begin() + 2);
		setAssoCache8[block%64].push_back(block);
	}
	else if (setAssoCache8[block%64][3] == block){
		setAsso8++;
		setAssoCache8[block%64].erase(setAssoCache8[block%64].begin() + 3);
		setAssoCache8[block%64].push_back(block);
	
	}
	else if (setAssoCache8[block%64][4] == block){
		setAsso8++;
		setAssoCache8[block%64].erase(setAssoCache8[block%64].begin() + 4);
		setAssoCache8[block%64].push_back(block);
	}
	else if (setAssoCache8[block%64][5] == block){
		setAsso8++;
		setAssoCache8[block%64].erase(setAssoCache8[block%64].begin() + 5);
		setAssoCache8[block%64].push_back(block);
	}
	else if (setAssoCache8[block%64][6] == block){
		setAsso8++;
		setAssoCache8[block%64].erase(setAssoCache8[block%64].begin() + 6);
		setAssoCache8[block%64].push_back(block);

	}
	else if (setAssoCache8[block%64][7] == block){
		setAsso8++;
		setAssoCache8[block%64].erase(setAssoCache8[block%64].begin() + 7);
		setAssoCache8[block%64].push_back(block);
	}
	
	else {
		setAssoCache8[block%64].erase(setAssoCache8[block%64].begin());
		setAssoCache8[block%64].push_back(block);
	}

	if (setAssoCache16[block%32][0] == block){
		setAsso16++;
		setAssoCache16[block%32].erase(setAssoCache16[block%32].begin());
		setAssoCache16[block%32].push_back(block);
	}
	else if (setAssoCache16[block%32][1] == block){
		setAsso16++;
		setAssoCache16[block%32].erase(setAssoCache16[block%32].begin() + 1);
		setAssoCache16[block%32].push_back(block);
	}
	else if (setAssoCache16[block%32][2] == block){
		setAsso16++;
		setAssoCache16[block%32].erase(setAssoCache16[block%32].begin() + 2);
		setAssoCache16[block%32].push_back(block);
	}
	else if (setAssoCache16[block%32][3] == block){
		setAsso16++;
		setAssoCache16[block%32].erase(setAssoCache16[block%32].begin() + 3);
		setAssoCache16[block%32].push_back(block);
	
	}
	else if (setAssoCache16[block%32][4] == block){
		setAsso16++;
		setAssoCache16[block%32].erase(setAssoCache16[block%32].begin() + 4);
		setAssoCache16[block%32].push_back(block);
	}
	else if (setAssoCache16[block%32][5] == block){
		setAsso16++;
		setAssoCache16[block%32].erase(setAssoCache16[block%32].begin() + 5);
		setAssoCache16[block%32].push_back(block);
	}
	else if (setAssoCache16[block%32][6] == block){
		setAsso16++;
		setAssoCache16[block%32].erase(setAssoCache16[block%32].begin() + 6);
		setAssoCache16[block%32].push_back(block);

	}
	else if (setAssoCache16[block%32][7] == block){
		setAsso16++;
		setAssoCache16[block%32].erase(setAssoCache16[block%32].begin() + 7);
		setAssoCache16[block%32].push_back(block);
	}
	else if (setAssoCache16[block%32][8] == block){
		setAsso16++;
		setAssoCache16[block%32].erase(setAssoCache16[block%32].begin() + 8);
		setAssoCache16[block%32].push_back(block);
	}
	else if (setAssoCache16[block%32][9] == block){
		setAsso16++;
		setAssoCache16[block%32].erase(setAssoCache16[block%32].begin() + 9);
		setAssoCache16[block%32].push_back(block);
	}
	else if (setAssoCache16[block%32][10] == block){
		setAsso16++;
		setAssoCache16[block%32].erase(setAssoCache16[block%32].begin() + 10);
		setAssoCache16[block%32].push_back(block);
	
	}
	else if (setAssoCache16[block%32][11] == block){
		setAsso16++;
		setAssoCache16[block%32].erase(setAssoCache16[block%32].begin() + 11);
		setAssoCache16[block%32].push_back(block);
	}
	else if (setAssoCache16[block%32][12] == block){
		setAsso16++;
		setAssoCache16[block%32].erase(setAssoCache16[block%32].begin() + 12);
		setAssoCache16[block%32].push_back(block);
	}
	else if (setAssoCache16[block%32][13] == block){
		setAsso16++;
		setAssoCache16[block%32].erase(setAssoCache16[block%32].begin() + 13);
		setAssoCache16[block%32].push_back(block);

	}
	else if (setAssoCache16[block%32][14] == block){
		setAsso16++;
		setAssoCache16[block%32].erase(setAssoCache16[block%32].begin() + 14);
		setAssoCache16[block%32].push_back(block);
	}
	else if (setAssoCache16[block%32][15] == block){
		setAsso16++;
		setAssoCache16[block%32].erase(setAssoCache16[block%32].begin() + 15);
		setAssoCache16[block%32].push_back(block);
	}
	
	else {
		setAssoCache16[block%32].erase(setAssoCache16[block%32].begin());
		setAssoCache16[block%32].push_back(block);
	}
		
}

void fullAssociative(){
	int block = (addr/32);
	int found = 0;
	for (int i = fullAssoCache.size() - 1; i > -1; i--){
		if (block == fullAssoCache[i]){
			fullAsso++;
			fullAssoCache.erase(fullAssoCache.begin() + i);
			fullAssoCache.push_back(block);
			found = 1;
			break;
		}		
	}
	if (!found){
		fullAssoCache.erase(fullAssoCache.begin());
		fullAssoCache.push_back(block);
	}

	for (int i = fullAssoHCCache.size() - 1; i > -1; i--){
		if (block == fullAssoHCCache[i]){
			fullAssoHC++;
			fullAssoHCCache.erase(fullAssoHCCache.begin() + i);
			fullAssoHCCache.push_back(block);
			found = 1;
			break;
		}		
	}
	if (!found){
		fullAssoHCCache.erase(fullAssoHCCache.begin() + 7);
		fullAssoHCCache.push_back(block);
	}
	
	
	
	
}

void setAssociativeNoAlloc(){
	bool found = false;
	int block = (addr/32);
	if (noAllocCache2[block%256].front() == block || noAllocCache2[block%256].back() == block){
		noAlloc2++;
		found = true;	
	}
	if (strcmp(behavior, "S") == 0 && !found){
	}
	else if (block == noAllocCache2[block%256].back()){
	}
	else {
		noAllocCache2[block%256].erase(noAllocCache2[block%256].begin());
		noAllocCache2[block%256].push_back(block);
	}

	if (noAllocCache4[block%128][0] == block){
		noAlloc4++;
		noAllocCache4[block%128].erase(noAllocCache4[block%128].begin());
		noAllocCache4[block%128].push_back(block);
	}
	else if (noAllocCache4[block%128][1] == block){
		noAlloc4++;
		noAllocCache4[block%128].erase(noAllocCache4[block%128].begin() + 1);
		noAllocCache4[block%128].push_back(block);
	}
	else if (noAllocCache4[block%128][2] == block){
		noAlloc4++;
		noAllocCache4[block%128].erase(noAllocCache4[block%128].begin() + 2);
		noAllocCache4[block%128].push_back(block);
	}
	else if (noAllocCache4[block%128][3] == block){
		noAlloc4++;
	}

	else {
		if (strcmp(behavior, "S") != 0){
			noAllocCache4[block%128].erase(noAllocCache4[block%128].begin());
			noAllocCache4[block%128].push_back(block);
		}
	}

	if (noAllocCache8[block%64][0] == block){
		noAlloc8++;
		noAllocCache8[block%64].erase(noAllocCache8[block%64].begin());
		noAllocCache8[block%64].push_back(block);
	}
	else if (noAllocCache8[block%64][1] == block){
		noAlloc8++;
		noAllocCache8[block%64].erase(noAllocCache8[block%64].begin() + 1);
		noAllocCache8[block%64].push_back(block);
	}
	else if (noAllocCache8[block%64][2] == block){
		noAlloc8++;
		noAllocCache8[block%64].erase(noAllocCache8[block%64].begin() + 2);
		noAllocCache8[block%64].push_back(block);
	}
	else if (noAllocCache8[block%64][3] == block){
		noAlloc8++;
		noAllocCache8[block%64].erase(noAllocCache8[block%64].begin() + 3);
		noAllocCache8[block%64].push_back(block);
	
	}
	else if (noAllocCache8[block%64][4] == block){
		noAlloc8++;
		noAllocCache8[block%64].erase(noAllocCache8[block%64].begin() + 4);
		noAllocCache8[block%64].push_back(block);
	}
	else if (noAllocCache8[block%64][5] == block){
		noAlloc8++;
		noAllocCache8[block%64].erase(noAllocCache8[block%64].begin() + 5);
		noAllocCache8[block%64].push_back(block);
	}
	else if (noAllocCache8[block%64][6] == block){
		noAlloc8++;
		noAllocCache8[block%64].erase(noAllocCache8[block%64].begin() + 6);
		noAllocCache8[block%64].push_back(block);

	}
	else if (noAllocCache8[block%64][7] == block){
		noAlloc8++;
		noAllocCache8[block%64].erase(noAllocCache8[block%64].begin() + 7);
		noAllocCache8[block%64].push_back(block);
	}
	
	else {
		if (strcmp(behavior, "S") != 0){
			noAllocCache8[block%64].erase(noAllocCache8[block%64].begin());
			noAllocCache8[block%64].push_back(block);
		}
	}

	if (noAllocCache16[block%32][0] == block){
		noAlloc16++;
		noAllocCache16[block%32].erase(noAllocCache16[block%32].begin());
		noAllocCache16[block%32].push_back(block);
	}
	else if (noAllocCache16[block%32][1] == block){
		noAlloc16++;
		noAllocCache16[block%32].erase(noAllocCache16[block%32].begin() + 1);
		noAllocCache16[block%32].push_back(block);
	}
	else if (noAllocCache16[block%32][2] == block){
		noAlloc16++;
		noAllocCache16[block%32].erase(noAllocCache16[block%32].begin() + 2);
		noAllocCache16[block%32].push_back(block);
	}
	else if (noAllocCache16[block%32][3] == block){
		noAlloc16++;
		noAllocCache16[block%32].erase(noAllocCache16[block%32].begin() + 3);
		noAllocCache16[block%32].push_back(block);
	
	}
	else if (noAllocCache16[block%32][4] == block){
		noAlloc16++;
		noAllocCache16[block%32].erase(noAllocCache16[block%32].begin() + 4);
		noAllocCache16[block%32].push_back(block);
	}
	else if (noAllocCache16[block%32][5] == block){
		noAlloc16++;
		noAllocCache16[block%32].erase(noAllocCache16[block%32].begin() + 5);
		noAllocCache16[block%32].push_back(block);
	}
	else if (noAllocCache16[block%32][6] == block){
		noAlloc16++;
		noAllocCache16[block%32].erase(noAllocCache16[block%32].begin() + 6);
		noAllocCache16[block%32].push_back(block);

	}
	else if (noAllocCache16[block%32][7] == block){
		noAlloc16++;
		noAllocCache16[block%32].erase(noAllocCache16[block%32].begin() + 7);
		noAllocCache16[block%32].push_back(block);
	}
	else if (noAllocCache16[block%32][8] == block){
		noAlloc16++;
		noAllocCache16[block%32].erase(noAllocCache16[block%32].begin() + 8);
		noAllocCache16[block%32].push_back(block);
	}
	else if (noAllocCache16[block%32][9] == block){
		noAlloc16++;
		noAllocCache16[block%32].erase(noAllocCache16[block%32].begin() + 9);
		noAllocCache16[block%32].push_back(block);
	}
	else if (noAllocCache16[block%32][10] == block){
		noAlloc16++;
		noAllocCache16[block%32].erase(noAllocCache16[block%32].begin() + 10);
		noAllocCache16[block%32].push_back(block);
	
	}
	else if (noAllocCache16[block%32][11] == block){
		noAlloc16++;
		noAllocCache16[block%32].erase(noAllocCache16[block%32].begin() + 11);
		noAllocCache16[block%32].push_back(block);
	}
	else if (noAllocCache16[block%32][12] == block){
		noAlloc16++;
		noAllocCache16[block%32].erase(noAllocCache16[block%32].begin() + 12);
		noAllocCache16[block%32].push_back(block);
	}
	else if (noAllocCache16[block%32][13] == block){
		noAlloc16++;
		noAllocCache16[block%32].erase(noAllocCache16[block%32].begin() + 13);
		noAllocCache16[block%32].push_back(block);

	}
	else if (noAllocCache16[block%32][14] == block){
		noAlloc16++;
		noAllocCache16[block%32].erase(noAllocCache16[block%32].begin() + 14);
		noAllocCache16[block%32].push_back(block);
	}
	else if (noAllocCache16[block%32][15] == block){
		noAlloc16++;
		noAllocCache16[block%32].erase(noAllocCache16[block%32].begin() + 15);
		noAllocCache16[block%32].push_back(block);
	}
	
	else {
		
		if (strcmp(behavior, "S") != 0){
			noAllocCache16[block%32].erase(noAllocCache16[block%32].begin());
			noAllocCache16[block%32].push_back(block);
		}
	}
}

void setAssociativePrefetch(){
	int block = (addr/32);
	int block2 = (block + 1);
	int val1 = 0;
	int val2 = 0;
	int i;
	for (i = 0; i < 2; i++){
		if (block == prefetchCache2[block%256][i]){
			prefetch2++;
			val1 = i;
		}
		if (block2 == prefetchCache2[block2%256][i]){
			val2 = i;
		}		
	}
	prefetchCache2[block%256].erase(prefetchCache2[block%256].begin() + val1);
	prefetchCache2[block%256].push_back(block);
	prefetchCache2[block2%256].erase(prefetchCache2[block2%256].begin() + val2);
	prefetchCache2[block2%256].push_back(block2);
	
	val1 = 0;
	val2 = 0;
	for (i = 0; i < 4; i++){
		if (block == prefetchCache4[block%128][i]){
			prefetch4++;
			val1 = i;
		}
		if (block2 == prefetchCache4[block2%128][i]){
			val2 = i;
		}		
	}
	prefetchCache4[block%128].erase(prefetchCache4[block%128].begin() + val1);
	prefetchCache4[block%128].push_back(block);
	prefetchCache4[block2%128].erase(prefetchCache4[block2%128].begin() + val2);
	prefetchCache4[block2%128].push_back(block2);

	val1 = 0;
	val2 = 0;
	for (i = 0; i < 8; i++){
		if (block == prefetchCache8[block%64][i]){
			prefetch8++;
			val1 = i;
		}
		if (block2 == prefetchCache8[block2%64][i]){
			val2 = i;
		}		
	}
	prefetchCache8[block%64].erase(prefetchCache8[block%64].begin() + val1);
	prefetchCache8[block%64].push_back(block);
	prefetchCache8[block2%64].erase(prefetchCache8[block2%64].begin() + val2);
	prefetchCache8[block2%64].push_back(block2);

	val1 = 0;
	val2 = 0;
	for (i = 0; i < 16; i++){
		if (block == prefetchCache16[block%32][i]){
			prefetch16++;
			val1 = i;
		}
		if (block2 == prefetchCache16[block2%32][i]){
			val2 = i;
		}		
	}
	prefetchCache16[block%32].erase(prefetchCache16[block%32].begin() + val1);
	prefetchCache16[block%32].push_back(block);
	prefetchCache16[block2%32].erase(prefetchCache16[block2%32].begin() + val2);
	prefetchCache16[block2%32].push_back(block2);
	

}

void prefetchOnMiss(){

	int block = (addr/32);
	int block2 = (block + 1);
	int val1 = 0;
	int val2 = 0;
	int i;
	bool found = false;
	for (i = 0; i < 2; i++){
		if (block == prefetchMissCache2[block%256][i]){
			prefetchMiss2++;
			val1 = i;
			found = true;
		}
		if (block2 == prefetchMissCache2[block2%256][i]){
			val2 = i;
		}		
	}
	prefetchMissCache2[block%256].erase(prefetchMissCache2[block%256].begin() + val1);
	prefetchMissCache2[block%256].push_back(block);
	if (!found) {
		prefetchMissCache2[block2%256].erase(prefetchMissCache2[block2%256].begin() + val2);
		prefetchMissCache2[block2%256].push_back(block2);
	}
	
	val1 = 0;
	val2 = 0;
	found = false;
	for (i = 0; i < 4; i++){
		if (block == prefetchMissCache4[block%128][i]){
			prefetchMiss4++;
			val1 = i;
			found = true;
		}
		if (block2 == prefetchMissCache4[block2%128][i]){
			val2 = i;
		}		
	}
	prefetchMissCache4[block%128].erase(prefetchMissCache4[block%128].begin() + val1);
	prefetchMissCache4[block%128].push_back(block);
	if (!found) {
		prefetchMissCache4[block2%128].erase(prefetchMissCache4[block2%128].begin() + val2);
		prefetchMissCache4[block2%128].push_back(block2);
	}

	val1 = 0;
	val2 = 0;
	found = false;
	for (i = 0; i < 8; i++){
		if (block == prefetchMissCache8[block%64][i]){
			prefetchMiss8++;
			val1 = i;
			found = true;
		}
		if (block2 == prefetchMissCache8[block2%64][i]){
			val2 = i;
		}		
	}
	prefetchMissCache8[block%64].erase(prefetchMissCache8[block%64].begin() + val1);
	prefetchMissCache8[block%64].push_back(block);
	if (!found) {
		prefetchMissCache8[block2%64].erase(prefetchMissCache8[block2%64].begin() + val2);
		prefetchMissCache8[block2%64].push_back(block2);
	}

	val1 = 0;
	val2 = 0;
	found = false;
	for (i = 0; i < 16; i++){
		if (block == prefetchMissCache16[block%32][i]){
			prefetchMiss16++;
			val1 = i;
			found = true;
		}
		if (block2 == prefetchMissCache16[block2%32][i]){
			val2 = i;
		}		
	}
	prefetchMissCache16[block%32].erase(prefetchMissCache16[block%32].begin() + val1);
	prefetchMissCache16[block%32].push_back(block);
	if (!found) {
		prefetchMissCache16[block2%32].erase(prefetchMissCache16[block2%32].begin() + val2);
		prefetchMissCache16[block2%32].push_back(block2);
	}	
}

void extraCredit(){
	//prefetch on miss, 32KB cache, 16 ways, 64 sets, line size 32 bytes
	int block = (addr/32);
	int block2 = (block + 1);
	int val1 = 0;
	int val2 = 0;
	int i;
	bool found = false;
	for (i = 0; i < 64; i++){
		if (block == extraCredCache[block%64][i]){
			extraCred++;
			val1 = i;
			found = true;
		}
		if (block2 == extraCredCache[block2%64][i]){
			val2 = i;
		}		
	}
	extraCredCache[block%64].erase(extraCredCache[block%64].begin() + val1);
	extraCredCache[block%64].push_back(block);
	if (!found) {
		extraCredCache[block2%64].erase(extraCredCache[block2%64].begin() + val2);
		extraCredCache[block2%64].push_back(block2);
	}
}

int main(int argc, char *argv[]) {

  	// Open file for reading
	FILE *input = fopen(argv[1], "r");
	FILE *output = fopen("output.txt", "w");

  	// The following loop will read a hexadecimal number and
 	// a string each time and then output them
 	while(fscanf(input, " %10s %llx\n" ,behavior, &addr) != EOF) {
  		//if(!strncmp(behavior, "T", 2)) {
      			//printf("%lld -> taken\n", addr);
		total++;
		directMapped();
		setAssociative();
		fullAssociative();
		setAssociativeNoAlloc();
		setAssociativePrefetch();
		prefetchOnMiss();
		extraCredit();
 	}
	fprintf(output, "%d,%d; %d,%d; %d,%d; %d,%d;\n", directMapped1, total, directMapped4, total, directMapped16, total, directMapped32, total);
	fprintf(output, "%d,%d; %d,%d; %d,%d; %d,%d;\n" ,setAsso2, total, setAsso4, total ,setAsso8, total, setAsso16, total);
	fprintf(output, "%d,%d;\n", fullAsso, total);
	fprintf(output, "%d,%d;\n", fullAssoHC, total);
	fprintf(output, "%d,%d; %d,%d; %d,%d; %d,%d;\n", noAlloc2, total, noAlloc4, total, noAlloc8, total, noAlloc16, total);
	fprintf(output, "%d,%d; %d,%d; %d,%d; %d,%d;\n", prefetch2, total, prefetch4, total, prefetch8, total, prefetch16, total);
	fprintf(output, "%d,%d; %d,%d; %d,%d; %d,%d;\n", prefetchMiss2, total, prefetchMiss4, total, prefetchMiss8, total, prefetchMiss16, total);
	fprintf(output, "%d,%d;", extraCred, total);
	
	
	fclose(output);

	return 0;
}
