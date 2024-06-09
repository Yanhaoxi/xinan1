#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <windows.h>
#include <wincrypt.h>

###exec:
def to_cx_string(s):
    t = ''
    for i in s:
        if isinstance(i,int):
            t += '\\x%02x' % i
        else:
            t += '\\x%02x' % ord(i)
    return '"' + t + '"'

def to_cx_int_arry(s):
    t = '{'
    for i in s:
        t += str(i) + ','
    t+='}'
    return t

from struct import pack, unpack

def convert(str_):
    byte_str=pack(f'{len(str_)}s', str_.encode('utf-8'))
    byte_str+=(4-len(byte_str)%4)*b'\x00'
    len_int=len(byte_str)//4
    int_=[unpack('I',byte_str[i*4:(i+1)*4])[0] for i in range(len_int)]
    return int_

def encrypted_saying(arr):
    temp = 0
    encrypt_arr = []
    for i in range(len(arr)):
        encrypt_arr.append(arr[i]^temp)
        temp += arr[i]
        temp = temp & 0xffffffff
    return encrypt_arr

import random
random_str = random.choice(['ctf', 'flag', 'hack', 'cyber', 'security', 'pwn', 'crypto', 'reverse', 'web', 'ai', 'misc'])+str(random.randint(100,999))
saying = f'Please input "{random_str}" to get the flag ,double quotes is unnecessary'
saying = convert(saying)
saying = encrypted_saying(saying)
flag_int = convert(flag) #len(flag)==31
from hashlib import md5, sha256
xor_flag=md5(random_str.encode()).hexdigest()
xor_flag=convert(xor_flag)[0:8]
encrypted_flag =[i^j for i,j in zip(flag_int, xor_flag)]
hash_answer=sha256(random_str.encode()).digest()
###

#define SHA256_DIGEST_LENGTH 32
#define MD5_DIGEST_LENGTH 16
int encrypted_flag[8]=###eval: to_cx_int_arry(encrypted_flag)###;
int saying[]=###eval: to_cx_int_arry(saying)###;
uint8_t hash_answer[SHA256_DIGEST_LENGTH] = ###eval: to_cx_string(hash_answer)###;


void calculate_sha256_hash(const char *input, size_t input_len, uint8_t *output) {
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    DWORD cbHash = SHA256_DIGEST_LENGTH;

    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        printf("CryptAcquireContext failed: %lu\n", GetLastError());
        return;
    }

    if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
        printf("CryptCreateHash failed: %lu\n", GetLastError());
        CryptReleaseContext(hProv, 0);
        return;
    }

    if (!CryptHashData(hHash, (const BYTE *)input, input_len, 0)) {
        printf("CryptHashData failed: %lu\n", GetLastError());
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return;
    }

    if (!CryptGetHashParam(hHash, HP_HASHVAL, output, &cbHash, 0)) {
        printf("CryptGetHashParam failed: %lu\n", GetLastError());
    }

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);
}

void printIntArray(int arr[], int size) {
    int temp=0;
    for (int i = 0; i < size; i++) {
        arr[i] = arr[i] ^ temp;
        printf("%d\n", arr[i]);
        temp+=arr[i];
    }
    printf("\n");
}
void calculate_md5_hash(const char *input, size_t input_len, uint8_t *output) {
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    DWORD cbHash = MD5_DIGEST_LENGTH;

    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        printf("CryptAcquireContext failed: %lu\n", GetLastError());
        return;
    }

    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
        printf("CryptCreateHash failed: %lu\n", GetLastError());
        CryptReleaseContext(hProv, 0);
        return;
    }

    if (!CryptHashData(hHash, (const BYTE *)input, input_len, 0)) {
        printf("CryptHashData failed: %lu\n", GetLastError());
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return;
    }

    if (!CryptGetHashParam(hHash, HP_HASHVAL, output, &cbHash, 0)) {
        printf("CryptGetHashParam failed: %lu\n", GetLastError());
    }

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);
}

int verify(uint8_t *hash, uint8_t *answer) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        if (hash[i] != answer[i]) {
            return 0;
        }
    }
    return 1;
}
int main() {
    char input[100];
    printIntArray(saying , ###eval: len(saying)###);
    if(fgets(input, sizeof(input), stdin)!=NULL){
        input[strcspn(input, "\n")] = 0;
    }
    else{
        return 0;
    }
    size_t input_len = strlen(input);
    uint8_t sha256_hash[SHA256_DIGEST_LENGTH];
    uint8_t md5_hash[MD5_DIGEST_LENGTH];
    calculate_sha256_hash(input, input_len, sha256_hash);
    if(verify(sha256_hash, hash_answer)){
        calculate_md5_hash(input, input_len, md5_hash);
        char str[MD5_DIGEST_LENGTH*2 + 1];
        for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
            sprintf(str + i*2, "%02x", md5_hash[i]);
        }
        uint32_t nums[4];
        for (int i = 0; i < 8; i++) {
            nums[i] = *(uint32_t*)(str+i*4);
        }
        for (int i = 0; i < 8; i++) {
            printf("%u\n", encrypted_flag[i] ^ nums[i]);
        }
        return 0;
    }
}