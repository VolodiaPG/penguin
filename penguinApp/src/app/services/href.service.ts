import { Injectable, Inject } from '@angular/core';
import { DOCUMENT, LocationStrategy } from '@angular/common';

@Injectable({
  providedIn: 'root'
})
export class HrefService {

  constructor(@Inject(DOCUMENT) private readonly document: any,
    private readonly locationStrategy: LocationStrategy) { }

  // for localhost: http://localhost:4200/someBaseHref
  getUrl(): string {
    return `${this.document.location.origin}/${this.locationStrategy.getBaseHref()}`
  }

}
