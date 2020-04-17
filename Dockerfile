#####################
# Main Docker Image #
#####################

FROM node:13.10-buster
ENV EMSCRIPTEN_VERSION 1.39.11
LABEL maintainer="volodia.parolguarino@gmail.com"

RUN apt-get update
RUN apt-get install -y software-properties-common
RUN apt-get update

RUN apt-get install -y apt-utils build-essential manpages-dev
RUN apt-get install -y cmake cppcheck clang gdb valgrind git && \
    apt-get install -y python2.7 default-jre

# Angular
RUN npm install -g @angular/cli

RUN git clone https://github.com/emscripten-core/emsdk.git /emsdk
WORKDIR /emsdk
RUN echo $EMSCRIPTEN_VERSION
RUN chmod +x ./emsdk && chmod +x ./emsdk_env.sh
RUN ./emsdk install $EMSCRIPTEN_VERSION
RUN ./emsdk activate $EMSCRIPTEN_VERSION
RUN /bin/bash -c "source ./emsdk_env.sh"

# adding libs to system
USER root
RUN cp -r /emsdk/upstream/emscripten/system/include/* /usr/local/include/

# Clean up APT when done.
RUN apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# expose port to access the wasm files later from the host
EXPOSE 8080 5500 9876 4200