set -eux;

apt-get install -y --no-install-recommends \
  gpg \
  wget

wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null

apt-get install -y --no-install-recommends \
  ca-certificates \
  build-essential \
  net-tools \
  cmake \
  gdb \
  git \
  vim \
  wget \
  curl \
  file \
  autotools-dev \
  automake \
  libc6-dbg \
  openssh-client \
  pkg-config \
  libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev \
  mesa-utils mesa-common-dev libglew-dev libglfw3-dev \
  libgtest-dev \
  libassimp-dev \
  python3 \
  python3-dev \
  python3-pip \
  python3-venv && \
  rm -rf /var/lib/apt/lists/*;

echo "Finished Ubuntu configuration for 3D-graphics-engine!"