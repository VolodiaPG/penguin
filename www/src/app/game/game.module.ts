import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { TranslateModule } from '@ngx-translate/core';
import { IonicModule } from '@ionic/angular';
import { FormsModule } from '@angular/forms';

import { GameRoutingModule } from './game-routing.module';
import { GameComponent } from './game.component';
import { BoardComponent } from './board/board.component';
import { ControlComponent } from './control/control.component';
import { ConsoleComponent } from './console/console.component';
import { HexComponent } from './board/hex/hex.component';

@NgModule({
  imports: [CommonModule, TranslateModule, IonicModule, GameRoutingModule,
    FormsModule],
  entryComponents: [GameComponent],
  declarations: [GameComponent, BoardComponent, ControlComponent, ConsoleComponent, HexComponent]
})
export class GameModule {}
