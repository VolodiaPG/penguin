import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';

import { IonicModule } from '@ionic/angular';

import { GamePageRoutingModule } from './game-routing.module';

import { GamePage } from './game.page';
import { BoardComponent } from './board/board.component';
import { ControlComponent } from './control/control.component';
import { ConsoleComponent } from './console/console.component';
import { HexComponent } from './board/hex/hex.component';
import { PenguinComponent } from './board/penguin/penguin.component';
import { InfoComponent } from './info/info.component';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    GamePageRoutingModule
  ],
  declarations: [
    GamePage,
    BoardComponent,
    InfoComponent,
    ControlComponent,
    ConsoleComponent,
    HexComponent,
    PenguinComponent
  ]
})
export class GamePageModule {}
