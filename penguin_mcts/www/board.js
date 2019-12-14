import {Cell} from './cell.js';

/**
 * 
 */

 export class Board {

/***************************************************************************************************************************
************************************* CONSTRUCTOR *************************************************************************
***************************************************************************************************************************/
     constructor() {
        this.hexes = new PIXI.Graphics();
        this.container = new PIXI.Container();
        this.pixiApp = new PIXI.Application({
            width: 800,         // default: 800
            height: 600,        // default: 600
            antialias: true,    // default: false
            transparent: true, // default: false
            resolution: 1,      // default: 1
            resizeTo: Window
        });

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
        // this.onHexClick = onHexClick;
        // this.onHexHover = null;
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

        this.onAssetsLoaded = function(){}


        this.cells = [];
        this.cellHighlighter = null;
        this.inCellCount = 0;
        this.hexAxis = { x: 0, y: 0 };
        this.hexDrawAxis = { x: ((1 - (Math.sqrt(3) / 2)) * this.hexWidth) + this.hexWidth, y: this.hexHeight };
        
        this.container.addChild(this.hexes);
        this.pixiApp.stage.addChild(this.container);
        this.hexes.clear();
        this.loadTextures();
    
        if(this.hexLineWidth){
            // Setup cell hilighter
            var cell = new Cell(0, 0, 0, null);
    
            cell.poly = this.createHexPoly(this.hexDrawAxis);
            var chg = this.createDrawHex_internal(cell, true, false);
            if (chg) {
                //this.updateLineStyle(chg, 3, 0xff5521);
                this.cellHighlighter = new PIXI.Container();
                this.cellHighlighter.addChild(chg);
            } else {
                console.log("Error creating cell hilighter");
            }
        } 
    
    }

/***************************************************************************************************************************
************************************* HEXAGON *************************************************************************
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
    createDrawHex_internal(cell, hasOutline, hasFill) {
        var graphics = new PIXI.Graphics(),
            i = 0,
            color = this.terrainTypes[cell.terrainIndex].color ? this.terrainTypes[cell.terrainIndex].color : 0xffffff;

        if (cell.poly === null) {
            console.log("Cell's poly must first be defined by calling createHexPoly");
            return null;
        }

        if (hasOutline === false) {
            // If this is for masking then we don't need the line itself. Just the poly filled.
            graphics.lineStyle(0, 0, 1);
        } else {
            graphics.lineStyle(this.hexLineWidth, this.hexLineColor, 1);
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

    // Used for manually drawing a hex cell. Creates the filled in hex, creates the outline (if there is one)
    // and then wraps them in a PIXI.Container.
    createDrawnHex (cell) {
        var parentContainer = new PIXI.Container();

        cell.inner = this.createDrawHex_internal(cell, false, true);
        parentContainer.addChild(cell.inner);

        if (this.hexLineWidth > 0) {
            cell.outline = this.createDrawHex_internal(cell, true, false);
            parentContainer.addChild(cell.outline);
        }

        parentContainer.position.x = cell.center.x;
        parentContainer.position.y = cell.center.y;

        return parentContainer;
    };

    // Use for creating a hex cell with a textured background. First creates a PIXI.Graphics of the hex shape.
    // Next creates a PIXI.Sprite and uses the PIXI.Graphics hex as a mask. Masked PIXI.Sprite is added to parent
    // PIXI.Container. Hex outline (if there is one) is created and added to parent container.
    // Parent container is returned.
    createTexturedHex (cell) {
        var sprite = new PIXI.Sprite(this.textures[this.terrainTypes[cell.terrainIndex].textureIndex]);
        var parentContainer = new PIXI.Container();

        sprite.anchor.x = 0.5;
        sprite.anchor.y = 0.5;
        if(!this.sizeBasedOnTexture){
            sprite.width = this.hexWidth;
            sprite.height = this.hexHeight;
        }
        parentContainer.addChild(sprite);

        cell.inner = sprite;

        if (this.hexLineWidth > 0) {
            cell.outline = this.createDrawHex_internal(cell, true, false);
            parentContainer.addChild(cell.outline);
        }

        parentContainer.position.x = cell.center.x;
        parentContainer.position.y = cell.center.y;

        return parentContainer;
    };

    // Use for creating a hex cell with a textured background that stands on it's own. The hex outline will
    // bee added if hexLineWidth is greater than 0. Parent container is returned.
    createTileHex (cell) {
        var sprite = new PIXI.Sprite(this.textures[this.terrainTypes[cell.terrainIndex].tileIndex]),
            parentContainer = new PIXI.Container(),
            mask = null,
            topPercent = 0.5;

        sprite.width = this.hexWidth;
        sprite.height = this.hexHeight + this.hexBottomPad;

        topPercent = this.hexHeight / sprite.height;
        sprite.anchor.x = 0.5;
        sprite.anchor.y = topPercent / 2;

        parentContainer.addChild(sprite);

        cell.inner = sprite;

        if (this.hexLineWidth > 0) {
            cell.outline = this.createDrawHex_internal(cell, true, false);
            parentContainer.addChild(cell.outline);
        }

        parentContainer.position.x = cell.center.x;
        parentContainer.position.y = cell.center.y;

        return parentContainer;
    };

    createEmptyHex (cell) {
        var parentContainer = new PIXI.Container();

        cell.inner = null;

        if (this.hexLineWidth > 0) {
            cell.outline = this.createDrawHex_internal(cell, true, false);
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
        cell.center = this.getCellCenter(cell.column, cell.row, this.coordinateSystem);

        // Generate poly first then use poly to draw hex and create masks and all that.
        cell.poly = this.createHexPoly(this.hexDrawAxis);
        cell.hitPoly = this.createHexPoly(this.hexAxis);

        // Create the hex or textured hex
        var hex = null;
        var terrain = this.terrainTypes[cell.terrainIndex];

        if (typeof terrain.isEmpty !== 'undefined' && terrain.isEmpty === true) {

            hex = this.createEmptyHex(cell);

        } else if (terrain.textureIndex >= 0) {

            hex = this.createTexturedHex(cell);

        } else if (terrain.tileIndex >= 0) {

            hex = this.createTileHex(cell);

        } else {
            hex = this.createDrawnHex(cell);

        }

        if(this.dontBlurryImages){
            hex.position.x = Math.ceil(hex.position.x);
            hex.position.y = Math.ceil(hex.position.y);

            if(Math.round(hex.width) % 2 !== 0 )
                hex.position.x += 0.5;

            if(Math.round(hex.height) % 2 !== 0 )
                hex.position.y += 0.5;
        }

        // Set a property on the hex that references the cell.
        hex.p_cell = cell;
        hex.p_cell.hex = hex;

        return hex;
    };


/***************************************************************************************************************************
************************************* MAP/TEXTURES *************************************************************************
***************************************************************************************************************************/

    // Loads all the textures specified in 
    loadTextures() {
        this.textures = [];

        var texturesStrings = [];
        var i;

        for (i = 0; i < this.textures.length; i++) {
            if(typeof this.textures[i] === 'string' || this.textures[i] instanceof String ){
                texturesStrings.push(this.textures[i]);
            }
        }

        for (i = 0; i < this.textures.length; i++) {
            if(this.textures[i] instanceof HTMLCanvasElement){
                this.textures.push(new PIXI.Texture.fromCanvas(this.textures[i]));
            }else if(typeof this.textures[i] === 'string' || this.textures[i] instanceof String){
                this.textures.push(new PIXI.Texture.fromImage(this.textures[i]));
            }else if(typeof this.textures[i]._uvs !== 'undefined'){
                this.textures.push(this.textures[i]);
            }else{
                console.log('Error in texture loading! Format not compatible.');
            }
        }

        if (texturesStrings.length > 0) {
            // create a new loader
            var loader = new PIXI.AssetLoader(texturesStrings, true);

            // use callback
            loader.onComplete = this.onAssetsLoaded;

            //begin load
            loader.load();

        } else {
            // No assets to load so just call onAssetsLoaded function to notify game that we are done.
            if(this.onAssetsLoaded)
                this.onAssetsLoaded();
        }
    };

    // Clears out all objects from this.hexes.children.
    clearHexes() {
        while (this.hexes.children.length) {
            this.hexes.removeChild(this.hexes.children[0]);
        }
    };

    
    generateMap(index) {
        var column, cell;
        for (var row = 0; row < this.mapHeight; row++) {
            this.cells.push([]);
            if((row % 2) == 0) {
                for (column = 0; column < this.mapWidth - 1 ; column += 1) {
                    cell = new Cell(row, column, index, null);
                    this.cells[cell.row].push(cell);
                }

            } else {
                for (column = 0; column < this.mapWidth ; column += 1) {
                    cell = new Cell(row, column, index, null);
                    this.cells[cell.row].push(cell);
                }
            }
        }
        this.createSceneGraph();
    };

    setCellTerrainType(cell, terrainIndex) {
        cell.terrainIndex = terrainIndex;
        this.createSceneGraph();
    }

    changeCellTerrainIndex(cell, terrainIndex) {

        cell.terrainIndex = terrainIndex;
    
        var textureIndex = this.terrainTypes[cell.terrainIndex].textureIndex;
        var texure = this.textures[textureIndex];
    
        cell.inner.setTexture(texure);
    };

/***************************************************************************************************************************
************************************* INTERACTIVE CELL *************************************************************************
***************************************************************************************************************************/

    // A wrapper for createCell that adds interactivity to the individual cells.
    createInteractiveCell(_cell) {
        var hex = this.createCell(_cell);
        hex.hitArea = _cell.hitPoly;
        hex.interactive = true;
        var _this = this;

        // set the mouseover callback..
        hex.mouseover = function (data) {
            var cell = getEventCell(data);

            if(cell && _this.cellHighlighter){
                _this.cellHighlighter.position.x = cell.center.x;
                _this.cellHighlighter.position.y = cell.center.y;

                if (_this.inCellCount === 0) {
                    _this.hexes.addChild(_this.cellHighlighter);
                }
            }

            if (cell && cell.isOver !== true) {
                cell.isOver = true;
                _this.inCellCount++;
            }

            if (cell && _this.onHexHover) {
                _this.onHexHover(_this, cell);
            }
        };

        // set the mouseout callback..
        hex.mouseout = function (data) {
            var cell = getEventCell(data);
            if (cell && cell.isOver === true) {
                _this.inCellCount--;

                if (_this.inCellCount === 0 && _this.cellHighlighter) {
                    _this.hexes.removeChild(_this.cellHighlighter);
                }

                cell.isOver = false;
            }
            if (cell && _this.onHexOut) {
                _this.onHexOut(_this, cell);
            }
        };

        hex.click = function (data) {
            var cell = getEventCell(data);
            if (cell && _this.onHexClick) {
                _this.onHexClick(_this, data.target.p_cell);
            }
        };

        hex.tap = function (data) {
            var cell = getEventCell(data);
            if (cell && _this.onHexClick) {
                _this.onHexClick(_this, data.target.p_cell);
            }
        };

        return hex;
    };

    getEventCell (event) {
        if(typeof event.target.p_cell !== 'undefined' && event.target.p_cell instanceof Cell)
            return event.target.p_cell;
        else
            return false;
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
                this.hexes.addChild(this.createInteractiveCell(cell));
                colIndex++;
            }
            rowIndex++;
        }
    };
    
/***************************************************************************************************************************
************************************* PIXI HELPERS *************************************************************************
***************************************************************************************************************************/
    updateLineStyle(lineWidth, color, alpha) {
        var len = this.graphicsData.length;
        for (var i = 0; i < len; i++) {
            var data = this.graphicsData[i];
            if (data.lineWidth && lineWidth) {
                data.lineWidth = lineWidth;
            }
            if (data.lineColor && color) {
                data.lineColor = color;
            }
            if (data.alpha && alpha) {
                data.alpha = alpha;
            }
            this.dirty = true;
            this.clearDirty = true;
        }
    };

    updateFillColor(fillColor, alpha) {
        var len = this.graphicsData.length;
        for (var i = 0; i < len; i++) {
            var data = this.graphicsData[i];
            if (data.fillColor && fillColor) {
                data.fillColor = fillColor;
            }
            if (data.alpha && alpha) {
                data.alpha = alpha;
            }
            this.dirty = true;
            this.clearDirty = true;
        }
    };

 }