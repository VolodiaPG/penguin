//https://github.com/kittykatattack/learningPixi#introduction

let type = "WebGL"
if(!PIXI.utils.isWebGLSupported()){
  type = "canvas"
}

PIXI.utils.sayHello(type);


//Create a Pixi Application
var app = new PIXI.Application({ 
  width: 800,         // default: 800
  height: 600,        // default: 600
  antialias: true,    // default: false
  transparent: false, // default: false
  resolution: 1,      // default: 1
  resizeTo: Window
}
);

app.renderer.backgroundColor = 0x061639;
app.renderer.view.style.position = "absolute";
app.renderer.view.style.display = "block";
app.renderer.autoResize = true;
app.renderer.resize(window.innerWidth, window.innerHeight);

//Add the canvas that Pixi automatically created for you to the HTML document
document.body.appendChild(app.view);

//load an image and run the `setup` function when it's done
PIXI.loader
  .add("images/mini_penguin.png")
  .on("progress", loadProgressHandler)
  .load(setup);

function loadProgressHandler(loader, resource) {
  //Display the file `url` currently being loaded
  console.log("loading: " + resource.url); 

  //Display the percentage of files currently loaded
  console.log("progress: " + loader.progress + "%"); 
}

var followOn;

var penguin, penguin2;

//This `setup` function will run when the image has loaded
function setup() {
  console.log("All files loaded");
  //Create the penguin sprite
  penguin = new PIXI.Sprite(PIXI.loader.resources["images/mini_penguin.png"].texture);
      penguin.scale.set(0.2, 0.2);
      penguin.position.set(300, 200);
      penguin.vx = 0;
      penguin.vy = 0;
      
      penguin.interactive = true;
      penguin.mousedown = initFollow;
      penguin.mouseup = stopFollow;
      penguin.mousemove = follow;
  //Add the penguin to the stage
  app.stage.addChild(penguin);
}

function initFollow() {
  followOn = true;
}
function stopFollow() {
  followOn = false;
}
function follow(mouseData) {
  if(followOn) {
    penguin.x += mouseData.data.originalEvent.movementX;
    penguin.y += mouseData.data.originalEvent.movementY;
  }
}


function gameLoop(){
    requestAnimationFrame(gameLoop);
    // app.renderer.render(stage);
  }

gameLoop();



var CoordinateSystems = [
    { name: "odd-q", isFlatTop: true, isOdd: true },
    { name: "even-q", isFlatTop: true, isOdd: false },
    { name: "odd-r", isFlatTop: false, isOdd: true },
    { name: "even-r", isFlatTop: false, isOdd: false }];

var defaultOptions = {
    // The HexPixi.CoordinateSystems index to use for the map.
    coordinateSystem: 1,
    // The map's number of cells across (cell column count).
    mapWidth: 10,
    // The map's number of cells high (cell row count).
    mapHeight: 10,
    // The radius of the hex. Ignored if hexWidth and hexHeight are set to non-null.
    hexSize: 40,
    drawHexSize: 40,
    // The pixel width of a hex.
    hexWidth: null,
    // The pixel height of a hex.
    hexHeight: null,
    // The color to use when drawing hex outlines.
    hexLineColor: 0x909090,
    // The width in pixels of the hex outline.
    hexLineWidth: 2,
    // If true then the hex's coordinates will be visible on the hex.
    showCoordinates: false,
    // Callback function (cell) that handles a hex being clicked on or tapped.
    onHexClick: null,
    onHexHover: null,
    dontBlurryImages: false,
    sizeBasedOnTexture: false,
    offsetX: 0,
    offsetY: 0,
    // Specify the types of terrain available on the map. Map cells reference these terrain
    // types by index. Add custom properties to extend functionality.
    terrainTypes: [{ name: "empty", color: 0xffffff, isEmpty: true }],
    // Array of strings that specify the url of a texture. Can be referenced by index in terrainType.
    textures: [],
    // This is the pixel height specifying an area of overlap for hex cells. Necessary when
    // working with isometric view art systems.
    hexBottomPad: 0,
    onAssetsLoaded: function(){}
};

