import { Component, OnInit,Output, EventEmitter } from '@angular/core';
import { AlertController, ToastController } from '@ionic/angular';

import { penguinGame } from '../board/board.component';

@Component({
  selector: 'app-control',
  templateUrl: './control.component.html',
  styleUrls: ['./control.component.scss']
})
export class ControlComponent implements OnInit {

  @Output() nbPenguinChanged = new EventEmitter<any>();
  @Output() nbHexagonalChanged = new EventEmitter<any>();

  gameStarted: boolean;

  nbPenguin: number;
  valueRangePenguin: number = 4;

  nbHexagonal: number;
  valueRangeHexagonal: number = 8;

  constructor(private alertController: AlertController, private toastController: ToastController) { }

  ngOnInit(): void { 
    this.gameStarted = false;
  }

  startGame():void {
    this.gameStarted = true;
    penguinGame.board.setRandomCells();
    this.presentToast();
  }

  newNumberPenguin(event:any) {
    this.nbPenguinChanged.emit(event);
  }

  newNumberHexagonal(event:any) {
    this.nbHexagonalChanged.emit(event);
  }

  async presentConfirm() {
    let alert = await this.alertController.create({
      // title: 'Confirm purchase',
      message: 'Do you want to start this game ?',
      buttons: [
        {
          text: 'Cancel',
          role: 'cancel',
          handler: () => {
            console.log('Cancel clicked');
          }
        },
        {
          text: 'Confirm',
          handler: () => {
            console.log('Confirm clicked');
            this.startGame();
          }
        }
      ]
    });
    alert.present();
  }

  async presentToast() {
    const toast = await this.toastController.create({
      message: "Let's go !!! ",
      position: 'bottom',
      duration: 3000,
    });
    toast.present();
  }
}
