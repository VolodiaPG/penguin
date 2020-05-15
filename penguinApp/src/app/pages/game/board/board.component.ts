import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { trigger, transition, animate, style, query, stagger, state } from '@angular/animations';
import { ToastController } from '@ionic/angular';

import { Cell } from './models/cell';
import { Penguin } from './models/penguin';

import { gameService } from './models/gameMachine';
import { appService } from './models/appMachine';


declare var Module: any;

/**
 * Component for all the components about the Penguin Game.
 */
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

  /**
   * Value to check if the game has been started by the user.
   * Two-way bindings with the game component.
   */
  @Input() gameStarted: boolean;

  /**
   * Emitter to the game component to notify when the user posed one of his penguins.
   */
  @Output() penguinPosed = new EventEmitter<any>();


  /**
   * Value to bind the State Controler FSM and to use its value.
   */
  stateControler: any = appService;

  isLoaded = false;

  /**
   * Value of hexagonals contains in one line on the board.
   */
  nbHexagonal: number = 8; // 8

  /**
   * The pixel width of a hex.
   */
  hexWidth: number = 90; // 90
  /**
   * The pixel height of a hex.
   */
  hexHeight: number = 90; // 90

  /**
   * 2D Array with all the cells on the map (row of column).
   */
  cells: Array<Array<Cell>>;

  /**
   * Value of penguins contains on the board.
   */
  nbPenguin: number = 2;

  /**
   * Array with all the penguins on the board.
   */
  penguins: Array<Penguin>;

  /**
   * Pointer to the current penguin selected by the curent player to play.
   */
  penguinSelected: Penguin;
  /**
   * Pointer to the current cell clicked by the curent player to play.
   */
  cellClicked: Cell;

  /**
   * Value of the current player id.
   */
  currentPlayerId: number;

  /**
   * Value of the user's id.
   */
  humanPlayerId: number = 2;

  /**
   * Pointer to the C++ object : Game.
   */
  wasmGame: any;
  /**
   * Pointer to the C++ object : Board.
   */
  wasmBoard: any;
  /**
   * Pointer to the C++ object : vector<Penguin>.
   */
  wasmPenguins: any;

  /**
   * Pointer to the C++ object, which contains the constraints for the MCTS.
   */
  mctsConstraints: any;
  /**
   * Pointer to the C++ object : MCTSPlayer.
   */
  wasmMCTSPlayer: any;

  /**
   * Pointer to the C++ object : Move, to be able to perform a move and update the MCTS tree.
   */
  wasmMove: any;


  /**
  * @ignore
  */
  constructor(private toastController: ToastController) { }

  /**
  * Call when the Board Component is created.
  * Initialize :
  *     - the Array of Cells,
  *     - the Array of Penguins,
  * Then call the generateMap() function.
  */
  ngOnInit(): void {
    this.isLoaded = false;
    this.cells = new Array(this.nbHexagonal);
    this.penguins = new Array();
    this.generateMap();
    console.log('Board ok');
  }

  /**
   * Call when the Board Component is destroyed.
   * Delete the c++ object Game if and only if it has been initialized.
   * Set null in all the others variables used in the front part.
   */
  ngOnDestroy(): void {
    if (this.gameStarted) {
      console.log('Game destroyed');
      this.wasmGame.delete();
      this.cells = null;
      this.penguins = null;
      this.gameStarted = false;
    }
  }


  //*************************************************************************************************************************
  //********************************************** START GAME ***************************************************************
  //*************************************************************************************************************************

  /**
   * Get the random board genrated by the C++ code.
   * Set the current player Id, the human player id, in agrement with the first player which has to play.
   * Then call the generateMapFromWasmBoard function to update the front part.
   */
  initWasmBoard() {
    console.log('Init WasmGame', this.nbHexagonal, this.nbPenguin);
    this.wasmGame = new Module.PenguinGame(this.nbHexagonal, this.nbPenguin);
    this.wasmBoard = this.wasmGame.getBoard();

    this.currentPlayerId = this.wasmGame.getPlayerToPlay();
    this.humanPlayerId = this.currentPlayerId;

    this.generateMapFromWasmBoard();
  }

  /**
   * Get a random vector of penguins generated in C++, when the IA penguins has to be initialize.
   * Generate the penguins of the Mcts player and then put these in the board.
   * Create the C++ object to use the MCTS.
   * Finally, launch the game !
   */
  startWasmGame() {
    this.wasmPenguins = this.wasmBoard.getPawnsOnBoard();
    this.generateWasmPenguin();
    this.putPenguinOnWasmBoard();

    this.wasmMCTSPlayer = new Module.penguin_MCTSPlayer(this.wasmGame, { time: 2000 });

    this.playTurn();
  }

  //*************************************************************************************************************************
  //********************************************** MAP/TEXTURES *************************************************************
  //*************************************************************************************************************************

  /**
   * Create an empty map, with a size of the hexagonals number, and with x penguins.
   */
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

  /**
   * Pose a penguin, not put yet, in the cell in parameter. 
   * @param {Cell} cellPos 
   */
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

  /**
   * Update the fish number on all the cells on the board, accordingly with the C++ board.
   */
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

  /**
   * Generate the penguins for the wasm player.
   */
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

  /**
   * Put the penguin on the right cell in C++, with a fake move.
   */
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

  //*************************************************************************************************************************
  //********************************************** GAME LOGIC ***************************************************************
  //*************************************************************************************************************************

  /**
   * Allow each player to play, when it is his turn.
   * Show a little toast to alert the user.
   */
   playTurn() {
    if (this.currentPlayerId === this.humanPlayerId) {
      this.presentSuccessToast('It is your turn ' + this.currentPlayerId + ' !');
      gameService.send(gameService.machine.states.moveBlocked.on.HUMANTURN[0].eventType);
    } else {
      this.presentErrorToast('Wasm is playing ' + this.currentPlayerId + ' !');

      this.setMCTSBestMove();
      this.playWasmMove();
    }
  }

  /**
   * Ask the MCTS PLayer to get the best move to play.
   */
  setMCTSBestMove() {
    this.wasmMove = this.wasmMCTSPlayer.bestMove();

    console.log('wasmMove: ');
    console.log(this.wasmMove.getPawn());
    console.log(this.wasmMove.getTarget());
    console.log(this.wasmMove.getFrom());

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

  /**
   * Play a move in the C++ game, then update the tree.
   */
  playWasmMove() {
    console.log(
      'pawn : ',
      this.wasmMove.getPawn().getId(),
      this.wasmMove.getPawn().getId() === this.penguinSelected.wasmPenguin.getId(),
      '\n from : ',
      Module.hex_cube_to_offset(Module.hex_axial_to_cube(this.wasmMove.getFrom().getPosition())),
      '\n target : ',
      Module.hex_cube_to_offset(Module.hex_axial_to_cube(this.wasmMove.getTarget().getPosition()))
    );

    // if the move is to be rejected, then it will also be in the trees,
    //but this function needs to be called before changing the state of the _main_ game board
    this.wasmMCTSPlayer.updateTree(this.wasmMove);

    if (this.wasmGame.play(this.penguinSelected.wasmPenguin, this.cellClicked.wasmCell)) {
      this.penguinSelected.moveTo(this.cellClicked);

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

  /**
   * Switch the id of the current player, accordingly with the changement in the C++ game.
   */
  switchCurrentPlayer() {
    this.currentPlayerId = this.wasmGame.getPlayerToPlay();
    gameService.send(gameService.machine.states.playerSwitched.on.PLAYERSWITCHED[0].eventType);
  }

  /**
   * Check the game status, after a move was performed.
   * Then react in agrement with the wasm return.
   * 
   * @exemple 
   * 0 : game not finish yet,
   * -1 : a draw,
   * 1 or 2 : id of the player which has won.
   */
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

  //*************************************************************************************************************************
  //********************************************** ANIMATION ****************************************************************
  //*************************************************************************************************************************

  /**
   * React on the click event on a penguin. The reaction depends of the current state of the stateControler and the game State Machine.
   * Some features are only available on our own penguins.
   * @param {Penguin} newPenguinClicked pointer on the penguin selected
   */
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

  /**
   * React on the click event on a cell. The reaction depends of the current state of the stateControler and the game State Machine.
   * Some features are only available when a penguin are selected or not.
   * @param {Cell} cellClicked pointer on the cell clicked
   */
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

        this.wasmMove = new Module.penguin_Move(
          this.penguinSelected.cellPosition.wasmCell,
          this.cellClicked.wasmCell,
          this.penguinSelected.wasmPenguin
        );
        this.playWasmMove();
        break;
    }
  }

  /**
   * Set/Remove the color penguin, if he is selected or not.
   * @param {boolean} set if the penguin had to be colorized or not
   */
  setSelectedPenguinColor(set: boolean) {
    this.penguinSelected.switchPenguinColor();
    this.setAvailableCellColor(set);
  }

  /**
   * Set/Remove the color cell, if he is selected or not.
   * @param {boolean} set if the cell had to be colorized or not
   */
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

  //*************************************************************************************************************************
  //********************************************** PREVIEW ******************************************************************
  //*************************************************************************************************************************

  /**
   * Increase the number of hexagonal.
   * Add a cell on each row, and initialize it.
   * Then add a row.
   * @exemple
   * 7x7 -> 8x8
   */
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

  /**
   * Decrease the number of hexagonal.
   * Remove a cell on each row.
   * Then Remove a row.
   * @exemple
   * 7x7 -> 6x6
   */
  removeHexagonal(): void {
    this.nbHexagonal--;
    //Remove a cell on all the row
    for (let row = 0; row < this.cells.length; row++) {
      this.cells[row].pop();
    }
    //Remove a row
    this.cells.pop();
  }

  /**
   * Increase the number of penguins.
   */
  addPenguin(): void {
    this.nbPenguin++;
  }

  /**
   * Decrease the number of penguins.
   */
  removePenguin(): void {
    this.nbPenguin--;
  }

  //************************************************************************************************************************
  //*********************************************** TOAST ******************************************************************
  //************************************************************************************************************************

  /**
   * Create a toast, in the top of the window, using the success theme.
   * @param {string} message that will be written in the toast
   */
  async presentSuccessToast(message: string) {
    const toast = await this.toastController.create({
      message: message,
      color: 'success',
      position: 'top',
      duration: 3000
    });
    toast.present();
  }

   /**
   * Create a toast, in the top of the window, using the error theme.
   * @param {string} message that will be written in the toast
   */
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