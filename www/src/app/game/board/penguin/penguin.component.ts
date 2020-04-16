import { Component, OnInit } from '@angular/core';
import anime from 'animejs/lib/anime.es';
import { Pos } from '../pos';

@Component({
  selector: 'app-penguin',
  templateUrl: './penguin.component.html',
  styleUrls: ['./penguin.component.scss']
})
export class PenguinComponent implements OnInit {

  position: Pos;

  moveToAnimation:any;

  constructor() { }

  ngOnInit() {
    this.position = new Pos(0,0);
  }

  /***************************************************************************************************************************
  ************************************************ ANIMATION******************************************************************
  ***************************************************************************************************************************/
  onPenguinClick() {
    console.log("Penguin clicked");

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

}
