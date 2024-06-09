#include <stdio.h>
#include <math.h>
#include <string.h>
###exec:
def to_cx_int_arry(s):
    t = '{'
    for i in s:
        t += str(i) + ','
    t+='}'
    return t

length=len(flag)
up,down=[],[]
import random
from math import sqrt
for i in range(5):
    down.append(random.randint(1, 10**1))
    up.append( int( (sqrt(down[-1])+ord(flag[i]))**2 ))
for i in range(5):
    down.append(random.randint(10**1, 10**3))
    up.append( int( (sqrt(down[-1])+ord(flag[5+i]))**2 ))
for i in range(5):
    down.append(random.randint(10**3, 10**5))
    up.append( int( (sqrt(down[-1])+ord(flag[10+i]))**2 ))
for i in range(5):
    down.append(random.randint(10**5, 10**7))
    up.append( int( (sqrt(down[-1])+ord(flag[15+i]))**2 ))
for i in range(5):
    down.append(random.randint(10**7, 10**9))
    up.append( int( (sqrt(down[-1])+ord(flag[20+i]))**2 ))
for i in range(5):
    down.append(random.randint(10**9, 10**11))
    up.append( int( (sqrt(down[-1])+ord(flag[25+i]))**2 ))
for i in range(5):
    down.append(random.randint(10**11, 10**13))
    up.append( int( (sqrt(down[-1])+ord(flag[30+i]))**2 ))
for i in range(5):
    down.append(random.randint(10**13, 10**15))
    up.append( int( (sqrt(down[-1])+ord(flag[35+i]))**2 ))


array_str = '{'
for i in range(len(up)):
    array_str += '{' + str(down[i]) + 'LL' + ',' + str(up[i]) + 'LL' + '},'
array_str = array_str.rstrip(',') + '}'

###
// 定义被积函数的宏
#define f(x) (1 / (2*sqrt(x)))

// 梯形积分函数
double integration(double a, double b, double step) {
    double x = a;
    double integral = 0.0;

    // 累积步长小于等于上限时继续累加
    while (x < b) {
        double next_x = x + step;
        if (next_x > b) {
            next_x = b; // 限制下一个x值在上限内
        }
        integral += 0.5 * (f(x) + f(next_x)) * (next_x - x);
        x = next_x; // 更新x值
    }

    return integral;
}
int main() {
    // 定义积分上下限的集合
    double intervals[][2] = ###eval:array_str ###; // 每一行是一对积分上下限
    int num_intervals = sizeof(intervals) / sizeof(intervals[0]); // 计算积分集合的数量
    // 逐一计算并输出积分结果
    char flag[50] = "";
    char str_result[2] = ""; // 要存储字符和终止符 '\0'
    for (int i = 0; i < num_intervals; i++) {
        double result = integration(intervals[i][0], intervals[i][1], 0.0001); // 步长设为0.00001
        int rounded_result = (int)(result + 0.5); // 将结果四舍五入到最近的整数
        str_result[0] = (char)rounded_result; // 将整数转换为字符
        str_result[1] = '\0'; // 添加终止符
        strcat(flag, str_result);
        printf("flag is %s now\n", flag); // 输出结果
    }
    printf("That's all"); // 输出结果字符串
    return 1;
}


