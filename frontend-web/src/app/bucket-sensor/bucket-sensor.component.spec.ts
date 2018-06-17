import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { BucketSensorComponent } from './bucket-sensor.component';

describe('BucketSensorComponent', () => {
  let component: BucketSensorComponent;
  let fixture: ComponentFixture<BucketSensorComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ BucketSensorComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(BucketSensorComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
