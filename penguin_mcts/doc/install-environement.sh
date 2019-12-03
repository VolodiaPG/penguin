apt-get install -y software-properties-common
add-apt-repository -y ppa:ubuntu-toolchain-r/test
apt-get update
apt-get install -y gcc-9 g++-9 cmake cppcheck clang gdb valgrind git && \
    apt-get install -y python2.7 default-jre && \
    apt-get clean autoclean && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*
update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 999 \
 && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 999 \
 && update-alternatives --install /usr/bin/cc  cc  /usr/bin/gcc-9 999 \
 && update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-9 999