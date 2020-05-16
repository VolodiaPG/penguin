import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';

import { Pos } from '../pos';
import { Cell } from '../cell';

import { gameService } from '../../models/gameMachine';
import { trigger, state, style, transition, animate } from '@angular/animations';
import { Penguin } from '../penguin';
import { appService } from '@app/game/models/appMachine';

/**
 * Penguin Component
 */
@Component({
  selector: 'app-penguin',
  templateUrl: './penguin.component.html',
  styleUrls: ['./penguin.component.scss'],
  animations: [
    trigger('initPenguin', [
      state(
        'appear',
        style({
          opacity: 1,
          transform: 'scale(1)'
        })
      ),
      state(
        'disappear',
        style({
          opacity: 0,
          transform: 'scale(0.3) translateX(-1000%) rotate(360deg)'
        })
      ),
      transition('appear => disappear', [animate('1s ease-in-out')]),
      transition('disappear => appear', [animate('2s ease-in-out')])
    ])
  ]
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
  textures: string[] = ['/assets/penguin_selected.png', '/assets/penguin_enemie.png', '/assets/penguin.png'];

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
