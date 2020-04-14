import { Component, OnInit, ViewChild } from '@angular/core';
import { BoardComponent } from './board/board.component';


declare var Module: any;

@Component({
  selector: 'app-game',
  templateUrl: './game.component.html',
  styleUrls: ['./game.component.scss']
})

export class GameComponent implements OnInit {
  @ViewChild(BoardComponent, { static: true })
  private boardComponent: BoardComponent;

  nbHexagonal: number = 8;
  nbPenguin: number = 4;

  constructor() { }

  ngOnInit(): void { }

  /***************************************************************************************************************************
  ************************************************ PREVIEW *******************************************************************
  ***************************************************************************************************************************/

  // nbHexagonalChanged(event: any) {
  //   if ((this.nbHexagonal - event.detail.value) < 0) {
  //     this.boardComponent.addHexagonal();
  //   } else {
  //     this.boardComponent.removeHexagonal();
  //   }
  //   this.nbHexagonal = event.detail.value;
  //   console.log("New nb of hexagonals : " + this.nbHexagonal);
  // }

  // nbPenguinChanged(event: any) {
  //   if ((this.nbPenguin - event.detail.value) < 0) {
  //     this.boardComponent.addPenguin();
  //   } else {
  //     this.boardComponent.removePenguin();
  //   }
  //   this.nbPenguin = event.detail.value;
  //   console.log("New nb of penguins : " + this.nbPenguin);
  // }
}
