FROM mcr.microsoft.com/devcontainers/cpp:2-ubuntu24.04

ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="3.25.2"

# Optionally install the cmake for vcpkg
COPY ./reinstall-cmake.sh /tmp/

RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
    chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive

RUN apt-get install -y --no-install-recommends \
    ca-certificates \
    git \
    vim \
    wget \
    curl \
    file \
    openssh-client \
    pkg-config \
    libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev \
    mesa-utils mesa-common-dev libglew-dev libglfw3-dev \
    libgtest-dev \
    libassimp-dev \
    && rm -rf /var/lib/apt/lists/*

# Default command
COPY entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
