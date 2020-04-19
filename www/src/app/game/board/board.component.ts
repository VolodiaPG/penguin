import { Component, OnInit, Input } from '@angular/core';

import { trigger, transition, animate, style, query, stagger, state } from '@angular/animations';

import { Cell } from './cell';
import { HexComponent } from './hex/hex.component';
import { Penguin } from './penguin';
import { gameService } from '../+xstate/gameMachine';
import { ToastController } from '@ionic/angular';
import { Pos } from './pos';

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

  nbPenguin: number = 2;
  penguins: Array<Penguin>;
  penguinSelected: Penguin;

  currentPlayerId: number = 1;

  humanPlayerId: number = 1;

  // Wasm objects
  wasmGame: any;
  wasmBoard: any;
  wasmPenguins: any;

  constructor(private toastController: ToastController) {}

  ngOnInit(): void {
    this.isLoaded = false;
    this.cells = new Array(this.nbHexagonal);
    this.penguins = new Array(this.nbPenguin * 2);
    this.generateMap();
    this.generatePenguin();
    console.log('Board ok');
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

    this.wasmPenguins = this.wasmBoard.getPawnsOnBoard();
    this.generatePenguinFromWasmBoard();
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

    for (let ii = 0; ii < wasmCells.size(); ii++) {
      let wasmCell: any = wasmCells.get(ii);
      let wasmCellPos = wasmCell.getPosition();
      wasmCellPos = Module.hex_cube_to_offset(Module.hex_axial_to_cube(wasmCellPos));
      this.cells[wasmCellPos.row][wasmCellPos.column].setWasmCell(wasmCell);
    }
  }

  generatePenguin() {
    console.log('Generate Penguins');
    let penguin: Penguin;
    let rndRow: number, rndColumn: number;
    for (let ii = 0; ii < this.penguins.length; ii++) {
      while (this.penguins[ii] === undefined) {
        rndRow = Math.floor(0 + Math.random() * (this.nbHexagonal - 0));
        rndColumn = Math.floor(0 + Math.random() * (this.nbHexagonal - 0));
        if (!this.cells[rndRow][rndColumn].hasPenguin) {
          this.penguins[ii] = new Penguin(this.cells[rndRow][rndColumn], true);
          this.cells[rndRow][rndColumn].hasPenguin = true;
        }
      }
    }
  }

  generatePenguinFromWasmBoard() {
    for (let ii = 0; ii < this.penguins.length; ii++) {
      this.penguins[ii].wasmPenguin = this.wasmPenguins.get(ii);

      let ownerId: any = this.penguins[ii].wasmPenguin.getOwner().getId();
      this.penguins[ii].textureIndex = ownerId;
      this.penguins[ii].playerPenguin = ownerId == this.humanPlayerId;

      this.wasmBoard.performMove(this.wasmPenguins.get(ii), this.penguins[ii].cellPosition.wasmCell);
    }
  }

  /***************************************************************************************************************************
   ************************************************ ANIMATION******************************************************************
   ***************************************************************************************************************************/
  onPenguinClick(newPenguinClicked: Penguin) {
    // Not the first time a penguin is clicked in this turn
    if (newPenguinClicked.playerPenguin) {
      if (this.penguinSelected !== undefined) {
        // The user clicked :
        // - on the same penguin
        if (this.penguinSelected === newPenguinClicked) {
          this.setSelectedPenguinColor(false);
          this.penguinSelected = undefined;
          gameService.send(gameService.machine.states.penguinSelected.on.PENGUINSELECTED[0].eventType);
        } else {
          // - on an another penguin
          // Keep the same state : PenguinSelected
          this.setSelectedPenguinColor(false);
          this.penguinSelected = newPenguinClicked;
          this.setSelectedPenguinColor(true);
        }
      } else {
        this.penguinSelected = newPenguinClicked;
        this.setSelectedPenguinColor(true);
        gameService.send(gameService.machine.states.waiting.on.PENGUINSELECTED[0].eventType);
      }
    } else {
      this.presentErrorToast('It is not your penguin !!');
    }
  }

  onCellClick(cellClicked: Cell) {
    if (gameService.state.value === 'penguinSelected') {
      this.penguinSelected.moveTo(cellClicked);
      this.penguinSelected = undefined;
      gameService.send(gameService.machine.states.penguinSelected.on.CELLSELECTED[0].eventType);
    }
  }

  setSelectedPenguinColor(set: boolean) {
    this.penguinSelected.switchPenguinColor();
    this.setAvailableCellColor(set);
  }

  setAvailableCellColor(set: boolean) {
    if (this.penguinSelected !== undefined) {
      var availableCells: any = this.wasmBoard.getAvailableCells(this.penguinSelected.wasmPenguin);
      for (let ii = 0; ii < availableCells.size(); ii++) {
        let wasmCellPos = availableCells.get(ii).getPosition();
        wasmCellPos = Module.hex_cube_to_offset(Module.hex_axial_to_cube(wasmCellPos));
        this.cells[wasmCellPos.row][wasmCellPos.column].setAvailableColor(set);
      }
    }
  }

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

  /***************************************************************************************************************************
   ************************************************ TOAST ********************************************************************
   ***************************************************************************************************************************/
  async presentErrorToast(message: string) {
    const toast = await this.toastController.create({
      message: message,
      position: 'top',
      color: 'danger',
      duration: 3000
    });
    toast.present();
  }
}
