#!/bin/bash

# Get host UID and GID
_UID=$(id -u)
_GID=$(id -g)

# Image and container names
IMAGE_NAME=platformio-dev
CONTAINER_NAME=PIO_SMW_ROTOM

# Remove any existing container with the same name
if [ "$(docker ps -aq -f name=^${CONTAINER_NAME}$)" ]; then
  echo "Removing existing container: $CONTAINER_NAME"
  docker rm -f $CONTAINER_NAME
fi

# Force rebuild the PlatformIO container image
docker build --no-cache -t $IMAGE_NAME -f Dockerfile \
  --build-arg USER_UID=${_UID} \
  --build-arg USER_GID=${_GID} .

# Run the container
docker run -it -d --name $CONTAINER_NAME \
  --device /dev/ttyUSB0:/dev/ttyUSB0 \
  -v $(pwd)/../../:/workspace/ \
  $IMAGE_NAME

# Tail logs
docker logs -f $CONTAINER_NAME &
