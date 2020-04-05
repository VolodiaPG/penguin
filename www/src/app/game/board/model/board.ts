import { Application, Loader, Container, Sprite, Graphics, Polygon, Point } from 'pixi.js';

import { Pos } from './pos';
import { Cell } from './cell';
import { TerrainType } from './terrainType';

/**
 * 
 */

//  import { loader } from '../controller/penguinGame';
let loader: any = Loader.shared;

export class Board {
    hexes: Graphics;          // new Graphics()
    pixiApp: Application;        // map

    // The map's number of cells across (cell column count).
    mapWidth: number = 8;       // 8
    // The map's number of cells high (cell row count).
    mapHeight: number = 8;      // 8

    nbPenguin: number = 4;

    // The pixel width of a hex.
    hexWidth: number = 90;       // 90
    // The pixel height of a hex.
    hexHeight: number = 90;      // 90
    // This is the pixel height specifying an area of overlap for hex cells. Necessary when
    // working with isometric view art systems.
    hexBottomPad: number = 33;   // 33 

    // The radius of the hex. Ignored if hexWidth and hexHeight are set to non-null.
    hexSize: number = this.hexWidth / 2;        // hexWidth / 2
    drawHexSize: number = 40;    // 40
    aspectRatio: number = this.hexHeight / this.hexWidth;    // hexHeight / hexWidth


    // The color to use when drawing hex outlines.
    hexLineColor: number = 0xd0d0d0;   // 0xd0d0d0
    hexLineColorSelected: number = 0xff5521;   // 0xff5521

    // The width in pixels of the hex outline.
    hexLineWidth: number = 2;   // 2

    // Specify the types of terrain available on the map. Map cells reference these terrain
    // types by index. Add custom properties to extend functionality.
    terrainTypes: TerrainType[] = [
        { name: "empty", tileIndex: -1, color: 0xffffff, isEmpty: true },
        { name: "fish1", tileIndex: 0, color: 0x808080, isEmpty: false },
        { name: "fish2", tileIndex: 1, color: 0xe2e2fa, isEmpty: false },
        { name: "fish3", tileIndex: 2, color: 0xe2e2fa, isEmpty: false },
        { name: "fish1_Selected", tileIndex: 3, color: 0x808080, isEmpty: false },
        { name: "fish2_Selected", tileIndex: 4, color: 0xe2e2fa, isEmpty: false },
        { name: "fish3_Selected", tileIndex: 5, color: 0xe2e2fa, isEmpty: false },
        { name: "neutral", tileIndex: 6, color: 0xe2e2fa, isEmpty: false }
    ];

    // Array of textures. Can be referenced by index in terrainType.
    textures: string[] = [
        "/assets/game/tileSnow_fish1.png",
        "/assets/game/tileSnow_fish2.png",
        "/assets/game/tileSnow_fish3.png",
        "/assets/game/tileWater_fish1.png",
        "/assets/game/tileWater_fish2.png",
        "/assets/game/tileWater_fish3.png",
        "/assets/game/tileSnow_big.png"
    ];

    cells: Array<Array<Cell>>;
    hexAxis: Pos = { x: 0, y: 0 };
    hexDrawAxis: Pos = { x: ((1 - (Math.sqrt(3) / 2)) * this.hexWidth) + this.hexWidth, y: this.hexHeight };

    constructor(private app: Application, size: number, nbPawn: number) {
        this.pixiApp = app;

        this.mapHeight = size;
        this.mapWidth = size;

        this.nbPenguin = nbPawn;

        this.cells = new Array(this.mapHeight);

        this.hexes = new Graphics();
        this.pixiApp.stage.addChild(this.hexes);
        this.hexes.clear();

        console.log("Board ok");
    }


    /***************************************************************************************************************************
    ************************************* HEXAGON ******************************************************************************
    ***************************************************************************************************************************/

    // Creates a hex shaped polygon that is used for the hex's hit area.
    createHexPoly(hexAxis: Pos) {
        let i: number = 0,
            offset: number = 0.5,
            angle: number = 2 * Math.PI / 6 * offset,
            center: Pos = { x: hexAxis.x / 2, y: hexAxis.y / 2 },
            x: number = center.x * Math.cos(angle),
            y: number = center.y * Math.sin(angle),
            points: Array<Point> = [];

        points.push(new Point(x, y));

        for (i = 1; i < 7; i++) {
            angle = 2 * Math.PI / 6 * (i + offset);
            x = center.x * Math.cos(angle);
            y = center.y * Math.sin(angle);

            points.push(new Point(x, y));
        }

        return new Polygon(points);
    };

    // Creates a drawn hex while ignoring the cell's position. A new Graphics object is created
    // and used to draw and (possibly) fill in the hex. The Graphics is returned to the caller.
    createDrawHex_internal(cell: Cell, color: number, hasOutline: boolean, hasFill: boolean) {
        let graphics: Graphics = new Graphics(),
            i: number = 0;

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

        graphics.moveTo(cell.poly.points[i], cell.poly.points[i + 1]);

        for (i = 2; i < cell.poly.points.length; i += 2) {
            graphics.lineTo(cell.poly.points[i], cell.poly.points[i + 1]);
        }

        if (hasFill !== false) {
            graphics.endFill();
        }

        return graphics;
    };


