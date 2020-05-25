import { Component, OnInit, Input } from '@angular/core';

@Component({
  selector: 'app-team-card',
  templateUrl: './team-card.component.html',
  styleUrls: ['./team-card.component.scss']
})
export class TeamCardComponent implements OnInit {
  @Input() name: string;
  @Input() role: string;
  @Input() description: string;

  constructor() {}

  ngOnInit() {}
}
