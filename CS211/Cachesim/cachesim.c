#include "cachesim.h"
void prefetchHelper(unsigned long int tagIndex, unsigned long int setIndex, int assoc){	
	int i = 0; int j = 0; int first;
	for (i = 0; i < assoc; i++){
		if (cacheP[setIndex][i].valid == 0) {
			readP++;
			countP++;		
			cacheP[setIndex][i].tag = tagIndex;
			cacheP[setIndex][i].valid = 1;
			cacheP[setIndex][i].linkCount = countP;
			return;
		}	else {
			if (cacheP[setIndex][i].tag == tagIndex) {		
				return;
			} 
			if (i == (assoc-1)){
				readP++;
				 first = 0;			
				for (j = 0; j < assoc; j++) {
					if ((cacheP[setIndex][j].linkCount < cacheP[setIndex][first].linkCount) || (cacheP[setIndex][j].linkCount < cacheP[setIndex][first].linkCount)) {
						first = j;				
					}				
				}
				cacheP[setIndex][first].valid = 1;
				cacheP[setIndex][first].tag = tagIndex;
				countP++;
				cacheP[setIndex][first].linkCount = countP;
				return;
			}
		}
	
	
	}
}

void writePrefetch(unsigned long int tagIndex, unsigned long int setIndex, int assoc, unsigned long int ptagIndex, unsigned long int psetIndex, int marker) {

	int i = 0; int j = 0; int first; 
	for (i = 0; i < assoc; i++) {
		if (cacheP[setIndex][i].valid ==0) {
			writeP++;
			readP++;		
			missP++;
			countP++;
			cacheP[setIndex][i].tag = tagIndex;
			cacheP[setIndex][i].linkCount = countP;
			cacheP[setIndex][i].valid =1;
			prefetchHelper(ptagIndex, psetIndex, assoc);			
			return;		
		}else {
			if (cacheP[setIndex][i].tag == tagIndex) {
				hitP++;			
				writeP++;
				if (marker == 1){
					countP++;
					cacheP[setIndex][i].linkCount=countP;
							
				}
				return;
			}
			if (i == (assoc-1)) {
				missP++;
				readP++;
				writeP++;
				first = 0;
				for (j = 0; j < assoc; j++) {
					if ((cacheP[setIndex][j].linkCount < cacheP[setIndex][first].linkCount) || (cacheP[setIndex][j].linkCount == cacheP[setIndex][first].linkCount) ) {				
						first = j;
					}	
				}	
				cacheP[setIndex][first].valid = 1;
				countP++;
				cacheP[setIndex][first].linkCount = countP;
				cacheP[setIndex][first].tag = tagIndex;
				prefetchHelper(ptagIndex, psetIndex, assoc);				
				return;
			}
		
		}	
	
	}
	return;
}

void readPrefetch(unsigned long int tagIndex, unsigned long int setIndex, int assoc, unsigned long int ptagIndex, unsigned long int psetIndex, int marker) {
		
		int i = 0; int j = 0; int first;
		for (i = 0; i < assoc; i++) {
				if (cacheP[setIndex][i].valid == 0) { 
						countP++;
						readP++;
						missP++;
						cacheP[setIndex][i].linkCount = countP;
						cacheP[setIndex][i].tag = tagIndex; 
						cacheP[setIndex][i].valid = 1; 						
						prefetchHelper(ptagIndex, psetIndex, assoc);
						return;
				}	else {
						if (cacheP[setIndex][i].tag == tagIndex){ 
							if (marker == 1) {
								countP++;
								cacheP[setIndex][i].linkCount = countP;
							} 							
 							hitP++;
							return;						
						}
 						if (i == (assoc-1)) {
 							missP++; 
							readP++; 						
 							first = 0;
 							for (j = 0; j < assoc; j++) {
 								if ((cacheP[setIndex][j].linkCount < cacheP[setIndex][first].linkCount) || (cacheP[setIndex][j].linkCount == cacheP[setIndex][first].linkCount) ) 
 									 first = j; 
 							}
 						countP++;
 						cacheP[setIndex][first].linkCount = countP;
 						cacheP[setIndex][first].tag = tagIndex;
						cacheP[setIndex][first].valid = 1;
						prefetchHelper(ptagIndex, psetIndex, assoc); 						
 						return;
 					}
			}		
	}	
	return;
}

void writeReg(unsigned long int tagIndex, unsigned long int setIndex, int assoc, int marker) {	
	int i = 0; int j = 0; int first; 
	for (i = 0; i < assoc; i++) {
		if (cacheR[setIndex][i].valid ==0) {
			writeR++;
			readR++;
			missR++;
			countR++;
			cacheR[setIndex][i].tag = tagIndex;
			cacheR[setIndex][i].linkCount = countR;
			cacheR[setIndex][i].valid =1;
			return;		
		}else {
			if (cacheR[setIndex][i].tag == tagIndex) {
				hitR++;			
				writeR++;
				
				if (marker == 1){
					countR++;
					cacheR[setIndex][i].linkCount = countR;				
				}
				return;
			}
			if (i == (assoc-1)) { 
				missR++;
				readR++;
				writeR++;
				first = 0;
				for (j = 0; j < assoc; j++) {
					if ((cacheR[setIndex][j].linkCount < cacheR[setIndex][first].linkCount) || (cacheR[setIndex][j].linkCount == cacheR[setIndex][first].linkCount) ) {				
						first = j;
					}	
				}	
				cacheR[setIndex][first].valid = 1; 
				countR++;
				cacheR[setIndex][first].linkCount = countR;
				cacheR[setIndex][first].tag = tagIndex;
				return;
			}
		
		}	
	
	}
	return;
}
void readReg(unsigned long int tagIndex, unsigned long int setIndex, int assoc, int marker) {		
		int i = 0; int j = 0; int first;
		for (i = 0; i < assoc; i++) {
				if (cacheR[setIndex][i].valid == 0) { 
						countR++; 
						readR++;
						missR++; 
						cacheR[setIndex][i].linkCount = countR;
						cacheR[setIndex][i].tag = tagIndex; 
						cacheR[setIndex][i].valid = 1; 
						return;
				}else{ 
						if (cacheR[setIndex][i].tag == tagIndex){ 
 							hitR++;
							if (marker == 1) {
							countR++;
							cacheR[setIndex][i].linkCount = countR;
							}							
							return;						
						}
 						if (i == (assoc-1)) {
  							missR++; 
				 			readR++; 						
 							first = 0;
 							for (j = 0; j < assoc; j++) {
 								if ((cacheR[setIndex][j].linkCount < cacheR[setIndex][first].linkCount) || (cacheR[setIndex][j].linkCount == cacheR[setIndex][first].linkCount) ) {
 									 first = j; 
								} 							
 							}
 						countR++; 
 						cacheR[setIndex][first].linkCount = countR;
 						cacheR[setIndex][first].tag = tagIndex;
						cacheR[setIndex][first].valid = 1;
 						return;
 					}
			}
	}
return;
}	


