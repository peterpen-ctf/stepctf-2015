#! /bin/bash

sudo docker kill ysnp
sudo docker rm ysnp
sudo docker build -t patrick/ysnp .
sudo docker run -d --link ysnp_mariadb:ysnp_mariadb --name ysnp patrick/ysnp
