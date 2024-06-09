#!/usr/bin/env python3

from hashlib import *
import os
import random

def gen_exe(flag, strip=False):
	print(flag)
	filename = gen_random_filename()
	while os.path.exists(filename):
		filename = gen_random_filename()
	with open('template.c', 'r',encoding='utf-8') as srcfile:
		src = srcfile.read().split('###')

	envs = {'flag': flag}
	for i in range(len(src)):
		if src[i].strip().startswith('eval:'):
			src[i] = '{}'.format(eval(src[i].strip()[5: ], envs))
		elif src[i].strip().startswith('exec:'):
			exec(src[i].strip()[5: ], envs)
			src[i] = ''

	tmpfile = open(filename + '.c', 'w')
	tmpfile.write(''.join(src))
	tmpfile.close()

	# sudo apt update && sudo apt-get install gcc-mingw-w64-i686
	# cmd = 'i686-w64-mingw32-gcc ./{0}.c -o ./exes/{0}.exe'
	cmd = 'gcc ./{0}.c -o ./exes/{0}.exe'
	if strip: cmd += ' && strip ./exes/{0}.exe'
	cmd = cmd.format(filename)
	result = os.system(cmd)
	if result == 0: # compile success
		os.remove(filename + '.c')
		return filename
	else:
		return None
	# os.remove(filename + '.exe')

def gen_random_filename(length=8):
	table = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
	name = ''
	for i in range(length):
		name += random.choice(table)
	return name

def run(token):
	salt = 'Encrypt20n'
	hash = md5
	# flag_inner = 'we1c0m3_tO_R3V3rse_Englneer1Ng'
	flag_inner = 'brut3_f0rc3_1s_4wes0m3'

	# flag = f"flag{{{flag_inner}_{hash(salt + token)[4: 12]}}}"
	flag = 'flag{' + flag_inner + '_' + hash((salt + token).encode()).hexdigest()[4: 12]+ '}'
	return gen_exe(flag)

if __name__ == '__main__':
	token = ''.join(random.choice('0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ') for i in range(32))
	# token = '16:MEQCIF+0Lr/jIJCZdnoJpT/xy/Uy0m99x3xz6hOEGh2hzH8YAiBFKhySTBwAIlX33DMmdEYZJrtFTJZxAvHk2yrkzux7MQ=='
	print(run(token))