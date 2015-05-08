#!/bin/bash

# openssl req -x509 -sha256 -newkey rsa:2048 -keyout key.pem -out cert.pem -days 1000 -nodes -subj '/CN=2015.step.ctf'

openssl req -x509 -sha256 -newkey rsa:2048 -keyout cert.key -out cert.pem -days 1000 -nodes 
