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
        printf("�������������룺\n");
        if(fgets(input_password, sizeof(input_password), stdin) == NULL) {
            printf("�������\n");
            exit(0);
        }
        input_password[strcspn(input_password, "\n")] = 0;
        char password[] = "flag";
        int len = strlen(input_password);
        if (len < 4) // �ַ�������С��4�޷����� "flag"
            {printf("�������\n");
            exit(0);}
        // ��������ָ�룬һ�����ڶ�ȡ�ַ���һ������д���ַ�
        int read_ptr = 0;
        int write_ptr = 0;

        // ����ɨ���ַ���
        while (read_ptr < len - 3) {
            // �ж��Ƿ�ƥ�� "flag"
            if (input_password[read_ptr] == 'f' && input_password[read_ptr + 1] == 'l' && input_password[read_ptr + 2] == 'a' && input_password[read_ptr + 3] == 'g') {
                read_ptr += 4; // ���� "flag"
            } else {
                // �����ǰλ�ò��� "flag"�����ַ�д��Ŀ��λ�ã����ƶ���дָ��
                input_password[write_ptr++] = input_password[read_ptr++];
            }
        }
        // ����ʣ����ַ���Ŀ��λ��
        while (read_ptr < len) {
            input_password[write_ptr++] = input_password[read_ptr++];
        }

        // ����ַ���������
        input_password[write_ptr] = '\0';
        if (strcmp(input_password, password) == 0) {
            printf("������ȷ\n");
        } else {
            printf("�������\n");
            exit(0);
        }
        printf("���������flag:\n");
        if(fgets(input_flag, sizeof(input_flag), stdin) == NULL) {
            printf("�������\n");
            exit(0);
        }
        input_flag[strcspn(input_flag, "\n")] = 0;
        if ((strlen(input_flag)) != 30) {
            printf("flag����\n");
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
                printf("flag����\n");
                return 0;
            }
        }
        printf("flag��ȷ\n");
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

