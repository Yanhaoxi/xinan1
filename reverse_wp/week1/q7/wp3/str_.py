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
125
"""
print(''.join([chr(int(char)) for char in str_.split()]))