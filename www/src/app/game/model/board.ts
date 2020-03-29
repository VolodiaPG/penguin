import { Pos } from './pos';
import { Cell } from './cell';
import { TerrainType } from './terrainType';

/**
 * 
 */

export class Board {
    hexes: object;          // new PIXI.Graphics()
    pixiApp: object;        // map
    pixiLoader: object;     // loader;

    // The map's number of cells across (cell column count).
    mapWidth: number;       // 8
    // The map's number of cells high (cell row count).
    mapHeight: number;      // 8
    
    // The pixel width of a hex.
    hexWidth: number;       // 90
    // The pixel height of a hex.
    hexHeight: number;      // 90
    // This is the pixel height specifying an area of overlap for hex cells. Necessary when
    // working with isometric view art systems.
    hexBottomPad: number;   // 33 

    // The radius of the hex. Ignored if hexWidth and hexHeight are set to non-null.
    hexSize: number;        // hexWidth / 2
    drawHexSize: number;    // 40
    aspectRatio: number;    // hexHeight / hexWidth


    // The color to use when drawing hex outlines.
    hexLineColor: number;   // 0xd0d0d0
    hexLineColorSelected: number;   // 0xff5521

    // The width in pixels of the hex outline.
    hexLineWidth: number;   // 2

    // Specify the types of terrain available on the map. Map cells reference these terrain
    // types by index. Add custom properties to extend functionality.
    terrainTypes: TerrainType[] = [
        { name: "empty", tileIndex: -1, color: 0xffffff, isEmpty: true },
        { name: "fish1", tileIndex: 0, color: 0x808080, isEmpty: false },
        { name: "fish2", tileIndex: 1, color: 0xe2e2fa, isEmpty: false },
        { name: "fish3", tileIndex: 2, color: 0xe2e2fa, isEmpty: false },
        { name: "fish1_Selected", tileIndex: 3, color: 0x808080, isEmpty: false },
        { name: "fish2_Selected", tileIndex: 4, color: 0xe2e2fa, isEmpty: false },
        { name: "fish3_Selected", tileIndex: 5, color: 0xe2e2fa, isEmpty: false }
    ];
    
    // Array of textures. Can be referenced by index in terrainType.
    textures: string[] = [
        "images/game/tileSnow_fish1.png",
        "images/game/tileSnow_fish2.png",
        "images/game/tileSnow_fish3.png",
        "images/game/tileWater_fish1.png",
        "images/game/tileWater_fish2.png",
        "images/game/tileWater_fish3.png"
    ];

    cells: Cell[] = [];
    hexAxis: Pos = {x:0, y:0};
    hexDrawAxis: Pos = { x: ((1 - (Math.sqrt(3) / 2)) * this.hexWidth) + this.hexWidth, y: this.hexHeight };

}