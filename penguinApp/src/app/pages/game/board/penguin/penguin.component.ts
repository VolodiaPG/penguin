import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';


import { gameService } from '../models/gameMachine';
import { Penguin } from '../models/penguin';

/**
 * Penguin Component
 */
@Component({
  selector: 'app-penguin',
  templateUrl: './penguin.component.html',
  styleUrls: ['./penguin.component.scss']
})
export class PenguinComponent implements OnInit {
  /**
   * Set the current penguin from the parent Board Component.
   */
  @Input() penguin: Penguin;
  /**
   * Variable from the parent Board Component, to show the penguin component or not.
   */
  @Input() isLoaded: boolean;

  /**
   * Emitter to the parent Board Component, to raise an event then the penguin is clicked.
   */
  @Output() penguinClicked = new EventEmitter<Penguin>();

  /**
   * Array of textures. Texture can be referenced by index of the penguin's owner.
   */
  textures: string[] = ['/assets/penguin_selected.png', '/assets/penguin.png', '/assets/penguin_enemie.png' ];

  /**
   * @ignore
   */
  constructor() {}

  /**
   * @ignore
   */
  ngOnInit() {}

  //***************************************************************************************************************************
  //************************************************ ANIMATION ****************************************************************
  //***************************************************************************************************************************

  /**
   * To react on the click, and raise the event to the parent Board Component, if the click is permitted.
   */
  onPenguinClick() {
    console.log(this.penguin.toString());
    if (gameService.state.value !== 'moveBlocked') {
      this.penguinClicked.emit(this.penguin);
    }
  }
}
