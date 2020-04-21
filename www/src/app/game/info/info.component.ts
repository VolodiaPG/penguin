import { Component, OnInit, Input } from '@angular/core';
import { Penguin } from '../board/penguin';

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
    console.log('done');
    this.penguinsNotPosed.pop();
  }
}
