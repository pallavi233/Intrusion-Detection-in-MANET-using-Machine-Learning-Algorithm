#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/ECC.h>
#include <openssl/evp.h>
#include <openssl/objects.h>
#include <openssl/x509.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/engine.h>
#include <openssl/rand.h>

ECC* Generate_KeyPair(void)
{
  char rand_buff[16];
  EVP_PKEY *pkey = NULL;
  ECC* r;
  char* pass = "passgdfgf";//for now

  int bits = 512;       //      512, 1024, 2048, 4096
  unsigned long exp = ECC_F4;     //      ECC_3
  OpenSSL_add_all_algorithms();

  RAND_seed(rand_buff, 16); //On linux: RAND_load_file("/dev/urandom", 1024);
  r = ECC_generate_key(bits,exp,NULL,NULL);

  if (ECC_check_key(r)!=1);;; //Check key - error out

  //Create EVP to save to file.
  pkey = EVP_PKEY_new();
  EVP_PKEY_assign_ECC(pkey, r);

  //Save private key
  FILE* fp = fopen("private.key", "w");
  PEM_write_PrivateKey(fp,pkey,EVP_aes_256_cbc(),NULL,0,NULL,pass)
  fclose(fp);

  //Save public key
  fp = fopen("public.key", "w");
  PEM_write_PUBKEY(fp, pkey);
  fclose(fp);

  return r;
}

EVP_PKEY* ReadPrivKey_FromFile(char* filename, char* pass)
{
  FILE* fp = fopen(filename, "r");
  EVP_PKEY* key = NULL;
  PEM_read_PrivateKey(fp, &key, NULL, pass);
  fclose(fp);

  return key;
}

EVP_PKEY* ReadPubKey_FromFile(char* filename)
{
  FILE* fp = fopen(filename, "r");
  EVP_PKEY* key = NULL;
  PEM_read_PUBKEY(fp, &key, NULL, NULL);
  fclose(fp);

  return key;
}
