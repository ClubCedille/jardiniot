import { Component, OnInit } from '@angular/core';
import { Observable } from 'rxjs/Rx';
import { Router } from '@angular/router';

import { Bucket } from './bucket';
import { BucketService } from './bucket.service';

@Component({
    selector: 'app-bucket',
    templateUrl: './bucket.component.html',
    styleUrls: ['./bucket.component.css'],
    providers: [BucketService]
})
export class BucketComponent implements OnInit {

    public buckets;
    selectedBucket: Bucket;

    constructor(private bucketService: BucketService) { }

    ngOnInit() {
        this.getBuckets();
    }

    getBuckets() {
        this.bucketService.getBuckets().subscribe(
            data => {this.buckets = data},
            err => console.error(err),
            () => console.log('done loading buckets')
        );
    }

    onSelect(bucket: Bucket) {
        this.selectedBucket = bucket;
    }

}
