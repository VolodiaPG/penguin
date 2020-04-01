import { Component, OnInit, ElementRef, NgZone, ViewChild, Renderer, AfterViewInit } from '@angular/core';
import { Platform, ToastController } from '@ionic/angular';
import { Application, Loader, Sprite, utils } from 'pixi.js';

import { Board } from './model/board';
import { Penguin } from './model/penguin';

let loader: any = Loader.shared;

@Component({
  selector: 'app-board',
  templateUrl: './board.component.html',
  styleUrls: ['./board.component.scss']
})
export class BoardComponent implements OnInit { // or AfterViewInit

  // @ViewChild('imageCanvas', { static: false }) canvas: any;
  // canvasElement: any;
  public board: Board;
  public app: Application;

  boardWidth: number = 8 * 90;
  boardHeight: number = 8 * 90;

  constructor(public platform: Platform, private elementRef: ElementRef, private ngZone: NgZone) { }

  // ngAfterViewInit() {
  //   // Set the Canvas Element
  //   // this.canvasElement = this.canvas.nativeElement;

  //   // this.renderer.setElementAttribute(this.canvasElement, 'width', this.platform.width() + '');
  //   // this.renderer.setElementAttribute(this.canvasElement, 'height', this.platform.height() + ''); 
  // }

  ngOnInit(): void {
    this.ngZone.runOutsideAngular(() => {
      this.app = new Application({
        // view: this.canvas,
        width: this.boardWidth,   // this.platform.width(),         // window.innerWidth, default: 800
        height: this.boardHeight, //this.platform.height(),        // window.innerHeight default: 600
        antialias: true,          // default: false
        transparent: true,        // default: false
        resolution: 1,            // default: 1
        // resizeTo: parent
      });

      if (loader.progress === 0) {
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
            // resources is an object where the key is the name of the resource loaded and the value is the resource object.
            // They have a couple default properties:
            // - `url`: The URL that the resource was loaded from
            // - `error`: The error that happened when trying to load (if any)
            // - `data`: The raw data that was loaded
            // also may contain other properties based on the middleware that runs.
            // sprites.bunny = new PIXI.TilingSprite(resources.bunny.texture);
            // sprites.spaceship = new PIXI.TilingSprite(resources.spaceship.texture);
            // sprites.scoreFont = new PIXI.TilingSprite(resources.scoreFont.texture);
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

    this.app.renderer.backgroundColor = 0x061639; //useless if transparent is true
    // this.app.renderer.view.style.position = "absolute";
    this.app.renderer.view.style.display = "block";
    this.app.renderer.autoDensity = true;

    // Add the view to the DOM
    // document.body.appendChild(app.view);
    this.elementRef.nativeElement.appendChild(this.app.view);
  }

  ngOnDestroy(): void {
    console.log("Game destroyed");
    // loader.destroy();
  }

  setupPixiJs(): void {
    console.log("All files loaded -> Setup pixi.js");
    //Create the penguin sprite
    // let penguin = new Sprite(this.loader.resources["/assets/penguin.png"].texture);
    // penguin.scale.set(0.2);
    // penguin.position.set(300, 200);

    // let penguin = new Penguin({ x: 300, y: 200 });
    //Add the penguin to the stage
    // this.app.stage.addChild(penguin.sprite);

    this.board = new Board(this.app);

    this.app.stage.width = this.board.mapWidth * this.board.hexWidth;
    this.app.stage.height = this.board.mapHeight * this.board.hexHeight;
    // width: this.board.mapWidth * this.board.hexWidth, // this.platform.width(),         // window.innerWidth, default: 800
    // height: this.board.mapHeight * this.board.hexHeight,// this.platform.height(),        // window.innerHeight default: 600

    this.board.generateRandomMap();

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

  public getPixiApplication(): Application {
    return this.app;
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
