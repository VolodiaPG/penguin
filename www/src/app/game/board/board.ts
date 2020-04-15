
import { Pos } from './pos';
import { Cell } from './cell';
import { Penguin } from './penguin';

/**
 * 
 */
export class Board {
    nbHexagonal: number;       // 8

    // The pixel width of a hex.
    hexWidth: number = 90;       // 90
    // The pixel height of a hex.
    hexHeight: number = 90;      // 90

    cells: Array<Array<Cell>>;

    penguinPlayers: any;

    constructor(nbHexagonal: number = 8) {
        this.nbHexagonal = nbHexagonal;
        this.cells = new Array(this.nbHexagonal);

        console.log("Board ok");
    }

    // addHexagonal(): void {
    //     this.nbHexagonal++;

    //     let cell: Cell;

    //     //Add a cell on all the row
    //     for (let row = 0; row < this.cells.length; row++) {
    //         cell = new Cell(row, this.cells[row].length, 7);
    //         this.cells[row].push(cell);
    //     }

    //     //Add a row
    //         this.cells.push(new Array(this.nbHexagonal));


    //     for (let column = 0; column < this.cells[this.nbHexagonal - 1].length; column++) {
    //         cell = new Cell(this.nbHexagonal - 1, column, 7);
    //         this.cells[this.nbHexagonal - 1][column] = cell;
    //     }

    // }

    // removeHexagonal(): void {
    //     this.nbHexagonal--;
    //     //Remove a cell on all the row
    //     for (let row = 0; row < this.cells.length; row++) {
    //         this.cells[row].pop();
    //     }
    //     //Remove a row
    //     this.cells.pop();
    // }

    /***************************************************************************************************************************
    ************************************* MAP/TEXTURES *************************************************************************
    ***************************************************************************************************************************/
    generateMap() {
        console.log("Generate Map");
        let cell: Cell;
        for (let row = 0; row < this.nbHexagonal; row++) {

            this.cells[row] = new Array(this.nbHexagonal);

            for (let column = 0; column < this.nbHexagonal; column++) {
                cell = new Cell(row, column, 1);
                this.cells[row][column] = cell;
            }
        }
    };

    generateMapFrom(gameBoard: any) {
        console.log("Generate Map");

        // generate cells from the wasm directives
        var wasmCells = gameBoard.getBoardCells();

        for (let row = 0; row < this.nbHexagonal; row++) {
            for (let column = 0; column < this.nbHexagonal; column++) {
                this.cells[row][column].setWasmCell(wasmCells.get(row * this.nbHexagonal + column));
            }
        }
    }
}