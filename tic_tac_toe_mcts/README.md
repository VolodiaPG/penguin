# Usage
## Normal usage
- `make` or `make release` to compile the release, or `make rel_run` to compile & run
- `make debug` to compile the release, or `make dbg_run` to compile & run
- `run` will compile & run the release target 
- `clean` to clean

## Advanced usage
An envionement (separate directory in bin/) can be specified for the object files and executable following the syntax `make BUILD_ENV=<subDir> <debug|release>`
eg. `make BUILD_ENV=debugDir debug` will generate all the files inside `./bin/debugDir` following the make parameters set for a debug compilation