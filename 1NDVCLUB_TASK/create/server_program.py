import socket, threading, sys, os
from datetime import datetime
from constants import *
from time import sleep
import gansta_eye

class ClientThread(threading.Thread):
    def __init__(self, client_socket, cleint_ip, client_port):
        threading.Thread.__init__(self)
        self.ip = cleint_ip
        self.port = client_port
        self.client_socket = client_socket
        self.client_socket.settimeout(socket_timeout)
        self.id = str(datetime.now()).replace(":", "-").replace(".", "-").replace(" ", "-")
        self.dead = False
        print "#::New thread started for ({0}, ({1}))".format(str(cleint_ip), str(client_port))
    
    def validate_video(self, video_file, letter):
        print "#:: Let's check u..."
        return gansta_eye.detectIt(video_file, letter)

    def run(self):    
        print "#{}::Listening for requests.".format(self.id)
        target_string = "1NDVCLUB"
        validated = 0
        for letter in target_string:
            print "#::Server is expecting", letter
            letter_video = None
            video_created = False
            client_bytes = "CamStudio"
            bytes_received = 0
            print "#::Ready to receive..."
            while len(client_bytes):
                try:
                    client_bytes = self.client_socket.recv(input_chunk_size)
                    bytes_received += len(client_bytes)
                    if bytes_received > max_size_bytes:
                        raise Exception("#::Too long video. Ain't u a cop?")
                    if client_bytes and client_bytes != "JustALilByte":
                        if not video_created: #lazy here
                            letter_video = open("video_{0}_{1}.avi".format(letter, self.id), 'wb')
                            video_created = True
                        letter_video.write(client_bytes)
                        letter_video.flush()
                        print "-",
                    else:
                        print
                        if video_created:
                            print "#::Shiip, it seems your video is over."
                            letter_video.flush()
                            letter_video.close()
                            print "#::video_{0}_{1} is saved.".format(letter, self.id)
                        else:
                            print "#::Nothin' from u nothin' from me, baby."
                        break
                except Exception as some_error:
                        print "#{0}::ERROR({1})".format(self.id, str(some_error))
                        break
            if letter_video is not None:
                filename = "video_{0}_{1}.avi".format(letter, self.id)
                if self.validate_video(filename, letter):
                    print "#::Cool, br0!"
                    validated += 1
                    os.remove(filename)
                    print "#::I have removed all da evidence, my little homie. Relax for a while and keep pushin'!"
                    sleep(pause)
                else:
                    print "#::U've made a mistake. VIP zone ain't for u."
                    os.remove(filename)
                    print "#::I do not need your video now, d0ll. I have thrown it away."
                    break
            else:
                print "#::No video - no deal. Get out from our hood."
                break
        if validated == len(target_string):
            print "#::Now you are in our club, man. Take your gun."
            try:
                flag_file = open(".\\test_folder\\flag.txt", "r")
                flag = flag_file.readline()
                flag_file.close()
                print flag
                self.client_socket.send(flag)
                print "#::Use it as a real gangsta."
            except Exception as error:
                print "#::Worse for you, baby.", error
        else:
            print "See ya."
        self.client_socket.close()
        self.dead = True
        return

def main():
    out = sys.stdout
    host = hosts
    port = server_port
    server_socket = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind((host, port))
    client_threads = []
    server_socket.listen(max_users)
    while True:
        try:
            print "\n~~~Listening for incoming connections...(online:" + str(len(client_threads))+ ")\n"
            (new_client_socket, (client_ip, client_port)) = server_socket.accept()
            client_thread = ClientThread(new_client_socket, client_ip, client_port)
            client_thread.start()
            client_threads.append(client_thread)
            for thread in client_threads:
                if thread.dead:
                    client_threads.remove(thread)
        except:
            print "~~~About to break..."
            break  
    server_socket.close()
    sys.stdout = out
    print "~~~PROGRAM OVER"
        
main()