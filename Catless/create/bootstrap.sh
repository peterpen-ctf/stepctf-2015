#!/usr/bin/env bash

# sudo apt-get update && sudo apt-get install -y sl cowsay


# Greeting
echo '< Welcome home >
 --------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\ 
                ||----w |
                ||     ||
' > /home/box/.greeting; chown box /home/box/.greeting



# Update bashrc
echo 'tac /home/box/.greeting 2> /dev/null | tac; rm -f /home/box/.greeting' >> /home/box/.bashrc
echo 'alias echo=/bin/echo' >> /home/box/.bashrc
# echo 'alias ls=sl' >> /home/box/.bashrc

# Write the flag
echo "Noooo, you've managed to read me!

Ok, here's the flag: STCTF#l1nvxH4sN1ceStvff#
" > /home/box/flag.txt

# Remove sudo
rm -f /etc/sudoers.d/box

# Remove programs
rm -f \
    /bin/less /usr/bin/tail* /bin/tail* /usr/bin/head /bin/*grep* /usr/bin/tmux \
    /usr/bin/*grep* /etc/alternatives/v* /usr/bin/xxd /usr/bin/strings \
    /usr/bin/python* /bin/cat /usr/bin/perl* /usr/bin/vi* /bin/more \
    /bin/sed /usr/bin/*diff* /usr/bin/curl /usr/bin/wget /usr/bin/base64 \
    /bin/nc* /bin/netcat /usr/bin/nano /bin/nano /bin/echo /usr/bin/sort /usr/bin/awk

# /usr/bin/cut?
# /usr/bin/nl?

