#! /bin/bash

sudo docker kill feeddapanda
sudo docker rm feeddapanda
sudo docker build -t patrick/feeddapanda .
sudo docker run -d --name feeddapanda patrick/feeddapanda
