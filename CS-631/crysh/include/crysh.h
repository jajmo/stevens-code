#ifndef _CRYSH_H_
#define _CRYSH_H_

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#if defined(__linux__)
#include <bsd/bsd.h>
#endif

#include <openssl/evp.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define FALSE 0
#define TRUE 1

/* Return codes */
#define PARSE_ERROR 3
#define DECRYPTION_FAILED 128

#define FILE_MODE 0644
#define SALT_LENGTH 8
#define KEY_LENGTH 32 /* Key for AES-256 is 32 bytes */
#define IV_LENGTH 16  /* IV  for AES-256 is 16 bytes */

int decrypt_init(const char *, size_t);
int decrypt_update(const char *, size_t);
unsigned char *decrypt_final();
int execute(const char *);
void free_2d_vec(char ***, int);
void free_vec(char **, int, int);
int get_token_count(const char *, int);
int get_command_count(const char *);
int is_redirect(const char *);
char ***tokenize(const char *);
char **extract_command(const char *, int);
char *get_word(const char *, int);

#endif
