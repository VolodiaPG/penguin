import { Component, OnInit, Input } from '@angular/core';
import { Penguin } from '../board/penguin';

import { appService } from '@app/game/+xstate/appMachine';

@Component({
  selector: 'app-info',
  templateUrl: './info.component.html',
  styleUrls: ['./info.component.scss']
})
export class InfoComponent implements OnInit {
  @Input() nbPenguin: number;

  nbPenguinNotPosed: number;
  penguinsNotPosed: Array<boolean>;

  constructor() {}

  ngOnInit() {
    this.penguinsNotPosed = new Array(this.nbPenguin);
  }

  penguinPosed() {
    this.penguinsNotPosed.pop();
    if (this.penguinsNotPosed.length === 0) {
      appService.send(appService.machine.states.initPosPenguin.on.PENGUINSPOSED[0].eventType);
    }
  }
}
