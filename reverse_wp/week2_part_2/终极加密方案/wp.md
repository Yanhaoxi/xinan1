# Question8
首先还原逻辑
```c
int main() {
    char flag[100]; 
    printf("Enter the flag: ");
    fgets(flag, sizeof(flag), stdin);

    // 移除flag字符串中的换行符
    flag[strcspn(flag, "\n")] = '\0';
    if (strlen(flag) != 36) {
        // 对输入长度的限制
        printf("Invalid flag length\n");
        return 0;
    }
    for (int i = 0; i<36; i++) {
        if(((flag[i]-47)^(flag[i]-58)^(flag[i]-64)^(flag[i]-91)^(flag[i]-94)^(flag[i]-126))>0) {
            printf("Invalid input\n");
            return 0;
        }
        // 对输入范围的限制
        // '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_`abcdefghijklmnopqrstuvwxyz{|}'
        flag[i] = flag[i] - '0';
    }

    char en_flag[36];
    for (int k = 0; k < 36; k++) {
        int temp = 31; 
        for (int i = 0; i < 36; i++) {
            temp = table_2[table_1[table[k][i]][flag[i]]][temp];
        }
        en_flag[k] = temp;
    }

    for (int i = 0; i < 36; i++) {
        en_flag[i] = en_flag[i] + '0';
    }
    for (int i = 0; i < 36; i++) {
        if(en_flag[i] != result[i]) {
            printf("Invalid flag\n");
            return 0;
        }
    }
    printf("Correct flag\n");
    return 0;
}
```
关键部分
```c
    for (int k = 0; k < 36; k++) {
        int temp = 31; 
        for (int i = 0; i < 36; i++) {
            temp = table_2[table_1[table[k][i]][flag[i]]][temp];
        }
        en_flag[k] = temp;
    }
```
类似于一般的矩阵乘法
table @ flag = en_flag
不同点在于 __加法__ 与 __乘法__ 是分别查table_2与table_1表实现的
那么由高斯消元可以获得结果
__注__：事实上这里是 __mod67域__ 与单表代换(随机生成的对应)```1~67->0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_`abcdefghijklmnopqrstuvwxyz{|})```结合的背景
不知道问题也不大

```python
# 数据自行提取
en_flag =[ord(i)-48 for i in 'H2Frj2dVrSHknSbGZhA{lUAF}blC7lwNQ{CV']
matrix = [[table[36*j+i] for i in range(36)] for j in range(36)]
mul_dict = [[table_1[78*i+j] for j in range(78)] for i in range(78)]
add_dict = [[table_2[78*i+j] for j in range(78)] for i in range(78)]
input_table=[ord(i)-48 for i in '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_`abcdefghijklmnopqrstuvwxyz{|}']
# 获得加法乘法的单位元
for i in range(78):
    if all(mul_dict[i][j]==j for j in input_table):
        mul_I=i
        break
print(mul_I)
for i in range(78):
    if all(add_dict[i][j]==j for j in input_table):
        add_I=i
        break
print(add_I)

def mul(a,b):
    return mul_dict[a][b]

def add(a,b):
    return add_dict[a][b]

def swap_rows(matrix_list, i, j):
    for matrix in matrix_list:
        matrix[i], matrix[j] = matrix[j], matrix[i]

#发现add_dict和mul_dict是对称的，这里我们可以先不考虑左乘和右乘的问题
def multiply_row(matrix_list, i, scalar):
    for matrix in matrix_list:
        matrix[i] = [mul(scalar,x) for x in matrix[i]]

def add_scaled_row(matrix_list, i, j, scalar):
    for matrix in matrix_list:
        matrix[j] = [add(mul(scalar,x),y) for x, y in zip(matrix[i], matrix[j])]

def re_add_get(element):
    for i in range(78):
        if add(element,i)==add_I:
            return i
        
def re_mul_get(element):
    for i in range(78):
        if mul(element,i)==mul_I:
            return i

def gauss_elimination(matrix,target):
    row, col = 0, 0 #当前所在位置
    rows,cols=len(matrix),len(matrix[0])
    assert cols==len(target) and len(target[0])==1 #(i*j) @ (j*1)
    # process:判断是否为0,为0则试图寻找，找到则交换行并处理，找不到则列+1，不为0则处理
    while row < rows and col < cols:
        flag=0
        if matrix[row][col]==add_I: #.is_zero():
            for i in range(row+1,rows):
                if not matrix[i][col]==add_I:#.is_zero():
                    swap_rows([matrix,target],row,i)
                    flag=1
                    break
            if flag==0:
                col+=1
                continue
        if matrix[row][col]!=mul_I:
            scalar = re_mul_get(matrix[row][col])
            multiply_row([matrix,target], row, scalar)
        for i in range(rows):
            if i==row:
                continue
            if matrix[i][col]!=add_I:
                scalar = re_add_get(matrix[i][col])
                add_scaled_row([matrix,target], row, i, scalar)
        row+=1
        col+=1
        continue
    return target

en_flag=[[i] for i in en_flag]
flag=gauss_elimination(matrix,en_flag)
print(''.join([chr(i[0]+48) for i in flag]))

# flag{you_are_final_w1nn3r1_febe3e21}
```

