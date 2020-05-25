import { Component, OnInit, ViewChild, AfterViewInit, ElementRef } from '@angular/core';
import { ConsoleService } from 'src/app/services/console.service';
import { Subscription } from 'rxjs';
import { Chart, ChartDataSets } from "chart.js";
import { Color, Label } from 'ng2-charts';

@Component({
  selector: 'app-results',
  templateUrl: './results.component.html',
  styleUrls: ['./results.component.scss'],
})
export class ResultsComponent implements OnInit {

  // @ViewChild('canvas', { read: ElementRef, static: true }) private resultsCanvas: ElementRef;

  private chart: Chart;

  private subscription: Subscription;

  private mctsRatio: number;
  private humanRatio: number;

  chartData: ChartDataSets[] =
    [
      { data: [0.5, 0.5], label: '% of wins' }
    ];

  chartLabels: Label[] = ['MCTS', 'YOU'];

  chartOptions = {
    responsive: true,
    maintainAspectRatio: false,
    title: {
      display: false,
      text: 'Score'
    },
    pan: {
      enabled: false,
      mode: 'xy'
    },
    zoom: {
      enabled: false,
      mode: 'xy'
    }
  };

  chartColors: Color[] = [
    {
      borderColor: '#3880ff',
      backgroundColor: ['#f04141', '#10dc60']
    }
  ];

  chartType = 'doughnut';
  showLegend = false;

  constructor(private consoleService: ConsoleService) {
    this.subscription = this.consoleService.getResults().subscribe(res => {
      if (res) {
        this.mctsRatio = res.score / res.visits;
        this.humanRatio = 1 - this.mctsRatio;

        this.chartData[0].data = [];

        this.chartData[0].data.push(this.mctsRatio);
        this.chartData[0].data.push(this.humanRatio);
      }
    });
  }

  ngOnInit() { }
}
