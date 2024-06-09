#include <stdio.h>
#include <string.h>
#include <math.h>
###exec:
import random
def code_gen():
    code=''
    while(len(code)+17<64):
        new=random.choice(['110','111','101','100','0100','0110','01110','01111','001','000'])
        match new:
            case '110'|'100'|'01110':
                for i in range(4):
                    new+=str(random.randint(0,1))
            case '111'|'101'|'01111':
                for i in range(8):
                    new+=str(random.randint(0,1))
            case '0100':
                for i in range(7):
                    new+=str(random.randint(0,1))
            case '001'|'000':
                for i in range(2):
                    new+=str(random.randint(0,1))
        code+=new
    code+='0101'
    while(len(code)<64):
        code+=str(random.randint(0,1))
    return int(code[::-1],2)
code_list=[code_gen() for i in range(35)]
code_list_str='{'
for i in code_list:
    code_list_str+=str(i)
    code_list_str+='ULL,'
code_list_str.rstrip(',')
code_list_str+='};'

from typing import NamedTuple
add=NamedTuple('add',[('num',int)])
sub=NamedTuple('sub',[('num',int)])
mul=NamedTuple('mul',[('num',int)])
end=NamedTuple('end','')
neg=NamedTuple('neg','')
xor=NamedTuple('xor',[('num',int)])
lshift=NamedTuple('lshift',[('num',int)])
rshift=NamedTuple('rshift',[('num',int)])

def en_num(num:int,input):
    instructions=[]
    end_of_program=0
    code=[int(i) for i in format(num,'064b')[::-1]]
    while len(code)>0:
        assert input>=0 and input<256
        match code:
            case 1,1,*code:
                match code:
                    case 0,*code:
                        tmp=int(''.join(map(str,code[0:4][::-1])),2)
                        instructions.append(add(num=tmp))
                        input+=tmp                        
                        input%=256
                        code=code[4:]
                    case 1,*code:
                        tmp=int(''.join(map(str,code[0:8][::-1])),2)
                        instructions.append(add(num=tmp))
                        input+=tmp
                        input%=256
                        code=code[8:]
            case 1,0,*code:
                match code:
                    case 0,*code:
                        tmp=int(''.join(map(str,code[0:4][::-1])),2)
                        instructions.append(sub(num=tmp))
                        input-=tmp
                        input%=256
                        code=code[4:]
                    case 1,*code:
                        tmp=int(''.join(map(str,code[0:8][::-1])),2)
                        instructions.append(sub(num=tmp))
                        input-=tmp
                        input%=256
                        code=code[8:]
            case 0,1,0,0,*code:
                tmp=(int(''.join(map(str,code[0:7][::-1])),2)*2+1)
                instructions.append(mul(num=tmp))
                input*=tmp
                input%=256
                code=code[7:]
            case 0,1,0,1,*code:
                instructions.append(end())
                end_of_program=1
                break
            case 0,1,1,0,*code:
                instructions.append(neg())
                input=255-input
            case 0,1,1,1,*code:
                match code:
                    case 0,*code:
                        tmp=int(''.join(map(str,code[0:4][::-1])),2)
                        instructions.append(xor(num=tmp))
                        input^=tmp
                        code=code[4:]
                    case 1,*code:
                        tmp=int(''.join(map(str,code[0:8][::-1])),2)
                        instructions.append(xor(num=tmp))
                        input^=tmp
                        code=code[8:]
            case 0,0,1,*code:#左循环tmp
                shift=int(''.join(map(str,code[0:2][::-1])),2)+1
                instructions.append(lshift(num=shift))
                input=(input << shift) | ((input >> (8 - shift)) & 0xFF)
                input%=256
                code=code[2:]
            case 0,0,0,*code:
                shift=int(''.join(map(str,code[0:2][::-1])),2)+1
                instructions.append(rshift(num=shift))
                input=((input >> shift) | ((input << (8 - shift)) & 0xFF))
                input%=256
                code=code[2:]
            case _:
                raise Exception('error')
    assert end_of_program==1
    return instructions, input

encoded_flag=[en_num(code_list[i],ord(flag[i]))[1] for i in range(35)]
encoded_flag_str='{'
for i in encoded_flag:
    encoded_flag_str+=str(i)+','
encoded_flag_str+='};'

###

long long int big_num[35]=###eval:code_list_str###
unsigned char encoded_flag[35]=###eval:encoded_flag_str###
int main(){
    unsigned char input[49]={0};
    printf("please input the flag\n");
    if(fgets(input, sizeof(input), stdin)!=NULL){
        input[strcspn(input, "\n")] = 0;
    }
    else{
        printf("error\n");
        return 0;
    }
    int length = strlen(input);
    if(length != 35){
        printf("The length is incorrect\n");
        return 0;
    }
    long long int code=0;
    int cond=0;
    int num=0;
    for(int i=0;i<35;i++){
        code=big_num[i];
        while(1){
            cond=code&0x1;
            code=code>>1;
            if(cond){//1
                cond=code&0x1;
                code=code>>1;
                if(cond){//11
                    cond=code&0x1;
                    code=code>>1;
                    if(cond){//11
                        num=code&0xff;
                        input[i]+=num;
                        code=code>>8;
                    }
                    else{//110
                        num=code&0xf;
                        input[i]+=num;
                        code=code>>4;
                    }
                }
                else{//10
                    cond=code&0x1;
                    code=code>>1;
                    if(cond){//101
                        num=code&0xff;
                        input[i]-=num;
                        code=code>>8;
                    }
                    else{//100
                        num=code&0xf;
                        input[i]-=num;
                        code=code>>4;
                    }
}
            }
            else{//0
                cond=code&0x1;
                code=code>>1;
                if(cond){//01
                    cond=code&0x1;
                    code=code>>1;
                    if(cond){//011
                        cond=code&0x1;
                        code=code>>1;
                        if(cond){//0111
                            cond=code&0x1;
                            code=code>>1;
                            if(cond){//01111
                                num=code&0xff;
                                input[i]=input[i]^num;
                                code=code>>8;
                            }
                            else{//01110
                                num=code&0xf;
                                input[i]=input[i]^num;
                                code=code>>4;
                            }
}
                        else{//0110
                            input[i]=~input[i];
                        }
                    }
                    else{//010
                        cond=code&0x1;
                        code=code>>1;
                        if(cond){//0101
                            break;
                        }
                        else{//0100
                            num=((code&0x7f)*2)+1;
                            input[i]*=num;
                            code=code>>7;
                        }
                    }
                }
                else{//00
                    cond=code&0x1;
                    code=code>>1;
                    if(cond){//001
                        num=(code&0x3)+1;
                        input[i] =input[i] << num | (input[i] >> (8 - num));
                        code=code>>2;
                    }
                    else{//000
                        num=(code&0x3)+1;
                        input[i] =input[i] >> num | (input[i] << (8 - num));
                        code=code>>2;
                    }
                }    
            }
        }
    }
    for(int i=0;i<35;i++){
        if(input[i]!=encoded_flag[i]){
            printf("wrong!!!!!!!!!!!!!!!!\n");
            return 0;
        }
    }
    printf("correct!!!!!!!!!!!!!!\n");
}