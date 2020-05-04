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
  cellClicked: Cell;

  currentPlayerId: number;

  humanPlayerId: number = 2;

  // Wasm objects
  wasmGame: any;
  wasmBoard: any;
  wasmPenguins: any;

  mctsConstraints: any;
  wasmMCTSPlayer: any;
  wasmMove: any;


  constructor(private toastController: ToastController) { }

  ngOnInit(): void {
    this.isLoaded = false;
    this.cells = new Array(this.nbHexagonal);
    this.penguins = new Array();
    this.generateMap();
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
    console.log('Init WasmGame', this.nbHexagonal, this.nbPenguin);
    this.wasmGame = new Module.PenguinGame(this.nbHexagonal, this.nbPenguin);
    this.wasmBoard = this.wasmGame.getBoard();
    this.humanPlayerId = this.wasmGame.getPlayerToPlay();
    this.generateMapFromWasmBoard();
  }

  startWasmGame() {
    this.wasmPenguins = this.wasmBoard.getPawnsOnBoard();
    this.generateWasmPenguin();
    this.putPenguinOnWasmBoard();

    this.currentPlayerId = this.wasmGame.getPlayerToPlay();
    this.humanPlayerId = this.currentPlayerId;

    this.wasmMCTSPlayer = new Module.penguin_MCTSPlayer(this.wasmGame, { time: 150 });

    this.playTurn();
  }

  /***************************************************************************************************************************
   ************************************* MAP/TEXTURES ************************************************************************
   ***************************************************************************************************************************/
  generateMap() {
    console.log('Generate Map', this.nbHexagonal, this.nbPenguin);
    let cell: Cell;
    for (let row = 0; row < this.nbHexagonal; row++) {
      this.cells[row] = new Array(this.nbHexagonal);

      for (let column = 0; column < this.nbHexagonal; column++) {
        cell = new Cell(row, column);
        this.cells[row][column] = cell;
      }
    }
  }

  posePenguinOn(cellPos: Cell) {
    if (this.penguins.length < this.nbPenguin) {
      let penguin = new Penguin();
      if (!cellPos.hasPenguin) {
        cellPos.hasPenguin = true;
        penguin.cellPosition = cellPos;
        penguin.textureIndex = this.humanPlayerId;
        penguin.isVisible = true;

        this.penguins.push(penguin);
        this.penguinPosed.emit();
      } else {
        this.presentErrorToast("This case isn't empty !");
      }
    } else {
      this.presentErrorToast('No more Penguins in stock !');
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

  generateWasmPenguin() {
    let rndRow: number, rndColumn: number;
    for (let ii = 0; ii < this.nbPenguin; ii++) {
      this.penguins.push(undefined);
      while (this.penguins[this.nbPenguin + ii] === undefined) {
        rndRow = Math.floor(0 + Math.random() * (this.nbHexagonal - 0));
        rndColumn = Math.floor(0 + Math.random() * (this.nbHexagonal - 0));
        if (!this.cells[rndRow][rndColumn].hasPenguin) {
          this.penguins[this.nbPenguin + ii] = new Penguin();
          this.penguins[this.nbPenguin + ii].cellPosition = this.cells[rndRow][rndColumn];
          this.cells[rndRow][rndColumn].hasPenguin = true;
          this.penguins[this.nbPenguin + ii].textureIndex = (this.humanPlayerId % 2) + 1;
        }
      }
    }
  }

  putPenguinOnWasmBoard() {
    for (let ii = 0; ii < this.wasmPenguins.size(); ii++) {
      let penguinPosed = false;
      let wasmPenguin = this.wasmPenguins.get(ii);
      for (let jj = 0; jj < this.penguins.length && !penguinPosed; jj++) {
        if (
          this.penguins[jj].wasmPenguin === undefined &&
          wasmPenguin.getOwner().getId() === this.penguins[jj].textureIndex
        ) {
          this.penguins[jj].setWasmPenguin(wasmPenguin);

          this.wasmBoard.performMove(this.penguins[jj].wasmPenguin, this.penguins[jj].cellPosition.wasmCell);

          this.penguins[jj].isVisible = true;
          penguinPosed = true;
        }
      }
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

      this.setMCTSBestMove();
      this.playWasmMove();
    }
  }

  setMCTSBestMove() {
    this.wasmMove = this.wasmMCTSPlayer.bestMove();

    let pawnId = this.wasmMove.getPawn().getId();

    for (let ii = 0; ii < this.penguins.length; ii++) {
      if (this.penguins[ii].wasmPenguin.getId() === pawnId) {
        this.penguinSelected = this.penguins[ii];
      }
    }

    // console.log('pawn : ', this.penguinSelected, 'from : ', this.wasmMove.getFrom().getPosition(), 'target : ', wasmCellClicked.getPosition());
    let wasmCellPos = Module.hex_cube_to_offset(Module.hex_axial_to_cube(this.wasmMove.getTarget().getPosition()));
    this.cellClicked = this.cells[wasmCellPos.row][wasmCellPos.column];
  }

  playWasmMove() {
    // console.log('pawn : ', this.penguinSelected.wasmPenguin.getId(), this.penguinSelected, 
    //             'from : ', this.penguinSelected.cellPosition, 
    //             'target : ', this.cellClicked);
    console.log('pawn : ', this.wasmMove.getPawn().getId(),  
                this.wasmMove.getPawn().getId() === this.penguinSelected.wasmPenguin.getId(),
                '\n from : ', Module.hex_cube_to_offset(Module.hex_axial_to_cube(this.wasmMove.getFrom().getPosition())), 
                '\n target : ', Module.hex_cube_to_offset(Module.hex_axial_to_cube(this.wasmMove.getTarget().getPosition())));

    if (this.wasmGame.play(this.penguinSelected.wasmPenguin, this.cellClicked.wasmCell)) {
      this.penguinSelected.moveTo(this.cellClicked);
      this.wasmMCTSPlayer.updateTree(this.wasmMove);

      // this.penguinSelected.wasmPenguin = this.wasmGame.getBoard().getPawnById(this.penguinSelected.wasmPenguin.getId());

      gameService.send(gameService.machine.states.penguinSelected.on.CELLSELECTED[0].eventType);
      gameService.send(gameService.machine.states.moveBlocked.on.MCTSPLAYED[0].eventType);

      this.movePerformed();
    } else {
      console.log('Wasm blocked the move');
      this.setAvailableCellColor(true);
      this.setSelectedPenguinColor(true);
    }

    this.penguinSelected = undefined;
    this.cellClicked = undefined;
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
      switch (gameService.state.value) {
        case 'waiting':
          this.penguinSelected = newPenguinClicked;
          this.setSelectedPenguinColor(true);
          gameService.send(gameService.machine.states.waiting.on.PENGUINSELECTED[0].eventType);
          break;

        case 'penguinSelected':
          // The user clicked on an another penguin
          // Keep the same state : PenguinSelected
          this.setSelectedPenguinColor(false);
          this.penguinSelected = newPenguinClicked;
          this.setSelectedPenguinColor(true);
          break;

        default:
          console.log('Sorry, state not ok : ', gameService.state.value);
      }
    } else {
      this.presentErrorToast('It is not your penguin !!');
    }
  }

  onCellClick(cellClicked: Cell) {
    switch (appService.state.value) {
      case 'initPosPenguin':
        // console.log('Pose a penguin here');
        this.posePenguinOn(cellClicked);
        break;
    }

    switch (gameService.state.value) {
      case 'penguinSelected':
        this.setAvailableCellColor(false);
        this.setSelectedPenguinColor(false);

        this.cellClicked = cellClicked;

        this.wasmMove = new Module.penguin_Move(this.penguinSelected.cellPosition.wasmCell, this.cellClicked.wasmCell, this.penguinSelected.wasmPenguin);
        this.playWasmMove();
        break;
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

  addPenguin(): void {
    this.nbPenguin++;
  }

  removePenguin(): void {
    this.nbPenguin--;
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
