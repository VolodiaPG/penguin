# Documentation
## Setup
- Install Docker
- Open the project in VSCode
- At the bottom left corner, click the green button and select `Remote-Containers: Reopen in container` (or create one from the `Dockerfile` present at the root of the project)
- Enjoy

## Dependencies
All dependencies used must be added into `docs/install-dependencies.sh` so as to provide a reliable and constant way to list and install all the dependencies of the project

## Environement
If you can't setup the environment you can use `WSL` and manually execute `docs/install-environement` to install all development dependencies.
<br>Once it's done you can also install the extension to have somewaht a better development experience:
- `ms-vscode.cpptools`
- `jbenden.c-cpp-flylint`
- `mitaki28.vscode-clang`
- `cschlosser.doxdocgen`