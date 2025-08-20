# Simple "REST API" c server

This example utilizes microhttpd package by GNU

to run this you need to have docker installed on your machine

## setup and run:

First build the image:
```bash
docker build -t c-rest-server . 
```

then run the image and expose the inner 8080
```bash
docker run -p 8080:8080 c-rest-server
```