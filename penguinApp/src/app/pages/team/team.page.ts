import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-team',
  templateUrl: './team.page.html',
  styleUrls: ['./team.page.scss'],
})
export class TeamPage implements OnInit {

  teamMembers: Array<{ name: string; role: string; description: string }> = [
    {
      name: 'Volodia',
      role: 'C++ / MCTS / WebAssembly',
      description: 'Penguin'
    },
    {
      name: 'Maxime',
      role: 'Graphical designer / WebAssembly',
      description: 'Penguin'
    },
    {
      name: 'Romain Hubert',
      role: 'C++ / MCTS',
      description: 'Penguin'
    },
    {
      name: 'Romain Hu',
      role: 'Graphical desginer',
      description: 'Penguin'
    },
    {
      name: 'Clément',
      role: 'Graphical designer',
      description: 'Penguin'
    }
  ];

  constructor() {}

  ngOnInit() {}

}
