import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Observable } from 'rxjs/Observable';
import { environment } from '../../environments/environment';

const HttpOptions = {
    headers: new HttpHeaders({ 'Content-Type': 'application/json' })
};

@Injectable()
export class BucketDetailService {

    constructor(private http: HttpClient) { }

    getBucket(id: number) {
        return this.http.get(environment.api_hostname + '/buckets/' + id);
    }

}
