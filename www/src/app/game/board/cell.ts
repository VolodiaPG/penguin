import { Pos } from './pos';

const EMPTYINDEX = 0,
  NORMALINDEX = 1,
  SELECTEDINDEX = 4,
  AVAILABLEINDEX = 7;

declare var Module: any;

/**
 *
 * The cell object represents one map hex cell.
 */

export class Cell {
  row: number;
  column: number;
  center: Pos = { x: 0, y: 0 };

  nbFish: number;
  terrainIndex: number;

  wasmCell: any;

  isAvailable: boolean = false;
  isGone: boolean = false;

  hasPenguin: boolean;

  // The pixel width of a hex.
  hexWidth: number = 90; // 90
  // The pixel height of a hex.
  hexHeight: number = 90; // 90
  // This is the pixel height specifying an area of overlap for hex cells. Necessary when
  // working with isometric view art systems.
  hexBottomPad: number = 33; // 33

  // The radius of the hex. Ignored if hexWidth and hexHeight are set to non-null.
  hexSize: number = this.hexWidth / 2; // hexWidth / 2

  constructor(row: number, column: number) {
    this.row = row;
    this.column = column;
    this.center = this.getCellCenter();
    this.hasPenguin = false;
    this.nbFish = 0;
    this.terrainIndex = NORMALINDEX;
  }

  setWasmCell(wasmCell: any) {
    this.wasmCell = wasmCell;
    this.nbFish = wasmCell.getFish();
    this.terrainIndex = NORMALINDEX + this.nbFish;
  }

  // Calculates and returns the width of a hex cell.
  getHexWidth() {
    let result: number = null;
    result = this.hexSize * 2;
    result = (Math.sqrt(3) / 2) * result;

    return result;
  }

  // Calculates and returns the height of a hex cell.
  getHexHeight() {
    let result: number = null;
    result = this.hexSize * 2;

    return result;
  }

  // Calculate the center of a cell based on column, row and coordinate system.
  getCellCenter() {
    // console.log("getCellCenter(" + this.row + "," + this.column + ")");
    let center: Pos = { x: 0, y: 0 };

    center.y = this.row * (this.hexHeight - 17);

    if (this.row % 2 === 0) {
      // even
      center.x = this.column * this.hexWidth;
    } else {
      // odd
      center.x = this.column * this.hexWidth + this.hexWidth / 2;
    }

    return center;
  }

  setSelectedColor(set: boolean) {
    if (set) {
      this.terrainIndex = SELECTEDINDEX + this.nbFish;
    } else {
      if (this.isAvailable) {
        this.terrainIndex = AVAILABLEINDEX + this.nbFish;
      } else {
        this.terrainIndex = NORMALINDEX + this.nbFish;
      }
    }
  }

  setAvailableColor(set: boolean) {
    this.isAvailable = set;
    if (set) {
      this.terrainIndex = AVAILABLEINDEX + this.nbFish;
    } else {
      this.terrainIndex = NORMALINDEX + this.nbFish;
    }
  }

  toString() {
    let wasmPos = Module.hex_cube_to_offset(Module.hex_axial_to_cube(this.wasmCell.getPosition()));
    return '(' + wasmPos.row + ',' + wasmPos.column + ')' + ' -> ' + this.wasmCell.getFish();
  }
}
