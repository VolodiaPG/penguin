import { Component, OnInit, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { BoardComponent } from './board/board.component';
import { InfoComponent } from './info/info.component';

import { Flip } from 'number-flip';

import { gameService } from './+xstate/gameMachine';
import { appService } from './+xstate/appMachine';

declare var Module: any;

@Component({
  selector: 'app-game',
  templateUrl: './game.component.html',
  styleUrls: ['./game.component.scss']
})
export class GameComponent implements OnInit {
  @ViewChild('numberbtn', { read: ElementRef, static: true }) private btn: ElementRef;
  flipAnim: any = null;

  @ViewChild(InfoComponent, { static: false })
  private infoComponent: InfoComponent;

  @ViewChild(BoardComponent, { static: true })
  private boardComponent: BoardComponent;

  stateControler: any = appService;

  gameStarted: boolean = false;

  nbHexagonal: number = 8;
  nbPenguin: number = 2;

  constructor() {}

  ngOnInit(): void {}

  /***************************************************************************************************************************
   ************************************************ START GAME ****************************************************************
   ***************************************************************************************************************************/
  initGameBoard() {
    console.log('Init Game Board');
    this.boardComponent.initWasmBoard();
  }

  penguinPosed() {
    this.infoComponent.penguinPosed();
  }

  launchGame() {
    appService.send(appService.machine.states.initPosPenguin.on.PENGUINSPOSED[0].eventType);
    this.gameStarted = true;
    this.boardComponent.startWasmGame();
  }

  /***************************************************************************************************************************
   ************************************************ ANIMATION *****************************************************************
   ***************************************************************************************************************************/

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

  /***************************************************************************************************************************
   ************************************************ PREVIEW *******************************************************************
   ***************************************************************************************************************************/

  nbHexagonalChanged(event: any) {
    if (this.nbHexagonal - event.detail.value < 0) {
      this.boardComponent.addHexagonal();
    } else {
      this.boardComponent.removeHexagonal();
    }
    this.nbHexagonal = event.detail.value;
  }

  nbPenguinChanged(event: any) {
    if (this.nbPenguin - event.detail.value < 0) {
      this.boardComponent.addPenguin();
    } else {
      this.boardComponent.removePenguin();
    }
    this.nbPenguin = event.detail.value;
    console.log(this.nbPenguin);
  }
}
