import {Cell} from './cell.js';

/**
 * 
 */

 export class Board {

/***************************************************************************************************************************
************************************* CONSTRUCTOR *************************************************************************
***************************************************************************************************************************/
     constructor(map, loader) {
        // // Loader for the textures.
        // this.loader = PIXI.Loader.shared;
        // this.loader.add("tileSelected","images/game/tileWater_full.png")
        //     .add("tileNormal","images/game/tileSnow.png")
        //     .on("progress", handleLoadProgress)
        //     .on("load", handleLoadAsset)
        //     .on("error", handleLoadError)
        //     .load(handleLoadComplete);

        this.hexes = new PIXI.Graphics();
        this.pixiApp = map;
        this.pixiLoader = loader;

        this.pixiApp.renderer.backgroundColor = 0x061639;
        this.pixiApp.renderer.view.style.position = "absolute";
        this.pixiApp.renderer.view.style.display = "block";
        this.pixiApp.renderer.autoDensity = true;
        this.pixiApp.renderer.resize(window.innerWidth, window.innerHeight);

        // The map's number of cells across (cell column count).
        this.mapWidth = 8;
        // The map's number of cells high (cell row count).
        this.mapHeight = 8;
        
        // The pixel width of a hex.
        this.hexWidth = 90;
        // The pixel height of a hex.
        this.hexHeight = 90;
        // This is the pixel height specifying an area of overlap for hex cells. Necessary when
        // working with isometric view art systems.
        this.hexBottomPad = 33; 

        // The radius of the hex. Ignored if hexWidth and hexHeight are set to non-null.
        this.hexSize = this.hexWidth / 2;
        this.drawHexSize = 40;
        this.aspectRatio = this.hexHeight / this.hexWidth;


        // The color to use when drawing hex outlines.
        this.hexLineColor = 0xd0d0d0;
        // The width in pixels of the hex outline.
        this.hexLineWidth = 2;
        // Callback function (cell) that handles a hex being clicked on or tapped.

        this.sizeBasedOnTexture = true;
        this.offsetX = 0;
        this.offsetY = 0;

        // Specify the types of terrain available on the map. Map cells reference these terrain
        // types by index. Add custom properties to extend functionality.
        this.terrainTypes = [
            { name: "empty", color: 0xffffff, isEmpty: true },
            { name: "selected", tileIndex: 0, color: 0x808080 },
            { name: "snow", tileIndex: 1, color: 0xe2e2fa }
        ];
        
        // Array of textures. Can be referenced by index in terrainType.
        this.textures = [
            "images/game/tileWater_full.png",
            "images/game/tileSnow.png"
        ];

        this.cells = [];
        this.cellHighlighter = null;
        this.inCellCount = 0;
        this.hexAxis = { x: 0, y: 0 };
        this.hexDrawAxis = { x: ((1 - (Math.sqrt(3) / 2)) * this.hexWidth) + this.hexWidth, y: this.hexHeight };

        this.pixiApp.stage.addChild(this.hexes);
        this.hexes.clear();
    
        if(this.hexLineWidth){
            // Setup cell hilighter
            var cell = new Cell(0, 0, 0, null);
            cell.poly = this.createHexPoly(this.hexDrawAxis);
            this.cellHighlighter = this.createDrawHex_internal(cell, 0xff5521, true, false);
           
        }

        console.log("Board ok");
    }

/***************************************************************************************************************************
************************************* HEXAGON ******************************************************************************
***************************************************************************************************************************/

    // Creates a hex shaped polygon that is used for the hex's hit area.
    createHexPoly (hexAxis) {
        var i = 0,
            offset = 0.5,
            angle = 2 * Math.PI / 6 * offset,
            center = { x: hexAxis.x / 2, y: hexAxis.y / 2 },
            x = center.x * Math.cos(angle),
            y = center.y * Math.sin(angle),
            points = [];

        points.push(new PIXI.Point(x, y));

        for (i = 1; i < 7; i++) {
            angle = 2 * Math.PI / 6 * (i + offset);
            x = center.x * Math.cos(angle);
            y = center.y * Math.sin(angle);

            points.push(new PIXI.Point(x, y));
        }

        return new PIXI.Polygon(points);
    };

    // Creates a drawn hex while ignoring the cell's position. A new PIXI.Graphics object is created
    // and used to draw and (possibly) fill in the hex. The PIXI.Graphics is returned to the caller.
    createDrawHex_internal(cell, color, hasOutline, hasFill) {
        var graphics = new PIXI.Graphics(),
            i = 0;

        if (cell.poly === null) {
            console.log("Cell's poly must first be defined by calling createHexPoly");
            return null;
        }

        if (hasOutline === false) {
            // If this is for masking then we don't need the line itself. Just the poly filled.
            graphics.lineStyle(0, 0, 1);
        } else {
            graphics.lineStyle(this.hexLineWidth, color, 1);
        }

        if (hasFill !== false) {
            graphics.beginFill(color, 1);
        }

        graphics.moveTo(cell.poly.points[i], cell.poly.points[i+1]);

        for (i = 2; i < cell.poly.points.length; i += 2) {
            graphics.lineTo(cell.poly.points[i], cell.poly.points[i+1]);
        }

        if (hasFill !== false) {
            graphics.endFill();
        }

        return graphics;
    };


    // Use for creating a hex cell with a textured background that stands on it's own. The hex outline will
    // bee added if hexLineWidth is greater than 0. Parent container is returned.
    createTileHex (cell) {
        
        var sprite = new PIXI.Sprite(this.pixiLoader.resources[this.textures[this.terrainTypes[cell.terrainIndex].tileIndex]].texture),
            parentContainer = new PIXI.Container(),
            topPercent = 0.5;
        
        sprite.width = this.hexWidth;
        sprite.height = this.hexHeight + this.hexBottomPad;

        topPercent = this.hexHeight / sprite.height;
        sprite.anchor.x = 0.5;
        sprite.anchor.y = topPercent / 2;

        sprite.interactive = true;
        sprite.buttonMode = true;
        sprite.hitArea = cell.poly;
        sprite.on('click', (event) => {cell.onCellClick(this)})
                       .on('pointerover', (event) => {cell.onCellHover(this)})
                       .on('pointerout', (event) => {cell.onCellOut(this)});
                       
                       
        parentContainer.addChild(sprite);

        cell.inner = sprite;

        if (!cell.isOver) {
            cell.outline = this.createDrawHex_internal(cell, 0xffffff, true, false);
        } else {
            cell.outline = this.cellHighlighter;        
        }

        parentContainer.addChild(cell.outline);

        parentContainer.position.x = cell.center.x;
        parentContainer.position.y = cell.center.y;

        return parentContainer;
    };

    createEmptyHex (cell) {
        var parentContainer = new PIXI.Container();

        cell.inner = null;

        if (this.hexLineWidth > 0) {
            cell.outline = this.createDrawHex_internal(cell, 0xffffff, false, false);
            parentContainer.addChild(cell.outline);
        }

        parentContainer.position.x = cell.center.x;
        parentContainer.position.y = cell.center.y;

        return parentContainer;
    };

    // Calculates and returns the width of a hex cell.
    getHexWidth () {
        var result = null;
        result = this.hexSize * 2;
        result = Math.sqrt(3) / 2 * result;

        return result;
    };

    // Calculates and returns the height of a hex cell.
    getHexHeight () {
        var result = null;
        result = this.hexSize * 2;

        return result;
    };

    // Calculate the center of a cell based on column, row and coordinate system.
    getCellCenter (column, row) {
        var incX = 0.75 * this.hexWidth,
            incY = this.hexHeight,
            center = { x: 0, y: 0 },

            incX = this.hexWidth;
            incY = (0.75 * this.hexHeight);
            center.y = (row * incY) + (this.hexHeight / 2);
            if (row % 2) {
                // even
                center.x = (column * incX) + (this.hexWidth / 2);
            } else {
                // odd
                center.x = (column * incX) + this.hexWidth;
            }

        //center.y -= this.hexBottomPad;
        center.x += this.offsetX;
        center.y += this.offsetY;

        return center;
    };

    // Takes a cell and creates all the graphics to display it.
    createCell(cell) {
        cell.center = this.getCellCenter(cell.column, cell.row);

        // Generate poly first then use poly to draw hex and create masks and all that.
        cell.poly = this.createHexPoly(this.hexDrawAxis);
        cell.hitPoly = this.createHexPoly(this.hexAxis);

        // Create the hex or textured hex
        var hex = null;
        var terrain = this.terrainTypes[cell.terrainIndex];

        if (typeof terrain.isEmpty !== 'undefined' && terrain.isEmpty === true) {

            hex = this.createEmptyHex(cell);

        } else {

            hex = this.createTileHex(cell);

        }
            
        // Set a property on the hex that references the cell.
        hex.p_cell = cell;
        hex.p_cell.hex = hex;

        return hex;
    };

/***************************************************************************************************************************
************************************* MAP/TEXTURES *************************************************************************
***************************************************************************************************************************/
    // Clears out all objects from this.hexes.children.
    clearHexes() {
        while (this.hexes.children.length) {
            this.hexes.removeChild(this.hexes.children[0]);
        }
    };

    
    generateMap() {
        console.log("Generate Map");
        var column, cell;
        for (var row = 0; row < this.mapHeight; row++) {
            this.cells.push([]);
            if((row % 2) == 0) {
                for (column = 0; column < this.mapWidth - 1 ; column += 1) {
                    cell = new Cell(row, column, 2, null);
                    this.cells[cell.row].push(cell);
                }

            } else {
                for (column = 0; column < this.mapWidth ; column += 1) {
                    cell = new Cell(row, column, 2, null);
                    this.cells[cell.row].push(cell);
                }
            }
        }

        // console.log("Ordre du tableau : ");
        // for(var r = 0; r < this.cells.length ; r+=1) {
        //     for(var c = 0 ; c < this.cells[r].length ; c+=1) {
        //         console.log("Cell : (" + this.cells[r][c].row + "," + this.cells[r][c].column + ")");
        //     }
        // }

        this.createSceneGraph();
    };

    generateCell(){
        console.log("Generate Cell");
        var cell = new Cell(0, 0, 2, null);

        this.pixiApp.stage.addChild(this.createCell(cell));
        //var t = this.createCell(cell);
    }

    setCellTerrainType(cell, terrainIndex) {
        cell.terrainIndex = terrainIndex;
        this.createSceneGraph();
    }

    createSceneGraph() {
        var cell = null,
            row = null,
            rowIndex = 0,
            colIndex = 0;
    
        this.clearHexes();
        while (rowIndex < this.cells.length) {
            row = this.cells[rowIndex];
            colIndex = 0;
            while (colIndex < row.length) {
                cell = row[colIndex];
                this.hexes.addChild(this.createCell(cell)); // Choice of type of cell
                colIndex++;
            }
            rowIndex++;
        }
    };
 }