import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { AlertController, ToastController } from '@ionic/angular';

import { appService } from '../board/models/appMachine';

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
   * Value of the Penguin Range element in the template.
   */
  rangePenguinValue: number;

  @Input()
  get rangePenguin() {
    return this.rangePenguinValue;
  }

  /**
   * Emitter to notify the parent Game Component, when the number of penguins changed.
   */
  @Output() rangePenguinChange = new EventEmitter();

  set rangePenguin(val:number) {
    this.rangePenguinValue = val;
    this.rangePenguinChange.emit(this.rangePenguinValue);
  }

  /**
   * Value of the Hexagonal Range element in the template.
   */
  rangeHexagonalValue: number;

  @Input()
  get rangeHexagonal() {
    return this.rangeHexagonalValue;
  }

  /**
   * Emitter to notify the parent Game Component, when the number of hexagonals changed.
   */
  @Output() rangeHexagonalChange = new EventEmitter();


  set rangeHexagonal(val:number) {
    this.rangeHexagonalValue = val;
    this.rangeHexagonalChange.emit(this.rangeHexagonalValue);
  }

  difficultyValue: number;

  @Input()
  get difficulty() {
    return this.difficultyValue;
  }
  
  @Output() difficultyChange = new EventEmitter();

  set difficulty(val:number) {
    this.difficultyValue = val;
    this.difficultyChange.emit(this.difficultyValue);
  }

  /**
   * Emitter to notify the parent Game Component, when the user clicked on next button.
   */
  @Output() nextStep = new EventEmitter<any>();

  /**
   * Service to access on the application Final State Machine.
   */
  stateControler: any = appService;

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

  segmentChanged(event: any)
  {
    console.log(event.detail.value);
    this.difficulty = event.detail.value === "hard" ? 2 : 1;
  }

  /**
   * Create a little toast to show the current state of the app.
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