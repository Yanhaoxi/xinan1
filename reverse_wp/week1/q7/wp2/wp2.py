a="""
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
"""
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
        sub_result = re.sub(pattern1, replacement, code[i][j])
        sub_result = re.sub(pattern2, replacement, sub_result)
        exec(sub_result)
    s.add(Buffer[i]==result[i])
if s.check()==z3.sat:
    m=s.model()
    dic={str(x):chr(m[x].as_long()) for x in m.decls()}
    for i in range(0x23):
        print(dic[f'Buffer[{i}]'],end='')