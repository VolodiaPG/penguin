import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';

import { Pos } from '../pos';
import { Cell } from '../cell';

import { gameService } from '@app/game/+xstate/gameMachine';
import { appService } from '@app/game/+xstate/appMachine';

@Component({
  selector: 'app-hex',
  templateUrl: './hex.component.html',
  styleUrls: ['./hex.component.scss']
})
export class HexComponent implements OnInit {
  @Input() cell: Cell;
  @Input() isLoaded: boolean;

  @Output() cellClicked = new EventEmitter<Cell>();

  center: Pos;

  // Specify the types of terrain available on the map. Map cells reference these terrain
  // types by index. Add custom properties to extend functionality.

  // Array of textures. Can be referenced by index in terrainType.
  textures: string[] = [
    '/assets/game/empty.png',
    '/assets/game/tileSnow_big.png',
    '/assets/game/normal_fish1.png',
    '/assets/game/normal_fish2.png',
    '/assets/game/normal_fish3.png',
    '/assets/game/selected_fish1.png',
    '/assets/game/selected_fish2.png',
    '/assets/game/selected_fish3.png',
    '/assets/game/available_fish1.png',
    '/assets/game/available_fish2.png',
    '/assets/game/available_fish3.png'
  ];

  isSelected: boolean;

  constructor() {}

  ngOnInit() {
    this.isSelected = false;
    this.center = this.cell.getCellCenter();
  }

  onCellClick() {
    // console.log(this.cell.toString());
    if (this.isSelectable()) {
      this.cellClicked.emit(this.cell);
    }
  }

  onCellHover(hover: boolean) {
    if (this.isSelectable()) {
      this.setSelectedColor(hover);
    } 
  }

  setSelectedColor(newStatus: boolean) {
      if (this.isSelected && !newStatus) {
        this.cell.setSelectedColor(false);
        this.isSelected = false;
      } else if (!this.isSelected && newStatus) {
        this.cell.setSelectedColor(true);
        this.isSelected = true;
      }
  }

  isSelectable(): boolean {
    return (
      this.isLoaded === true &&
      this.cell.terrainIndex !== 0 &&
      (appService.state.value === 'initPosPenguin' ||
        gameService.state.value === 'waiting' ||
        (gameService.state.value === 'penguinSelected' && this.cell.isAvailable))
    );
  }
}
