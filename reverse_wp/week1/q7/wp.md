首先恢复程序逻辑
程序通过解析big_num来对input进行操作
```c
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
```
用python写出解题脚本

```python
# 程序指令解析器
from Crypto.Util.number import inverse
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
                print(input)
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

# 逆向还原
def de_num(instructions:list,input):
    for i in instructions[:-1][::-1]:
        match i:
            case add(num=i):
                input-=i
                input%=256
            case sub(num=i):
                input+=i
                input%=256
            case mul(num=i):
                input=inverse(i,256)*input
                input%=256
            case end():
                return input
            case neg():
                input=255-input
            case xor(num=i):
                input^=i
            case lshift(num=i):
                input=(input >> i) | ((input << (8 - i)) & 0xFF)
                input%=256
            case rshift(num=i):
                input=(input << i) | ((input >> (8 - i)) & 0xFF)
                input%=256
            case _:
                raise Exception('error')
    return input
    
code_list=[0x7329B95559CED890, 0x4ACA925FE72D0069, 0x87AA1EE2EF21770B, 0xB3699C8FEE675633, 0x3D35F1CCAF2A7442, 0x941A697CE43CE668, 0x0875496903E5BF1B, 0xF2A43B541AD7CFA2, 0x96EA5C86DFD4F124, 0x46B2BF143B949886, 0xB52A7B741EBC51B4, 0xBBA55579BB4DE5CC, 0x6A18579ECB27FD65, 0x7B455F145E36B47E, 0x8A77EC50FC785C6E, 0x4DD406DC56E14ED8, 0x0574C62AF426738D, 0xDCD129947799D05E, 0xD5AADACAD614A258, 0x4A2817B65F88CABE, 0x7490B0D091E7E186, 0x14AD2F78F888572B, 0x556B6EAE24333D26, 0xE9AEBF4EF993D87E, 0xD7650351B07E4F9B, 0xABF3CCA5B8C4733B, 0x946A62DF32B88EE6, 0xF835869DFAE277F2, 0xA6D63D64D14A8C3E, 0x9FAA6FD479D961CD, 0xDACA48375B9B3EAB, 0x5558A191030CDEC2, 0xEB552662E9252A3E, 0x7A26E2D8D7D8986F, 0x7CDD3700C05313C5]
encode_flag=[0xE3, 0x23, 0x08, 0x3F, 0x7C, 0x34, 0x51, 0xDD, 0x28, 0xE7, 0x77, 0x41, 0x9E, 0x8D, 0x02, 0x98, 0x98, 0x2B, 0xA3, 0xE4, 0x53, 0x94, 0xB7, 0xB5, 0x41, 0x90, 0xB5, 0x38, 0x95, 0x06, 0xE9, 0x3B, 0x49, 0xBF, 0x0C]
print(''.join([chr(de_num(en_num(code,0)[0],enflag)) for code,enflag in zip(code_list,encode_flag)]))
# flag{calculation_is_ready_60ebcfb5}
```
# 动态方法
我们查看对输入的操作
```
Xref	Line	Column	Pseudocode line
rw	60	20	                    Buffer[i] += j;
rw	66	20	                    Buffer[i] += j & 0xF;
rw	77	20	                    Buffer[i] -= j;
rw	83	20	                    Buffer[i] -= j & 0xF;
w	96	16	                Buffer[i] = ((unsigned __int8)Buffer[i] << ((j & 3) + 1)) | ((int)(unsigned __int8)Buffer[i] >> (8 - v12));
r	96	46	                Buffer[i] = ((unsigned __int8)Buffer[i] << ((j & 3) + 1)) | ((int)(unsigned __int8)Buffer[i] >> (8 - v12));
r	96	99	                Buffer[i] = ((unsigned __int8)Buffer[i] << ((j & 3) + 1)) | ((int)(unsigned __int8)Buffer[i] >> (8 - v12));
w	98	16	                Buffer[i] = ((int)(unsigned __int8)Buffer[i] >> ((j & 3) + 1)) | (Buffer[i] << (8 - v12));
r	98	51	                Buffer[i] = ((int)(unsigned __int8)Buffer[i] >> ((j & 3) + 1)) | (Buffer[i] << (8 - v12));
r	98	82	                Buffer[i] = ((int)(unsigned __int8)Buffer[i] >> ((j & 3) + 1)) | (Buffer[i] << (8 - v12));
rw	114	16	                Buffer[i] ^= j;
rw	120	16	                Buffer[i] ^= j & 0xF;
w	126	14	              Buffer[i] = ~Buffer[i];
r	126	27	              Buffer[i] = ~Buffer[i];
rw	134	10	          Buffer[i] *= 2 * (j & 0x7F) + 1;
```
且继续探索发现对于每一位输入的操作都是固定的
那么把所有对输入的操作打印出来再逆向也是可以的
那么去汇编处下相应断点如下图
__注__:事实上从ida处提取出伪代码修改后自行编译，再用printf打印出来也是可以的
![](./png/屏幕截图%202024-04-07%20224043.png)
其余的是
```
msg("第%#x位加密开始\n",dword(RBP-0xC)),0
msg("Buffer[%d] += %d\n",dword(RBP-0xC),EDX),0
msg("Buffer[%d] -= %d\n",dword(RBP-0xC),ECX),0
msg("Buffer[%d] = Buffer[%d] << %d | Buffer[%d] >> (8 - %d)\n",dword(RBP-0xC),dword(RBP-0xC),CL,dword(RBP-0xC),CL),0
msg("Buffer[%d] = Buffer[%d] >> %d | Buffer[%d] << (8 - %d)\n",dword(RBP-0xC),dword(RBP-0xC),CL,dword(RBP-0xC),CL),0
msg("Buffer[%d] ^= %d\n",dword(RBP-0xC),EAX),0
msg("Buffer[%d] =~Buffer[%d]\n",dword(RBP-0xC),dword(RBP-0xC)),0
msg("Buffer[%d]*=%d\n",dword(RBP-0xC),EDX),0
```
打印出来
```
第0x0位加密开始
Buffer[0] -= 116
Buffer[0] ^= 14
Buffer[0] ^= 26
Buffer[0] ^= 30
Buffer[0] = Buffer[0] >> 1 | Buffer[0] << (8 - 1)
第0x1位加密开始
Buffer[1]*=127
Buffer[1] -= 123
Buffer[1]=~Buffer[1]
Buffer[1] = Buffer[1] << 4 | Buffer[1] >> (8 - 4)
Buffer[1]=~Buffer[1]
Buffer[1] += 14
Buffer[1] += 1
第0x2位加密开始
Buffer[2] = Buffer[2] >> 2 | Buffer[2] << (8 - 2)
Buffer[2] ^= 12
Buffer[2]*=5
Buffer[2] += 3
Buffer[2] -= 190
第0x3位加密开始
Buffer[3] -= 128
Buffer[3] += 124
Buffer[3]*=1
Buffer[3] = Buffer[3] >> 2 | Buffer[3] << (8 - 2)
Buffer[3] -= 84
第0x4位加密开始
Buffer[4]*=113
Buffer[4]=~Buffer[4]
Buffer[4] = Buffer[4] << 1 | Buffer[4] >> (8 - 1)
Buffer[4] = Buffer[4] >> 1 | Buffer[4] << (8 - 1)
Buffer[4]*=173
Buffer[4] += 9
Buffer[4] = Buffer[4] << 4 | Buffer[4] >> (8 - 4)
第0x5位加密开始
Buffer[5] -= 0
Buffer[5] += 160
Buffer[5]*=127
Buffer[5] += 15
Buffer[5] = Buffer[5] >> 2 | Buffer[5] << (8 - 2)
Buffer[5] ^= 7
第0x6位加密开始
Buffer[6] = Buffer[6] << 2 | Buffer[6] >> (8 - 2)
Buffer[6] += 179
Buffer[6] -= 3
Buffer[6]*=71
Buffer[6]*=39
Buffer[6] = Buffer[6] << 1 | Buffer[6] >> (8 - 1)
第0x7位加密开始
Buffer[7] += 8
Buffer[7]*=145
Buffer[7] ^= 13
Buffer[7]*=85
Buffer[7] = Buffer[7] << 4 | Buffer[7] >> (8 - 4)
Buffer[7] ^= 83
第0x8位加密开始
Buffer[8] += 221
Buffer[8] ^= 255
Buffer[8] ^= 41
Buffer[8] ^= 183
第0x9位加密开始
Buffer[9] -= 9
Buffer[9] ^= 13
Buffer[9] -= 14
Buffer[9] -= 208
Buffer[9] = Buffer[9] >> 3 | Buffer[9] << (8 - 3)
Buffer[9] ^= 24
第0xa位加密开始
Buffer[10] += 195
Buffer[10]*=211
Buffer[10] -= 11
Buffer[10] -= 165
Buffer[10] = Buffer[10] << 3 | Buffer[10] >> (8 - 3)
Buffer[10] += 242
第0xb位加密开始
Buffer[11] = Buffer[11] >> 4 | Buffer[11] << (8 - 4)
Buffer[11] = Buffer[11] << 4 | Buffer[11] >> (8 - 4)
Buffer[11]=~Buffer[11]
Buffer[11] += 155
Buffer[11] += 161
Buffer[11] += 1
Buffer[11] ^= 130
第0xc位加密开始
Buffer[12] -= 120
Buffer[12] -= 2
Buffer[12] += 2
Buffer[12] = Buffer[12] << 3 | Buffer[12] >> (8 - 3)
Buffer[12] -= 10
Buffer[12] += 123
第0xd位加密开始
Buffer[13]*=151
Buffer[13]=~Buffer[13]
Buffer[13]=~Buffer[13]
Buffer[13] ^= 45
Buffer[13] -= 13
Buffer[13] = Buffer[13] << 3 | Buffer[13] >> (8 - 3)
Buffer[13]*=175
第0xe位加密开始
Buffer[14] -= 240
Buffer[14] = Buffer[14] << 2 | Buffer[14] >> (8 - 2)
Buffer[14] ^= 163
Buffer[14] -= 5
Buffer[14]*=21
第0xf位加密开始
Buffer[15]*=57
Buffer[15] += 205
Buffer[15] = Buffer[15] >> 4 | Buffer[15] << (8 - 4)
Buffer[15]=~Buffer[15]
Buffer[15] -= 2
Buffer[15]=~Buffer[15]
Buffer[15] ^= 7
第0x10位加密开始
Buffer[16] = Buffer[16] >> 4 | Buffer[16] << (8 - 4)
Buffer[16] -= 144
Buffer[16] ^= 105
Buffer[16] += 8
Buffer[16] -= 13
Buffer[16] = Buffer[16] >> 2 | Buffer[16] << (8 - 2)
第0x11位加密开始
Buffer[17]*=83
Buffer[17] ^= 36
Buffer[17] = Buffer[17] >> 2 | Buffer[17] << (8 - 2)
Buffer[17] += 12
Buffer[17] ^= 15
第0x12位加密开始
Buffer[18] -= 12
Buffer[18] = Buffer[18] >> 3 | Buffer[18] << (8 - 3)
Buffer[18] = Buffer[18] << 2 | Buffer[18] >> (8 - 2)
Buffer[18] ^= 11
Buffer[18] -= 3
Buffer[18] += 5
Buffer[18]*=161
第0x13位加密开始
Buffer[19] ^= 103
Buffer[19] -= 128
Buffer[19] -= 230
Buffer[19] += 186
Buffer[19]*=25
第0x14位加密开始
Buffer[20]=~Buffer[20]
Buffer[20] ^= 158
Buffer[20] -= 223
Buffer[20] ^= 5
Buffer[20] = Buffer[20] >> 2 | Buffer[20] << (8 - 2)
Buffer[20] = Buffer[20] >> 3 | Buffer[20] << (8 - 3)
第0x15位加密开始
Buffer[21] += 125
Buffer[21]*=129
Buffer[21] += 136
Buffer[21] -= 209
Buffer[21] = Buffer[21] >> 1 | Buffer[21] << (8 - 1)
第0x16位加密开始
Buffer[22] = Buffer[22] << 1 | Buffer[22] >> (8 - 1)
Buffer[22] ^= 15
Buffer[22] = Buffer[22] >> 1 | Buffer[22] << (8 - 1)
Buffer[22] = Buffer[22] << 1 | Buffer[22] >> (8 - 1)
Buffer[22] += 55
Buffer[22] = Buffer[22] >> 2 | Buffer[22] << (8 - 2)
Buffer[22] -= 2
第0x17位加密开始
Buffer[23] -= 172
Buffer[23] -= 141
Buffer[23]=~Buffer[23]
Buffer[23] = Buffer[23] >> 3 | Buffer[23] << (8 - 3)
Buffer[23] = Buffer[23] >> 4 | Buffer[23] << (8 - 4)
Buffer[23] = Buffer[23] << 3 | Buffer[23] >> (8 - 3)
Buffer[23]=~Buffer[23]
Buffer[23] = Buffer[23] << 2 | Buffer[23] >> (8 - 2)
第0x18位加密开始
Buffer[24]*=3
Buffer[24] += 60
Buffer[24] ^= 92
Buffer[24] += 7
Buffer[24] -= 86
第0x19位加密开始
Buffer[25] += 0
Buffer[25]*=45
Buffer[25] ^= 126
Buffer[25] = Buffer[25] << 2 | Buffer[25] >> (8 - 2)
Buffer[25] = Buffer[25] >> 4 | Buffer[25] << (8 - 4)
Buffer[25] = Buffer[25] >> 2 | Buffer[25] << (8 - 2)
Buffer[25] ^= 3
第0x1a位加密开始
Buffer[26] = Buffer[26] >> 2 | Buffer[26] << (8 - 2)
Buffer[26] += 7
Buffer[26] += 13
Buffer[26]*=149
Buffer[26] = Buffer[26] << 1 | Buffer[26] >> (8 - 1)
Buffer[26] += 10
Buffer[26]=~Buffer[26]
Buffer[26] ^= 135
第0x1b位加密开始
Buffer[27] ^= 96
Buffer[27] = Buffer[27] << 1 | Buffer[27] >> (8 - 1)
Buffer[27] -= 7
Buffer[27]=~Buffer[27]
Buffer[27]=~Buffer[27]
Buffer[27]*=177
Buffer[27] -= 147
第0x1c位加密开始
Buffer[28] -= 8
Buffer[28]*=243
Buffer[28] += 30
Buffer[28]*=57
Buffer[28] -= 97
第0x1d位加密开始
Buffer[29] -= 46
Buffer[29] += 126
Buffer[29]=~Buffer[29]
Buffer[29] = Buffer[29] << 4 | Buffer[29] >> (8 - 4)
Buffer[29] ^= 5
Buffer[29] ^= 2
第0x1e位加密开始
Buffer[30] ^= 5
Buffer[30] -= 12
Buffer[30] = Buffer[30] >> 3 | Buffer[30] << (8 - 3)
Buffer[30] ^= 3
Buffer[30] -= 1
Buffer[30]=~Buffer[30]
Buffer[30] ^= 128
第0x1f位加密开始
Buffer[31] ^= 7
Buffer[31] = Buffer[31] << 4 | Buffer[31] >> (8 - 4)
Buffer[31]=~Buffer[31]
Buffer[31] -= 230
Buffer[31] -= 208
Buffer[31] += 47
第0x20位加密开始
Buffer[32] = Buffer[32] << 2 | Buffer[32] >> (8 - 2)
Buffer[32] -= 15
Buffer[32] ^= 147
Buffer[32] += 13
Buffer[32] = Buffer[32] >> 1 | Buffer[32] << (8 - 1)
Buffer[32] = Buffer[32] << 2 | Buffer[32] >> (8 - 2)
Buffer[32] -= 72
第0x21位加密开始
Buffer[33] ^= 0
Buffer[33] += 83
Buffer[33] = Buffer[33] >> 2 | Buffer[33] << (8 - 2)
Buffer[33] -= 1
Buffer[33] -= 13
Buffer[33]=~Buffer[33]
第0x22位加密开始
Buffer[34] -= 161
Buffer[34] = Buffer[34] >> 1 | Buffer[34] << (8 - 1)
Buffer[34]=~Buffer[34]
Buffer[34] += 192
Buffer[34] -= 3
Buffer[34] ^= 2
```
之后只需要做逆向操作就行
```python
import re
lines = a.split('\n')
chinese_lines = [i for i,line in enumerate(lines) if re.search('[\u4e00-\u9fff]', line)]
chinese_lines.append(len(lines))
code = [lines[chinese_lines[i]+1:chinese_lines[i+1]] for i in range(len(chinese_lines)-1)]
result = [0x7C, 0xA0, 0xE9, 0x84, 0xDA, 0x24, 0x8A, 0x85, 0x21, 0x68, 0x5A, 0x59, 0x58, 0x43, 0x4D, 0xB1, 0xC1, 0xD8, 0xFA, 0xAC, 0x89, 0xCC, 0xFF, 0xCA, 0xAC, 0xDF, 0x8C, 0xF8, 0xD6, 0x90, 0x3A, 0x55, 0x7E, 0xE0, 0x4C]
import z3
LShR = z3.LShR
s=z3.Solver()
Buffer=[z3.BitVec(f'Buffer[{i}]',8) for i in range(0x23)]
pattern1 = r"Buffer\[(\d+)\] >> (\d+)"
pattern2 = r"Buffer\[(\d+)\] >> \((.*?)\)"
for i in range(len(code)):
    for j in range(len(code[i])):
        replacement = r"LShR(Buffer[\1],\2)"
        # 用z3求解器注意>>默认是算术右移所以这里使用LShR
        sub_result = re.sub(pattern1, replacement, code[i][j])
        sub_result = re.sub(pattern2, replacement, sub_result)
        exec(sub_result)
    s.add(Buffer[i]==result[i])
if s.check()==z3.sat:
    m=s.model()
    dic={str(x):chr(m[x].as_long()) for x in m.decls()}
    for i in range(0x23):
        print(dic[f'Buffer[{i}]'],end='')
flag{calculation_is_ready_5a36355a}
```