    // Use for creating a hex cell with a textured background that stands on it's own. The hex outline will
    // bee added if hexLineWidth is greater than 0. Parent container is returned.
    createTileHex(cell: Cell) {
        let sprite: Sprite = new Sprite(loader.resources[this.textures[this.terrainTypes[cell.terrainIndex].tileIndex]].texture),
            parentContainer: Container = new Container(),
            topPercent: number = 0.5;

        sprite.width = this.hexWidth;
        sprite.height = this.hexHeight + this.hexBottomPad;

        topPercent = this.hexHeight / sprite.height;
        sprite.anchor.x = 0.5;
        sprite.anchor.y = topPercent / 2;

        sprite.alpha = cell.alpha;

        sprite.interactive = true;
        sprite.buttonMode = false;
        sprite.hitArea = cell.poly;
        sprite.on('click', () => { cell.onCellClick(this) })
            .on('mouseover', () => { cell.onCellHover(this) })
            .on('mouseout', () => { cell.onCellOut(this) });


        parentContainer.addChild(sprite);

        cell.inner = sprite;

        cell.outline = this.createDrawHex_internal(cell, this.hexLineColor, true, false);

        parentContainer.addChild(cell.outline);

        parentContainer.position.x = cell.center.x;
        parentContainer.position.y = cell.center.y;

        return parentContainer;
    };

    createEmptyHex(cell: Cell) {
        let parentContainer: Container = new Container();

        cell.inner = null;

        if (this.hexLineWidth > 0) {
            cell.outline = this.createDrawHex_internal(cell, 0xffffff, false, false); // Border false
            parentContainer.addChild(cell.outline);
        }

        parentContainer.position.x = cell.center.x;
        parentContainer.position.y = cell.center.y;

        return parentContainer;
    };

    // Calculates and returns the width of a hex cell.
    getHexWidth() {
        let result: number = null;
        result = this.hexSize * 2;
        result = Math.sqrt(3) / 2 * result;

        return result;
    };

    // Calculates and returns the height of a hex cell.
    getHexHeight() {
        let result: number = null;
        result = this.hexSize * 2;

        return result;
    };

    // Calculate the center of a cell based on column, row and coordinate system.
    getCellCenter(column: number, row: number) {
        let incX: number = this.hexWidth,
            incY: number = this.hexHeight,
            center: Pos = { x: 0, y: 0 };
        // incX = 0.75 * this.hexWidth;
        incY = 0.75 * this.hexHeight;

        center.y = (row * incY) + (this.hexHeight / 2);

        if (row % 2) {
            // even
            center.x = (column * incX) + (this.hexWidth / 2);
        } else {
            // odd
            center.x = (column * incX) + this.hexWidth;
        }

        return center;
    };

    // Takes a cell and creates all the graphics to display it.
    createCell(cell: Cell) {
        cell.center = this.getCellCenter(cell.column, cell.row);

        // Generate poly first then use poly to draw hex and create masks and all that.
        cell.poly = this.createHexPoly(this.hexDrawAxis);
        cell.hitPoly = this.createHexPoly(this.hexAxis);

        // Create the hex or textured hex
        let hex: Container = null;
        let terrain: TerrainType = this.terrainTypes[cell.terrainIndex];

        if (typeof terrain.isEmpty !== 'undefined' && terrain.isEmpty === true) {

            hex = this.createEmptyHex(cell);

        } else {

            hex = this.createTileHex(cell);

        }

        // Set a property on the hex that references the cell.
        // hex.p_cell = cell;
        // hex.p_cell.hex = hex;

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
        let column: number, cell: Cell;
        for (var row = 0; row < this.mapHeight; row++) {

            if ((row % 2) == 0) {
                this.cells[row] = new Array(this.mapWidth - 1);
            } else {
                this.cells[row] = new Array(this.mapWidth);
            }

            for (column = 0; column < this.cells[row].length; column++) {
                cell = new Cell(row, column, 7);
                this.cells[row][column] = cell;
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

    setRandomCells() {
        console.log("Set Random Cells");
        let column: number, rnd: number, cell: Cell;
        for (var row = 0; row < this.mapHeight; row++) {
            for (column = 0; column < this.cells[row].length; column++) {
                rnd = Math.floor(1 + (Math.random() * 3));
                this.setCellTerrainType(this.cells[row][column], rnd);
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

    setCellTerrainType(cell: Cell, terrainIndex: number) {
        cell.terrainIndex = terrainIndex;
        this.createSceneGraph();
    }

    setCellSelectedTexture(cell: Cell, select: boolean, alpha: number) {
        if (select && cell.terrainIndex <= 3) {
            cell.terrainIndex += 3;
        } else if (!select && cell.terrainIndex > 3) {
            cell.terrainIndex -= 3;
        } else {

        }

        cell.alpha = alpha;

        this.createSceneGraph();
    }

    setDiagoSelectedTexture(cell: Cell, select: boolean, alpha: number) {
        //diago droite
        var cellX = cell.column - (cell.row + (cell.row & 1)) / 2;

        //ligne
        var cellZ = cell.row;

        //diago gauche
        var cellY = - cellX - cellZ;

        for (var r = 0; r < this.cells.length; r += 1) {
            for (var c = 0; c < this.cells[r].length; c += 1) {
                var tempX = this.cells[r][c].column - (this.cells[r][c].row + (this.cells[r][c].row & 1)) / 2;
                var tempZ = this.cells[r][c].row;
                var tempY = - tempX - tempZ;

                if ((tempX == cellX) || (tempY == cellY) || (tempZ == cellZ)) {
                    this.setCellSelectedTexture(this.cells[r][c], select, alpha); // cell, Selected, alpha
                }

            }
        }

    }

    createSceneGraph() {
        let cell: Cell,
            columnCells: Array<Cell>,
            rowIndex: number = 0,
            colIndex: number = 0;

        this.clearHexes();

        while (rowIndex < this.cells.length) {
            columnCells = this.cells[rowIndex];
            colIndex = 0;
            while (colIndex < columnCells.length) {
                cell = columnCells[colIndex];
                this.hexes.addChild(this.createCell(cell)); // Choice of type of cell
                colIndex++;
            }
            rowIndex++;
        }
    };
}