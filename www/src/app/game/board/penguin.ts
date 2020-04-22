import { Pos } from './pos';
import { Cell } from './cell';

declare var Module: any;

export class Penguin {
  cellPosition: Cell = null;
  textureIndex: number = 2;

  wasmPenguin: any;

  // playerPenguin: boolean;

  private moveToAnimation: any;

  isVisible: boolean;
  isSelected: boolean;

  constructor(cell: Cell) {
    this.cellPosition = cell;
    this.isVisible = false;
    this.isSelected = false;
  }

  setWasmPenguin(wasmPenguin: any) {
    this.wasmPenguin = wasmPenguin;
    this.textureIndex = this.wasmPenguin.getOwner().getId();
  }

  switchPenguinColor() {
    this.isSelected = !this.isSelected;
    if (this.isSelected) {
      this.textureIndex = 0;
    } else {
      this.textureIndex = this.wasmPenguin.getOwner().getId();
    }
  }

  moveTo(newCell: Cell) {
    console.log(this.toString() + ' move from ' + this.cellPosition.toString() + ' to ' + newCell.toString());
    this.cellPosition.isGone();
    this.cellPosition = newCell;
  }

  // moveTo(newCell: Cell) {
  //     if (this.cellPosition !== null) {
  //         this.cellPosition.hasPenguin = false;
  //     }
  //     this.cellPosition = newCell;
  //     this.cellPosition.hasPenguin = true;
  //     this.center = newCell.getCellCenter();
  // }

  toString() {
    let wasmPos = Module.hex_cube_to_offset(Module.hex_axial_to_cube(this.wasmPenguin.getCurrentCell().getPosition()));
    return (
      'Penguin : ' +
      //  + '[' + this.cellPosition.row + '][' + this.cellPosition.column + ']'
      '(' +
      wasmPos.row +
      ',' +
      wasmPos.column +
      ')' +
      this.wasmPenguin.getOwner().getId()
    );
  }
}
