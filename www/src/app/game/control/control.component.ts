import { Component, OnInit, Output, EventEmitter } from '@angular/core';
import { AlertController, ToastController } from '@ionic/angular';

import { appService } from '../+xstate/appMachine';

@Component({
  selector: 'app-control',
  templateUrl: './control.component.html',
  styleUrls: ['./control.component.scss']
})
export class ControlComponent implements OnInit {
  @Output() nbPenguinChanged = new EventEmitter<any>();
  @Output() nbHexagonalChanged = new EventEmitter<any>();
  @Output() gameReady = new EventEmitter<any>();

  gameStarted: boolean;

  valueRangePenguin: number = 2;

  valueRangeHexagonal: number = 8;

  constructor(private alertController: AlertController, private toastController: ToastController) {}

  ngOnInit(): void {
    this.gameStarted = false;
  }

  startGame(): void {
    this.gameStarted = true;
    this.gameReady.emit();
    this.presentToast();
  }

  newNumberPenguin(event: any) {
    this.nbPenguinChanged.emit(event);
  }

  newNumberHexagonal(event: any) {
    this.nbHexagonalChanged.emit(event);
  }

  /***************************************************************************************************************************
   ******************************************** CONFIRM / TOAST **************************************************************
   ***************************************************************************************************************************/

  async presentConfirm() {
    let alert = await this.alertController.create({
      // title: 'Confirm purchase',
      message: 'Do you want to continue with these settings ?',
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
            appService.send(appService.machine.states.settings.on.NEXTSTEP[0].eventType);
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
      color: 'success',
      position: 'top',
      duration: 1000
    });
    toast.present();
  }
}
