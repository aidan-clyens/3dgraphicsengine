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
    libgtest-dev \
    libx11-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev \
    libxext-dev \
    libwayland-dev \
    libxkbcommon-dev \
    wayland-protocols \
    extra-cmake-modules \
    && rm -rf /var/lib/apt/lists/*

# Default command
COPY entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
