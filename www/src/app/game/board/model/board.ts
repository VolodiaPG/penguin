import { Application, Loader, Container, Sprite, Graphics, Polygon, Point } from 'pixi.js';

import { Pos } from './pos';
import { Cell } from './cell';
import { Penguin } from './penguin';

/**
 * 
 */

let loader: any = Loader.shared;

export class Board {
    hexes: Graphics;          // new Graphics()
    pixiApp: Application;        // map

    // The map's number of cells across (cell column count).
    mapWidth: number = 8;       // 8
    // The map's number of cells high (cell row count).
    mapHeight: number = 8;      // 8

    // The pixel width of a hex.
    hexWidth: number = 90;       // 90
    // The pixel height of a hex.
    hexHeight: number = 90;      // 90

    nbPenguin: number = 4;

    cells: Array<Cell>;

    penguinPlayers: any;

    // cells: Array<Array<Cell>>;
    penguinsAllies: Array<Penguin>;
    penguinsEnemis: Array<Penguin>;

    constructor(private app: Application, nbHexagonal:number, nbPenguin: number) {
        this.pixiApp = app;

        this.mapHeight = nbHexagonal;
        this.mapWidth = nbHexagonal;


        this.cells = new Array(this.mapHeight * this.mapWidth);
        
        this.nbPenguin = nbPenguin;
        this.penguinsAllies = new Array(this.nbPenguin);
        this.penguinsEnemis = new Array(this.nbPenguin);

        this.hexes = new Graphics();
        this.pixiApp.stage.addChild(this.hexes);
        this.hexes.clear();

        console.log("Board ok");
    }


    /***************************************************************************************************************************
    ************************************* PREVIEW *************************************************************************
    ***************************************************************************************************************************/
    generatePreviewMap() {
        console.log("Generate Preview Map");
        let cell: Cell;
        for (let row = 0; row < this.mapWidth; row++) {
            for (let column = 0; column < this.mapHeight; column++) {
                cell = new Cell(column, row, 7);
                cell.setBlurFilter(true);
                this.cells[row * this.mapWidth + column] = cell;
            }

        }
        this.loadPreviewSceneGraph();
    }

    generatePreviewPenguin() {
        for (let pg = 0; pg < this.penguinsAllies.length; pg++) {
            this.penguinsAllies[pg] = new Penguin(this.cells[this.mapHeight + pg].getCellCenter(), true);
            this.penguinsEnemis[pg] = new Penguin(this.cells[3 * this.mapHeight + pg].getCellCenter(), false);

            this.pixiApp.stage.addChild(this.penguinsAllies[pg].sprite);
            this.pixiApp.stage.addChild(this.penguinsEnemis[pg].sprite);
        }
    }

    loadPreviewSceneGraph() {
        while (this.hexes.children.length) {
            this.hexes.removeChild(this.hexes.children[0]);
        }

        for (let ii = 0; ii < this.cells.length; ii++) {
            this.hexes.addChild(this.cells[ii].parentContainer);
        }
    }

    addHexagonal(): void {
        var newCells: Array<Cell> = new Array<Cell>();
        let cell: Cell;

        //Add a cell on all the row
        for (let row = 0; row < this.mapHeight; row++) {
            for (let column = 0; column < this.mapWidth; column++) {
                newCells.push(this.cells[row * this.mapWidth + column]);
            }
            cell = new Cell(this.mapWidth, row, 7);
            cell.setBlurFilter(true);
            newCells.push(cell);
        }

        //Add a row
        for (let column = 0; column < this.mapWidth + 1; column++) {
            cell = new Cell(column, this.mapWidth, 7);
            cell.setBlurFilter(true);
            newCells.push(cell);
        }

        this.mapHeight++;
        this.mapWidth++;

        this.cells = newCells;

        this.loadPreviewSceneGraph();
        this.pixiApp.resize();
    }

    removeHexagonal(): void {
        var newCells: Array<Cell> = new Array<Cell>();

        //Remove a cell on all the column and remove a column
        for (let row = 0; row < this.mapHeight; row++) {
            for (let column = 0; column < this.mapWidth; column++) {
                if (row !== this.mapHeight - 1 && column !== this.mapWidth - 1) {
                    newCells.push(this.cells[row * this.mapHeight + column]);
                }
            }
        }

        this.mapHeight--;
        this.mapWidth--;

        this.cells = newCells;

        this.loadPreviewSceneGraph();
        this.pixiApp.resize();
    }

    addPenguin(): void {
        this.penguinsAllies.push(new Penguin(this.cells[this.mapHeight + this.nbPenguin].getCellCenter(), true));
        this.pixiApp.stage.addChild(this.penguinsAllies[this.nbPenguin].sprite);

        this.penguinsEnemis.push(new Penguin(this.cells[3 * this.mapHeight + this.nbPenguin].getCellCenter(), false));
        this.pixiApp.stage.addChild(this.penguinsEnemis[this.nbPenguin].sprite);

        this.nbPenguin++;
    }

    removePenguin(): void {
        this.pixiApp.stage.removeChild(this.penguinsAllies[this.nbPenguin - 1].sprite);
        this.penguinsAllies.pop();

        this.pixiApp.stage.removeChild(this.penguinsEnemis[this.nbPenguin - 1].sprite);
        this.penguinsEnemis.pop();
        this.nbPenguin--;
    }

    /***************************************************************************************************************************
    ************************************* MAP *************************************************************************
    ***************************************************************************************************************************/
    generateMapFrom(gameBoard: any) {
        console.log("Generate Map");
        var wasmCells = gameBoard.getBoardCells();

        for (let row = 0; row < this.mapHeight; row++) {
            for (let column = 0; column < this.mapWidth; column++) {
                this.cells[row * this.mapHeight + column].setWasmCell(wasmCells.get(row * this.mapHeight + column));
            }
        }
        this.loadSceneGraph();
    }
    
    loadSceneGraph() {
        var currentCell: Cell;
        while (this.hexes.children.length) {
            this.hexes.removeChild(this.hexes.children[0]);
        }

        for (let row = 0; row < this.mapHeight; row++) {
            for (let column = 0; column < this.mapWidth; column++) {
                currentCell = this.cells[row * this.mapHeight + column];
                currentCell.setBlurFilter(false);
                this.hexes.addChild(currentCell.parentContainer);
            }
        }
    };
}