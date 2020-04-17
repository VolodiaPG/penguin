import { Component, OnInit, Input } from '@angular/core';

import { trigger, transition, animate, style, query, stagger, state } from '@angular/animations';

import { Cell } from './cell';
import { HexComponent } from './hex/hex.component';
import { Penguin } from './penguin';
import { gameService } from '../+xstate/gameMachine';

declare var Module: any;

@Component({
  selector: 'app-board',
  templateUrl: './board.component.html',
  styleUrls: ['./board.component.scss'],
  animations: [
    trigger('initAnimation', [
      state(
        'enter',
        style({
          opacity: 1,
          transform: 'scale(1)'
        })
      ),
      state(
        'leave',
        style({
          opacity: 0.5,
          transform: 'scale(0.8)'
        })
      ),
      transition('enter => leave', [animate('1s')]),
      transition('leave => enter', [animate('0.5s')])
    ])
  ]
})
export class BoardComponent implements OnInit {
  @Input() currentGameState: any;

  isLoaded = false;

  nbHexagonal: number = 8; // 8

  // The pixel width of a hex.
  hexWidth: number = 90; // 90
  // The pixel height of a hex.
  hexHeight: number = 90; // 90

  cells: Array<Array<Cell>>;

  nbPenguin: number = 4;
  penguins: Array<Penguin>;
  penguinSelected: Penguin;

  humanPlayerId: number = 1;

  // Wasm objects
  wasmGame: any;
  wasmBoard: any;
  wasmPenguins: any;

  constructor() {}

  ngOnInit(): void {
    this.isLoaded = false;
    this.cells = new Array(this.nbHexagonal);
    this.penguins = new Array(this.nbPenguin);
    this.generateMap();
    this.generatePenguin();
    console.log('Board ok');

    console.log(gameService.machine.states.penguinSelected.on.PENGUINSELECTED[0].eventType);
  }

  ngOnDestroy(): void {
    console.log('Game destroyed');
    this.wasmGame.delete();
  }

  /***************************************************************************************************************************
   ************************************************ START GAME ****************************************************************
   ***************************************************************************************************************************/
  startWasmGame() {
    this.isLoaded = true;
    this.wasmGame = new Module.PenguinGame(this.nbHexagonal, this.nbPenguin);
    this.wasmBoard = this.wasmGame.getBoard();
    this.generateMapFromWasmBoard();

    this.wasmPenguins = this.wasmBoard.getPlayersOnBoard();
    // console.log("WasmGame loaded : " + this.currentGameState.value);
  }

  /***************************************************************************************************************************
   ************************************* MAP/TEXTURES *************************************************************************
   ***************************************************************************************************************************/
  generateMap() {
    console.log('Generate Map');
    let cell: Cell;
    for (let row = 0; row < this.nbHexagonal; row++) {
      this.cells[row] = new Array(this.nbHexagonal);

      for (let column = 0; column < this.nbHexagonal; column++) {
        cell = new Cell(row, column, 0);
        this.cells[row][column] = cell;
      }
    }
  }

  generateMapFromWasmBoard() {
    console.log('Generate Map from WasmBoard');

    // generate cells from the wasm directives
    var wasmCells = this.wasmBoard.getBoardCells();

    for (let row = 0; row < this.nbHexagonal; row++) {
      for (let column = 0; column < this.nbHexagonal; column++) {
        this.cells[row][column].setWasmCell(wasmCells.get(row * this.nbHexagonal + column));
      }
    }
  }

  generatePenguin() {
    console.log('Generate Penguins');
    let penguin: Penguin;
    let rndRow: number, rndColumn: number;
    for (let ii = 0; ii < this.nbPenguin; ii++) {
      rndRow = Math.floor(0 + Math.random() * (this.nbHexagonal - 0));
      rndColumn = Math.floor(0 + Math.random() * (this.nbHexagonal - 0));
      this.penguins[ii] = new Penguin(this.cells[rndRow][rndColumn], true);
    }
  }

  generatePenguinFromWasmBoard() {}

  /***************************************************************************************************************************
   ************************************************ ANIMATION******************************************************************
   ***************************************************************************************************************************/
  onPenguinClick(newPenguinClicked: Penguin) {
    newPenguinClicked.switchPenguinColor();

    // Not the first time a penguin is clicked in this turn
    if (this.penguinSelected !== undefined) {
      // The user clicked on another penguin
      if (this.penguinSelected === newPenguinClicked) {
        gameService.send(gameService.machine.states.penguinSelected.on.PENGUINSELECTED[0].eventType);
        this.penguinSelected = undefined;
      } else {
        // Keep the same state : PenguinSelected
        this.penguinSelected.switchPenguinColor();
        this.penguinSelected = newPenguinClicked;
      }
    } else {
      this.penguinSelected = newPenguinClicked;
      gameService.send(gameService.machine.states.penguinSelected.on.PENGUINSELECTED[0].eventType);
    }
  }

  onCellClick(cellClicked: Cell) {}

  /***************************************************************************************************************************
   ************************************************ PREVIEW *******************************************************************
   ***************************************************************************************************************************/
  addHexagonal(): void {
    this.nbHexagonal++;

    let cell: Cell;

    //Add a cell on all the row
    for (let row = 0; row < this.cells.length; row++) {
      cell = new Cell(row, this.cells[row].length, 0);
      this.cells[row].push(cell);
    }

    //Add a row
    this.cells.push(new Array(this.nbHexagonal));

    for (let column = 0; column < this.cells[this.nbHexagonal - 1].length; column++) {
      cell = new Cell(this.nbHexagonal - 1, column, 0);
      this.cells[this.nbHexagonal - 1][column] = cell;
    }
  }

  removeHexagonal(): void {
    this.nbHexagonal--;
    //Remove a cell on all the row
    for (let row = 0; row < this.cells.length; row++) {
      this.cells[row].pop();
    }
    //Remove a row
    this.cells.pop();
  }

  addPenguin(): void {}

  removePenguin(): void {}
}
