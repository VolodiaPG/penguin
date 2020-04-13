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

    this.boardWidth = (nbHexagonal + 1) * 90;
    this.boardHeight = nbHexagonal * 90;
    this.initPixiApp();
    this.initLoader();
  }

  /***************************************************************************************************************************
  ************************************************ INITIALIZATION ************************************************************
  ***************************************************************************************************************************/
  initPixiApp() {
    this.pixiApp = new Application({
      width: this.boardWidth,   // this.platform.width(),         // window.innerWidth, default: 800
      height: this.boardHeight, //this.platform.height(),        // window.innerHeight default: 600
      antialias: true,          // default: false
      transparent: true,        // default: false
      resolution: 1,            // default: 1
    });

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

    this.board = new Board(this.pixiApp, this.nbHexagonal, this.nbPenguin);

    this.pixiApp.renderer.view.width = this.board.mapWidth * this.board.hexWidth;
    this.pixiApp.renderer.view.height = this.board.mapHeight * this.board.hexHeight;
    this.pixiApp.renderer.view.style.width = this.boardWidth.toString() + 'px';
    this.pixiApp.renderer.view.style.height = this.boardHeight.toString() + 'px';

    this.board.generatePreviewMap();
    this.board.generatePreviewPenguin();

    this.pixiApp.resize();

    // this.pixiApp.ticker.add(animate);
  }

  startWasmGame(): void {
    this.game = new Module.PenguinGame(this.nbHexagonal, this.nbPenguin);
    this.board.generateMapFrom(this.game.getBoard());
    this.board.penguinPlayers = this.game.getBoard().getPlayersOnBoard();
  }

  /***************************************************************************************************************************
  ************************************************ PREVIEW *******************************************************************
  ***************************************************************************************************************************/

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
    this.boardWidth = (this.nbHexagonal + 1) * 90;
    this.boardHeight = this.nbHexagonal * 90;
    this.pixiApp.renderer.view.width = this.boardWidth;
    this.pixiApp.renderer.view.height = this.boardHeight;
    this.pixiApp.renderer.view.style.width = this.boardWidth.toString() + 'px';
    this.pixiApp.renderer.view.style.height = this.boardHeight.toString() + 'px';

    this.pixiApp.resize();
  }
}

/***************************************************************************************************************************
************************************************ LOADER FUNCTION ***********************************************************
***************************************************************************************************************************/

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