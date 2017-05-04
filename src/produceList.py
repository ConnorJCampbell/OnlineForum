#!/usr/bin/python3

import sys
import os
import os.path
import curses
import subprocess

if __name__ == "__main__":

	#exit if no username is provided
	if len(sys.argv) < 2:
		print("Please run with a username. Exiting program.")
		sys.exit()

	#format username
	username = str(sys.argv[1])
	#for i in range(2, len(sys.argv)):
	#	username += " "
	#	username += str(sys.argv[i])

	#Check if the streams exist
	subprocess.call(['./db', '-access', username])
	
	

	