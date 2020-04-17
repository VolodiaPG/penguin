import { NgModule, CUSTOM_ELEMENTS_SCHEMA } from '@angular/core';
import { CommonModule } from '@angular/common';
import { TranslateModule } from '@ngx-translate/core';
import { RouterModule } from '@angular/router';
import { IonicModule } from '@ionic/angular';

import { ShellComponent } from './shell.component';

@NgModule({
  imports: [CommonModule, TranslateModule, IonicModule, RouterModule],
  entryComponents: [ShellComponent],
  declarations: [ShellComponent],
  schemas: [CUSTOM_ELEMENTS_SCHEMA]
})
export class ShellModule {}
