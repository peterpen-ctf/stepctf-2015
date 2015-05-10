from constants import *
import socket               # Import socket module

s = socket.socket()         # Create a socket object
server_host = socket.gethostname() # Get local machine name

s.connect((server_host, server_port))
video = open('test_1.avi','r')
chunk = "trvpLord" if video else ""
while chunk:
    chunk = video.read(1024)
    s.send(chunk)
    print 'Sent some part...'
video.close()
print "Done Sending"
s.close   