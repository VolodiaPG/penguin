import { Pos } from './pos';
import { Cell }  from './cell';

export class Penguin {
    cellPosition: Cell = null;
    center: Pos;
    playerPenguin: boolean;

    constructor(center: Pos, playerPenguin: boolean) {
        this.center = center;
        this.playerPenguin = playerPenguin;
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