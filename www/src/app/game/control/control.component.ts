import { Component, OnInit, Output, EventEmitter } from '@angular/core';
import { AlertController, ToastController } from '@ionic/angular';

import { appService } from '@app/game/models/appMachine';

/**
 * Control component for the game settings.
 */
@Component({
  selector: 'app-control',
  templateUrl: './control.component.html',
  styleUrls: ['./control.component.scss']
})
export class ControlComponent implements OnInit {
  /**
   * Emitter to notify the parent Game Component, when the number of penguins changed.
   */
  @Output() nbPenguinChanged = new EventEmitter<any>();

  /**
   * Emitter to notify the parent Game Component, when the number of hexagonals changed.
   */
  @Output() nbHexagonalChanged = new EventEmitter<any>();

  /**
   * Emitter to notify the parent Game Component, when the user clicked on next button.
   */
  @Output() nextStep = new EventEmitter<any>();

  /**
   * Service to access on the application Final State Machine.
   */
  stateControler: any = appService;

  /**
   * Value of the Penguin Range element in the template.
   */
  valueRangePenguin: number = 2;

   /**
   * Value of the Hexagonal Range element in the template.
   */
  valueRangeHexagonal: number = 8;

  /**
   * Constructor of the Control Component
   * @param alertController 
   * @param toastController 
   */
  constructor(private alertController: AlertController, private toastController: ToastController) {}

  /**
   * @ignore
   */
  ngOnInit(): void {}

  /**
   * Raise event when the penguin range value changed
   * @param {any} event 
   */
  newNumberPenguin(event: any) {
    this.nbPenguinChanged.emit(event);
  }

  /**
   * Raise event when the hexagonal range value changed
   * @param {any} event 
   */
  newNumberHexagonal(event: any) {
    this.nbHexagonalChanged.emit(event);
  }

  //***************************************************************************************************************************
  //******************************************** CONFIRM / TOAST **************************************************************
  //***************************************************************************************************************************

   /**
    * Create a asynchronous confirm box.
    */
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
            this.presentToast();
            this.nextStep.emit();
          }
        }
      ]
    });
    alert.present();
  }

  /**
   * Create a little toast to show the current state of the app.
   */
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
