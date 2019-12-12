# Tic-tac-toe MCTS
MCTS tic-tac-toe in C++

# Installation
## Vagrant

In order to ease the development process, we use Vagrant alongside VirtualBox.
The commands are then easy (do them in the root directory, where the `VagrantFile` is located):
- `vagrant up --provider=virtualbox` to run the box
- `vagrant halt` to shutdown the box
- `vagrant delete` to delete the box
- `vagrant ssh-config` is usseful to configure your ssh access ()
- `vagrant ssh` to open a shell directly inside the box
- `vagrant reload` to apply the modifications made to the `VagrantFile` while in use (not to rebuild everything from scracth)
- any other vagrant commands

**IMPORTANT NOTICE**: You might want to be careful when installing vagrant and follow the recommendations : https://www.vagrantup.com/docs/installation/
Especially on Windows, you might want to disable Hyper-V thanks to these commands (both):
```ps
Disable-WindowsOptionalFeature -Online -FeatureName Microsoft-Hyper-V-All
bcdedit /set hypervisorlaunchtype off
```

## VSCode
We used VSCode to develop in multiple languages of this project. It is possible thanks to the VSCode extension `Remote - SSH` (aka `ms-vscode-remote.remote-ssh`). We then connect in ssh to the Vagrant box and can enjoy the developement experience.
<br>
*Note that you might want to install all the recommended extensions when you start!*
<br>
<br>
VSCode uses SSH to connect to the Vagrant box, so you will have to configure your `~/.ssh/config` accordingly, thanks to the output of `vagrant ssh-config`.
<br>
<br>
Once evrything is done and you are inside the VSCode menu to select where to land with the ssh connection, head to `/vagrant`, this is the shared directory where all the project is accessible!

## Helpful links
- Vagrant crash course in 5 minutes: https://gist.github.com/yeukhon/b35d94f4aa859a5477e4
- Vagrant installation https://www.vagrantup.com/docs/installation/



## Basis
- Initial Tutorial : https://www.baeldung.com/java-monte-carlo-tree-search
- The basis of the project is https://github.com/eugenp/tutorials/tree/master/algorithms-miscellaneous-1/src/main/java/com/baeldung/algorithms/mcts
- https://www.codeflow.site/fr/article/java-monte-carlo-tree-search
- https://github.com/memo/ofxMSAmcts/tree/master/src

- https://github.com/hayoung-kim/mcts-tic-tac-toe
- http://codegatherer.com/mcts_tic_tac_toe.php

## Resources
### Board
- https://simblob.blogspot.com/2019/03/improving-hexagon-map-storage-diagram.html#more
- https://moodle.insa-rennes.fr/pluginfile.php/45332/mod_resource/content/1/bitboards.pdf

### Penguins
- https://gitlab.insa-rennes.fr/francesco-bariatti/pingouins/tree/master
