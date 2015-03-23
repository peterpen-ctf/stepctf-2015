#!/usr/bin/env python3
import socket
import sys
import os
import signal

def main():
    if len(sys.argv) < 3 or not sys.argv[1].isnumeric():
        print("Usage: %s port program [arguments]" % sys.argv[0])
        exit(0)
    program = sys.argv[2]
    port    = int(sys.argv[1])
    args    = sys.argv[2:]
        
    child_pids  = []
    child_limit = 5
    
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(('',port))

    sock.listen(0)

    while 1:
        client, address = sock.accept()
        pid = os.fork()
        if pid == 0:
            # child
            sys.stdout.write('[+] new connection from %s:%d\n' % (address[0], address[1]))
            sock.close()
            os.dup2(client.fileno(), 1) # stdout
            os.dup2(client.fileno(), 0) # stdin
            client.close()
            os.execv(program, args)
            exit(0)
        # parent
        child_pids.append(pid)
        if len(child_pids) > child_limit:
            sys.stdout.write('[*] killing...\n')
            os.kill(child_pids[0], 15)
        try:
            status = os.waitpid(-1, os.WNOHANG);
            while status[0] > 0:
                sys.stdout.write('[-] %d returned %d\n' % status)
                child_pids.remove(status[0])
                status = os.waitpid(-1, os.WNOHANG);
        except OSError as e:
            sys.stdout.write(str(e) + '\n')

            
if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt as k:
        sys.stdout.write("Ctrl+C...\n")
    finally:
        sys.stdout.write("finally kill...\n")
        os.kill(0, 15)
        
