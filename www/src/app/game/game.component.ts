import { Component, OnInit, ViewChild, ElementRef } from '@angular/core';
import { BoardComponent } from './board/board.component';

import { Flip } from 'number-flip';


declare var Module: any;

@Component({
  selector: 'app-game',
  templateUrl: './game.component.html',
  styleUrls: ['./game.component.scss']
})

export class GameComponent implements OnInit {
  @ViewChild('numberbtn', { read: ElementRef, static: true }) private btn: ElementRef;
  flipAnim: any = null;
  
  @ViewChild(BoardComponent, { static: true })
  private boardComponent: BoardComponent;

  nbHexagonal: number = 8;
  nbPenguin: number = 4;

  gameStarted: boolean = false;

  constructor() { }

  ngOnInit(): void { }

  /***************************************************************************************************************************
  ************************************************ START GAME ****************************************************************
  ***************************************************************************************************************************/
  launchGame() {
    this.boardComponent.startWasmGame();
    this.gameStarted = true;
  }

  /***************************************************************************************************************************
  ************************************************ ANIMATION *****************************************************************
  ***************************************************************************************************************************/

  flip() {
    console.log("Number-flip in action");
    if(!this.flipAnim) {
      this.flipAnim = new Flip({
        node: this.btn.nativeElement,
        from: '9999',
      });
    }
    this.flipAnim.flipTo({
      to: Math.floor((Math.random() * 1000) + 1)
    });
  }


  /***************************************************************************************************************************
  ************************************************ PREVIEW *******************************************************************
  ***************************************************************************************************************************/

  nbHexagonalChanged(event: any) {
    if ((this.nbHexagonal - event.detail.value) < 0) {
      this.boardComponent.addHexagonal();
    } else {
      this.boardComponent.removeHexagonal();
    }
    this.nbHexagonal = event.detail.value;
    console.log("New nb of hexagonals : " + this.nbHexagonal);
  }

  nbPenguinChanged(event: any) {
    if ((this.nbPenguin - event.detail.value) < 0) {
      this.boardComponent.addPenguin();
    } else {
      this.boardComponent.removePenguin();
    }
    this.nbPenguin = event.detail.value;
    console.log("New nb of penguins : " + this.nbPenguin);
  }

}
