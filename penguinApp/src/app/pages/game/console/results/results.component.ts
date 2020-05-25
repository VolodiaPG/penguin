import { Component, OnInit, ViewChild, AfterViewInit, ElementRef } from '@angular/core';
import { ConsoleService } from 'src/app/services/console.service';
import { Subscription } from 'rxjs';
import { Chart } from 'chart.js';

@Component({
  selector: 'app-results',
  templateUrl: './results.component.html',
  styleUrls: ['./results.component.scss'],
})
export class ResultsComponent implements OnInit {

  @ViewChild('canvas', { read: ElementRef, static: true }) private resultsCanvas: ElementRef;

  private chart: Chart;

  private subscription: Subscription;

  private mctsRatio: number;
  private humanRatio: number;

  constructor(private consoleService: ConsoleService {
    this.subscription = this.consoleService.getResults().subscribe(res => {
      if(res) {
        this.mctsRatio = res.score/res.visits;
        this.humanRatio = 1 - this.mctsRatio;
      }
    });
   }

  ngOnInit() {
    this.chart = new Chart(this.resultsCanvas.nativeElement, {
      type: "doughnut",
      data: {
        labels: ["YOU", "MCTS"],
        datasets: [
          {
            label: "# of wins",
            data: [12, 19, 3, 5, 2, 3],
            backgroundColor: [
              "rgba(255, 99, 132, 0.2)",
              "rgba(54, 162, 235, 0.2)",
              "rgba(255, 206, 86, 0.2)",
              "rgba(75, 192, 192, 0.2)",
              "rgba(153, 102, 255, 0.2)",
              "rgba(255, 159, 64, 0.2)"
            ],
            hoverBackgroundColor: ["#FF6384", "#36A2EB", "#FFCE56", "#FF6384", "#36A2EB", "#FFCE56"]
          }
        ]
      }
    }); 
  }
}
