#####################
# Main Docker Image #
#####################

FROM node:13.10-buster
ENV EMSCRIPTEN_VERSION 1.39.2
LABEL maintainer="volodia.parolguarino@gmail.com"

ARG USERNAME=develop
ARG USER_UID=3000
ARG USER_GID=$USER_UID

RUN apt-get update
RUN apt-get install -y software-properties-common
RUN apt-get update

RUN apt-get install -y apt-utils build-essential manpages-dev
RUN apt-get install -y cmake cppcheck clang gdb valgrind git && \
    apt-get install -y python2.7 default-jre

# Angular
RUN npm install -g @angular/cli
    
# RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 999 \
#  && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 999 \
#  && update-alternatives --install /usr/bin/cc  cc  /usr/bin/gcc-9 999 \
#  && update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-9 999

# RUN useradd -ms /bin/bash develop
# RUN echo "develop   ALL=(ALL:ALL) ALL" >> /etc/sudoers
# Create a non-root user to use if preferred - see https://aka.ms/vscode-remote/containers/non-root-user.
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME \
    # [Optional] Add sudo support for the non-root user
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME\
    && chmod 0440 /etc/sudoers.d/$USERNAME

USER $USERNAME

RUN git clone https://github.com/emscripten-core/emsdk.git /home/$USERNAME/emsdk
WORKDIR /home/$USERNAME/emsdk
RUN echo $EMSCRIPTEN_VERSION
RUN chmod +x ./emsdk && chmod +x ./emsdk_env.sh
RUN ./emsdk install $EMSCRIPTEN_VERSION-fastcomp
RUN ./emsdk activate $EMSCRIPTEN_VERSION-fastcomp
RUN /bin/bash -c "source ./emsdk_env.sh"

# adding libs to system
USER root
RUN cp -r /home/$USERNAME/emsdk/fastcomp/emscripten/system/include/* /usr/local/include/

# Clean up APT when done.
RUN apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

USER $USERNAME

# expose port to access the wasm files later from the host
EXPOSE 8080 9876 4200