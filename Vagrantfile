# -*- mode: ruby -*-
# vi: set ft=ruby :

# variables
EMSCRIPTEN_VERSION = "1.39.2"


# All Vagrant configuration is done below. The "2" in Vagrant.configure
# configures the configuration version (we support older styles for
# backwards compatibility). Please don't change it unless you know what
# you're doing.
Vagrant.configure("2") do |config|
  # The most common configuration options are documented and commented below.
  # For a complete reference, please see the online documentation at
  # https://docs.vagrantup.com.

  # Every Vagrant development environment requires a box. You can search for
  # boxes at https://vagrantcloud.com/search.
  config.vm.box = "ubuntu/bionic64"

  # Disable automatic box update checking. If you disable this, then
  # boxes will only be checked for updates when the user runs
  # `vagrant box outdated`. This is not recommended.
  # config.vm.box_check_update = false

  # Create a forwarded port mapping which allows access to a specific port
  # within the machine from a port on the host machine. In the example below,
  # accessing "localhost:8080" will access port 80 on the guest machine.
  # NOTE: This will enable public access to the opened port
  # config.vm.network "forwarded_port", guest: 80, host: 8080

  # Create a forwarded port mapping which allows access to a specific port
  # within the machine from a port on the host machine and only allow access
  # via 127.0.0.1 to disable public access
  # config.vm.network "forwarded_port", guest: 80, host: 8080, host_ip: "127.0.0.1"
  config.vm.network "forwarded_port", guest: 8080, host: 8080 # Nginx
  config.vm.network "forwarded_port", guest: 4200, host: 4200 # Angular
  config.vm.network "forwarded_port", guest: 9876, host: 9876 # Angular Testing

  # Create a private network, which allows host-only access to the machine
  # using a specific IP.
  config.vm.network "private_network", ip: "192.168.33.10"

  # Create a public network, which generally matched to bridged network.
  # Bridged networks make the machine appear as another physical device on
  # your network.
  # config.vm.network "public_network"

  # Share an additional folder to the guest VM. The first argument is
  # the path on the host to the actual folder. The second argument is
  # the path on the guest to mount the folder. And the optional third
  # argument is a set of non-required options.
  # config.vm.synced_folder "../data", "/vagrant_data"

  # Provider-specific configuration so you can fine-tune various
  # backing providers for Vagrant. These expose provider-specific options.
  # Example for VirtualBox:
  #
  # config.vm.provider "virtualbox" do |vb|
  #   # Display the VirtualBox GUI when booting the machine
  #   vb.gui = true
  #
  #   # Customize the amount of memory on the VM:
  #   vb.memory = "1024"
  # end
  #
  # View the documentation for the provider you are using for more
  # information on available options.

  # Enable provisioning with a shell script. Additional provisioners such as
  # Puppet, Chef, Ansible, Salt, and Docker are also available. Please see the
  # documentation for more information about their specific syntax and use.
  config.vm.provision "shell", inline: <<-SHELL
  echo "========================= Update ======================="
  apt-get update
  apt-get install -y software-properties-common
  add-apt-repository -y ppa:ubuntu-toolchain-r/test
  apt-get update
  
  echo "========================= Install gcc, Python, Java ======================="
  apt-get install -y gcc-9 g++-9 cmake cppcheck clang gdb valgrind git && \
  apt-get install -y python2.7 default-jre
  
  echo "========================= Install Nginx (light) ======================="
  apt-get install -y nginx-light   
  
  echo "========================= Clean ======================="
  apt-get clean autoclean && \
  apt-get autoremove -y && \
  rm -rf /var/lib/apt/lists/*
  
  update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 999 \
  && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 999 \
  && update-alternatives --install /usr/bin/cc  cc  /usr/bin/gcc-9 999 \
  && update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-9 999
  
  echo "========================= Clean after update ======================="
  apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
  SHELL
  
  config.vm.provision "shell", privileged: false, inline: <<-SHELL
  echo "========================= Install Emscripten ======================="
  git clone https://github.com/emscripten-core/emsdk.git /home/vagrant/emsdk \
  && cd /home/vagrant/emsdk
  chmod +x ./emsdk && chmod +x ./emsdk_env.sh
  ./emsdk install #{EMSCRIPTEN_VERSION}-fastcomp
  ./emsdk activate #{EMSCRIPTEN_VERSION}-fastcomp
  /bin/bash -c "source ./emsdk_env.sh"
  SHELL
  
  config.vm.provision "shell", inline: <<-SHELL
  echo "========================= Copy libraries ======================="
  cp -r /home/vagrant/emsdk/fastcomp/emscripten/system/include/* /usr/local/include/
  
  apt-get update

  echo "========================= Install Angular ======================="
  cd /vagrant
  
  curl -sL https://deb.nodesource.com/setup_13.x | bash -
  apt-get update

  apt-get install -y nodejs
  npm install npm --global

  npm install --unsafe-perm -g @angular/cli

  echo "========================= Install doxygen ======================="
  
  apt-get install -y doxygen doxygen-doc graphviz
  
  echo "========================= Clean ======================="
  apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
  
  echo "========================= Set the arrival point in ssh ======================="
  echo "cd /vagrant" >> /home/vagrant/.bashrc
  SHELL
end
