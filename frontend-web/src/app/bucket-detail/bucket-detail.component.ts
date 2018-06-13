import { Component, OnInit } from '@angular/core';
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
export class BucketDetailComponent implements OnInit, on {

    public id: number;
    public bucket;
    public sensors;
    private sub: any;

    constructor(private bucketDetailService: BucketDetailService,
        private sensorsService: SensorsService,
        private route: ActivatedRoute) { }

    ngOnInit() {
        this.sub = this.route.params.subscribe(params => {
            this.id = +params['id'];
        });
        this.getBucket(this.id);
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
        console.log(this.sensors);

        this.sensors.forEach((sensor) => {
            console.log("try getSensorData " + this.bucket.id + " - " + sensor.id + "  +@@@@@@@@@");
            console.log(sensor);

            this.getSensorData(this.bucket.id, sensor);

            console.log(sensor);
        });
    }

    getSensorData(bucketId: number, sensor: Sensor) {
        this.sensorsService.getLatestData(bucketId, sensor.id).subscribe(
            data => {
                sensor.data = data;
            },
            err => console.error(err),
            () => {
                console.log('done loading sensor ' + sensor.id);
            }
        );
    }
}

