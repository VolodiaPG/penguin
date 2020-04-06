import { Application, Loader, Container, Sprite, Graphics, Polygon, Point } from 'pixi.js';

import { Pos } from './pos';
import { Cell } from './cell';
import { Penguin } from './penguin';

/**
 * 
 */

//  import { loader } from '../controller/penguinGame';
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

    cells: Array<Array<Cell>>;
    penguinsAllies: Array<Penguin>;
    penguinsEnemis: Array<Penguin>;

    constructor(private app: Application, size: number, nbPawn: number) {
        this.pixiApp = app;

        this.mapHeight = size;
        this.mapWidth = size;

        this.nbPenguin = nbPawn;
        this.penguinsAllies = new Array(this.nbPenguin);
        this.penguinsEnemis = new Array(this.nbPenguin);
        console.log("Lg penguins : "+ this.penguinsAllies.length);

        this.cells = new Array(this.mapHeight);

        this.hexes = new Graphics();
        this.pixiApp.stage.addChild(this.hexes);
        this.hexes.clear();

        console.log("Board ok");
    }

    addHexagonal(): void {
        this.mapHeight++;
        this.mapWidth++;

        let cell: Cell;

        //Add a cell on all the row
        for (let row = 0; row < this.cells.length; row++) {
            cell = new Cell(row, this.cells[row].length, 7);
            cell.setBlurFilter(true);
            this.cells[row].push(cell);
        }

        //Add a row
        if ((this.cells.length % 2) == 0) {
            this.cells.push(new Array(this.mapWidth - 1));
        } else {
            this.cells.push(new Array(this.mapWidth));
        }

        for (let column = 0; column < this.cells[this.mapHeight - 1].length; column++) {
            cell = new Cell(this.mapHeight - 1, column, 7);
            cell.setBlurFilter(true);
            this.cells[this.mapHeight - 1][column] = cell;
        }

        this.loadSceneGraph();
        this.pixiApp.resize();
    }

    removeHexagonal(): void {
        this.mapHeight--;
        this.mapWidth--;

        //Remove a cell on all the row
        for (let row = 0; row < this.cells.length; row++) {
            this.cells[row].pop();
        }
        //Remove a row
        this.cells.pop();

        this.loadSceneGraph();
        this.pixiApp.resize();
    }

    addPenguin(): void {
        this.penguinsAllies.push(new Penguin(this.cells[2][this.nbPenguin].getCellCenter(), true));
        this.pixiApp.stage.addChild(this.penguinsAllies[this.nbPenguin].sprite);

        this.penguinsEnemis.push(new Penguin(this.cells[4][this.nbPenguin].getCellCenter(), false));
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
    ************************************* MAP/TEXTURES *************************************************************************
    ***************************************************************************************************************************/
    generateMap() {
        console.log("Generate Map");
        let cell: Cell;
        for (let row = 0; row < this.cells.length; row++) {

            if ((row % 2) == 0) {
                this.cells[row] = new Array(this.mapWidth - 1);
            } else {
                this.cells[row] = new Array(this.mapWidth);
            }

            for (let column = 0; column < this.cells[row].length; column++) {
                cell = new Cell(row, column, 7);
                cell.setBlurFilter(true);
                this.cells[row][column] = cell;
            }
        }

        // console.log("Ordre du tableau : ");
        // for(var r = 0; r < this.cells.length ; r+=1) {
        //     for(var c = 0 ; c < this.cells[r].length ; c+=1) {
        //         console.log("Cell : (" + this.cells[r][c].row + "," + this.cells[r][c].column + ")");
        //     }
        // }

        this.loadSceneGraph();
    };

    generatePreviewPenguin() {
        for(let pg = 0; pg < this.penguinsAllies.length; pg++) {
                this.penguinsAllies[pg] = new Penguin(this.cells[2][pg].getCellCenter(), true);
                this.penguinsEnemis[pg] = new Penguin(this.cells[4][pg].getCellCenter(), false);
            
            this.pixiApp.stage.addChild(this.penguinsAllies[pg].sprite);
            this.pixiApp.stage.addChild(this.penguinsEnemis[pg].sprite);
        }
    }

    setRandomCells() {
        console.log("Set Random Cells");
        let rnd: number;
        for (let row = 0; row < this.cells.length; row++) {
            for (let column = 0; column < this.cells[row].length; column++) {
                rnd = Math.floor(1 + (Math.random() * 3));
                this.cells[row][column].setBlurFilter(false);
                this.cells[row][column].setCellTerrainType(rnd);
            }
        }
        // console.log("Ordre du tableau : ");
        // for(var r = 0; r < this.cells.length ; r+=1) {
        //     for(var c = 0 ; c < this.cells[r].length ; c+=1) {
        //         console.log("Cell : (" + this.cells[r][c].row + "," + this.cells[r][c].column + ")");
        //     }
        // }

        this.loadSceneGraph();
    };

    setRandomPenguins() {
        console.log("Set Random Penguins Positions");
        let rndRow: number, rndColumn: number;

        for (let pg = 0; pg < this.penguinsAllies.length; pg++) {
            while(this.penguinsAllies[pg].cellPosition === null) {
                rndRow = Math.floor(0 + Math.random() * (this.cells.length));
                rndColumn = Math.floor(0 + Math.random() * (this.cells[rndRow].length));
                if (!this.cells[rndRow][rndColumn].hasPenguin) {
                    this.penguinsAllies[pg].moveTo(this.cells[rndRow][rndColumn]);
                }
            }
        }

        for (let pg = 0; pg < this.penguinsEnemis.length; pg++) {
            while(this.penguinsEnemis[pg].cellPosition === null) {
                rndRow = Math.floor(0 + Math.random() * (this.cells.length));
                rndColumn = Math.floor(0 + Math.random() * (this.cells[rndRow].length));
                if (!this.cells[rndRow][rndColumn].hasPenguin) {
                    this.penguinsEnemis[pg].moveTo(this.cells[rndRow][rndColumn]);
                }
            }
        }
    }


    setDiagoSelectedTexture(cell: Cell, select: boolean, alpha: number) {
        //diago droite
        var cellX = cell.column - (cell.row + (cell.row & 1)) / 2;

        //ligne
        var cellZ = cell.row;

        //diago gauche
        var cellY = - cellX - cellZ;

        for (var r = 0; r < this.cells.length; r += 1) {
            for (var c = 0; c < this.cells[r].length; c += 1) {
                var tempX = this.cells[r][c].column - (this.cells[r][c].row + (this.cells[r][c].row & 1)) / 2;
                var tempZ = this.cells[r][c].row;
                var tempY = - tempX - tempZ;

                if ((tempX == cellX) || (tempY == cellY) || (tempZ == cellZ)) {
                    this.cells[r][c].setCellSelectedTexture(select, alpha); // cell, Selected, alpha
                }

            }
        }

    }

    loadSceneGraph() {
        while (this.hexes.children.length) {
            this.hexes.removeChild(this.hexes.children[0]);
        }

        for (let row = 0; row < this.cells.length; row++) {
            for (let column = 0; column < this.cells[row].length; column++) {
                this.hexes.addChild(this.cells[row][column].parentContainer);
            }
        }
    };
}