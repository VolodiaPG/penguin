import { Component, OnInit, ElementRef, NgZone, ViewChild, Renderer, AfterViewInit } from '@angular/core';
import { Platform, ToastController } from '@ionic/angular';
import { Application, Loader, Sprite, utils, Graphics, filters } from 'pixi.js';

import { Board } from './model/board';
import { Penguin } from './model/penguin';
import { filter } from 'rxjs/operators';

export const PENGUINS_NUMBER: number = 4;
export const HEXAGONALS_NUMBER: number = 8;

export let pixiApp: Application;

let loader: any = Loader.shared;


export function setBlurFilter(enable: boolean) {
  let blurFilter: filters.BlurFilter = new filters.BlurFilter();
  if (enable) {
    // Display blur filter
    pixiApp.stage.filters = [blurFilter];
  } else {
    pixiApp.stage.filters = [];
  }
}

@Component({
  selector: 'app-board',
  templateUrl: './board.component.html',
  styleUrls: ['./board.component.scss']
})
export class BoardComponent implements OnInit { // or AfterViewInit

  // @ViewChild('imageCanvas', { static: false }) canvas: any;
  // canvasElement: any;
  board: Board;

  boardWidth: number = HEXAGONALS_NUMBER * 90;
  boardHeight: number = HEXAGONALS_NUMBER * 90;

  constructor(public platform: Platform, private elementRef: ElementRef, private ngZone: NgZone) { }

  // ngAfterViewInit() {
  //   // Set the Canvas Element
  //   // this.canvasElement = this.canvas.nativeElement;

  //   // this.renderer.setElementAttribute(this.canvasElement, 'width', this.platform.width() + '');
  //   // this.renderer.setElementAttribute(this.canvasElement, 'height', this.platform.height() + ''); 
  // }

  ngOnInit(): void {
    this.ngZone.runOutsideAngular(() => {
      pixiApp = new Application({
        // view: this.canvas,
        width: this.boardWidth,   // this.platform.width(),         // window.innerWidth, default: 800
        height: this.boardHeight, //this.platform.height(),        // window.innerHeight default: 600
        antialias: true,          // default: false
        transparent: true,        // default: false
        resolution: 1,            // default: 1
        // resizeTo: parent
      });

      if (loader.progress === 0) { //already charged
        // Loader for the textures.
        loader.add("/assets/game/tileSnow_fish1.png")
          .add("/assets/game/tileSnow_fish2.png")
          .add("/assets/game/tileSnow_fish3.png")
          .add("/assets/game/tileWater_fish1.png")
          .add("/assets/game/tileWater_fish2.png")
          .add("/assets/game/tileWater_fish3.png")
          .add("/assets/penguin.png")
          .add("/assets/water.png")
          // The `load` method loads the queue of resources, and calls the passed in callback called once all
          // resources have loaded.
          .load((loader: any, resources: any) => {
            console.log(loader);
            this.setupPixiJs();
          });
        // throughout the process multiple signals can be dispatched.
        loader.onStart.add(this.handleLoadStart);
        loader.onProgress.add(this.handleLoadProgress); // called once per loaded/errored file
        loader.onError.add(this.handleLoadError); // called once per errored file
        loader.onLoad.add(this.handleLoadAsset); // called once per loaded file
        loader.onComplete.add(this.handleLoadComplete); // called once when the queued resources all load.
      } else {
        this.setupPixiJs();
      }
      // console.log(utils.TextureCache);
    });

    // pixiApp.renderer.backgroundColor = 0x061639; //useless if transparent is true
    // pixiApp.renderer.view.style.position = "absolute";
    pixiApp.renderer.view.style.display = "block";
    pixiApp.renderer.autoDensity = true;

    // Add the view to the DOM
    // document.body.appendChild(app.view);
    this.elementRef.nativeElement.appendChild(pixiApp.view);
  }

  ngOnDestroy(): void {
    console.log("Game destroyed");
    // loader.destroy();
  }

  setupPixiJs(): void {
    console.log("All files loaded -> Setup pixi.js");

    this.board = new Board(pixiApp, HEXAGONALS_NUMBER, PENGUINS_NUMBER);

    pixiApp.stage.width = this.board.mapWidth * this.board.hexWidth;
    pixiApp.stage.height = this.board.mapHeight * this.board.hexHeight;
    // width: this.board.mapWidth * this.board.hexWidth, // this.platform.width(),         // window.innerWidth, default: 800
    // height: this.board.mapHeight * this.board.hexHeight,// this.platform.height(),        // window.innerHeight default: 600

    this.board.generateRandomMap();

    setBlurFilter(true);

    // // console.log("Ordre du tableau : ");
    // // for(var r = 0; r < board.cells.length ; r+=1) {
    // //     for(var c = 0 ; c < board.cells[r].length ; c+=1) {
    // //         console.log("Cell : (" + board.cells[r][c].row + "," + board.cells[r][c].column + ")");
    // //     }
    // // }

    // board.pixiApp.ticker.add(animate);

    // this.penguin = new Penguin(this.board, loader, board.cells[2][2]);
    // // penguin2 = new Penguin(board, loader, board.cells[5][5]);

    // pixiApp.stage.addChild(penguin.sprite);
    // // board.pixiApp.stage.addChild(penguin2.sprite);
  }

  handleLoadStart(): void {
    console.log("load start");
  }
  handleLoadProgress(loader: any, resource: any): void {
    console.log(loader.progress + "% loaded");
  }
  handleLoadAsset(loader: any, resource: any): void {
    console.log("asset loaded " + resource.name);
  }
  handleLoadError(): void {
    console.error("load error");
  }
  handleLoadComplete(): void {
    console.log("Load completed");
  }

}
