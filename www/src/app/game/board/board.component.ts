import { Component, OnInit, ViewChild } from '@angular/core';

import { Cell } from './cell';
import { HexComponent } from './hex/hex.component';

declare var Module: any;

@Component({
  selector: 'app-board',
  templateUrl: './board.component.html',
  styleUrls: ['./board.component.scss']
})
export class BoardComponent implements OnInit {
  nbHexagonal: number = 8;       // 8

  // The pixel width of a hex.
  hexWidth: number = 90;       // 90
  // The pixel height of a hex.
  hexHeight: number = 90;      // 90

  cells: Array<Array<Cell>>;

  nbPenguin: number = 4;
  penguinPlayers: any;

  humanPlayerId: number = 1;

  // Wasm objects
  wasmGame: any;
  wasmBoard: any;
  wasmPenguins: any;

  constructor() { }

  ngOnInit(): void {
    this.cells = new Array(this.nbHexagonal);
    this.generateMap();
    console.log("Board ok");
  }

  ngOnDestroy(): void {
    console.log("Game destroyed");
    this.wasmGame.delete();
  }

  /***************************************************************************************************************************
  ************************************************ START GAME ****************************************************************
  ***************************************************************************************************************************/
  startWasmGame() {
    this.wasmGame = new Module.PenguinGame(this.nbHexagonal, this.nbPenguin);
    this.wasmBoard = this.wasmGame.getBoard();
    this.generateMapFromWasmBoard();

    this.wasmPenguins = this.wasmBoard.getPlayersOnBoard();
  }


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

  generateMapFromWasmBoard() {
    console.log("Generate Map from WasmBoard");

    // generate cells from the wasm directives
    var wasmCells = this.wasmBoard.getBoardCells();

    for (let row = 0; row < this.nbHexagonal; row++) {
      for (let column = 0; column < this.nbHexagonal; column++) {
        this.cells[row][column].setWasmCell(wasmCells.get(row * this.nbHexagonal + column));
      }
    }
  }

  /***************************************************************************************************************************
  ************************************************ PREVIEW *******************************************************************
  ***************************************************************************************************************************/
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


  // addPenguin(): void {
  //   penguinGame.addPenguin();
  // }

  // removePenguin(): void {
  //   penguinGame.removePenguin();
  // }
}
