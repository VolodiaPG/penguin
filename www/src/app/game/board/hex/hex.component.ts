import { Component, OnInit, Input } from '@angular/core';
import { Pos } from '../pos';
import { Cell } from '../cell';


@Component({
  selector: 'app-hex',
  templateUrl: './hex.component.html',
  styleUrls: ['./hex.component.scss']
})
export class HexComponent implements OnInit {
  @Input() cell: Cell;
  @Input() terrainIndex: number;

  center: Pos;

  // Specify the types of terrain available on the map. Map cells reference these terrain
  // types by index. Add custom properties to extend functionality.

  // Array of textures. Can be referenced by index in terrainType.
  textures: string[] = [
    "/assets/game/tileSnow_big.png",
    "/assets/game/tileSnow_fish1.png",
    "/assets/game/tileSnow_fish2.png",
    "/assets/game/tileSnow_fish3.png",
    "/assets/game/tileWater_fish1.png",
    "/assets/game/tileWater_fish2.png",
    "/assets/game/tileWater_fish3.png"
  ];

  isSelected: boolean;

  constructor() { }

  ngOnInit() {
    this.isSelected = false;
    this.center = this.cell.getCellCenter();
  }

  onCellClick() {
    console.log("Cell selected : (" + this.cell.row + "," + this.cell.column + ")" + " -> " + this.cell.nbFish);
  }

  onCellHover(hover: boolean) {
    this.setSelectColor(hover);
  }

  setSelectColor(isSelected: boolean) {
    if (this.isSelected && !isSelected && this.cell.nbFish !== 0) {
      this.terrainIndex = Number.parseInt(this.terrainIndex.toString()) - 3;
      this.isSelected = false;
    } else if (!this.isSelected && isSelected && this.cell.nbFish !== 0) {
      this.terrainIndex = Number.parseInt(this.terrainIndex.toString()) + 3;
      this.isSelected = true;
    }
  }

}
