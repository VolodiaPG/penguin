import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';

import { Cell } from '../models/cell';

import { gameService } from '../models/gameMachine';
import { appService } from '../models/appMachine';

/**
 * Hexagonal Component
 */
@Component({
  selector: 'app-hex',
  templateUrl: './hex.component.html',
  styleUrls: ['./hex.component.scss']
})
export class HexComponent implements OnInit {
  /**
   * Set the cell of the componennt from the parent Board Component.
   */
  @Input() cell: Cell;

  /**
   * Set the boolean variable from the parent Board Component, if the cell has to be show or not.
   */
  @Input() isLoaded: boolean;

  /**
   * Emitter to the parent Board Component, to raise an event when the user clicked on the component.
   */
  @Output() cellClicked = new EventEmitter<Cell>();

  /**
   * Array of textures. Can be referenced by index in terrainType.
   * Specify the types of terrain available on the map. Map cells reference these terrain
   * types by index. Add custom properties to extend functionality.
   */
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

  /**
   * Variable to know if the cell is selected or not.
   */
  isSelected: boolean;

  /**
   * @ignore
   */
  constructor() {}

  /**
   * @ignore 
   */
  ngOnInit() {
    this.isSelected = false;
  }

  /**
   * Raise an event to the parent Board Component, when the user clicked on the hex component.
   */
  onCellClick() {
    // console.log(this.cell.toString());
    if (this.isSelectable()) {
      this.cellClicked.emit(this.cell);
    }
  }

  /**
   * To react, when the mouse over or mouse out of the chex component.
   * @param {boolean} hover 
   */
  onCellHover(hover: boolean) {
    if (this.isSelectable()) {
      this.setSelectedColor(hover);
    }
  }

  /**
   * To set the color on the cell, if it is selected or not.
   * @param {boolean} newStatus 
   */
  setSelectedColor(newStatus: boolean) {
    if (this.isSelected && !newStatus) {
      this.cell.setSelectedColor(false);
      this.isSelected = false;
    } else if (!this.isSelected && newStatus) {
      this.cell.setSelectedColor(true);
      this.isSelected = true;
    }
  }

  /**
   * @returns if the cell is selectable or not
   */
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
