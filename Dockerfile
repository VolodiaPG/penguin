#####################
# Main Docker Image #
#####################

FROM ubuntu:bionic
LABEL maintainer="volodia.parolguarino@gmail.com"

RUN apt-get update
RUN apt-get install -y software-properties-common
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt-get update

RUN apt-get install -y gcc-9 g++-9 cmake cppcheck clang gdb valgrind git && \
    apt-get clean autoclean && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*
    
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 999 \
 && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 999 \
 && update-alternatives --install /usr/bin/cc  cc  /usr/bin/gcc-9 999 \
 && update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-9 999

RUN useradd -ms /bin/bash develop
RUN echo "develop   ALL=(ALL:ALL) ALL" >> /etc/sudoers

USER develop
RUN mkdir /home/develop/project
VOLUME /home/develop/project
WORKDIR /home/develop/project

#####################
# User Docker Image #
#####################

USER root
COPY ./doc/install-dependencies.sh /usr/

#Remove windows EOL
RUN sed -i -e 's/\r$//' /usr/install-dependencies.sh

RUN chmod +x /usr/install-dependencies.sh

RUN apt-get update
RUN /usr/install-dependencies.sh

# Clean up APT when done.
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

USER develop