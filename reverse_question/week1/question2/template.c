#include <stdio.h>
#include <string.h>
###exec:
def to_cx_string(s):
	t = ''
	for i in s:
		t += '\\x%02x' % ord(i)
	return '"' + t + '"'
import random
key = random.randint(1, 255)
encrypted_flag = ''
for i in flag:
    encrypted_flag += chr(ord(i) ^ key)
###

// 加密函数
char encrypted_flag[50]=###eval: to_cx_string(encrypted_flag)###;

void encrypt(char* input) {
    int length = strlen(input);
    for (int i = 0; i < length; i++) {
        input[i] = input[i] ^ ###eval: key###; // 异或操作
    }
}
int main() {
    char input[50];
    printf("input your flag: ");
    if(fgets(input, sizeof(input), stdin) != NULL){
        input[strcspn(input, "\n")] = 0; // 去掉换行符
        encrypt(input);
        if(strcmp(input, ###eval: to_cx_string(encrypted_flag)###)==0){
            printf("Congratulations! You are right!\n");
        } else {
            printf("Sorry, you are wrong.\n");
        }
    } else {
        printf("Error reading input.\n");
    }
    return 0;
}
