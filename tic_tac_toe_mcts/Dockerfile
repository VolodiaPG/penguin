#####################
# Main Docker Image #
#####################

# FROM trzeci/emscripten:sdk-tag-1.38.25-64bit
# FROM trzeci/emscripten-slim:sdk-tag-${EMSCRIPTEN_VERSION}-64bit
FROM ubuntu:bionic-20191029
ENV EMSCRIPTEN_VERSION 1.39.2
LABEL maintainer="volodia.parolguarino@gmail.com"

# ENV EMSDK_VERSION 1.38.45

RUN apt-get update
RUN apt-get install -y software-properties-common
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt-get update

RUN apt-get install -y gcc-9 g++-9 cmake cppcheck clang gdb valgrind git && \
    apt-get install -y python2.7 default-jre && \
    apt-get install doxygen doxygen-doc graphviz\
    apt-get clean autoclean && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*
    
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 999 \
 && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 999 \
 && update-alternatives --install /usr/bin/cc  cc  /usr/bin/gcc-9 999 \
 && update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-9 999

RUN useradd -ms /bin/bash develop
RUN echo "develop   ALL=(ALL:ALL) ALL" >> /etc/sudoers
# RUN mkdir /home/develop

USER develop

RUN git clone https://github.com/emscripten-core/emsdk.git /home/develop/emsdk
WORKDIR /home/develop/emsdk
RUN echo $EMSCRIPTEN_VERSION
RUN chmod +x ./emsdk && chmod +x ./emsdk_env.sh
RUN ./emsdk install $EMSCRIPTEN_VERSION-fastcomp
RUN ./emsdk activate $EMSCRIPTEN_VERSION-fastcomp
RUN /bin/bash -c "source ./emsdk_env.sh"

# adding libs to system
USER root
RUN cp -r /home/develop/emsdk/fastcomp/emscripten/system/include/* /usr/local/include/

USER develop

# VOLUME /home/develop
WORKDIR /home/develop

#####################
# User Docker Image #
#####################

WORKDIR /home/develop

USER root
COPY ./doc/install-dependencies.sh /usr/

# Remove windows EOL
RUN sed -i -e 's/\r$//' /usr/install-dependencies.sh

RUN chmod +x /usr/install-dependencies.sh

RUN apt-get update
RUN /usr/install-dependencies.sh

# Clean up APT when done.
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

USER develop

# expose port to access the wasm files later from the host
EXPOSE 8080:8080