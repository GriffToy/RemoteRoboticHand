import socket
import RPi.GPIO as GPIO
import serial

GPIO.setmode(GPIO.BCM)
GPIO.cleanup()
GPIO.setwarnings(False)
GPIO.setup(12,GPIO.OUT)

from signal import signal, SIGPIPE, SIG_DFL
signal(SIGPIPE,SIG_DFL)

HOST = '10.16.8.155' # Server IP
PORT = 1234 # Server Port : netstat -a | grep 123
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print 'Socket created'

ARDUINOUSBPORT = '/dev/ttyACM0'
ser = serial.Serial(ARDUINOUSBPORT, 9600) # 9600 is the baud rate
 
#managing error exception
try:
    s.bind((HOST, PORT))
except socket.error:
    print 'Bind failed '


s.listen(5)
print 'Socket awaiting messages'
(conn, addr) = s.accept()
print 'Connected'

# awaiting for message
while True:    
    data = conn.recv(1024)
    if data != '-1':
        print 'Received data: ' + data
        ser.write(data + '\n')
        reply  = ''
        # Wait for reply from arduino
        reply = reply + ser.readline()
        print 'reply from arduino: ' + reply
        # Send reply
        conn.send(reply)
conn.close() # Close connections
