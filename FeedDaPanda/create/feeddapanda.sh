#! /bin/bash

sudo docker kill web100
sudo docker rm web100
sudo docker build -t patrick/web100 .
sudo docker run -d --name web100 -p 127.0.0.1:13371:8080 patrick/web100