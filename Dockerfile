# Get the base Ubuntu image from Docker Hub
FROM ubuntu:latest

# Update apps on the base image
RUN apt-get -y update && apt-get install -y

# Install the gcc compiler
RUN apt-get -y install gcc

# Specify the working directory
WORKDIR /ws

# Copy the current folder which contains C source code to the Docker image
COPY . .