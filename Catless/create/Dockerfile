FROM ubuntu:14.04
MAINTAINER tonyo

RUN /bin/rm -f \
    /bin/less /usr/bin/tail /usr/bin/head /bin/*grep* \
    /usr/bin/*grep* /etc/alternatives/v* /usr/bin/xxd \
    /usr/bin/python* /bin/cat /usr/bin/perl* /usr/bin/vi* /bin/more \
    /bin/sed /usr/bin/*diff* /usr/bin/curl /usr/bin/wget /usr/bin/base64 \
  && useradd -m user
# /usr/bin/cut?
# /usr/bin/nl?

COPY flag.txt /home/user/flag.txt

CMD cd /home/user && while true; do su user; done
