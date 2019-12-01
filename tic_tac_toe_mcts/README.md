# Modelisation
Here is the basic structure of the project, not all classes are represented, only the ones needed to fully understand the construction of the project
![UML schema](./doc/modelisation.svg)

# Usage
## Normal usage
- `make` or `make release` to compile the release, or `make rel_run` to compile & run
- `make debug` to compile the release, or `make dbg_run` to compile & run
- `run` will compile & run the release target 
- `clean` to clean

## Advanced usage
An envionement (separate directory in bin/) can be specified for the object files and executable following the syntax `make BUILD_ENV=<subDir> <debug|release>`
eg. `make BUILD_ENV=debugDir debug` will generate all the files inside `./bin/debugDir` following the make parameters set for a debug compilation

# Useful commands
- `c++filt _ZN4game14AbstractPlayer6actionEPNS_17AbstractBoardCellE` gives us `game::AbstractPlayer::action(game::AbstractBoardCell*)`
- to access container from another computer, for DockerWindows : https://github.com/docker/for-win/issues/4391#issuecomment-520420942