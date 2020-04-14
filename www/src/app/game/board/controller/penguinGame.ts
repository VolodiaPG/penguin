import { Application, Loader, Sprite, utils, Graphics, filters } from 'pixi.js';

import { Board } from '../model/board';
import { Penguin } from '../model/penguin';
import { ViewChild } from '@angular/core';

declare var Module: any;

let loader: any = Loader.shared;

export class PenguinGame {
  pixiApp: Application;
  board: Board;

  idHumanPlayer: number = 1;

  game: any;

  nbPenguin: number;
  nbHexagonal: number;

  penguinsAllies: Array<Penguin>;
  penguinsEnemis: Array<Penguin>;


  constructor(nbHexagonal: number, nbPenguin: number) {
    this.nbHexagonal = nbHexagonal;
    this.nbPenguin = nbPenguin;

    this.initPixiApp();
    this.initLoader();
  }

  /***************************************************************************************************************************
  ************************************************ INIT PIXIJS ************************************************************
  ***************************************************************************************************************************/
  initPixiApp() {
    this.pixiApp = new Application({
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

    this.board = new Board(this.pixiApp, this.nbHexagonal);

    this.board.generatePreviewMap();
    this.generatePreviewPenguin();

    // this.pixiApp.ticker.add(animate);
  }

  startWasmGame(): void {
    this.game = new Module.PenguinGame(this.nbHexagonal, this.nbPenguin);
    this.board.generateMapFrom(this.game.getBoard());
  }

  /***************************************************************************************************************************
  ************************************************ PREVIEW *******************************************************************
  ***************************************************************************************************************************/

  addHexagonal(): void {
    this.nbHexagonal++;
    this.board.addHexagonal();
  }

  removeHexagonal(): void {
    this.nbHexagonal--;
    this.board.removeHexagonal();
  }

  generatePreviewPenguin() {
    this.penguinsAllies = new Array<Penguin>(this.nbPenguin);
    this.penguinsEnemis = new Array<Penguin>(this.nbPenguin);

    for (let pg = 0; pg < this.nbPenguin; pg++) {
        this.penguinsAllies[pg] = new Penguin(this.board.cells[this.nbHexagonal + pg].getCellCenter(), true);
        this.penguinsEnemis[pg] = new Penguin(this.board.cells[3 * this.nbHexagonal + pg].getCellCenter(), false);

        this.pixiApp.stage.addChild(this.penguinsAllies[pg].sprite);
        this.pixiApp.stage.addChild(this.penguinsEnemis[pg].sprite);
    }
}

  addPenguin(): void {
    this.penguinsAllies.push(new Penguin(this.board.cells[this.nbHexagonal + this.nbPenguin].getCellCenter(), true));
    this.pixiApp.stage.addChild(this.penguinsAllies[this.nbPenguin].sprite);

    this.penguinsEnemis.push(new Penguin(this.board.cells[3 * this.nbHexagonal + this.nbPenguin].getCellCenter(), false));
    this.pixiApp.stage.addChild(this.penguinsEnemis[this.nbPenguin].sprite);

    this.nbPenguin++;
  }

  removePenguin(): void {
    this.nbPenguin--;
    this.pixiApp.stage.removeChild(this.penguinsAllies[this.nbPenguin].sprite);
    this.penguinsAllies.pop();

    this.pixiApp.stage.removeChild(this.penguinsEnemis[this.nbPenguin].sprite);
    this.penguinsEnemis.pop();
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