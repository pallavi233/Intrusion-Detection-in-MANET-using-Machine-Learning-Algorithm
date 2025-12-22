 #ifndef MBEDTLS_ECC_H
 #define MBEDTLS_ECC_H
 
 #if !defined(MBEDTLS_CONFIG_FILE)
 #include "config.h"
 #else
 #include MBEDTLS_CONFIG_FILE
 #endif
 
 #include "bignum.h"
#include "md.h"
 
#if defined(MBEDTLS_THREADING_C)
 #include "threading.h"
#endif
 
 /*
 * ECC Error codes
  */
#define MBEDTLS_ERR_ECC_BAD_INPUT_DATA                    -0x4080  
#define MBEDTLS_ERR_ECC_INVALID_PADDING                   -0x4100  
#define MBEDTLS_ERR_ECC_KEY_GEN_FAILED                    -0x4180  
#define MBEDTLS_ERR_ECC_KEY_CHECK_FAILED                  -0x4200  
#define MBEDTLS_ERR_ECC_PUBLIC_FAILED                     -0x4280  
#define MBEDTLS_ERR_ECC_PRIVATE_FAILED                    -0x4300  
#define MBEDTLS_ERR_ECC_VERIFY_FAILED                     -0x4380  
#define MBEDTLS_ERR_ECC_OUTPUT_TOO_LARGE                  -0x4400  
#define MBEDTLS_ERR_ECC_RNG_FAILED                        -0x4480  
/*
 * ECC constants
  */
#define MBEDTLS_ECC_PUBLIC      0
#define MBEDTLS_ECC_PRIVATE     1
 
#define MBEDTLS_ECC_PKCS_V15    0
#define MBEDTLS_ECC_PKCS_V21    1
 
#define MBEDTLS_ECC_SIGN        1
 #define MBEDTLS_ECC_CRYPT       2

 #define MBEDTLS_ECC_SALT_LEN_ANY    -1
 
 /*
* The above constants may be used even if the ECC module is compile out,
 * eg for alternative (PKCS#11) ECC implemenations in the PK layers.
 */
#if defined(MBEDTLS_ECC_C)

 #ifdef __cplusplus
