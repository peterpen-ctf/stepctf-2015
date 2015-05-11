#! /bin/bash

sudo docker kill ysnp_mariadb
sudo docker rm ysnp_mariadb
sudo docker build -t patrick/ysnp_mariadb .
sudo docker run -d --name ysnp_mariadb patrick/ysnp_mariadb
