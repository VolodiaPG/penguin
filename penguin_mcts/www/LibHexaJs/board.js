/**
 * 
 */

 export class Board {
     constructor() {
        this.mapWidth = 8;
        this.mapHeight = 8;
        
        this.textures = [];
        this.hexes = new PIXI.Graphics();
        this.container = new PIXI.Container();
        this.pixiStage = null;
        this.pixiApp = new PIXI.Application({
            width: 800,         // default: 800
            height: 600,        // default: 600
            antialias: true,    // default: false
            transparent: false, // default: false
            resolution: 1,      // default: 1
            resizeTo: Window
        });

        this.pixiApp.renderer.backgroundColor = 0x061639;
        this.pixiApp.renderer.view.style.position = "absolute";
        this.pixiApp.renderer.view.style.display = "block";
        this.pixiApp.renderer.autoResize = true;
        this.pixiApp.renderer.resize(window.innerWidth, window.innerHeight);

        this.cells = [];
        this.cellHighlighter = null;
        this.inCellCount = 0;
        this.hexAxis = { x: 0, y: 0 };
        this.hexDrawAxis = { x: 0, y: 0 };
        this.aspectRatio = 1;
     }
 }