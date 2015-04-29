#!/bin/bash

rm -f \
    /bin/less /usr/bin/tail* /usr/bin/head /bin/*grep* \
    /usr/bin/*grep* /etc/alternatives/v* /usr/bin/xxd \
    /usr/bin/python* /bin/cat /usr/bin/perl* /usr/bin/vi* /bin/more \
    /bin/sed /usr/bin/*diff* /usr/bin/curl /usr/bin/wget /usr/bin/base64 \
    /bin/nc* /bin/netcat /usr/bin/nano /bin/nano /usr/bin/sort \
    /usr/bin/awk /bin/echo

# /usr/bin/cut?
# /usr/bin/nl?

# Greeting
echo '### Welcome home! ###' > /.box/.greeting

# Update bashrc
echo 'alias echo=/bin/echo' >> /home/box/.bashrc


echo "Noooo, you've managed to read me!

Ok, here's the flag: STCTF#l1nvxH4sN1ceStvff#
" > /home/box/flag.txt

# Remove sudo
rm -f /etc/sudoers.d/box

