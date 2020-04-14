import { Pos } from './pos';
import { TerrainType } from './terrainType';

/**
*
* The cell object represents one map hex cell.
*/

export class Cell {
        row: number;
        column: number;
        center: Pos = { x: 0, y: 0 };

        terrainIndex: number;

        isEmpty: boolean;
        isOver: boolean;
        alpha: number = 0.8;

        hasPenguin: boolean;

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
                this.hasPenguin = false;
                if (terrainIndex === -1) {
                        this.isEmpty = true;
                } else {
                        this.terrainIndex = terrainIndex ? terrainIndex : 0;
                }
        }

        setCellTerrainType(terrainIndex: number) {
                this.terrainIndex = terrainIndex;
        }

        setCellSelectedTexture(select: boolean, alpha: number) {
                if (select && this.terrainIndex <= 3) {
                        this.terrainIndex += 3;
                } else if (!select && this.terrainIndex > 3) {
                        this.terrainIndex -= 3;
                } else {

                }

                this.alpha = alpha;
        }


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
}
