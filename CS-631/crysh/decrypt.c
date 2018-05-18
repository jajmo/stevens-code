#include "crysh.h"

unsigned char *decrypted_data;
int pt_len;
EVP_CIPHER_CTX *ctx;

int decrypt_init(const char *input, size_t len)
{
    const EVP_MD *digest;
    const EVP_CIPHER *cipher;
    char *password;
    int getpass_used;
    unsigned char salt[SALT_LENGTH + 1];
    unsigned char key[KEY_LENGTH + 1];
    unsigned char iv[IV_LENGTH + 1];

    getpass_used = FALSE;

    if (input == NULL)
        return -1;

    if (len <= 8 + SALT_LENGTH) /* strlen("Salted__") + saltlen */
        return -1;

    if (strncmp(input, "Salted__", 8) != 0)
        return -1;

    decrypted_data = NULL;
    pt_len = 0;

    if ((ctx = EVP_CIPHER_CTX_new()) == NULL)
        errx(DECRYPTION_FAILED, "unable to initialize cipher context");

    if ((cipher = EVP_aes_256_cbc()) == NULL)
    {
        EVP_CIPHER_CTX_free(ctx);
        errx(DECRYPTION_FAILED, "cipher init error");
    }

    if ((digest = EVP_sha1()) == NULL)
    {
        EVP_CIPHER_CTX_free(ctx);
        errx(DECRYPTION_FAILED, "digest init error");
    }

    (void) memcpy(salt, input + 8, SALT_LENGTH);
    salt[SALT_LENGTH] = '\0';

    if ((password = getenv("CRYSH_PASSWORD")) == NULL)
    {
        password = getpass("Password: ");
        getpass_used = TRUE;
    }

    if (EVP_BytesToKey(cipher, digest, salt, (unsigned char *) password, strlen(password), 1, key, iv) < 32)
    {
        EVP_CIPHER_CTX_free(ctx);
        bzero(password, strlen(password));
        if (getpass_used == TRUE)
            free(password);
        return -1;
    }

    bzero(password, strlen(password));
    if (getpass_used == TRUE)
        free(password);
    bzero(salt, SALT_LENGTH);

    key[KEY_LENGTH] = '\0';
    iv[IV_LENGTH] = '\0';

    if (EVP_DecryptInit(ctx, cipher, key, iv) == 0)
    {
        EVP_CIPHER_CTX_free(ctx);
        errx(DECRYPTION_FAILED, "unable to initialize decryption context");
    }

    bzero(key, KEY_LENGTH);
    bzero(iv, IV_LENGTH);

    return decrypt_update(input + 8 + SALT_LENGTH, len - 8 - SALT_LENGTH);
}

int decrypt_update(const char *input, size_t len)
{
    int outlen;

    if ((decrypted_data = (unsigned char *) realloc(decrypted_data, (pt_len + len + 1) * sizeof(unsigned char))) == NULL)
    {
        EVP_CIPHER_CTX_free(ctx);
        errx(errno, "realloc failed");
    }

    if (EVP_DecryptUpdate(ctx, decrypted_data + pt_len, &outlen, (unsigned char *) input, len) < 1)
    {
        free(decrypted_data);
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }

    pt_len += outlen;

    decrypted_data[pt_len] = '\0';
    return 1;
}

unsigned char *decrypt_final()
{
    int outlen;

    if (EVP_DecryptFinal(ctx, decrypted_data + pt_len, &outlen) < 1)
    {
        free(decrypted_data);
        EVP_CIPHER_CTX_free(ctx);
        return NULL;
    }

    decrypted_data[pt_len + outlen - 1] = '\0';
    EVP_CIPHER_CTX_free(ctx);
    return decrypted_data;
}