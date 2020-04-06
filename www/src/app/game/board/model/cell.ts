import { Application, Container, Loader, Sprite, Graphics, Polygon, Point, filters } from 'pixi.js';

import { Pos } from './pos';
import { Board } from './board';
import { TerrainType } from './terrainType';

let loader: any = Loader.shared;

/**
*
* The cell object represents one map hex cell.
*/

export class Cell {
        row: number;
        column: number;
        center: Pos = { x: 0, y: 0 };

        terrainIndex: number;

        sprite: Sprite;
        parentContainer: Container = new Container();

        topPercent: number = 0.5;

        poly: any;
        hitPoly: any;
        outline: any;
        inner: any;
        hex: any;

        isEmpty: boolean;
        isOver: boolean;
        alpha: number = 1;

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

        hexAxis: Pos = { x: 0, y: 0 };
        hexDrawAxis: Pos = { x: ((1 - (Math.sqrt(3) / 2)) * this.hexWidth) + this.hexWidth, y: this.hexHeight };   

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


        constructor(row: number, column: number, terrainIndex: number) {
                this.row = row;
                this.column = column;
                if (terrainIndex === -1) {
                        this.isEmpty = true;
                } else {
                        this.terrainIndex = terrainIndex ? terrainIndex : 0;
                }

                this.createCell();
        }

        setCellTerrainType(terrainIndex: number) {
                this.terrainIndex = terrainIndex;
                this.createTileHex();
        }

        setCellSelectedTexture(select: boolean, alpha: number) {
                if (select && this.terrainIndex <= 3) {
                        this.terrainIndex += 3;
                } else if (!select && this.terrainIndex > 3) {
                        this.terrainIndex -= 3;
                } else {

                }

                this.alpha = alpha;

                this.createTileHex();
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
        createDrawHex_internal(color: number, hasOutline: boolean, hasFill: boolean) {
                let graphics: Graphics = new Graphics(),
                        i: number = 0;

                if (this.poly === null) {
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

                graphics.moveTo(this.poly.points[i], this.poly.points[i + 1]);

                for (i = 2; i < this.poly.points.length; i += 2) {
                        graphics.lineTo(this.poly.points[i], this.poly.points[i + 1]);
                }

                if (hasFill !== false) {
                        graphics.endFill();
                }

                return graphics;
        };


        // Use for creating a hex cell with a textured background that stands on it's own. The hex outline will
        // bee added if hexLineWidth is greater than 0. Parent container is returned.
        createTileHex():void {
                this.sprite = new Sprite(loader.resources[this.textures[this.terrainTypes[this.terrainIndex].tileIndex]].texture),
                        this.parentContainer,
                        this.topPercent;

                this.sprite.width = this.hexWidth;
                this.sprite.height = this.hexHeight + this.hexBottomPad;

                this.topPercent = this.hexHeight / this.sprite.height;
                this.sprite.anchor.x = 0.5;
                this.sprite.anchor.y = this.topPercent / 2;

                this.sprite.alpha = this.alpha;

                this.sprite.interactive = true;
                this.sprite.buttonMode = false;
                this.sprite.hitArea = this.poly;
                this.sprite.on('click', () => { this.onCellClick() })
                        .on('mouseover', () => { this.onCellHover() })
                        .on('mouseout', () => { this.onCellOut() });


                this.parentContainer.addChild(this.sprite);

                this.inner = this.sprite;

                this.outline = this.createDrawHex_internal(this.hexLineColor, true, false);

                this.parentContainer.addChild(this.outline);

                this.parentContainer.position.x = this.center.x;
                this.parentContainer.position.y = this.center.y;
        };

        createEmptyHex(): void {
                this.inner = null;

                if (this.hexLineWidth > 0) {
                        this.outline = this.createDrawHex_internal(0xffffff, false, false); // Border false
                        this.parentContainer.addChild(this.outline);
                }

                this.parentContainer.position.x = this.center.x;
                this.parentContainer.position.y = this.center.y;
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
        getCellCenter() {
                let incX: number = this.hexWidth,
                        incY: number = this.hexHeight,
                        center: Pos = { x: 0, y: 0 };
                // incX = 0.75 * this.hexWidth;
                incY = 0.75 * this.hexHeight;

                center.y = (this.row * incY) + (this.hexHeight / 2);

                if (this.row % 2) {
                        // even
                        center.x = (this.column * incX) + (this.hexWidth / 2);
                } else {
                        // odd
                        center.x = (this.column * incX) + this.hexWidth;
                }

                return center;
        };

        // Takes a cell and creates all the graphics to display it.
        createCell(): Container {
                this.center = this.getCellCenter();

                // Generate poly first then use poly to draw hex and create masks and all that.
                this.poly = this.createHexPoly(this.hexDrawAxis);
                this.hitPoly = this.createHexPoly(this.hexAxis);

                // Create the hex or textured hex
                let terrain: TerrainType = this.terrainTypes[this.terrainIndex];

                if (typeof terrain.isEmpty !== 'undefined' && terrain.isEmpty === true) {

                        this.createEmptyHex();

                } else {

                        this.createTileHex();

                }

                // Set a property on the hex that references the cell.
                // hex.p_cell = cell;
                // hex.p_cell.hex = hex;
                return this.parentContainer;
        };


        resetGraphics() {
                this.terrainIndex = 0;
                this.poly = null; // The cell's poly that is used as a hit area.
                this.outline = null; // The PIXI.Graphics outline of the cell's hex.
                this.inner = null; // If a non-textured cell then this is the PIXI.Graphics of the hex inner.
                this.hex = null; // The parent container of the hex's graphics objects.
        }


        onCellClick() {
                var r, c;
                console.log("Cell selected : (" + this.row + "," + this.column + ")");


                // //diago droite
                // var cellX = this.column - (this.row + (this.row & 1)) / 2;

                // //ligne
                // var cellZ = this.row;

                // //diago gauche
                // var cellY = - cellX - cellZ;

                // for(var r = 0; r < m.cells.length ; r+=1) {
                //     for(var c = 0 ; c < m.cells[r].length ; c+=1) {
                //         var tempX = m.cells[r][c].column - (m.cells[r][c].row + (m.cells[r][c].row & 1)) / 2;
                //         var tempZ = m.cells[r][c].row;
                //         var tempY = - tempX - tempZ;

                //         if ((tempX == cellX) || (tempY == cellY) || (tempZ == cellZ)){
                //             m.setCellTerrainType(m.cells[r][c], 1);
                //         }

                //     }
                // }     
        }

        onCellHover() {
                this.isOver = true;
                // console.log("Cell Hover : (" + this.row + "," + this.column + ")");
                this.updateColorOutline(this.hexLineColorSelected);
        }

        onCellOut() {
                this.isOver = false;
                this.updateColorOutline(this.hexLineColor);
        }

        updateColorOutline(color: number) {
                var len = this.outline.geometry.graphicsData.length;
                for (var i = 0; i < len; i++) {
                        var data = this.outline.geometry.graphicsData[i];
                        data.lineStyle.color = color;
                }
                this.outline.geometry.invalidate();
        };

        setBlurFilter(enable: boolean) {
                let blurFilter: filters.BlurFilter = new filters.BlurFilter();
                if (enable) {
                        // Display blur filter
                        this.sprite.filters = [blurFilter];
                } else {
                        this.sprite.filters = [];
                }
        }

}
