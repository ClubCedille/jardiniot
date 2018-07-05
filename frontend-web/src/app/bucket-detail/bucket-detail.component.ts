import { Component, OnInit, OnDestroy } from '@angular/core';
import { Bucket } from '../bucket/bucket';
import { Sensor } from '../sensors/sensor';
import { ActivatedRoute } from '@angular/router';
import { BucketDetailService } from './bucket-detail.service';
import { SensorsService } from "../sensors/sensors.service";
import { Observable } from 'rxjs/Observable';
import 'rxjs/add/observable/interval';

@Component({
    selector: 'app-bucket-detail',
    templateUrl: './bucket-detail.component.html',
    styleUrls: ['./bucket-detail.component.css'],
    providers: [BucketDetailService, SensorsService]
})
export class BucketDetailComponent implements OnInit, OnDestroy {

    public id: number;
    public bucket;
    public sensors;
    private sub: any;
    private intervalUpdateSensors;

    constructor(private bucketDetailService: BucketDetailService,
        private sensorsService: SensorsService,
        private route: ActivatedRoute) { }

    ngOnInit() {
        this.sub = this.route.params.subscribe(params => {
            this.id = +params['id'];
        });
        this.getBucket(this.id);
    }

    ngOnDestroy() {
        clearInterval(this.intervalUpdateSensors);
    }

    getBucket(id: number) {
        this.bucketDetailService.getBucket(this.id).subscribe(
            data => {
                this.bucket = data,
                    this.sensors = this.bucket.sensors
            },
            err => console.error(err),
            () => {
                console.log('done loading bucket ' + this.bucket.name);
                console.log('On passe maintenant au sensors');
                this.prepareSensors();
            }
        );
    }

    prepareSensors() {
        console.log("Les sensors: ");

        this.intervalUpdateSensors = setInterval(() => {
            this.sensors.forEach((sensor) => {
                this.getSensorData(this.bucket.id, sensor);
            });
        }, 1 * 1000);
    }

    getSensorData(bucketId: number, sensor: Sensor) {
        this.sensorsService.getLatestData(bucketId, sensor.id).subscribe(
            data => {
                sensor.data = data;
            },
            err => console.error(err),
            () => {
                console.log('refreshed sensor ' + sensor.id);
            }
        );

    }
}

