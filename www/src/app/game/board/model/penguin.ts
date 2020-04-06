import { Sprite, Loader, filters } from 'pixi.js';

import { Pos } from './pos';
import { Cell }  from './cell';

let loader: any = Loader.shared

export class Penguin {
    cellPosition: Cell = null;
    center: Pos;
    sprite: any;
    playerPenguin: boolean;

    constructor(center: Pos, playerPenguin: boolean) {
        this.center = center;
        this.playerPenguin = playerPenguin;
        // loader.add("/assets/penguin.png")
        this.sprite = new Sprite(loader.resources["/assets/penguin.png"].texture);
        // center the penguins's anchor point
        this.sprite.anchor.set(0.5);

        this.sprite.scale.set(0.16);
        // this.sprite.width = map.hexWidth / 1.2;
        // this.sprite.height = map.hexHeight / 1.2;

        this.sprite.position.set(this.center.x, this.center.y);

        this.sprite.filters = [];

        let contrastMatrix = new filters.ColorMatrixFilter();
        contrastMatrix.contrast(3, false);
        this.sprite.filters.push(contrastMatrix);

        if (playerPenguin) {
            let colorMatrix = new filters.ColorMatrixFilter();
            colorMatrix.sepia(false);
            this.sprite.filters.push(colorMatrix);

        } else {
            let colorMatrix1 = new filters.ColorMatrixFilter();
            let colorMatrix2 = new filters.ColorMatrixFilter();
            colorMatrix1.night(0.3, false);
            colorMatrix2.toBGR(false);
            this.sprite.filters.push(colorMatrix1);
            this.sprite.filters.push(colorMatrix2);
        }
    }

    moveTo(newCell: Cell) {
        if (this.cellPosition !== null) {
            this.cellPosition.hasPenguin = false;
        }
        this.cellPosition = newCell;
        this.cellPosition.hasPenguin = true;
        this.center = newCell.getCellCenter();
        this.sprite.position.set(this.center.x, this.center.y);
    }


}