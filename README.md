title: Penguin game : user documentation

# Installation

## Setup

### How to start
First, you can just use the deployed version on : `https://volodiapg.github.io/penguin/game`
Or you can clone our git repositorie : `https://github.com/VolodiaPG/penguin.git` and setup the project environnement.

## Docker

Docker is required in order to set up the environment to launch the game.<br>
_Note that for Windows, Docker desktop will only work with Windows Pro!_

### General setup

1. Open VSCode and make sure you have the _Remote - Containers_ extension installed (`ms-vscode-remote.remote-containers`)
2. Choose (at the bottom left corner) `open folder in container`
3. Let the process finish (sometimes when building the Docker image the process can be stuck and you'll need to restart VSCode)

> ### Some issues
>
> - Check you switched and used Linux container in the Docker Desktop
> - Check you have enough memory in your disk
> - If you are reading this line, you have to change your DNS address to establish the connection with the server

# Launch

## Web part

When using the application, you'll need to go the the `penguinApp/` folder and do : 

- `npm install` to install dependencies
- `npm run wasm` to generate all the wasm files required for the app to run
- `npm run start` to serve (the host part is needed for the server to be accessible from the host OS)

> ### Some issues
>
> - If you have `.env` related errors, type `npm run env -s`

# Penguin Game
## Presentation
This project is an implementation of the game "Pingouins", made by 5 INSA students, during their Practical Studies in their 3rd year in the Computer Science Department of INSA Rennes. 
The application allows the user to play this game against an Artificial Intelligence (AI). The AI coded in C++, is compiled with Emscripten in WebAssembly, to be able to display the game in a web browser. Warning it works better on Chromium-based web browser.

## Rules
Initially, the game is represented by a board of 60 hexagonal cells, with 1,2 or 3 fish. You dispose a certain number of penguins posed on one hexagonal cell. Each turn you will move one penguin, to an available cell (diagonals), and "eat" the fish in the cell you came from. The goal is to eat more fish than your opponent.


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
Then you have to put your penguins on the board, by clicking on an available cell, while you have penguins in stock.
Click the NEXT button and do the same for the IA penguins.
Finally START the game.

### Move
Only possible when it is your turn.
First, you have to select one of your penguins, and then click one of its available cells to move to it.

### Restart
You can restart, at any moment, by refreshing all the website with F5.