# Installation

## Docker

Docker is required in order to set up the development environment, so it can work with VSCode.<br>
_Note that for Windows, docker desktop will only work with Windows Pro!_

## Setup

### General setup

1. Open VSCode and make sure you have the _Remote - Containers_ extension installed (`ms-vscode-remote.remote-containers`)
2. Choose (at the bottom left corner) `open folder in container`
3. Let the process finish (sometimes when building the docker image the process can be stuck and you'll need to restart VSCode)

> ### Some issues
>
> - Check you switched and used Linux container in the Docker Desktop
> - Check you have enough memory in your disk
> - If you are reading this line, you have to change your DNS address to etablish the connection with the server

# Launch

## Cpp part

- `make` to compile the release with the emscriten compiler
- `make ENV=emscripten MODE=release` to compile the emscripten release version
- `make ENV=emscripten MODE=debug` to compile the emscripten debug version
- `make ENV=native MODE=debug` to compile the release version on the OS
- `make ENV=native MODE=debug` to compile the debug version on the OS
- the executable can be found in `./bin/main`
- `make serve` to serve the Doxygen documentation on port `8080`
- `clean` to clean
  <br>
  All these commands are accessible via the `tasks` of VSCode!

## Web part

When using the application, you'll need to go the the `penguinApp/` folder and do : 

- `npm install` to install dependencies
- `npm run wasm` to generate all the wasm files requiered for the appt to run
- `npm run start` to serve (the host part is needed for the server to be accessible from the host OS)
- `npm run compodoc` to document and run server

> ### Some issues
>
> - If you have `.env` related errors, type `npm run env -s`


# Application

## Organisation
`
|- Home
|- Game
| |- Board
| |- Console
| |- Control
| |- Info
|- Team
|- Documentation
|- About
`

## Game
### Settings & Launch
First you need to set all the variables of the board and the IA level (restriction by time).
Then you have to pose your penguin on the board, by clicking on an available cell, while you have penguins in your stock.
Click the NEXT button and do the same for the IA penguins.
Finally START the game.

### Move
Only possible when it is your turn.
First, you have to select one of your penguin, and then click one of its availables cells to move to it.

### Restart
You can restart, at any moment, by refreshing all the site with F5.

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
