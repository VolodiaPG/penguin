import { Component, OnInit, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { BoardComponent } from './board/board.component';
import { InfoComponent } from './info/info.component';

import { Flip } from 'number-flip';

import { gameService } from './board/models/gameMachine';
import { appService } from './board/models/appMachine';

/**
 * Wasm Module
 */
declare var Module: any;

/**
 * Game Component, symbolize the page with the game and with all the above components.
 */
@Component({
  selector: 'app-game',
  templateUrl: './game.page.html',
  styleUrls: ['./game.page.scss']
})
export class GamePage implements OnInit {
  /**
   * To control the flip and the button to show the current score.
   */
  @ViewChild('divHuman', { read: ElementRef, static: true }) private scoreHuman: ElementRef;

  /**
   * To control the flip and the button to show the current score.
   */
  @ViewChild('divMcts', { read: ElementRef, static: true }) private scoreMcts: ElementRef;

  playerToPlay: string = "human";

  /**
   * To animate, to flip, the human score when it changes.
   */
  flipHumanScore: any = null;

    /**
   * To animate, to flip, the MCTS score when it changes.
   */
  flipMctsScore: any = null;

  /**
   * Allow us to control the son component : InfoComponent
   */
  @ViewChild(InfoComponent, { static: false })
  private infoComponent: InfoComponent;


  /**
   * Allow us to control the son component : BoardComponent
   */
  @ViewChild(BoardComponent, { static: true })
  private boardComponent: BoardComponent;

  
  /**
   * Service to use the State Machine which controle the app flux.
   */
  stateControler: any = appService;

  /**
   * Variable to control when the game is started or not.
   */
  gameStarted: boolean = false;

  /**
   * Value of hexagonals on a single row on the board.
   */
  nbHexagonal: number = 8;

  /**
   * Value of penguins on the board.
   */
  nbPenguin: number = 2;

  /**
   * Value to count the fishes owned by the user.
   */
  nbHumanFish: number;

  /**
   * Value to count the fishes owned by the mcts.
   */
  nbMctsFish: number;

  /**
   * @ignore
   */
  constructor() {}

  /**
   * @ignore
   */
  ngOnInit(): void {
    this.nbHumanFish = 0;
    this.nbMctsFish = 0;
  }

  //***************************************************************************************************************************
  // ************************************************ START GAME **************************************************************
  // **************************************************************************************************************************
  
  /**
   * Launch the init oh the wasm part and the C++ game.
   */
  initGameBoard() {
    console.log('Init Game Board');
    this.boardComponent.initWasmBoard();
  }

  /**
   * Call a function in the Info Component, when the user posed one penguin.
   */
  penguinPosed() {
    this.infoComponent.penguinPosed();
  }

  /**
   * Launch the wasm Game when the user press the Start button.
   */
  launchGame() {
    appService.send(appService.machine.states.initPosPenguin.on.PENGUINSPOSED[0].eventType);
    this.gameStarted = true;
    this.boardComponent.startWasmGame();
    this.flipScore();
  }

  //***************************************************************************************************************************
  //************************************************ ANIMATION ****************************************************************
  //***************************************************************************************************************************

  /**
   * Create the animation for the button which show the current score.
   */
  flipScore() {
    if (!this.flipHumanScore) {
      this.flipHumanScore = new Flip({
        node: this.scoreHuman.nativeElement,
        from: '99'
      });
    }
    if (!this.flipMctsScore) {
      this.flipMctsScore = new Flip({
        node: this.scoreMcts.nativeElement,
        from: '99'
      });
    }

    this.flipHumanScore.flipTo({
      to: this.nbHumanFish
    });

    this.flipMctsScore.flipTo({
      to: this.nbMctsFish
    });
  }

  /**
   * Function to switch the visual information of which player to play.
   */
  switchPlayerTurn(humanPlayerId: number, currentPlayerId: number) {
    let choice = humanPlayerId === currentPlayerId;
    if(choice) {
      this.playerToPlay = "human";
    } else {
      this.playerToPlay = "mcts"
    }
  }

  switchPlayerToPlay() {
    if(this.playerToPlay === "human") {
      this.playerToPlay = "mcts";
    } else {
      this.playerToPlay = "human";
    }
    this.flipScore();
  }

  //***************************************************************************************************************************
  //************************************************ PREVIEW ******************************************************************
  //***************************************************************************************************************************

  /**
   * Function which react on an event coming from the Consol Component, raise when the number of hexagonals changed.
   * @param {any} event 
   */
  nbHexagonalChanged(event: any) {
    if (this.nbHexagonal - event.detail.value < 0) {
      this.boardComponent.addHexagonal();
    } else {
      this.boardComponent.removeHexagonal();
    }
    this.nbHexagonal = event.detail.value;
  }

  /**
   * Function which react on an event coming from the Consol Component, raise when the number of penguins changed.
   * @param {any} event 
   */
  nbPenguinChanged(event: any) {
    if (this.nbPenguin - event.detail.value < 0) {
      this.boardComponent.addPenguin();
    } else {
      this.boardComponent.removePenguin();
    }
    this.nbPenguin = event.detail.value;
  }
}
