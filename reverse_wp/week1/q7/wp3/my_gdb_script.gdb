set logging file my_gdb_log.txt
set logging enabled on
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



