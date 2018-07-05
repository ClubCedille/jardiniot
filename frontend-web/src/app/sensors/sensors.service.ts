import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Observable } from 'rxjs/Observable';
import { environment } from '../../environments/environment';

const HttpOptions = {
    headers: new HttpHeaders({ 'Content-Type': 'application/json' })
};

@Injectable()
export class SensorsService {

    constructor(private http: HttpClient) { }

    getSensor(sensorId: number) {
        return this.http.get(environment.api_hostname + '/sensors/' + sensorId);
    }

    getLatestData(bucketId: number, sensorId: number) {
        return this.http.get(environment.api_hostname + '/buckets/' + bucketId + '/sensor/' + sensorId + '/latest');
    }

}
