import { Application, Loader, Sprite, utils, Graphics, filters } from 'pixi.js';

import { Board } from '../model/board';
import { Penguin } from '../model/penguin';
import { ViewChild } from '@angular/core';

declare var Module: any;

let loader: any = Loader.shared;

export class PenguinGame {
  pixiApp: Application;
  board: Board;

  humanPlayerId: number = 1;

  // Wasm objects
  wasmGame: any;
  wasmBoard: any;
  wasmPenguins: any;

  nbPenguin: number;
  nbHexagonal: number;

  // Array to display the penguin preview
  penguinsAllies: Array<Penguin>;
  penguinsEnemis: Array<Penguin>;

  penguins: Array<Penguin>;


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
    this.wasmGame = new Module.PenguinGame(this.nbHexagonal, this.nbPenguin);
    this.wasmBoard = this.wasmGame.getBoard();
    this.board.generateMapFrom(this.wasmBoard);

    this.removePenguinsPreview();
    this.setRandomPenguins();
  }

  setRandomPenguins() {
    console.log("Set Random Penguins Positions");
    let rndPos: number, penguin: Penguin;

    this.wasmPenguins = this.wasmBoard.getPlayersOnBoard();

    this.penguins = Array<Penguin>(this.wasmPenguins.size());

    for (let ii = 0; ii < this.wasmPenguins.size(); ii++) {
      let pawn: any = this.wasmPenguins.get(ii);
      rndPos = Math.floor(0 + Math.random() * (this.nbHexagonal * this.nbHexagonal - 0)); // min + rand() * (max - min + 1)
      this.wasmBoard.performMove(ii, this.board.cells[rndPos].wasmCell);

      this.pixiApp.stage.addChild(new Penguin(this.board.cells[rndPos].getCellCenter(), pawn.getOwner()).sprite);
      console.log("Penguin belows to : " + pawn.getOwner());
    }
  }

  loadPenguinsFromWasm() {
    this.wasmPenguins = this.wasmGame.getPlayersOnBoard();

    // set on the board the penguins
    for (let ii = 0; ii < this.wasmPenguins.size(); ii++) {
        var pawn: any = this.wasmPenguins.get(ii);
        var pawnPos: any = pawn.getStandingOn().getPosition();
        pawnPos = Module.hex_cube_to_offset(Module.hex_axial_to_cube(pawnPos));
        console.log(pawnPos);
        // this.pixiApp.stage.addChild(new Penguin(this.cells[this.mapHeight + this.nbPenguin].getCellCenter(), true).sprite);
    }
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
      this.penguinsAllies[pg] = new Penguin(this.board.cells[this.nbHexagonal + pg].getCellCenter(), this.humanPlayerId);
      this.penguinsEnemis[pg] = new Penguin(this.board.cells[3 * this.nbHexagonal + pg].getCellCenter(), this.humanPlayerId + 1);

      this.pixiApp.stage.addChild(this.penguinsAllies[pg].sprite);
      this.pixiApp.stage.addChild(this.penguinsEnemis[pg].sprite);
    }
  }

  removePenguinsPreview() {
    for (let pg = 0; pg < this.nbPenguin; pg++) {
      this.pixiApp.stage.removeChild(this.penguinsAllies[pg].sprite);
      this.pixiApp.stage.removeChild(this.penguinsEnemis[pg].sprite);
    }
  }

  addPenguin(): void {
    this.penguinsAllies.push(new Penguin(this.board.cells[this.nbHexagonal + this.nbPenguin].getCellCenter(), this.humanPlayerId));
    this.pixiApp.stage.addChild(this.penguinsAllies[this.nbPenguin].sprite);

    this.penguinsEnemis.push(new Penguin(this.board.cells[3 * this.nbHexagonal + this.nbPenguin].getCellCenter(), this.humanPlayerId + 1));
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