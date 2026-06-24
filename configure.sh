set -eux;
apt-get update;
apt-get upgrade -y;
apt-get install -y --no-install-recommends \
  ca-certificates \
  gpg \
  wget \
  build-essential \
  net-tools \
  cmake \
  gdb \
  git \
  vim \
  wget \
  curl \
  autotools-dev \
  automake \
  libc6-dbg \
  openssh-client \
  python3 \
  python3-dev \
  python3-pip \
  python3-venv && \
  rm -rf /var/lib/apt/lists/*;
