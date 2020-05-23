import { Component, OnInit } from '@angular/core';

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

  console_conv = [
    {
      icon: 'book',
      color: 'success',
      text: 'Welcome Back !!!'
    }
  ];

  /**
   * @ignore
   */
  constructor() {}

  /**
   * Create an EventListener, when the Console Component is created, to bind with the C++ console.
   */
  ngOnInit() {
    document.addEventListener('mcts_console', (e: any) => {
      console.log(e);
      let line = e.detail.replace(new RegExp('\n', 'g'), '<br />');

      console.log(line);
      this.console_conv.push({icon: 'contact', color: 'warning', text: line});

      this.console_outputs += line + '<br />';
      console.log(this.console_outputs);
    });
  }
}