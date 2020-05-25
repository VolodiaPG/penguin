import { Injectable } from '@angular/core';
import { Observable, Subject } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class ConsoleService {

  private subject = new Subject<any>();

  constructor() { }

  sendResults(s: number, v: number): any {
    this.subject.next({ score: s, visits: v });
  }

  getResults(): Observable<any> {
    return this.subject.asObservable();
  }
}
