import { Component, OnInit } from '@angular/core';
import { ConsoleService } from 'src/app/services/console.service';
import { Subscription } from 'rxjs';

/**
 * Bind with the C++ Wasm Module
 */
declare var Module: any;

/**
 * Console component
 */
@Component({
  selector: 'app-console',
  templateUrl: './console.component.html',l
  styleUrls: ['./console.component.scss']
})
export class ConsoleComponent implements OnInit {
  /**
   * The message which has to be show in the console.
   */
  public console_outputs: String = '';

  messages: any[] = [];
  subscription: Subscription;

  console_conv = [
    {
      human: false,
      avatar: 'assets/penguin_enemie.png',
      color: 'danger',
      text: 'Welcome Back !!!'
    },
    {
      human: true,
      avatar: 'assets/penguin.png',
      color: 'success',
      text: 'I am ready this time !!! Be careful > <'
    }
  ];

  /**
   * @ignore
   */
  constructor(private consoleService: ConsoleService) {
    this.subscription = this.consoleService.getResults().subscribe(res => {
      if(res) {
        this.messages.push(res);
        console.log(res.score, res.visits);
        let line = "Easy !!! I will win : " + res.score/res.visits;
        this.console_conv.push({human: false, avatar: 'assets/penguin_enemie.png', color: 'warning', text: line});
      }
    });
  }

  /**
   * Create an EventListener, when the Console Component is created, to bind with the C++ console.
   */
  ngOnInit() {
    console.log(this.console_conv);
    document.addEventListener('mcts_console', (e: any) => {
      console.log(e);
      let line = e.detail.replace(new RegExp('\n', 'g'), '<br />');

      console.log(line);
      this.console_conv.push({human: false, avatar: 'assets/penguin_enemie.png', color: 'warning', text: line});
      console.log(this.console_conv);

      this.console_outputs += line + '<br />';
      console.log(this.console_outputs);
    });
  }

  ngOnDestroy() {
    // unsubscribe to ensure no memory leaks
    this.subscription.unsubscribe();
}
}