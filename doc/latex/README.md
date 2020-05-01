---
title: Exercices cours de Secu sur les clouds
author: Volodia PAROL-GUARINO
date: mercredi 29 avril 2020
...

# Installation
## Docker
Docker is required in order to set up the development environment, so it can work with VSCode.<br>
Toto [@handsOnWebAssembly]
*Note that for Windows, docker desktop will only work with Windows Pro!*

## Setup
### General setup
1. Open VSCode and make sure you have the *Remote - Containers* extension installed (`ms-vscode-remote.remote-containers`)
2. Choose (at the bottom left corner) `open folder in container`
3. Let the process finish (sometimes when building the docker image the process can be stuck and you'll need to restart VSCode)

> ### Some issues
> * Check you switched and used Linux container in the Docker Desktop
> * Check you have enough memory in your disk
> * If you are reading this line, you have to change your DNS address to etablish the connection with the server

### For the Web Part
When developing the angular side of the project, you'll need to go the the `www/` folder and do a `yarn install`.

# Usage
## Cpp part
- `make` to compile the release with the emscriten compiler
- `make ENV=emscripten MODE=release` to compile the emscripten release version
- `make ENV=emscripten MODE=debug` to compile the emscripten debug version
- `make ENV=native MODE=debug` to compile the release version on the OS
- `make ENV=native MODE=debug` to compile the debug version on the OS
- the executable can be found in `./bin/main`
- `make doc` to compile the Doxygen documentation
- `clean` to clean
Note that the attribute `MULTITHREADED` can be set to `true` or `false` to enable it or not (works for both `emscripten` and `native`).
<br>
Most of these commands are accessible via the `tasks` of VSCode!

## Documentation
Generated documentation (for the cpp part) is put in a generated folder: `doxygen`. To make use of the html format generated, please execute the script `serve_doc.sh`.

## Web part
Everyting is as you are developing normally.
- If you have `.env` related errors, type `yarn run env -s`
- to serve : `ng serve --host 0.0.0.0` (the host part is needed for the server to be accessible from the host OS)

## Ports
This environnement makes use of different ports:
- `4200` for `angular`
- `8080` to serve the `doxygen` doc
- `5500` to make use of the `go live` extension in VsCode
- `9876` is the default test port for test in `angular`

# Useful other commands
- `c++filt _ZN4game14AbstractPlayer6actionEPNS_17AbstractBoardCellE` gives us `game::AbstractPlayer::action(game::AbstractBoardCell*)`
- to access container from another computer, for DockerWindows : https://github.com/docker/for-win/issues/4391#issuecomment-520420942

# Basis
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

### Angular
- installation came using this resource : https://github.com/nvm-sh/nvm (tutorial : http://redgreenrepeat.com/2018/02/09/setting-up-angular-in-virtualbox/)
- https://github.com/nodesource/distributions/tree/master/deb

# References