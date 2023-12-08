#ifndef DES_ENCRYPTER_H
#define DES_ENCRYPTER_H

#include "BaseEncrypter.h"
#include <pthread.h>
#include <semaphore.h>

typedef enum{ECB, CBC, CFB, OFB, CTR}DESMode;

class DESEncrypter:public BaseEncrypter{
 public:
  DESEncrypter(const char *pInputFile, const char *pOutputFile, DESMode pMode, uint64_t pKey);
  virtual RetCode encryptData();
  virtual RetCode decryptData();
private:
  RetCode initialPermutation();
  RetCode decryptionRound(uint32_t pCipherText);
  RetCode encryptionRound(uint32_t pPlainText);
  //Encryption Round Steps
  RetCode keyTransform();
  RetCode expansionPermutation();
  RetCode sBoxPermutation();
  RetCode pBoxPermutation();
  RetCode xorSwap();
  uint64_t mKey;
};

#endif
