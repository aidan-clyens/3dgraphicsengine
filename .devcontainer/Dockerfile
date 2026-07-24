FROM ubuntu:24.04

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive

RUN apt-get install -y --no-install-recommends \
    ca-certificates \
    git \
    vim \
    wget \
    curl \
    file \
    openssh-client \
    cmake \
    build-essential \
    gdb \
    pkg-config \
    x11-apps \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    freeglut3-dev \
    mesa-utils \
    mesa-common-dev \
    libglew-dev \
    libglfw3-dev \
    libgtest-dev \
    libassimp-dev \
    && rm -rf /var/lib/apt/lists/*

ENV DISPLAY=host.docker.internal:0.0

# Default command
COPY entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
