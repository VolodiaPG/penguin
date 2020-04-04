import { Component, OnInit } from '@angular/core';

import { setBlurFilter } from '../board/board.component';

@Component({
  selector: 'app-control',
  templateUrl: './control.component.html',
  styleUrls: ['./control.component.scss']
})
export class ControlComponent implements OnInit {

  constructor() { }

  ngOnInit() {
  }

  startGame():void {
    setBlurFilter(false);
  }

}
