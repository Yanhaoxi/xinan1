encrypted_flag=[   12,  21,  16,  65,  19,  10,  52,  61, 115,  70, 
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