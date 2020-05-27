import { Component, OnInit, Input } from '@angular/core';
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
  templateUrl: './console.component.html',
  styleUrls: ['./console.component.scss']
})
export class ConsoleComponent implements OnInit {
  /**
   * The message which has to be show in the console.
   */
  public console_outputs: String = '';

  messages: any[] = [];
  subscription: Subscription;

  public console_conv = [
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
      text: 'I am ready this time !!! Be careful 🤪'
    }
  ];

  /**
   * @ignore
   */
  constructor(private consoleService: ConsoleService) {
    this.subscription = this.consoleService.getResults().subscribe(res => {
      if (res) {
        if (res.type === 'score') {
          // this.messages.push(res);
          console.log(res.score, res.visits);
          let percentage = Math.floor(res.score / res.visits * 100);
          let line = "Trust rate is " + percentage + ", played " + res.visits + " simulations total";

          this.console_conv.push({ human: true, avatar: 'assets/logo/favicon.png', color: 'secondary', text: line });

          line = "";

          if (percentage < -50)
            line += "Oh dear, will you stop now !?! 🤬";
          else if (percentage < 0)
            line += "I'm going to re-evaluate the situation... 🧐";
          else if (percentage < 10)
            line += "Hmmm...";
          else if (percentage < 15)
            line += "Let's see where this goes! 🤭";
          else if (percentage < 25)
            line += "Well, I'm feeling good, and you? 🔥";
          else if (percentage < 30)
            line += "Are you sure about that? 🤪";
          else if (percentage < 40)
            line += "I'm feeling confident 🤫";
          else if (percentage < 50)
            line += "Are you letting me win? That's so sweet 💗";
          else if (percentage < 60)
            line += "I don't even know the rules and I still am playing better than you 🤤";
          else if (percentage < 75)
            line += "I'm seriously questionning your abilities right now... 🤓";
          else if (percentage < 90)
            line += "I wish I was playing with someone as strong as me... 🥱";
          else
            line += "We might as well skip to the end, we know who will win 🤣";

          this.console_conv.push({ human: false, avatar: 'assets/penguin_enemie.png', color: 'danger', text: line });
        } else if (res.type === 'end_message' && res.msg !== undefined) {
          if (res.draw) {
            this.console_conv.push({ human: true, avatar: 'assets/penguin.png', color: 'warning', text: res.msg });
          } else if (res.humanwon) {
            this.console_conv.push({ human: true, avatar: 'assets/penguin.png', color: 'success', text: res.msg });
          } else {
            this.console_conv.push({ human: false, avatar: 'assets/penguin_enemie.png', color: 'danger', text: res.msg });
          }
        }
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
      // this.console_conv.push({ human: false, avatar: 'assets/penguin_enemie.png', color: 'warning', text: line });
      // console.log(this.console_conv);

      this.console_outputs += line + '<br />';
      console.log(this.console_outputs);
    });
  }

  ngOnDestroy() {
    // unsubscribe to ensure no memory leaks
    this.subscription.unsubscribe();
  }
}