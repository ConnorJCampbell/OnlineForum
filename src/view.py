#!/usr/bin/python3

import sys
import os
import os.path
import subprocess

if __name__ == "__main__":


	#format username
	username = str(sys.argv[1])
	choice  = str(sys.argv[2])
	flag = sys.argv[3]
	offset = int(sys.argv[4])
	

	if(choice == 'all'):
		if(flag == 'a'):
			subprocess.call(['./db', '-increase', username, choice, str(offset)])

		elif(flag == 's'):
			subprocess.call(['./db', '-decrease', username, choice, str(offset)])

		else:
			subprocess.call(['./db', '-viewAll', username, choice])
	else:
		if(flag == 'v'):
			subprocess.call(['./db', '-view', username, choice])

		elif(flag == 'a'):
			subprocess.call(['./db', '-increase', username, choice, str(offset)])

		elif(flag == 's'):
			subprocess.call(['./db', '-decrease', username, choice, str(offset)])

		elif(flag == 'm'):
			subprocess.call(['./db', '-mark', username, choice])