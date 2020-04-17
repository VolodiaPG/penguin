import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import anime from 'animejs/lib/anime.es';
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

  moveToAnimation: any;

  constructor() {}

  ngOnInit() {}

  /***************************************************************************************************************************
   ************************************************ ANIMATION******************************************************************
   ***************************************************************************************************************************/
  onPenguinClick() {
    console.log(
      'Penguin [' +
        this.penguin.cellPosition.row +
        '][' +
        this.penguin.cellPosition.column +
        ']' +
        ' (' +
        this.penguin.center.x +
        ',' +
        this.penguin.center.y +
        ')'
    );
    this.penguinClicked.emit(this.penguin);
  }

  // moveTo(cell: Cell) {
  //   this.position.x = this.position.x + 180;
  //   this.position.y = this.position.y + 450;

  //   this.moveToAnimation = anime({
  //     targets: '.penguin',
  //     translateX: this.position.x,
  //     translateY: this.position.y,
  //     duration: 2000,
  //     property: [this.position],
  //   });
  // }
}
