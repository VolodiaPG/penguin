import { Component, OnInit, Input } from '@angular/core';
import anime from 'animejs/lib/anime.es';
import { Pos } from '../pos';
import { Cell } from '../cell';

import { gameService } from '../../+xstate/gameMachine';
import { trigger, state, style, transition, animate } from '@angular/animations';

@Component({
  selector: 'app-penguin',
  templateUrl: './penguin.component.html',
  styleUrls: ['./penguin.component.scss'],
  animations: [
    trigger('initPenguin', [
      state('appear', style({
        opacity: 1,
        transform: 'scale(1)'
      })),
      state('disappear', style({
        opacity: 0,
        transform: 'scale(0.3) translateX(-1000%) rotate(360deg)'
      })),
      transition('appear => disappear', [
        animate('1s ease-in-out')
      ]),
      transition('disappear => appear', [
        animate('2s ease-in-out')
      ]),
    ]),
  ]
})
export class PenguinComponent implements OnInit {
  @Input() cell: Cell;
  @Input() isLoaded: boolean;

  position: Pos;
  imageUrl: string;

  isSelected: boolean;

  moveToAnimation: any;

  constructor() { }

  ngOnInit() {
    this.isSelected = false;
    this.position = this.cell.getCellCenter();
    this.switchPenguinColor();
  }

  /***************************************************************************************************************************
  ************************************************ ANIMATION******************************************************************
  ***************************************************************************************************************************/
  onPenguinClick() {
    gameService.send('PENGUINSELECTED');
    console.log("Penguin [" + this.cell.row + "][" + this.cell.column + "]" + " (" + this.position.x + "," + this.position.y + ")");
    this.isSelected = !this.isSelected;
    this.switchPenguinColor();
  }

  moveTo(cell: Cell) {
    this.position.x = this.position.x + 180;
    this.position.y = this.position.y + 450;

    this.moveToAnimation = anime({
      targets: '.penguin',
      translateX: this.position.x,
      translateY: this.position.y,
      duration: 2000,
      property: [this.position],
    });
  }

  switchPenguinColor() {
    if (this.isSelected) {
      this.imageUrl = "/assets/penguin_selected.png";
    } else {
      this.imageUrl = "/assets/penguin.png";
    }
  }

}