int main (int argc, char* argv[]) {
	readR = 0; writeR = 0; hitR = 0; missR = 0; countR = 0;
	readP = 0; writeP = 0; hitP = 0; missP = 0; countP = 0;
	int bbits;
	int sbits;
	char type;
	unsigned long int address; unsigned long int paddress;
	unsigned long int tagIndex; unsigned long int ptagIndex;
	unsigned long int setIndex; unsigned long int psetIndex;

	if (argc != 6) {
		return 0;
	}
	FILE * file = fopen(argv[5], "r");
	if (file == NULL) {
		return 0;
	}
	int cacheSize = atoi(argv[1]);
	int blockSize = atoi(argv[4]);
	if (!powerOfTwo(cacheSize)){	
		return 0;	
	}
	if (!powerOfTwo(blockSize)){
		return 0;	
	}
	int assoc = 0; int sets = 0;
	 if (strcmp(argv[2], "direct") == 0) {
		assoc = 1;
		sets = atoi(argv[1]) / atoi(argv[4]);
	} else if (strcmp(argv[2], "assoc") == 0) {
		assoc = atoi(argv[1]) / atoi(argv[4]);	
		sets = 1;
	}else {
		assoc = atoi(&argv[2][6]);
		if (!powerOfTwo(assoc)) {
			return 0;
		}
		sets = atoi(argv[1]) / (assoc * atoi(argv[4]));
		
	}

	int i = 0; int j = 0;
	cacheP =(cBlock**)malloc(sets* sizeof(cBlock*));

	for (i = 0; i < sets; i ++) {
			cacheP[i]=(cBlock*)malloc((assoc)*sizeof(cBlock));
	}	
	for (i = 0; i < sets; i ++) {
		for (j = 0; j < assoc; j++) {
			cacheP[i][j].valid = 0;
		}
	}
	
	cacheR = (cBlock**) malloc ((sets) * sizeof(cBlock*));
	for (i = 0; i < sets; i ++) {
			cacheR[i]=(cBlock*)malloc((assoc) * sizeof(cBlock));
	}	
	for (i = 0; i < sets; i ++) {
		for (j = 0; j < assoc; j++) {
			cacheR[i][j].valid = 0;
		}
	}
	
	bbits = (log(atoi(argv[4])) / log(2)); 
	sbits = log(sets) / log(2);



	while (fscanf (file, "%*x: %c %lx", &type, &address) == 2) {
		tagIndex = address >> (sbits + bbits);
		setIndex = (address >> bbits) % ((int) power(2, sbits));	
		
				
		paddress = address + atoi(argv[4]);
		psetIndex = (paddress >> bbits) % ((int) power(2, sbits));		
		ptagIndex = paddress >> (bbits+sbits);

		if((strcmp(argv[3], "fifo") == 0)) {
			if (type == 'W') {
				writeReg(tagIndex, setIndex, assoc, 0); 
				writePrefetch(tagIndex, setIndex, assoc, ptagIndex, psetIndex, 0);
			} else if (type == 'R') {
				readReg(tagIndex, setIndex, assoc, 0);
				readPrefetch(tagIndex, setIndex, assoc, ptagIndex, psetIndex, 0);
			}
	
		} 
		else if ((strcmp(argv[3], "lru") == 0)) {
			if (type == 'W') {
				writeReg(tagIndex, setIndex, assoc, 1);
				writePrefetch(tagIndex, setIndex, assoc, ptagIndex, psetIndex, 1);
			} else if (type == 'W') {
				readReg(tagIndex, setIndex, assoc, 1);
				readPrefetch(tagIndex, setIndex, assoc, ptagIndex, psetIndex, 1);
			}
		}
		
	
 	}
	printf("Prefetch 0\n");
 	printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n", readR, writeR, hitR, missR);
	for (i = 0; i < sets; i++) {
		for (j = 0; j < assoc; j++) {
			cacheR[i][j].tag = 0;
			cacheR[i][j].valid = 0;
			cacheR[i][j].linkCount = 0;
		}
	}	
	readR = 0; writeR = 0; hitR = 0; missR = 0; countR = 0;

	printf("Prefetch 1\n");
 	printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n", readP, writeP, hitP, missP);	
	for (i = 0; i < sets; i++) {
		for (j = 0; j < assoc; j++) {
			cacheP[i][j].tag = 0;
			cacheP[i][j].valid = 0;
			cacheP[i][j].linkCount = 0;
		}
	}
	readP = 0; writeP = 0; hitP = 0; missP = 0; countP = 0;

return 0;
}