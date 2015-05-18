# Remove sudo
rm -f /etc/sudoers.d/box

# Greeting
cat <<'EOF' > /.box/greeting
Welcome to Linux Challenge on
      _             _
     | |           (_)
  ___| |_ ___ _ __  _  ___   ___  _ __ __ _
 / __| __/ _ \ '_ \| |/ __| / _ \| '__/ _` |
 \__ \ ||  __/ |_) | | (__ | (_) | | | (_| |
 |___/\__\___| .__/|_|\___(_)___/|_|  \__, |
             | |                       __/ |
             |_|                      |___/

This box runs Ubuntu 14.04. You are logged in as user "box".

Web terminal usage
==================
 * Click the titlebar to drag
 * Double-click the titlebar to maximize
 * Click and drag the lower-right corner to resize
EOF

# Create flag.txt
echo "# this is the first line of flag.txt
STCTF#WellDumped#
# this is the last line of flag.txt" > /home/box/flag.txt
chown box:box /home/box/flag.txt

# Run process that reads flag.txt and sleeps forever
echo "#!/usr/bin/env python3
import os
import time

content = open('/home/box/flag.txt').read()
os.remove('/home/box/flag.txt')
os.remove('/home/box/flagd')
while True:
    time.sleep(1)" > /home/box/flagd

cd /home/box
su box -c "python3 flagd &"
