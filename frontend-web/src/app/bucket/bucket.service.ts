import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Observable } from 'rxjs/Observable';

const HttpOptions = {
    headers: new HttpHeaders({ 'Content-Type': 'application/json' })
};

@Injectable()
export class BucketService {

    constructor(private http:HttpClient) { }

    getBuckets() {
        return this.http.get('http://localhost:8080/buckets');
    }

}
