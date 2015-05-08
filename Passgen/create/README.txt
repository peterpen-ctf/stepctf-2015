0. Start Docker in TCP mode

$ sudo docker -d -H tcp://localhost:1234

1. Build the Docker image

$ sudo docker -H tcp://localhost:1234 build -t passgen-ubuntu .

2. Start a container

# sudo docker -H tcp://localhost:1234 run -it passgen-ubuntu

3. Run commands from gen.sh

