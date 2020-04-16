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

  startPoint: number;
  endPoint:number;

  moveToAnimation:any;

  constructor() { }

  ngOnInit() {
    this.position = new Pos(0,0);
    this.startPoint = this.position.x;
    this.endPoint = this.position.x;
  }

  /***************************************************************************************************************************
  ************************************************ ANIMATION******************************************************************
  ***************************************************************************************************************************/
  onPenguinClick() {
    console.log("Penguin clicked");

    this.startPoint = this.position.x;
    this.position.x = this.position.x + 90;
    this.endPoint = this.position.x;

    this.moveToAnimation = anime({
      targets: '.penguin',
      translateX: this.endPoint,
      duration: 2000,
      property: [this.startPoint, this.endPoint],
    });

    console.log(this.startPoint + "->" + this.endPoint);

    // anime({
    //   targets: '.penguin',
    //   translateX: function(el:any) {
    //     el.setAttribute('data-x', el.getAttribute('data-x') + 90)
    //     return el.getAttribute('data-x');
    //   },
    //   rotate: '1turn',
    //   duration: 2000,
    //   loop: true
    // });

  }

}
