FROM ubuntu:14.04

COPY reader tag run.sh ~
WORKDIR ~
RUN chmod +x run.sh reader tag
RUN apt-get install nmap
CMD ./run.sh
