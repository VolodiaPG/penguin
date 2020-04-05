import { Sprite, Loader } from 'pixi.js';

import { Pos } from './pos';

let loader: any = Loader.shared

export class Penguin {
    cellPosition: any;
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
    }


}