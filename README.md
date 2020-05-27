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

# Penguin Game
## Presentation
This project is an implementation of the game "Pengouins", made by 5 INSA's students, during their Pratical Studies, in their 3rd year in the Computer Science Departement of the INSA Rennes. 
The application allows the user to play this game against an IA (MCTS). The IA coded in C++, compiled with emscripten in WebAssembly, to be able to display the game in a web browser.

## Rules
Initially, the game is reprensented by a board of 60 hexagonals, with 1,2 or 3 fishes. You dispose a certain number of penguins posed on one hexagonal cell. In each turn you will moved one penguin, to an available cells (diagonals), and eat the fishes in this new cell. The goal is to eat more fishes than your opponent.


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