import { Application, Loader, Sprite, utils, Graphics, filters } from 'pixi.js';

import { Board } from '../model/board';
import { Penguin } from '../model/penguin';
import { ViewChild } from '@angular/core';

declare var Module: any;

let loader: any = Loader.shared;

export class PenguinGame {
  pixiApp: Application;
  board: Board;

  game: any;

  boardWidth: number;
  boardHeight: number;

  nbPenguin: number;
  nbHexagonal: number;

  constructor(nbHexagonal: number, nbPenguin: number) {
    this.nbHexagonal = nbHexagonal;
    this.nbPenguin = nbPenguin;

    this.game = new Module.PenguinGame(this.nbHexagonal, this.nbPenguin);

    this.boardWidth = nbHexagonal * 90;
    this.boardHeight = nbHexagonal * 90;
    this.initPixiApp();
    this.initLoader();
  }

  initPixiApp() {
    this.pixiApp = new Application({
      // view: this.canvas,
      width: this.boardWidth,   // this.platform.width(),         // window.innerWidth, default: 800
      height: this.boardHeight, //this.platform.height(),        // window.innerHeight default: 600
      antialias: true,          // default: false
      transparent: true,        // default: false
      resolution: 1,            // default: 1
    });

    // this.pixiApp.renderer.backgroundColor = 0x061639; //useless if transparent is true
    // this.pixiApp.renderer.view.style.position = "absolute";
    this.pixiApp.renderer.view.style.display = "block";
    this.pixiApp.renderer.autoDensity = true;
    
    this.pixiApp.resizeTo = this.pixiApp.renderer.view;
  }

  initLoader() {
    if (loader.progress === 0) { //already charged
      // Loader for the textures.
      loader.add("/assets/game/tileSnow_big.png")
        .add("/assets/game/tileSnow_fish1.png")
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
      loader.onStart.add(handleLoadStart);
      loader.onProgress.add(handleLoadProgress); // called once per loaded/errored file
      loader.onError.add(handleLoadError); // called once per errored file
      loader.onLoad.add(handleLoadAsset); // called once per loaded file
      loader.onComplete.add(handleLoadComplete); // called once when the queued resources all load.
    } else {
      this.setupPixiJs();
    }
    // console.log(utils.TextureCache);
  }

  setupPixiJs(): void {
    console.log("All files loaded -> Setup pixi.js");

    this.board = new Board(this.pixiApp, this.game.getBoard());

    // this.pixiApp.stage.width = this.board.mapWidth * this.board.hexWidth;
    // this.pixiApp.stage.height = this.board.mapHeight * this.board.hexHeight;
    this.pixiApp.renderer.view.width = this.board.mapWidth * this.board.hexWidth;
    this.pixiApp.renderer.view.height = this.board.mapHeight * this.board.hexHeight;
    this.pixiApp.renderer.view.style.width = this.boardWidth.toString() + 'px';
    this.pixiApp.renderer.view.style.height = this.boardHeight.toString() + 'px';
    // width: this.board.mapWidth * this.board.hexWidth, // this.platform.width(),         // window.innerWidth, default: 800
    // height: this.board.mapHeight * this.board.hexHeight,// this.platform.height(),        // window.innerHeight default: 600

    this.board.generateMap();
    this.board.generatePreviewPenguin();

    this.pixiApp.resize();

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

  addHexagonal(): void {
    this.nbHexagonal++;
    this.updatePixiAppSize();

    this.board.addHexagonal();
  }

  removeHexagonal(): void {
    this.nbHexagonal--;
    this.updatePixiAppSize();

    this.board.removeHexagonal();
  }

  addPenguin(): void {
    this.nbPenguin++;
    this.updatePixiAppSize();

    this.board.addPenguin();
  }

  removePenguin(): void {
    this.nbPenguin--;
    this.updatePixiAppSize();

    this.board.removePenguin();
  }

  updatePixiAppSize(): void {
    this.boardWidth = this.nbHexagonal * 90;
    this.boardHeight = this.nbHexagonal * 90;
    this.pixiApp.renderer.view.width = this.boardWidth;
    this.pixiApp.renderer.view.height = this.boardHeight;
    this.pixiApp.renderer.view.style.width = this.boardWidth.toString() + 'px';
    this.pixiApp.renderer.view.style.height = this.boardHeight.toString() + 'px';

    this.pixiApp.resize();
  }
}

function handleLoadStart(): void {
  console.log("load start");
}
function handleLoadProgress(loader: any, resource: any): void {
  console.log(loader.progress + "% loaded");
}
function handleLoadAsset(loader: any, resource: any): void {
  console.log("asset loaded " + resource.name);
}
function handleLoadError(): void {
  console.error("load error");
}
function handleLoadComplete(): void {
  console.log("Load completed");
}