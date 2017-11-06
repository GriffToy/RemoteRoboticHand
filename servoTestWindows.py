import socket
import random
import time
import serial
 
HOST = '10.16.8.155' # Server IP
PORT =  1234 # Server Port
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST,PORT))

ARDUINOUSBPORT = '/dev/ttyACM0'
ser = serial.Serial(ARDUINOUSBPORT, 9600)

while True:
    	#command = raw_input('Command > ')
	#command = random.randint(0, 120)
	#read from arduino
	command = ser.readline()
	print 'Sending command: '
	print command
	s.send(command)
	#wait for reply from pi
	reply = ''
	reply = s.recv(1024)
        print 'Reply from raspberry pi: '
	print reply
	#Send to arduino
	ser.write(reply)
