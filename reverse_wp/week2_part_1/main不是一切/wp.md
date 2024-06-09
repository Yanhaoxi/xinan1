# main
![main逻辑](./png/屏幕截图%202024-02-15%20162032.png)
发现几乎什么也没有，那么打开_main()看看

# _main
![_main逻辑](./png/屏幕截图%202024-02-15%20162133.png) 

可以猜测这里做的是一次初始化，且仅进行一次

## _main的调用
![_main的调用](./png/屏幕截图%202024-02-15%20162146.png)
进入看一看_main的第一次调用

## _main的第一次调用
![_main的第一次调用](./png/屏幕截图%202024-02-15%20162255.png)

可以发现他是在main前调用的
（事实上这部分做的是程序的初始化）

# _do_global_ctors
进入_main的_do_global_ctors
![_do_global_ctors](./png/屏幕截图%202024-02-15%20162408.png)

refptr__CTOR_LIST 储存着一个地址

![refptr__CTOR_LIST](./png/屏幕截图%202024-02-15%20162514.png)

这个地址首项是-1，剩下的是函数地址，以0结尾

![__CTOR_LIST](./png/屏幕截图%202024-02-15%20162527.png)

再回来看_do_global_ctors的逻辑：先获取到函数地址的个数赋值给v0,然后依次执行这些函数
>atexit(_do_global_dtors);：在执行完所有全局构造函数后，注册 _do_global_dtors() 函数，在程序退出时执行全局析构函数。这个函数的作用是确保在程序退出时执行全局析构函数，进行清理工作,没有用到这里暂时就不分析了

# 发现真相
![](./png/屏幕截图%202024-02-15%20162548.png)
![](./png/屏幕截图%202024-02-15%20162557.png)

原来这里有个类的构造函数
![](./png/屏幕截图%202024-02-15%20162607.png)
同时析构函数也被atexit注册
![](./png/屏幕截图%202024-02-15%20162633.png)
![](./png/屏幕截图%202024-02-15%20162642.png)




# get_input
输入处理部分
主要逻辑即为线性扫描字符串并替换掉flag
故构造fflaglag即可通过密码验证
输入的flag做了初步处理

```c
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
```

# validate_input
```c
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
```
解密：
```python
encrypted_flag=[    12,  21,  16,  65,  19,  10,  52,  61, 115,  70, 
  115, 118, 117, 105,  47,  50, 107, 111, 104,  57, 
   52,  80,  83,   9,  15,  10,  75,   5,  74,   6, ]
a=encrypted_flag
a[-2]=a[-2]^a[-1]
a[-3]=a[-3]^a[-2]^a[-1]
for i in range(len(a)-4,-1,-1):
    a[i]=a[i]^a[i+1]^a[i+2]^a[i+3]
for i in range(len(a)):
    a[i]=a[i]^0x66^i
print(bytes(a).decode('utf-8'))

# flag{m41n_1s_n0t_411_7d878226}
```