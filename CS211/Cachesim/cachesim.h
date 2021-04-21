  
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


int readR; 
int writeR; 
int hitR;
int missR;
unsigned long int countR;

int readP;
int writeP;
int hitP; 
int missP;
unsigned long int countP; 

struct cBlock** cacheR; 
struct cBlock** cacheP; 

typedef struct cBlock{
	int valid; 
	unsigned long int tag;
	unsigned long int linkCount;
}cBlock;

bool powerOfTwo(int x);
void prefetchHelper(unsigned long int tagIndex, unsigned long int setIndex, int assoc);
void writePrefetch(unsigned long int tagIndex, unsigned long int setIndex, int assoc, unsigned long int ptagIndex, unsigned long int psetIndex, int marker);//prefetch read
void readPrefetch(unsigned long int tagIndex, unsigned long int setIndex, int assoc, unsigned long int ptagIndex, unsigned long int psetIndex, int marker);//prefetch write
void writeReg(unsigned long int tagIndex, unsigned long int setIndex, int assoc, int marker);
void readReg(unsigned long int tagIndex, unsigned long int setIndex, int assoc, int marker);


int power(int base, int exp)
    {
      if(exp < 0)
        return -1;

        int result = 1;
        while (exp)
        {
            if (exp & 1)
                result *= base;
            exp >>= 1;
            base *= base;
        }

        return result;
    }
bool powerOfTwo(int n) {
  if (n == 0) 
    return 0; 
  while (n != 1) 
  { 
      if (n%2 != 0) 
         return 0; 
      n = n/2; 
  } 
  return 1; 
} 
