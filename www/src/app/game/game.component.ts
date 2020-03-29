import { Component, OnInit, ElementRef, NgZone, ViewChild, AfterViewInit } from '@angular/core';
import { Platform, ToastController } from '@ionic/angular';
import { Application, Loader, Sprite, utils } from 'pixi.js';

import { Board } from './model/board';

@Component({
  selector: 'app-game',
  templateUrl: './game.component.html',
  styleUrls: ['./game.component.scss']
})
export class GameComponent implements AfterViewInit {
  @ViewChild('imageCanvas', { static: false }) canvas: any;
  canvasElement: any;
  public board: Board;
  public loader: any;

  public app: Application;

  // public penguin: Sprite;

  constructor(private elementRef: ElementRef, private ngZone: NgZone) { }

  ngAfterViewInit() {
    // Set the Canvas Element
    this.canvasElement = this.canvas.nativeElement;
  }

  ngOnInit(): void {
    this.ngZone.runOutsideAngular(() => {
      this.app = new Application({
        view: this.canvas,
        width: window.innerWidth,         // default: 800
        height: window.innerHeight,        // default: 600
        antialias: true,    // default: false
        transparent: false, // default: false
        resolution: 1,      // default: 1
        resizeTo: window
      });
      // Loader for the textures.
      this.loader = new Loader();
      this.loader.add("/assets/game/tileSnow_fish1.png")
        .add("/assets/game/tileSnow_fish2.png")
        .add("/assets/game/tileSnow_fish3.png")
        .add("/assets/game/tileWater_fish1.png")
        .add("/assets/game/tileWater_fish2.png")
        .add("/assets/game/tileWater_fish3.png")
        .add("/assets/penguin.png")
        .add("/assets/water.png")
        .on("start", this.handleLoadStart)
        .on("progress", this.handleLoadProgress)
        .on("load", this.handleLoadAsset)
        .on("error", this.handleLoadError)
        .on("complete", this.handleLoadComplete)
        .load(this.setupPixiJs.bind(this));

      // console.log(utils.TextureCache);
    });
    this.app.renderer.backgroundColor = 0x061639;

    this.elementRef.nativeElement.appendChild(this.app.view);
  }

  setupPixiJs(): void {
    console.log("All files loaded -> Setup pixi.js");
    //Create the penguin sprite
    let penguin = new Sprite(this.loader.resources["/assets/penguin.png"].texture);
    penguin.scale.set(0.2);
    penguin.position.set(300, 200);

    //Add the penguin to the stage
    this.app.stage.addChild(penguin);

    // board = new Board(map, loader);

    // board.generateRandomMap();

    // // console.log("Ordre du tableau : ");
    // // for(var r = 0; r < board.cells.length ; r+=1) {
    // //     for(var c = 0 ; c < board.cells[r].length ; c+=1) {
    // //         console.log("Cell : (" + board.cells[r][c].row + "," + board.cells[r][c].column + ")");
    // //     }
    // // }

    // board.pixiApp.ticker.add(animate);

    // this.penguin = new Penguin(this.board, loader, board.cells[2][2]);
    // // penguin2 = new Penguin(board, loader, board.cells[5][5]);

    // this.app.stage.addChild(penguin.sprite);
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

    // this.setupPixiJs();
  }

}