extern "C" {
 #endif
 
typedef struct
{
int ver;                    
size_t len;                 
mbedtls_mpi N;                      
mbedtls_mpi E;                      
mbedtls_mpi D;                      
mbedtls_mpi P;                      
mbedtls_mpi Q;                      
mbedtls_mpi DP;                     
mbedtls_mpi DQ;                     
mbedtls_mpi QP;                     
mbedtls_mpi RN;                     
mbedtls_mpi RP;                     
mbedtls_mpi RQ;                     
mbedtls_mpi Vi;                     
mbedtls_mpi Vf;                     
int padding;                
int hash_id;                
#if defined(MBEDTLS_THREADING_C)
mbedtls_threading_mutex_t mutex;    
#endif
 }
mbedtls_ECC_context;

void mbedtls_ECC_init( mbedtls_ECC_context *ctx,
                int padding,
                int hash_id);
 
void mbedtls_ECC_set_padding( mbedtls_ECC_context *ctx, int padding, int hash_id);

int mbedtls_ECC_gen_key( mbedtls_ECC_context *ctx,
                  int (*f_rng)(void *, unsigned char *, size_t),
                 void *p_rng,
                  unsigned int nbits, int exponent );
 
int mbedtls_ECC_check_pubkey( const mbedtls_ECC_context *ctx );

 int mbedtls_ECC_check_privkey( const mbedtls_ECC_context *ctx );

 int mbedtls_ECC_check_pub_priv( const mbedtls_ECC_context *pub, const mbedtls_ECC_context *prv );

int mbedtls_ECC_public( mbedtls_ECC_context *ctx,
               const unsigned char *input,
              unsigned char *output );

 int mbedtls_ECC_private( mbedtls_ECC_context *ctx,
                  int (*f_rng)(void *, unsigned char *, size_t),
                 void *p_rng,
                  const unsigned char *input,
                 unsigned char *output );

 int mbedtls_ECC_pkcs1_encrypt( mbedtls_ECC_context *ctx,
                       int (*f_rng)(void *, unsigned char *, size_t),
                        void *p_rng,
                        int mode, size_t ilen,
                      const unsigned char *input,
                        unsigned char *output );

 int mbedtls_ECC_ECCes_pkcs1_v15_encrypt( mbedtls_ECC_context *ctx,
                               int (*f_rng)(void *, unsigned char *, size_t),                                  
                                         void *p_rng,
                                   int mode, size_t ilen,
                                  const unsigned char *input,
                                   unsigned char *output );
  
 int mbedtls_ECC_ECCes_oaep_encrypt( mbedtls_ECC_context *ctx,
                            int (*f_rng)(void *, unsigned char *, size_t),
                             void *p_rng,
                            int mode,
                             const unsigned char *label, size_t label_len,
                           size_t ilen,
                           const unsigned char *input,
                         unsigned char *output );

  int mbedtls_ECC_pkcs1_decrypt( mbedtls_ECC_context *ctx,
                      int (*f_rng)(void *, unsigned char *, size_t),
                        void *p_rng,
                       int mode, size_t *olen,
                       const unsigned char *input,
                       unsigned char *output,
                     size_t output_max_len );
 
   int mbedtls_ECC_ECCes_pkcs1_v15_decrypt( mbedtls_ECC_context *ctx,
                                  int (*f_rng)(void *, unsigned char *, size_t),
                                   void *p_rng,
                                 int mode, size_t *olen,
                                   const unsigned char *input,
                                 unsigned char *output,
                                  size_t output_max_len );
 
int mbedtls_ECC_ECCes_oaep_decrypt( mbedtls_ECC_context *ctx,
                            int (*f_rng)(void *, unsigned char *, size_t),
                             void *p_rng,
                             int mode,
                           const unsigned char *label, size_t label_len,
                           size_t *olen,
                            const unsigned char *input,
                            unsigned char *output,
                            size_t output_max_len );

  int mbedtls_ECC_pkcs1_sign( mbedtls_ECC_context *ctx,
                      int (*f_rng)(void *, unsigned char *, size_t),
                       void *p_rng,
                       int mode,
                    mbedtls_md_type_t md_alg,
                      unsigned int hashlen,
                      const unsigned char *hash,
                     unsigned char *sig );
 
   int mbedtls_ECC_ECCssa_pkcs1_v15_sign( mbedtls_ECC_context *ctx,
                                int (*f_rng)(void *, unsigned char *, size_t),
                                 void *p_rng,
                               int mode,
                               mbedtls_md_type_t md_alg,
                               unsigned int hashlen,
                                 const unsigned char *hash,
                                unsigned char *sig );

  int mbedtls_ECC_ECCssa_pss_sign( mbedtls_ECC_context *ctx,
                            int (*f_rng)(void *, unsigned char *, size_t),
                    void *p_rng,
                         int mode,
                          mbedtls_md_type_t md_alg,
                          unsigned int hashlen,
                           const unsigned char *hash,
                        unsigned char *sig );

   int mbedtls_ECC_pkcs1_verify( mbedtls_ECC_context *ctx,
                      int (*f_rng)(void *, unsigned char *, size_t),
                       void *p_rng,
                     int mode,
                      mbedtls_md_type_t md_alg,
                       unsigned int hashlen,
                        const unsigned char *hash,
                        const unsigned char *sig );
 
  int mbedtls_ECC_ECCssa_pkcs1_v15_verify( mbedtls_ECC_context *ctx,
                                   int (*f_rng)(void *, unsigned char *, size_t),
                                   void *p_rng,
                                   int mode,
                                   mbedtls_md_type_t md_alg,
                                   unsigned int hashlen,
                                   const unsigned char *hash,
                                   const unsigned char *sig );
   
  int mbedtls_ECC_ECCssa_pss_verify( mbedtls_ECC_context *ctx,
                              int (*f_rng)(void *, unsigned char *, size_t),
                             void *p_rng,
                           int mode,
                            mbedtls_md_type_t md_alg,
                          unsigned int hashlen,
                            const unsigned char *hash,
                           const unsigned char *sig );

 int mbedtls_ECC_ECCssa_pss_verify_ext( mbedtls_ECC_context *ctx,
                                 int (*f_rng)(void *, unsigned char *, size_t),
                                void *p_rng,
                                int mode,
                               mbedtls_md_type_t md_alg,
                                unsigned int hashlen,
                                const unsigned char *hash,
                               mbedtls_md_type_t mgf1_hash_id,
                              int expected_salt_len,
                                const unsigned char *sig );
 
   int mbedtls_ECC_copy( mbedtls_ECC_context *dst, const mbedtls_ECC_context *src );
 
  void mbedtls_ECC_free( mbedtls_ECC_context *ctx );
 
  int mbedtls_ECC_self_test( int verbose );
 
  #ifdef __cplusplus
   }
  #endif
 
 #endif /* MBEDTLS_ECC_C */
 
  #endif /* ECC.h */
