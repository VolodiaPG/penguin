import { TestBed } from '@angular/core/testing';

import { HrefService } from './href.service';

describe('HrefService', () => {
  let service: HrefService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(HrefService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
