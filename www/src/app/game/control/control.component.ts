import { Component, OnInit,Output, EventEmitter } from '@angular/core';

import { penguinGame } from '../board/board.component';

@Component({
  selector: 'app-control',
  templateUrl: './control.component.html',
  styleUrls: ['./control.component.scss']
})
export class ControlComponent implements OnInit {

  @Output() nbPenguinChanged = new EventEmitter<any>();
  @Output() nbHexagonalChanged = new EventEmitter<any>();

  nbPenguin: number;
  valueRangePenguin: number = 4;

  nbHexagonal: number;
  valueRangeHexagonal: number = 8;

  constructor() { }

  ngOnInit(): void {

  }

  startGame():void {
    penguinGame.setBlurFilter(false);
  }

  newNumberPenguin(event:any) {
    this.nbPenguinChanged.emit(event);
  }

  newNumberHexagonal(event:any) {
    this.nbHexagonalChanged.emit(event);
  }
}
