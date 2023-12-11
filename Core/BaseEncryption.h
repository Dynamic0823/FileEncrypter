#ifndef BASE_ENCRYPTION_H
#define BASE_ENCRYPTION_H
#include "CoreTypes.h"
#include "EncryptionTypes.h"
class BaseEncryption{
 public:
  BaseEncryption(KeyType pKeyType, EncryptionAlgorithm pAlgorithm, uint8_t *pKey);
  virtual RetCode encrypt(uint8_t *pData, int pSize);
 private:
  KeyType mKeyType;
  EncryptionAlgorithm mAlg;
  uint8_t *mKey;
};

#endif
