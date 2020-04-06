import { Component, OnInit, ElementRef, NgZone } from '@angular/core';

import { PenguinGame } from './controller/penguinGame';

export let penguinGame: PenguinGame;

@Component({
  selector: 'app-board',
  templateUrl: './board.component.html',
  styleUrls: ['./board.component.scss']
})
export class BoardComponent implements OnInit { // or AfterViewInit

  // @ViewChild('imageCanvas', { static: false }) canvas: any;
  // canvasElement: any;

  constructor(private elementRef: ElementRef, private ngZone: NgZone) { }

  // ngAfterViewInit() {
  //   // Set the Canvas Element
  //   // this.canvasElement = this.canvas.nativeElement;

  //   // this.renderer.setElementAttribute(this.canvasElement, 'width', this.platform.width() + '');
  //   // this.renderer.setElementAttribute(this.canvasElement, 'height', this.platform.height() + ''); 
  // }

  ngOnInit(): void {
    this.setUpGameBoard(8, 4); //default : 8 hexagonals, 4 penguins
  }

  ngOnDestroy(): void {
    console.log("Game destroyed");
    // loader.destroy();
  }

  setUpGameBoard(nbHex: number, nbPeng: number) {
    this.ngZone.runOutsideAngular(() => {
      penguinGame = new PenguinGame(nbHex, nbPeng);
    });
    // Add the view to the DOM
    // document.body.appendChild(app.view);
    this.elementRef.nativeElement.appendChild(penguinGame.pixiApp.view);
  }

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

  reloadGameBoard(nbHex: number, nbPeng: number) {
    this.elementRef.nativeElement.removeChild(penguinGame.pixiApp.view);
    this.ngZone.runOutsideAngular(() => {
      penguinGame = new PenguinGame(nbHex, nbPeng);
    });
    // Add the view to the DOM
    // document.body.appendChild(app.view);
    this.elementRef.nativeElement.appendChild(penguinGame.pixiApp.view);
  }

  launchGame() {
    penguinGame.board.setRandomCells();
  }
}
