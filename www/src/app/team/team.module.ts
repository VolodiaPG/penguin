import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { TranslateModule } from '@ngx-translate/core';
import { IonicModule } from '@ionic/angular';

import { TeamRoutingModule } from './team-routing.module';
import { TeamComponent } from './team.component';

@NgModule({
  entryComponents: [TeamComponent],
  imports: [CommonModule, TranslateModule, IonicModule, TeamRoutingModule],
  declarations: [TeamComponent]
})
export class TeamModule {}
