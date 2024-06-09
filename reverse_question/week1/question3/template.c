#include <stdio.h>
#include <string.h>
#include <math.h>
###exec:
def to_cx_string(s):
	t = ''
	for i in s:
		t += '\\x%02x' % ord(i)
	return '"' + t + '"'

def to_cx_int_arry(s):
    t = '{'
    for i in s:
        t += str(i) + ','
    t+='}'
    return t

encrypted_flag = [0 for i in range(len(flag))]
for i in range(len(flag)):
    temp=flag[i]
    encrypted_flag[i] += ord(temp)**3 + 3*ord(temp)**2 + 2*ord(temp) + 3
###

// 加密函数
int encrypted_flag[50]=###eval: to_cx_int_arry(encrypted_flag)###;

int main() {
    char input[50];

    printf("input your flag: ");
    if(fgets(input, sizeof(input), stdin) != NULL){
        input[strcspn(input, "\n")] = 0; // 去掉换行符
        for(int i = 0; i < strlen(input); i++){
            if((pow(input[i],3) + 3*pow(input[i],2) + 2*input[i] + 3) != encrypted_flag[i]){
                printf("Wrong flag!\n");
                return 0;
            }
        }
        printf("Correct flag!\n");
    } else {
        printf("Error reading input.\n");
    }
    return 0;
}
