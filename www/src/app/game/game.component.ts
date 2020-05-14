import { Component, OnInit, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { BoardComponent } from './board/board.component';
import { InfoComponent } from './info/info.component';

import { Flip } from 'number-flip';

import { gameService } from '@app/game/models/gameMachine';
import { appService } from '@app/game/models/appMachine';

/**
 * Wasm Module
 */
declare var Module: any;

/**
 * Game Component, symbolize the page with the game and with all the above components.
 */
@Component({
  selector: 'app-game',
  templateUrl: './game.component.html',
  styleUrls: ['./game.component.scss']
})
export class GameComponent implements OnInit {
  /**
   * To control the flip and the button to show the current score.
   */
  @ViewChild('numberbtn', { read: ElementRef, static: true }) private btn: ElementRef;

  /**
   * To animate, to flip, the score when it changes.
   */
  flipAnim: any = null;

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
   * @ignore
   */
  constructor() {}

  /**
   * @ignore
   */
  ngOnInit(): void {}

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
  }

  //***************************************************************************************************************************
  //************************************************ ANIMATION ****************************************************************
  //***************************************************************************************************************************

  /**
   * Create the animation for the button which show the current score.
   */
  flip() {
    console.log('Number-flip in action');
    if (!this.flipAnim) {
      this.flipAnim = new Flip({
        node: this.btn.nativeElement,
        from: '9999'
      });
    }
    this.flipAnim.flipTo({
      to: Math.floor(Math.random() * 1000 + 1)
    });
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
