import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { ToastController } from '@ionic/angular';
import { trigger, transition, animate, style, query, stagger, state } from '@angular/animations';

import { Cell } from './cell';
import { Penguin } from './penguin';

import { gameService } from '../+xstate/gameMachine';
import { appService } from '../+xstate/appMachine';

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
  @Output() penguinPosed = new EventEmitter<any>();

  stateControler: any = appService;

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

  currentPlayerId: number;

  humanPlayerId: number;

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
   ************************************************ START GAME ***************************************************************
   ***************************************************************************************************************************/
  initWasmBoard() {
    this.wasmGame = new Module.PenguinGame(this.nbHexagonal, this.nbPenguin);
    this.wasmBoard = this.wasmGame.getBoard();
    this.generateMapFromWasmBoard();
  }

  startWasmGame() {
    this.wasmPenguins = this.wasmBoard.getPawnsOnBoard();
    this.generatePenguin();
    this.generatePenguinFromWasmBoard();

    this.currentPlayerId = this.wasmGame.getPlayerToPlay();
    this.humanPlayerId = this.currentPlayerId;

    this.playTurn();
  }

  /***************************************************************************************************************************
   ************************************* MAP/TEXTURES ************************************************************************
   ***************************************************************************************************************************/
  generateMap() {
    console.log('Generate Map');
    let cell: Cell;
    for (let row = 0; row < this.nbHexagonal; row++) {
      this.cells[row] = new Array(this.nbHexagonal);

      for (let column = 0; column < this.nbHexagonal; column++) {
        cell = new Cell(row, column);
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
          this.penguins[ii] = new Penguin(this.cells[rndRow][rndColumn]);
          this.cells[rndRow][rndColumn].hasPenguin = true;
        }
      }
    }
  }

  generatePenguinFromWasmBoard() {
    console.log(this.penguins.length, this.wasmPenguins.size());
    for (let ii = 0; ii < this.penguins.length; ii++) {
      this.penguins[ii].setWasmPenguin(this.wasmPenguins.get(ii));

      this.wasmBoard.performMove(this.penguins[ii].wasmPenguin, this.penguins[ii].cellPosition.wasmCell);
    }
  }

  /***************************************************************************************************************************
   ************************************************ GAME LOGIC ***************************************************************
   ***************************************************************************************************************************/
  playTurn() {
    if (this.currentPlayerId === this.humanPlayerId) {
      this.presentSuccessToast('It is your turn !');
      gameService.send(gameService.machine.states.moveBlocked.on.HUMANTURN[0].eventType);
    } else {
      this.presentErrorToast('Wasm is playing !');
    }
  }

  switchCurrentPlayer() {
    this.currentPlayerId = (this.currentPlayerId % 2) + 1;
    gameService.send(gameService.machine.states.playerSwitched.on.PLAYERSWITCHED[0].eventType);
  }

  movePerformed() {
    let currentStatus = this.wasmBoard.checkStatus();
    if (currentStatus === 0) {
      // The game isn't finished
      gameService.send(gameService.machine.states.movePerformed.on.SWITCHPLAYER[0].eventType);
      this.switchCurrentPlayer();
      this.playTurn();
    } else {
      gameService.send(gameService.machine.states.movePerformed.on.FINISHED[0].eventType);
      if (currentStatus === -1) {
        // draw
      } else {
        console.log(currentStatus + ' has won !');
      }
    }
  }

  /***************************************************************************************************************************
   ************************************************ ANIMATION ****************************************************************
   ***************************************************************************************************************************/
  onPenguinClick(newPenguinClicked: Penguin) {
    if (newPenguinClicked.textureIndex === 0) {
      // The user clicked on the same penguin
      this.setSelectedPenguinColor(false);
      this.penguinSelected = undefined;
      gameService.send(gameService.machine.states.penguinSelected.on.PENGUINSELECTED[0].eventType);
    } else if (newPenguinClicked.textureIndex === this.humanPlayerId) {
      if (gameService.state.value === 'waiting') {
        this.penguinSelected = newPenguinClicked;
        this.setSelectedPenguinColor(true);
        gameService.send(gameService.machine.states.waiting.on.PENGUINSELECTED[0].eventType);
      } else if (gameService.state.value === 'penguinSelected') {
        // The user clicked on an another penguin
        // Keep the same state : PenguinSelected
        this.setSelectedPenguinColor(false);
        this.penguinSelected = newPenguinClicked;
        this.setSelectedPenguinColor(true);
      }
    } else {
      this.presentErrorToast('It is not your penguin !!');
    }
  }

  onCellClick(cellClicked: Cell) {
    if (appService.state.value === 'initPosPenguin') {
      // console.log('Pose a penguin here');
      this.penguinPosed.emit();
    } else if (gameService.state.value === 'penguinSelected') {
      this.setAvailableCellColor(false);
      this.setSelectedPenguinColor(false);

      if (this.wasmGame.play(this.penguinSelected.wasmPenguin, cellClicked.wasmCell)) {
        this.penguinSelected.moveTo(cellClicked);
        this.penguinSelected = undefined;
        gameService.send(gameService.machine.states.penguinSelected.on.CELLSELECTED[0].eventType);
        this.movePerformed();
      } else {
        console.log('Wasm blocked the move');
        this.setAvailableCellColor(true);
        this.setSelectedPenguinColor(true);
      }
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
   ************************************************ PREVIEW ******************************************************************
   ***************************************************************************************************************************/
  addHexagonal(): void {
    this.nbHexagonal++;

    let cell: Cell;

    //Add a cell on all the row
    for (let row = 0; row < this.cells.length; row++) {
      cell = new Cell(row, this.cells[row].length);
      this.cells[row].push(cell);
    }

    //Add a row
    this.cells.push(new Array(this.nbHexagonal));

    for (let column = 0; column < this.cells[this.nbHexagonal - 1].length; column++) {
      cell = new Cell(this.nbHexagonal - 1, column);
      this.cells[this.nbHexagonal - 1][column] = cell;
    }

    console.log('New nb of hexagonals : ', this.nbHexagonal);
  }

  removeHexagonal(): void {
    this.nbHexagonal--;
    //Remove a cell on all the row
    for (let row = 0; row < this.cells.length; row++) {
      this.cells[row].pop();
    }
    //Remove a row
    this.cells.pop();

    console.log('New nb of hexagonals : ', this.nbHexagonal);
  }

  addPenguin(): void {
    let penguin: Penguin = undefined;
    let rndRow: number, rndColumn: number;

    for (let ii = 0; ii < 2; ii++) {
      while (penguin === undefined) {
        rndRow = Math.floor(0 + Math.random() * (this.nbHexagonal - 0));
        rndColumn = Math.floor(0 + Math.random() * (this.nbHexagonal - 0));

        if (!this.cells[rndRow][rndColumn].hasPenguin) {
          penguin = new Penguin(this.cells[rndRow][rndColumn]);
          this.cells[rndRow][rndColumn].hasPenguin = true;
        }
      }
      this.penguins.push(penguin);
      penguin = undefined;
    }

    this.nbPenguin = this.nbPenguin + 1;
    console.log('New nb of penguins : ', this.nbPenguin, 'New lg of penguins : ', this.penguins.length);
  }

  removePenguin(): void {
    this.nbPenguin = this.nbPenguin - 1;
    this.penguins.pop();
    this.penguins.pop();
  }

  /***************************************************************************************************************************
   ************************************************ TOAST ********************************************************************
   ***************************************************************************************************************************/
  async presentSuccessToast(message: string) {
    const toast = await this.toastController.create({
      message: message,
      color: 'success',
      position: 'top',
      duration: 3000
    });
    toast.present();
  }

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