# 爆破
因为没有扩散，所以遍历单字符即可
接下来用gdb编写动态调试脚本 直接patch二进制文件也是可以的 在源码层面上修改也是可以的
```
set logging file my_gdb_log.txt
set logging enabled on
#把输出信息放入文件中
b main
set $main_p=&main
set $Buffer=-0x50
set $i=-0xC

run < input.txt
set $main_a=&main
set $offset=$main_a-$main_p
#算出位移
set $try=0

b * $offset+0x1400018B7
set $flag=0
b * $offset+0x1400018B3


continue
while($flag==0)
    # 到达第二个断点
    set $now_i=*(int*)($rbp+$i)
    set *(char*)($rbp+$Buffer+$now_i)=$try
    continue
    # 到达第三个断点
    if *(char*)($rbp+$Buffer+$now_i)==((char*)&encoded_flag)[$now_i]
        p $try
        set $try=0
    else
        set $try=$try+1
        set *(int*)($rbp+$i)=*(int*)($rbp+$i)-1
    end
    continue
end
```
实际处理过程中有些小问题比如gdb命令行变量有大小限制  
对于开了high entry_ponit的文件会导致偏移量过大超过最大  
可以采用引入python接口的方法解决  
为了不涉及太多所以我去pe文件头里把high entry_ponit关了  
同时输出的信息有点多，理论上也可以去通过python接口定制输出但是没有继续尝试了  
```
命令行：过滤出有用数据  
awk -F' = ' 'NF>1 {print $2}' my_gdb_log.txt
```
结果
```python
str_="""102
108
97
103
123
99
97
108
99
117
108
97
116
105
111
110
95
105
115
95
114
101
97
100
121
95
53
97
51
54
51
53
53
97
125"""
print(''.join([chr(int(char)) for char in str_.split()]))
# flag{calculation_is_ready_5a36355a}
```
<!-- # 用angr做符号执行
angr是用于模拟符号执行的工具  
个人对其工作原理简要理解如下(详细具体可以自行查找官方文档或其他资料)：
- 可以从可执行文件处任意位置开始模拟执行，未知值用符号代替，在控制流发生转移时，向所有方向发生转移，形成n条支路，并将相应转移所需的约束加入相应支路，最后通过约束求解器(基于z3的claripy)，获得从起始点转移到此处所需要的条件。(类似先设未知量x，再根据题目条件列方程最后求解)   
- 局限在于对于大型程序，由于需要考虑所有路径故会造成路径爆炸(内存不够，所需时间长)。  
- 此外约束求解器能力有限，比如：
```
if hash(x)==y:
    do_sth
约束求解器很难有能力在有限时间内找到满足跳转的x
```
解题脚本如下：(需安装angr(pip install angr)）
```python
import angr
import claripy
def main():
    p = angr.Project("./exes/Ee2ICjkC.exe",main_opts={'base_addr': 0x140000000}, auto_load_libs=False)
    flag = claripy.BVS('flag', 8*35)
    state = p.factory.blank_state(addr=0x14000157F)
    buf = state.regs.rbp-0x50
    state.memory.store(buf, flag)
    for i in range(35):
        state.add_constraints(flag.get_byte(i) >= 0x20)
        state.add_constraints(flag.get_byte(i) <= 0x7e)
    sm = p.factory.simulation_manager(state)
    sm.explore(find=0x140001908, avoid=0x1400018E8)
    found = sm.found[0]
    solution = found.solver.eval(flag, cast_to=bytes)
    print(solution)

if __name__ == '__main__':
    main()
# b'flag{calculation_is_ready_5a36355a}'
``` -->
