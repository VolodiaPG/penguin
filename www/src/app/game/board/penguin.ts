import { Pos } from './pos';
import { Cell } from './cell';

export class Penguin {
  cellPosition: Cell = null;
  textureIndex: number = 1;

  wasmPenguin: any;

  playerPenguin: boolean;

  private moveToAnimation: any;

  isSelected: boolean;

  imageUrl: string;

  constructor(cell: Cell, playerPenguin: boolean) {
    this.cellPosition = cell;
    this.playerPenguin = playerPenguin;
    this.isSelected = false;
    this.imageUrl = '/assets/penguin.png';
  }

  switchPenguinColor() {
    this.isSelected = !this.isSelected;
    if (this.isSelected) {
      this.imageUrl = '/assets/penguin_selected.png';
    } else {
      this.imageUrl = '/assets/penguin.png';
    }
  }

  moveTo(newCell: Cell) {
    console.log(this.toString() + ' move from ' + this.cellPosition.toString() + ' to ' + newCell.toString());
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
    return (
      'Penguin [' +
      this.cellPosition.row +
      '][' +
      this.cellPosition.column +
      ']' +
      ' (' +
      this.cellPosition.center.x +
      ',' +
      this.cellPosition.center.y +
      ')'
    );
  }
}
