import { Pos } from './pos';
import { Cell } from './cell';

export class Penguin {
  cellPosition: Cell = null;
  center: Pos;
  playerPenguin: boolean;

  isSelected: boolean;

  imageUrl: string;

  constructor(cell: Cell, playerPenguin: boolean) {
    this.cellPosition = cell;
    this.center = this.cellPosition.getCellCenter();
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

  // moveTo(newCell: Cell) {
  //     if (this.cellPosition !== null) {
  //         this.cellPosition.hasPenguin = false;
  //     }
  //     this.cellPosition = newCell;
  //     this.cellPosition.hasPenguin = true;
  //     this.center = newCell.getCellCenter();
  // }
}
