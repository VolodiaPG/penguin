import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';

import { Pos } from '../pos';
import { Cell } from '../cell';

import { gameService } from '../../+xstate/gameMachine';
import { trigger, state, style, transition, animate } from '@angular/animations';
import { Penguin } from '../penguin';

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
  @Input() penguin: Penguin;
  @Input() isLoaded: boolean;

  @Output() penguinClicked = new EventEmitter<Penguin>();

  // Array of textures. Can be referenced by index of the penguin's owner
  textures: string[] = ['/assets/penguin_selected.png', '/assets/penguin.png', '/assets/penguin_enemie.png'];

  constructor() {}

  ngOnInit() {}

  /***************************************************************************************************************************
   ************************************************ ANIMATION ****************************************************************
   ***************************************************************************************************************************/
  onPenguinClick() {
    console.log(this.penguin.toString());
    this.penguinClicked.emit(this.penguin);
  }
}
