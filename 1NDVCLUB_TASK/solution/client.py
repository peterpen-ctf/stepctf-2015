from constants import *
import socket               # Import socket module
from time import sleep

print "Starting"
s = socket.socket()         # Create a socket object
server_host = "78.47.155.75" # Get local machine name

s.connect((server_host, server_port))
for letter in "1NDVCLUB":
    filename = "test_"+letter+".avi"
    print "Opening ", filename
    video = open(filename,"r")
    go = raw_input("send?:")
    chunk = "trvpLord" if video else ""
    while chunk:
        chunk = video.read(1024)
        s.send(chunk)
        print 'Sent some part...'
    video.close()
    s.send("JustALilByte")
    response = str(s.recv(1024))
    print "Sending:", response
    print "----------------------"
flag = str(s.recv(1024))
print "Got:", flag
s.close
