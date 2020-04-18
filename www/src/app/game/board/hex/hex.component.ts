import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { Pos } from '../pos';
import { Cell } from '../cell';
import { gameService } from '@app/game/+xstate/gameMachine';

@Component({
  selector: 'app-hex',
  templateUrl: './hex.component.html',
  styleUrls: ['./hex.component.scss']
})
export class HexComponent implements OnInit {
  @Input() cell: Cell;
  @Output() cellClicked = new EventEmitter<Cell>();

  center: Pos;

  // Specify the types of terrain available on the map. Map cells reference these terrain
  // types by index. Add custom properties to extend functionality.

  // Array of textures. Can be referenced by index in terrainType.
  textures: string[] = [
    '/assets/game/tileSnow_big.png',
    '/assets/game/normal_fish1.png',
    '/assets/game/normal_fish2.png',
    '/assets/game/normal_fish3.png',
    '/assets/game/selected_fish1.png',
    '/assets/game/selected_fish2.png',
    '/assets/game/selected_fish3.png'
  ];

  isSelected: boolean;

  constructor() {}

  ngOnInit() {
    this.isSelected = false;
    this.center = this.cell.getCellCenter();
  }

  onCellClick() {
    console.log(this.cell.toString());
    this.cellClicked.emit(this.cell);
  }

  onCellHover(hover: boolean) {
    this.setSelectedColor(hover);
  }

  setSelectedColor(isSelected: boolean) {
    if (this.isSelected && !isSelected && this.cell.terrainIndex !== 0) {
      this.cell.setSelectedColor(false);
      this.isSelected = false;
    } else if (!this.isSelected && isSelected && this.cell.terrainIndex !== 0) {
      this.cell.setSelectedColor(true);
      this.isSelected = true;
    }
  }
}
