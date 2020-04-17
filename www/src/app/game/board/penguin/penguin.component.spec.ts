import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { PenguinComponent } from './penguin.component';

describe('PenguinComponent', () => {
  let component: PenguinComponent;
  let fixture: ComponentFixture<PenguinComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [PenguinComponent]
    }).compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(PenguinComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
