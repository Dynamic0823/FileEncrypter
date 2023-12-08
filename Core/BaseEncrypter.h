#ifndef BASE_ENCRYPTER_H
#define BASE_ENCRYPTER_H
#include "CoreTypes.h"
#include "EncryptionTypes.h"

class BaseEncrypter{
 public:
  BaseEncrypter(const char *pPathToFile, const char *pOutputFile, KeyType pKeyFormat, EncryptionType pEncrypt);
  virtual RetCode encryptData()={return ERROR;};//virtual encrypt function, to be filled by child class
  virtual RetCode decryptData()={return ERROR;};//virtual decrypt function, to e filled by child class
  int getInputFile();//return input filedescriptor
  int getOutputFile();//return output filedescriptor
  RetCode openFiles();//open input and output file descriptors, return ok if and only if both open
  void closeFiles();//close the input and output file descriptors
private:
  const char *mInput;
  const char *mOutput;
  int mInputFd;
  int mOutputFd;
};

#endif
