sudo docker build -t patrick/web100 .
sudo docker run -it -d -p 13371:8080 patrick/web100
