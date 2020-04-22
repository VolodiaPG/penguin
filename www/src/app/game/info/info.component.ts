import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { Penguin } from '../board/penguin';

import { appService } from '@app/game/+xstate/appMachine';
import { AlertController, ToastController } from '@ionic/angular';

@Component({
  selector: 'app-info',
  templateUrl: './info.component.html',
  styleUrls: ['./info.component.scss']
})
export class InfoComponent implements OnInit {
  @Input() nbPenguin: number;

  @Output() launchGame = new EventEmitter<any>();

  penguinsNotPosed: Array<boolean>;

  constructor(private alertController: AlertController, private toastController: ToastController) {}

  ngOnInit() {
    this.penguinsNotPosed = new Array(this.nbPenguin);
  }

  penguinPosed() {
    this.penguinsNotPosed.pop();
  }

  /***************************************************************************************************************************
   ******************************************** CONFIRM / TOAST **************************************************************
   ***************************************************************************************************************************/
  async startConfirm() {
    let alert = await this.alertController.create({
      // title: 'Confirm purchase',
      message: 'Do you want to start the game ?',
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
            console.log('Confirm clicked, game launched !');
            this.launchGame.emit();
            this.presentToast();
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
