# Installation
## Docker
Docker is required in order to set up the development environment, so it can work with VSCode.<br>
*Note that for Windows, docker desktop will only work with Windows Pro!*

## Setup
### General setup
1. Open VSCode and make sure you have the *Remote - Containers* extension installed (`ms-vscode-remote.remote-containers`)
2. Choose (at the bottom left corner) `open folder in container`
3. Let the process finish (sometimes when building the docker image the process can be stuck and you'll need to restart VSCode)
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
- `make serve` to serve the Doxygen documentation on port `8080`
- `clean` to clean
<br>
All these commands are accessible via the `tasks` of VSCode!

## Web part
Everyting is as you are developing normally.
- If you have `.env` related errors, type `yarn run env -s`
- to serve : `ng serve --host 0.0.0.0` (the host part is needed for the server to be accessible from the host OS)

# Useful other commands
- `c++filt _ZN4game14AbstractPlayer6actionEPNS_17AbstractBoardCellE` gives us `game::AbstractPlayer::action(game::AbstractBoardCell*)`
- to access container from another computer, for DockerWindows : https://github.com/docker/for-win/issues/4391#issuecomment-520420942