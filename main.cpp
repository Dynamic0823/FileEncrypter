#include <stdio.h>
#include <stdint.h>

static uint8_t ip[] = {58,50,42,34,26,18,10,2 ,
		       60,52,44,36,28,20,12,4 ,
		       62,54,46,38,30,22,14,6 ,
		       64,56,48,40,32,24,16,8 ,
		       57,49,41,33,25,17, 9,1 ,
		       59,51,43,35,27,19,11,3 ,
		       61,53,45,37,29,21,13,5 ,
		       63,55,47,39,31,23,15,7 };

static uint8_t up[] = {40, 8,48,16,56,24,64,32,
		       39, 7,47,15,55,23,63,31,
		       38, 6,46,14,54,22,62,30,
		       37, 5,45,13,53,21,61,29,
		       36, 4,44,12,52,20,60,28,
		       35, 3,43,11,51,19,59,27,
		       34, 2,42,10,50,18,58,26,
		       33, 1,41, 9,49,17,57,25};

static uint8_t shift[] = {1, 1, 2, 2,
			  2, 2, 2, 2,
			  1, 2, 2, 2,
			  2, 2, 2, 1 };

void keyPermute(uint64_t pKey, uint64_t *pNewKey){
  uint8_t portion;
  *pNewKey = 0;
  for(uint8_t c = 0; c<8; c++){
    portion = (uint8_t)(pKey >> 8*c) & ~(0x80);
    *pNewKey |= ((uint64_t)portion) << (7*c);
  }
}

void permute(uint64_t pInput, const uint8_t *pPermutationTable, uint64_t *pOutput, uint8_t pSize){
  for(uint8_t c=0; c<pSize; c++){
    if(pInput & (((uint64_t)1)) << (pPermutationTable[c]-1)){
      *pOutput |= ((uint64_t)1) << c;
    }
  }
}

//0x3ffffff

void shift_key(uint32_t *pKey, uint8_t pShifts){
  uint8_t shifted;
  uint32_t data = *pKey;
  shifted = (uint8_t)((data)>>(28-pShifts));
  data = data << pShifts;
  data |= shifted;
  data &= 0xfffffff;
  *pKey = data;
}

int main(){
  uint64_t plaintext = 0x0303010101010303;
  uint64_t iptext=0;
  uint64_t key=0xc0c0c0c0c0c0c0c0;
  uint64_t pkey=0;
  uint64_t unpermute=0;
  uint64_t round_keys[16];
  uint32_t key_halves[2];
  keyPermute(key, &pkey);
  printf("plaintext: 0x%lx\n", plaintext);
  printf("key permutation: 0x%lx\n", pkey);
  permute(plaintext, ip, &iptext, 64);
  printf("initial permutation: 0x%lx\n", iptext);
  permute(iptext, up, &unpermute, 64);
  key_halves[0] = key & 0xfffffff;
  key_halves[1] = key >> 28;
  for(uint8_t c=0; c<16; c++){
    shift_key(&key_halves[0], shifts[c]);
    shift_key(&key_halves[1], shifts[c]);
    
  }
  printf("undo permutation: 0x%lx\n", unpermute);
  return 0;
}
