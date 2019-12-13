/**
 * 
 */

 export class Board {
     constructor() {
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

        // The map's number of cells across (cell column count).
        this.mapWidth = 8;
        // The map's number of cells high (cell row count).
        this.mapHeight = 8;
        // The map's number of cells high (cell row count).
        this.mapHeight = 10;
        // The radius of the hex. Ignored if hexWidth and hexHeight are set to non-null.
        this.hexSize = 40;
        this.drawHexSize = 40;
        // The pixel width of a hex.
        this.hexWidth = 65;
        // The pixel height of a hex.
        this.hexHeight = 65;
        // The color to use when drawing hex outlines.
        this.hexLineColor = 0xd0d0d0;
        // The width in pixels of the hex outline.
        this.hexLineWidth = 2;
        // Callback function (cell) that handles a hex being clicked on or tapped.
        this.onHexClick = null;
        this.onHexHover = null;
        this.dontBlurryImages = false;
        this.sizeBasedOnTexture = false;
        this.offsetX = 0;
        this.offsetY = 0;

        // Specify the types of terrain available on the map. Map cells reference these terrain
        // types by index. Add custom properties to extend functionality.
        this.terrainTypes = [
            { name: "empty", color: 0xffffff, isEmpty: true },
            { name: "selected", tileIndex: 0, color: 0x808080 },
            { name: "snow", tileIndex: 1, color: 0xe2e2fa }
        ];
        // Array of strings that specify the url of a texture. Can be referenced by index in terrainType.
        this.textures = [
            "images/game/tileWater_full.png",
            "images/game/tileSnow.png",
        ];

        // This is the pixel height specifying an area of overlap for hex cells. Necessary when
        // working with isometric view art systems.
        this.hexBottomPad = 24;    

        this.cells = [];
        this.cellHighlighter = null;
        this.inCellCount = 0;
        this.hexAxis = { x: 0, y: 0 };
        this.hexDrawAxis = { x: 0, y: 0 };
        this.aspectRatio = 1;
     }
 }