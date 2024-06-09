#!/usr/bin/env python3

from hashlib import *
import os
import random

def gen_exe(flag, strip=False):
	print(flag)
	filename = gen_random_filename()
	while os.path.exists(filename):
		filename = gen_random_filename()
	with open('template.cpp', 'r',encoding='utf-8') as srcfile:
		src = srcfile.read().split('###')

	envs = {'flag': flag}
	for i in range(len(src)):
		if src[i].strip().startswith('eval:'):
			src[i] = '{}'.format(eval(src[i].strip()[5: ], envs))
		elif src[i].strip().startswith('exec:'):
			exec(src[i].strip()[5: ], envs)
			src[i] = ''

	tmpfile = open(filename + '.cpp', 'w')
	tmpfile.write(''.join(src))
	tmpfile.close()

	# sudo apt update && sudo apt-get install gcc-mingw-w64-i686
	# cmd = 'i686-w64-mingw32-gcc ./{0}.c -o ./exes/{0}.exe'
	cmd = 'g++ -static -static-libgcc -static-libstdc++ ./{0}.cpp -o ./exes/{0}.exe'
	if strip: cmd += ' && strip ./exes/{0}.exe'
	cmd = cmd.format(filename)
	result = os.system(cmd)
	if result == 0: # compile success
		os.remove(filename + '.cpp')
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
	salt = 'loop'
	hash = md5
	# flag_inner = 'we1c0m3_tO_R3V3rse_Englneer1Ng'
	flag_inner = 'equal_sign_is_overloaded'

	# flag = f"flag{{{flag_inner}_{hash(salt + token)[4: 12]}}}"
	flag = 'flag{' + flag_inner + '_' + hash((salt + token).encode()).hexdigest()[4: 12]+ '}'
	return gen_exe(flag)

if __name__ == '__main__':
	# token = ''.join(random.choice('0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ') for i in range(32))
	token = '18:MEUCIG75rlWoeD4rOiTJuQ3zb0Qb3pE3pIFiMMWVcBHRk/aRAiEAxkH/pc+txjFHP/54iYrLcLAwgtW/jmDOTIP67n3fEmE='
	print(run(token))