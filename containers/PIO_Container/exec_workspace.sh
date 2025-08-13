#!/bin/bash

# This must be your running container name
CONTAINER_NAME="PIO_SMW_ROTOM"  

# Enter the container and switch to desired directory
docker exec -it $CONTAINER_NAME bash -c "cd ../../workspace/ && exec bash"
