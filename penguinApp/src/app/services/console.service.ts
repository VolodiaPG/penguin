import { Injectable } from '@angular/core';
import { Observable, Subject } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class ConsoleService {

  private subject = new Subject<any>();

  constructor() { }

  sendResults(s: number, v: number): any {
    this.subject.next({ type: 'score', score: s, visits: v });
  }

  sendEndMessage(draw: boolean, humanwon: boolean, msg: string) {
    this.subject.next({ type: 'end_message', draw: draw, humanwon: humanwon, msg: msg });
  }

  getResults(): Observable<any> {
    return this.subject.asObservable();
  }
}
