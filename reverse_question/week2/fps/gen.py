#!/usr/bin/env python3

from hashlib import *
import os
import random

def gen_exe(flag, strip=True):
	print(flag)
	filename = gen_random_filename()
	while os.path.exists(filename):
		filename = gen_random_filename()
	for name in ['Welcome','Game']:
		with open(name+'.c', 'r') as srcfile:
			src = srcfile.read().split('###')

		envs = {'flag': flag}
		for i in range(len(src)):
			if src[i].strip().startswith('eval:'):
				src[i] = '{}'.format(eval(src[i].strip()[5: ], envs))
			elif src[i].strip().startswith('exec:'):
				exec(src[i].strip()[5: ], envs)
				src[i] = ''
		# print(f'{name} finished')

		tmpfile = open(name +'1' + '.c', 'w')
		tmpfile.write(''.join(src))
		tmpfile.close()

	# sudo apt update && sudo apt-get install gcc-mingw-w64-i686
	# cmd = 'i686-w64-mingw32-gcc ./{0}.c -o ./exes/{0}.exe'
	cmd = 'gcc ./Welcome1.c Game1.c -o ./exes/{0}.exe'
	if strip: cmd += ' && strip ./exes/{0}.exe'
	cmd = cmd.format(filename)
	result = os.system(cmd)
	if result == 0: # compile success
		# for i in ['Welcome1.c', 'Game1.c']:
		# 	os.remove(i)
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
	salt = 'Winner'
	hash = md5
	# flag_inner = 'we1c0m3_tO_R3V3rse_Englneer1Ng'
	flag_inner = 'you_are_best_player'

	# flag = f"flag{{{flag_inner}_{hash(salt + token)[4: 12]}}}"
	flag = 'flag{' + flag_inner + '_' + hash((salt + token).encode()).hexdigest()[4: 13] + '}'
	return gen_exe(flag)

if __name__ == '__main__':
	token = ''.join(random.choice('0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ') for i in range(32))
	# token = '16:MEQCIF+0Lr/jIJCZdnoJpT/xy/Uy0m99x3xz6hOEGh2hzH8YAiBFKhySTBwAIlX33DMmdEYZJrtFTJZxAvHk2yrkzux7MQ=='
	print(run(token))