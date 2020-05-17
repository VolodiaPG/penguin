import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { Penguin } from '../board/models/penguin';

import { appService } from '../board/models/appMachine';
import { AlertController, ToastController } from '@ionic/angular';

/**
 * Info Component to show the stock of penguins.
 */
@Component({
  selector: 'app-info',
  templateUrl: './info.component.html',
  styleUrls: ['./info.component.scss']
})
export class InfoComponent implements OnInit {
  /**
   * To catch the number of penguin from the parent Game Component
   */
  @Input() nbPenguin: number;

  /**
   * Emitter to launch the game in the Game Component.
   */
  @Output() launchGame = new EventEmitter<any>();

  /**
   * Arraw to describe the stock of non-posed penguins.
   */
  penguinsNotPosed: Array<boolean>;

  /**
   * Constructor of the Info Component.
   * @param alertController 
   * @param toastController 
   */
  constructor(private alertController: AlertController, private toastController: ToastController) {}

  /**
   * Init the array of penguins, when the Component is init.
   */
  ngOnInit() {
    this.penguinsNotPosed = new Array(this.nbPenguin);
  }

  /**
   * Update the array of the penguins stock.
   */
  penguinPosed() {
    this.penguinsNotPosed.pop();
  }

  //***************************************************************************************************************************
  //******************************************** CONFIRM / TOAST **************************************************************
  //***************************************************************************************************************************
  /**
   * To create a little controller, to confirm or not the action to be performed.
   */
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

  /**
   * Create a little toast to show the current state of the app service.
   */
  async presentToast() {
    const toast = await this.toastController.create({
      message: "Let's go !!! ",
      color: 'success',
      position: 'bottom',
      duration: 1000
    });
    toast.present();
  }
}