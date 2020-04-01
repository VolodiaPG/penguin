import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { TranslateModule } from '@ngx-translate/core';
import { IonicModule } from '@ionic/angular';

import { GameRoutingModule } from './game-routing.module';
import { GameComponent } from './game.component';
import { BoardComponent } from './board/board.component';
import { ControlComponent } from './control/control.component';

@NgModule({
  imports: [CommonModule, TranslateModule, IonicModule, GameRoutingModule],
  entryComponents: [GameComponent],
  declarations: [GameComponent, BoardComponent, ControlComponent]
})
export class GameModule {}
