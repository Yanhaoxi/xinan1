#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
###exec:
def to_cx_string(s):
	t = ''
	for i in s:
		t += '\\x%02x' % ord(i)
	return '"' + t + '"'

def random_password():
    import random
    password = ''
    for i in range(38):
        password += random.choice('1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!_-+?')
    return password

password=random_password()
fake_flag='flag{'
for i in range(38):
	fake_flag+=chr(ord(flag[i+5])^ord(password[i]))
fake_flag+='}'
###

char flag[100]=###eval: to_cx_string(fake_flag)###;

void decrypt(char* flag, char* password){
    int i;
    for (i=0; i<38; i++) {
        flag[i+5]=flag[i+5]^password[i];
    }
    printf("%s\n", flag);
}

int verify(char* password){
    if (strcmp(password, ###eval: to_cx_string(password)###)==0 && strlen(password)==38) {
        decrypt(flag,password);
        return 1;
    } else {
        return 0;
    }
}
int main(int argc, char *argv[]) {
    char* password;
    if (argc != 4) {
        printf("I can't understand you.\n");
        return 1;
    }
    if (strcmp(argv[1],"flag")==0) {
        printf("I will give you the flag if your password is right\n");
    } else {
        printf("What are you doing?\n");
        return 0;
    }
    if (strcmp(argv[2], "-password")==0) {
        printf("verifying password...\n");
        Sleep(5000);
        password=argv[3];
        if (verify(password)) {
            printf("Here you are!\n");
        } else {
            printf("Who are you?\n");
            return 0;
        }
    }
    else {
        printf("Password!\n");
        return 0;
    }
}
