import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Observable } from 'rxjs/Observable';

const HttpOptions = {
    headers: new HttpHeaders({ 'Content-Type': 'application/json' })
};

@Injectable()
export class SensorsService {

    constructor(private http: HttpClient) { }

    getSensor(sensorId: number) {
        return this.http.get('http://localhost:8080/sensors/' + sensorId);
    }

    getLatestData(bucketId: number, sensorId: number) {
        return this.http.get('http://localhost:8080/buckets/' + bucketId + '/' + sensorId + '/latest');
    }

}
