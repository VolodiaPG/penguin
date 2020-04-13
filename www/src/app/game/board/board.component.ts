import { Component, OnInit, ElementRef, NgZone } from '@angular/core';

import { PenguinGame } from './controller/penguinGame';

export let penguinGame: PenguinGame;

@Component({
  selector: 'app-board',
  templateUrl: './board.component.html',
  styleUrls: ['./board.component.scss']
})
export class BoardComponent implements OnInit {

  constructor(private elementRef: ElementRef, private ngZone: NgZone) { }

  ngOnInit(): void {
    this.setUpGameBoard(8, 4); //default : 8 hexagonals, 4 penguins
  }

  ngOnDestroy(): void {
    console.log("Game destroyed");
  }

  /***************************************************************************************************************************
  ************************************************ START GAME ****************************************************************
  ***************************************************************************************************************************/
  setUpGameBoard(nbHex: number, nbPeng: number) {
    this.ngZone.runOutsideAngular(() => {
      penguinGame = new PenguinGame(nbHex, nbPeng);
    });
    this.elementRef.nativeElement.appendChild(penguinGame.pixiApp.view);
  }

  launchGame() {
    penguinGame.startWasmGame();
  }

  /***************************************************************************************************************************
  ************************************************ PREVIEW *******************************************************************
  ***************************************************************************************************************************/
  addHexagonal(): void {
    penguinGame.addHexagonal();
  }

  removeHexagonal(): void {
    penguinGame.removeHexagonal();
  }

  addPenguin(): void {
    penguinGame.addPenguin();
  }

  removePenguin(): void {
    penguinGame.removePenguin();
  }
}
