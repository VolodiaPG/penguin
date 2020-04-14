import { Application, Loader, Container, Sprite, Graphics, Polygon, Point } from 'pixi.js';

import { Pos } from './pos';
import { Cell } from './cell';
import { Penguin } from './penguin';

/**
 * 
 */

declare var Module: any;

let loader: any = Loader.shared;

export class Board {
    hexes: Graphics;          // new Graphics()
    pixiApp: Application;        // map

    nbHexagonal: number = 8;
    nbPenguin: number = 4;

    // The pixel width of a hex.
    hexWidth: number = 90;       // 90
    // The pixel height of a hex.
    hexHeight: number = 90;      // 90

    boardWidth: number;       
    boardHeight: number;      

    idHumanPlayer: number = 1;

    cells: Array<Cell>;

    pawns: any;

    constructor(private app: Application, nbHexagonal: number) {
        this.pixiApp = app;

        this.nbHexagonal = nbHexagonal;

        this.resizeBoard();
        this.updatePixiAppSize();

        this.cells = new Array(this.nbHexagonal * this.nbHexagonal);

        this.hexes = new Graphics();
        this.pixiApp.stage.addChild(this.hexes);
        this.hexes.clear();

        console.log("Board ok : " + this.nbHexagonal);
    }

    resizeBoard() {
        this.boardHeight = this.nbHexagonal * this.hexWidth;
        this.boardWidth = (this.nbHexagonal + 1) * this.hexHeight; 
    }

    /***************************************************************************************************************************
    ************************************************ PREVIEW *******************************************************************
    ***************************************************************************************************************************/
    generatePreviewMap() {
        console.log("Generate Preview Map");
        let cell: Cell;
        for (let row = 0; row < this.nbHexagonal; row++) {
            for (let column = 0; column < this.nbHexagonal; column++) {
                cell = new Cell(column, row, 7);
                cell.setBlurFilter(true);
                this.cells[row * this.nbHexagonal + column] = cell;
            }

        }
        this.loadPreviewSceneGraph();
    }

    loadPreviewSceneGraph() {
        while (this.hexes.children.length) {
            this.hexes.removeChild(this.hexes.children[0]);
        }

        for (let ii = 0; ii < this.cells.length; ii++) {
            this.hexes.addChild(this.cells[ii].parentContainer);
        }
        this.updatePixiAppSize();
    }

    addHexagonal(): void {
        var newCells: Array<Cell> = new Array<Cell>();
        let cell: Cell;

        //Add a cell on all the row
        for (let row = 0; row < this.nbHexagonal; row++) {
            for (let column = 0; column < this.nbHexagonal; column++) {
                newCells.push(this.cells[row * this.nbHexagonal + column]);
            }
            cell = new Cell(this.nbHexagonal, row, 7);
            cell.setBlurFilter(true);
            newCells.push(cell);
        }

        //Add a row
        for (let column = 0; column < this.nbHexagonal + 1; column++) {
            cell = new Cell(column, this.nbHexagonal, 7);
            cell.setBlurFilter(true);
            newCells.push(cell);
        }

        this.nbHexagonal++;
        this.resizeBoard();

        this.cells = newCells;

        this.loadPreviewSceneGraph();
        this.updatePixiAppSize();
    }

    removeHexagonal(): void {
        var newCells: Array<Cell> = new Array<Cell>();

        //Remove a cell on all the column and remove a column
        for (let row = 0; row < this.nbHexagonal; row++) {
            for (let column = 0; column < this.nbHexagonal; column++) {
                if (row !== this.nbHexagonal - 1 && column !== this.nbHexagonal - 1) {
                    newCells.push(this.cells[row * this.nbHexagonal + column]);
                }
            }
        }

        this.nbHexagonal--;
        this.resizeBoard();

        this.cells = newCells;

        this.loadPreviewSceneGraph();
        this.updatePixiAppSize();
    }

    updatePixiAppSize(): void {
        this.pixiApp.renderer.view.width = this.boardWidth;
        this.pixiApp.renderer.view.height = this.boardHeight;
        this.pixiApp.renderer.view.style.width = this.boardWidth.toString() + 'px';
        this.pixiApp.renderer.view.style.height = this.boardHeight.toString() + 'px';

        this.pixiApp.resize();
    }

    /***************************************************************************************************************************
    ************************************************ MAP ***********************************************************************
    ***************************************************************************************************************************/
    generateMapFrom(gameBoard: any) {
        console.log("Generate Map");

        // generate cells from the wasm directives
        var wasmCells = gameBoard.getBoardCells();

        for (let row = 0; row < this.nbHexagonal; row++) {
            for (let column = 0; column < this.nbHexagonal; column++) {
                this.cells[row * this.nbHexagonal + column].setWasmCell(wasmCells.get(row * this.nbHexagonal + column));
            }
        }

        this.pawns = gameBoard.getPlayersOnBoard();

        this.setRandomPenguins(gameBoard);

        // set on the board the penguins
        for (let ii = 0; ii < this.pawns.size(); ii++) {
            var pawn: any = this.pawns.get(ii);
            var pawnPos: any = pawn.getStandingOn().getPosition();
            pawnPos = Module.hex_cube_to_offset(Module.hex_axial_to_cube(pawnPos));
            console.log(pawnPos);
            // this.pixiApp.stage.addChild(new Penguin(this.cells[this.mapHeight + this.nbPenguin].getCellCenter(), true).sprite);
        }
        this.loadSceneGraph();
    }

    setRandomPenguins(gameBoard: any) {
        console.log("Set Random Penguins Positions");
        let rndPos: number;

        for (let ii = 0; ii < this.pawns.size(); ii++) {
            var pawn: any = this.pawns.get(ii);
            rndPos = Math.floor(0 + Math.random() * (this.nbHexagonal * this.nbHexagonal));
            gameBoard.performMove(pawn.getId(), this.cells[rndPos].wasmCell);

            this.pixiApp.stage.addChild(new Penguin(this.cells[rndPos].getCellCenter(), true).sprite);
        }
    }

    loadSceneGraph() {
        var currentCell: Cell;
        while (this.hexes.children.length) {
            this.hexes.removeChild(this.hexes.children[0]);
        }

        for (let row = 0; row < this.nbHexagonal; row++) {
            for (let column = 0; column < this.nbHexagonal; column++) {
                currentCell = this.cells[row * this.nbHexagonal + column];
                currentCell.setBlurFilter(false);
                this.hexes.addChild(currentCell.parentContainer);
            }
        }
        this.updatePixiAppSize();
    };
}