// Scene graph heirarchy = pixiState -> container -> hexes
function Map (pixiStage, options) {

    this.textures = [];
    this.hexes = new PIXI.Graphics();
    this.container = new PIXI.DisplayObjectContainer();
    this.pixiStage = null;
    this.options = null;
    this.cells = [];
    this.cellHighlighter = null;
    this.inCellCount = 0;
    this.hexAxis = { x: 0, y: 0 };
    this.hexDrawAxis = { x: 0, y: 0 };
    this.aspectRatio = 1;


    this.init(pixiStage, options);
}

Map.prototype.setCellTerrainType = function (cell, terrainIndex) {
    cell.terrainIndex = terrainIndex;
    this.createSceneGraph();
};

// Creates a hex shaped polygon that is used for the hex's hit area.
Map.prototype.createHexPoly = function (hexAxis) {
    var i = 0,
        cs = CoordinateSystems[this.options.coordinateSystem],
        offset = cs.isFlatTop ? 0 : 0.5,
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
Map.prototype.createDrawHex_internal = function (cell, hasOutline, hasFill) {
    var graphics = new PIXI.Graphics(),
        i = 0,
        cs = CoordinateSystems[this.options.coordinateSystem],
        color = this.options.terrainTypes[cell.terrainIndex].color ? this.options.terrainTypes[cell.terrainIndex].color : 0xffffff;

    if (cell.poly === null) {
        console.log("Cell's poly must first be defined by calling createHexPoly");
        return null;
    }

    if (hasOutline === false) {
        // If this is for masking then we don't need the line itself. Just the poly filled.
        graphics.lineStyle(0, 0, 1);
    } else {
        graphics.lineStyle(this.options.hexLineWidth, this.options.hexLineColor, 1);
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
// and then wraps them in a PIXI.DisplayObjectContainer.
Map.prototype.createDrawnHex = function (cell) {
    var parentContainer = new PIXI.DisplayObjectContainer();

    cell.inner = this.createDrawHex_internal(cell, false, true);
    parentContainer.addChild(cell.inner);

    if (this.options.hexLineWidth > 0) {
        cell.outline = this.createDrawHex_internal(cell, true, false);
        parentContainer.addChild(cell.outline);
    }

    parentContainer.position.x = cell.center.x;
    parentContainer.position.y = cell.center.y;

    return parentContainer;
};

// Use for creating a hex cell with a textured background. First creates a PIXI.Graphics of the hex shape.
// Next creates a PIXI.Sprite and uses the PIXI.Graphics hex as a mask. Masked PIXI.Sprite is added to parent
// PIXI.DisplayObjectContainer. Hex outline (if there is one) is created and added to parent container.
// Parent container is returned.
Map.prototype.createTexturedHex = function (cell) {
    var sprite = new PIXI.Sprite(this.textures[this.options.terrainTypes[cell.terrainIndex].textureIndex]);
    var cs = CoordinateSystems[this.options.coordinateSystem];
    var parentContainer = new PIXI.DisplayObjectContainer();

    sprite.anchor.x = 0.5;
    sprite.anchor.y = 0.5;
    if(!this.options.sizeBasedOnTexture){
        sprite.width = this.options.hexWidth;
        sprite.height = this.options.hexHeight;
    }
    parentContainer.addChild(sprite);

    cell.inner = sprite;

    if (this.options.hexLineWidth > 0) {
        cell.outline = this.createDrawHex_internal(cell, true, false);
        parentContainer.addChild(cell.outline);
    }

    parentContainer.position.x = cell.center.x;
    parentContainer.position.y = cell.center.y;

    return parentContainer;
};

// Use for creating a hex cell with a textured background that stands on it's own. The hex outline will
// bee added if options.hexLineWidth is greater than 0. Parent container is returned.
Map.prototype.createTileHex = function (cell) {
    var sprite = new PIXI.Sprite(this.textures[this.options.terrainTypes[cell.terrainIndex].tileIndex]),
        cs = CoordinateSystems[this.options.coordinateSystem],
        parentContainer = new PIXI.DisplayObjectContainer(),
        mask = null,
        topPercent = 0.5;

    sprite.width = this.options.hexWidth;
    sprite.height = this.options.hexHeight + this.options.hexBottomPad;

    topPercent = this.options.hexHeight / sprite.height;
    sprite.anchor.x = 0.5;
    sprite.anchor.y = topPercent / 2;

    parentContainer.addChild(sprite);

    cell.inner = sprite;

    if (this.options.hexLineWidth > 0) {
        cell.outline = this.createDrawHex_internal(cell, true, false);
        parentContainer.addChild(cell.outline);
    }

    parentContainer.position.x = cell.center.x;
    parentContainer.position.y = cell.center.y;

    return parentContainer;
};

Map.prototype.createEmptyHex = function (cell) {
    var parentContainer = new PIXI.DisplayObjectContainer();

    cell.inner = null;

    if (this.options.hexLineWidth > 0) {
        cell.outline = this.createDrawHex_internal(cell, true, false);
        parentContainer.addChild(cell.outline);
    }

    parentContainer.position.x = cell.center.x;
    parentContainer.position.y = cell.center.y;

    return parentContainer;
};

// Calculates and returns the width of a hex cell.
Map.prototype.getHexWidth = function () {
    var result = null,
        cs = CoordinateSystems[this.options.coordinateSystem];
    result = this.options.hexSize * 2;
    if (cs.isFlatTop === false) {
        result = Math.sqrt(3) / 2 * result;
    }

    return result;
};

// Calculates and returns the height of a hex cell.
Map.prototype.getHexHeight = function () {
    var result = null,
        cs = CoordinateSystems[this.options.coordinateSystem];
    result = this.options.hexSize * 2;
    if (cs.isFlatTop === true) {
        result = Math.sqrt(3) / 2 * result;
    }

    return result;
};

// Calculate the center of a cell based on column, row and coordinate system.
Map.prototype.getCellCenter = function (column, row, coordinateSystem) {
    var incX = 0.75 * this.options.hexWidth,
        incY = this.options.hexHeight,
        cs = CoordinateSystems[coordinateSystem],
        center = { x: 0, y: 0 },
        offset = (cs.isOdd) ? 0 : 1;

    if (cs.isFlatTop) {
        center.x = (column * incX) + (this.options.hexWidth / 2);
        if ((column + offset) % 2) {
            // even
            center.y = (row * incY) + (incY / 2);
        } else {
            // odd
            center.y = (row * incY) + incY;
        }
    } else {
        incX = this.options.hexWidth;
        incY = (0.75 * this.options.hexHeight);
        center.y = (row * incY) + (this.options.hexHeight / 2);
        offset = (cs.isOdd) ? 1 : 0;
        if ((row + offset) % 2) {
            // even
            center.x = (column * incX) + (this.options.hexWidth / 2);
        } else {
            // odd
            center.x = (column * incX) + this.options.hexWidth;
        }
    }

    //center.y -= this.options.hexBottomPad;
    center.x += this.options.offsetX;
    center.y += this.options.offsetY;

    return center;
};

// Takes a cell and creates all the graphics to display it.
Map.prototype.createCell = function(cell) {
    cell.center = this.getCellCenter(cell.column, cell.row, this.options.coordinateSystem);

    // Generate poly first then use poly to draw hex and create masks and all that.
    cell.poly = this.createHexPoly(this.hexDrawAxis);
    cell.hitPoly = this.createHexPoly(this.hexAxis);

    // Create the hex or textured hex
    var hex = null;
    var terrain = this.options.terrainTypes[cell.terrainIndex];

    if (typeof terrain.isEmpty !== 'undefined' && terrain.isEmpty === true) {

        hex = this.createEmptyHex(cell);

    } else if (terrain.textureIndex >= 0) {

        hex = this.createTexturedHex(cell);

    } else if (terrain.tileIndex >= 0) {

        hex = this.createTileHex(cell);

    } else {
        hex = this.createDrawnHex(cell);

    }

    // Text is a child of the display object container containing the hex.
    if (this.options.showCoordinates) {
        cell.text = new PIXI.Text("1", { font: "10px Arial", fill: "black", dropShadow: "true", dropShadowDistance: 1, dropShadowColor: "white" });
        cell.text.setText(
            (3-(cell.row - (-cell.column - (-cell.column & 1)) / 2)).toString() +
            ", " +
            (cell.column).toString()
        );
        cell.text.position.x = -Math.round((cell.text.width / 2));
        cell.text.position.y = 8 - Math.round(this.options.hexHeight / 2);
        hex.addChild(cell.text);
    }

    if(this.options.dontBlurryImages){
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
************************************* INTERACTIVE CELL *************************************************************************
***************************************************************************************************************************/

// A wrapper for createCell that adds interactivity to the individual cells.
Map.prototype.createInteractiveCell = function (_cell) {
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

        if (cell && _this.options.onHexHover) {
            _this.options.onHexHover(_this, cell);
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
        if (cell && _this.options.onHexOut) {
            _this.options.onHexOut(_this, cell);
        }
    };

    hex.click = function (data) {
        var cell = getEventCell(data);
        if (cell && _this.options.onHexClick) {
            _this.options.onHexClick(_this, data.target.p_cell);
        }
    };

    hex.tap = function (data) {
        var cell = getEventCell(data);
        if (cell && _this.options.onHexClick) {
            _this.options.onHexClick(_this, data.target.p_cell);
        }
    };

    return hex;
};

function getEventCell (event) {
    if(typeof event.target.p_cell !== 'undefined' && event.target.p_cell instanceof Cell)
        return event.target.p_cell;
    else
        return false;
}

/***************************************************************************************************************************
************************************* MAP/TEXTURES *************************************************************************
***************************************************************************************************************************/

// Loads all the textures specified in options.
Map.prototype.loadTextures = function() {
    this.textures = [];

    var texturesStrings = [];
    var i;

    for (i = 0; i < this.options.textures.length; i++) {
        if(typeof this.options.textures[i] === 'string' || this.options.textures[i] instanceof String ){
            texturesStrings.push(this.options.textures[i]);
        }
    }

    for (i = 0; i < this.options.textures.length; i++) {
        if(this.options.textures[i] instanceof HTMLCanvasElement){
            this.textures.push(new PIXI.Texture.fromCanvas(this.options.textures[i]));
        }else if(typeof this.options.textures[i] === 'string' || this.options.textures[i] instanceof String){
            this.textures.push(new PIXI.Texture.fromImage(this.options.textures[i]));
        }else if(typeof this.options.textures[i]._uvs !== 'undefined'){
            this.textures.push(this.options.textures[i]);
        }else{
            console.log('Error in texture loading! Format not compatible.');
        }
    }

    if (texturesStrings.length > 0) {
        // create a new loader
        var loader = new PIXI.AssetLoader(texturesStrings, true);

        // use callback
        loader.onComplete = this.options.onAssetsLoaded;

        //begin load
        loader.load();

    } else {
        // No assets to load so just call onAssetsLoaded function to notify game that we are done.
        if(this.options.onAssetsLoaded)
            this.options.onAssetsLoaded();
    }
};

// Clears out all objects from this.hexes.children.
Map.prototype.clearHexes = function () {
    while (this.hexes.children.length) {
        this.hexes.removeChild(this.hexes.children[0]);
    }
};

// Resets the entire map without destroying the HexPixi.Map instance.
Map.prototype.reset = function (options) {
    while (this.cells.length > 0) {
        while (this.cells[0].length > 0) {
            this.cells[0].splice(0, 1);
        }
        this.cells.splice(0, 1);
    }

    this.clearHexes();

    while (this.container.children.length > 0) {
        this.container.removeChildAt(0);
    }

    this.pixiStage.removeChild(this.container);

    if (this.cellHighlighter) {
        this.cellHighlighter = null;
    }

    this.init(this.pixiStage, options);
};

// Clears the scene graph and recreates it from this.cells.
Map.prototype.createSceneGraph = function() {
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

Map.prototype.generateMap = function (index) {
    var column, cell;
    for (var row = 0; row < this.options.mapHeight; row++) {
        this.cells.push([]);
        if((row % 2) == 0) {
            for (column = 0; column < this.options.mapWidth - 1 ; column += 1) {
                cell = new Cell(row, column, index, null);
                this.cells[cell.row].push(cell);
            }

        } else {
            for (column = 0; column < this.options.mapWidth ; column += 1) {
                cell = new Cell(row, column, index, null);
                this.cells[cell.row].push(cell);
            }
        }
    }
    this.createSceneGraph();
};


Map.prototype.changeCellTerrainIndex = function(cell, terrainIndex) {

    cell.terrainIndex = terrainIndex;

    var textureIndex = this.options.terrainTypes[cell.terrainIndex].textureIndex;
    var texure = this.textures[textureIndex];

    cell.inner.setTexture(texure);
};

/***************************************************************************************************************************
************************************* CONSTRUCTOR *************************************************************************
***************************************************************************************************************************/

Map.prototype.init = function(pixiStage, options) {
    this.options = extend(defaultOptions, options);

    // If we are overiding the top-down view method then need to force some settings
    if (this.options.hexWidth && this.options.hexHeight) {
        var cs = CoordinateSystems[this.options.coordinateSystem];
        this.options.hexSize = this.options.hexWidth / 2;
        this.aspectRatio = this.options.hexHeight / this.options.hexWidth;
        this.hexDrawAxis.x = this.hexAxis.x = cs.isFlatTop ? this.options.hexWidth : ((1 - (Math.sqrt(3) / 2)) * this.options.hexWidth) + this.options.hexWidth;
        this.hexDrawAxis.y = this.hexAxis.y = cs.isFlatTop ? ((1 - (Math.sqrt(3) / 2)) * this.options.hexHeight) + this.options.hexHeight : this.options.hexHeight;
    } else {
        this.aspectRatio = 1;
        this.options.hexWidth = this.getHexWidth();
        this.options.hexHeight = this.getHexHeight();
        this.hexAxis.x = this.options.hexSize * 2;
        this.hexAxis.y = this.options.hexSize * 2;
        this.hexDrawAxis.x = this.options.drawHexSize * 2;
        this.hexDrawAxis.y = this.options.drawHexSize * 2;
    }

    if (this.pixiStage === null) {
        this.pixiStage = pixiStage;
    }

    this.container.addChild(this.hexes);
    this.pixiStage.addChild(this.container);
    this.hexes.clear();
    this.loadTextures();

    if(this.options.hexLineWidth){
        // Setup cell hilighter
        var cell = new Cell(0, 0, 0);

        cell.poly = this.createHexPoly(this.hexDrawAxis);
        var chg = this.createDrawHex_internal(cell, true, false);
        if (chg) {
            updateLineStyle.call(chg, 3, 0xff5521);
            this.cellHighlighter = new PIXI.DisplayObjectContainer();
            this.cellHighlighter.addChild(chg);
        } else {
            console.log("Error creating cell hilighter");
        }
    }
};


/***************************************************************************************************************************
************************************* PIXI HELPERS *************************************************************************
***************************************************************************************************************************/
function updateLineStyle(lineWidth, color, alpha) {
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

function updateFillColor(fillColor, alpha) {
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



