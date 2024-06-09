#include <iostream>
#include <cstring>
#include <stdio.h>
###exec:
def to_cx_string(s):
	t = ''
	for i in s:
		t += '\\x%02x' % ord(i)
	return '"' + t + '"'
encrypted_flag =[ord(flag[i])^0x66^i  for i in range(len(flag))]
for i in range(len(flag)-3):
    encrypted_flag[i] = chr(encrypted_flag[i]^encrypted_flag[i+1]^encrypted_flag[i+2]^encrypted_flag[i+3])
encrypted_flag[-3] = chr(encrypted_flag[-3]^encrypted_flag[-2]^encrypted_flag[-1])
encrypted_flag[-2] = chr(encrypted_flag[-2]^encrypted_flag[-1])
encrypted_flag [-1]= chr(encrypted_flag[-1])
###
char encrypted_flag[] =###eval: to_cx_string(encrypted_flag)###;
class Validator {
private:
    char input_password[100];
    char input_flag[100];

public:
    Validator() {
        get_input(); 
    }

    int get_input() {
        printf("请输入启动密码：\n");
        if(fgets(input_password, sizeof(input_password), stdin) == NULL) {
            printf("输入错误\n");
            exit(0);
        }
        input_password[strcspn(input_password, "\n")] = 0;
        char password[] = "flag";
        int len = strlen(input_password);
        if (len < 4) // 字符串长度小于4无法包含 "flag"
            {printf("密码错误\n");
            exit(0);}
        // 定义两个指针，一个用于读取字符，一个用于写入字符
        int read_ptr = 0;
        int write_ptr = 0;

        // 线性扫描字符串
        while (read_ptr < len - 3) {
            // 判断是否匹配 "flag"
            if (input_password[read_ptr] == 'f' && input_password[read_ptr + 1] == 'l' && input_password[read_ptr + 2] == 'a' && input_password[read_ptr + 3] == 'g') {
                read_ptr += 4; // 跳过 "flag"
            } else {
                // 如果当前位置不是 "flag"，则将字符写入目标位置，并移动读写指针
                input_password[write_ptr++] = input_password[read_ptr++];
            }
        }
        // 复制剩余的字符到目标位置
        while (read_ptr < len) {
            input_password[write_ptr++] = input_password[read_ptr++];
        }

        // 添加字符串结束符
        input_password[write_ptr] = '\0';
        if (strcmp(input_password, password) == 0) {
            printf("密码正确\n");
        } else {
            printf("密码错误\n");
            exit(0);
        }
        printf("请输入你的flag:\n");
        if(fgets(input_flag, sizeof(input_flag), stdin) == NULL) {
            printf("输入错误\n");
            exit(0);
        }
        input_flag[strcspn(input_flag, "\n")] = 0;
        if ((strlen(input_flag)) != 30) {
            printf("flag错误\n");
            exit(0);
        }
        for(int i=0;i<30;i++){
            input_flag[i] = input_flag[i] ^ i ^0x66;
        }
        return 1;
    }

    int validate_input(){
        for(int i = 0; i < 27; i++) {
            input_flag[i] = input_flag[i]^input_flag[i+1]^input_flag[i+2]^input_flag[i+3];
        }
        input_flag[27] = input_flag[27]^input_flag[28]^input_flag[29];
        input_flag[28] = input_flag[28]^input_flag[29];
        input_flag[29] = input_flag[29];

        for (int i = 0; i < 30; i++) {
            if (input_flag[i] != encrypted_flag[i]) {
                printf("flag错误\n");
                return 0;
            }
        }
        printf("flag正确\n");
        return 1;
    }
    ~Validator() {
        validate_input();
    }
};
Validator validator;
int main() {
    char hint[]="Main logic is not here!";
    return 0;
}

