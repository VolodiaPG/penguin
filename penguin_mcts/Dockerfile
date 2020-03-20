#####################
# Main Docker Image #
#####################

FROM node:13.10-buster
ENV EMSCRIPTEN_VERSION 1.39.2
LABEL maintainer="volodia.parolguarino@gmail.com"

RUN apt-get update
RUN apt-get install -y software-properties-common
RUN apt-get update

RUN apt-get install -y apt-utils build-essential manpages-dev
RUN apt-get install -y cmake cppcheck clang gdb valgrind git && \
    apt-get install -y python2.7 default-jre && \
    apt-get clean autoclean && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*

# Angular
RUN npm install -g @angular/cli
    
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 999 \
 && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 999 \
 && update-alternatives --install /usr/bin/cc  cc  /usr/bin/gcc-9 999 \
 && update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-9 999

RUN useradd -ms /bin/bash develop
# RUN echo "develop   ALL=(ALL:ALL) ALL" >> /etc/sudoers

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

# Clean up APT when done.
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

USER develop

# expose port to access the wasm files later from the host
EXPOSE 8080 9876 4200