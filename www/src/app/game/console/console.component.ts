import { Component, OnInit } from '@angular/core';

declare var Module: any;

@Component({
  selector: 'app-console',
  templateUrl: './console.component.html',
  styleUrls: ['./console.component.scss']
})
export class ConsoleComponent implements OnInit {
  public console_outputs: String = '';

  constructor() {}

  ngOnInit() {
    document.addEventListener('mcts_console', (e: any) => {
      console.log(e);
      this.console_outputs += e.detail.replace(new RegExp('\n', 'g'), '<br />') + '<br />';
      console.log(this.console_outputs);
    });
  }
}
