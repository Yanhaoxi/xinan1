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