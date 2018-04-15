import { Component, OnInit } from '@angular/core';
import { BucketService } from './bucket.service';
import { Observable } from 'rxjs/Rx';

@Component({
    selector: 'app-bucket',
    templateUrl: './bucket.component.html',
    styleUrls: ['./bucket.component.css'],
    providers: [BucketService]
})
export class BucketComponent implements OnInit {

    public buckets;

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

}
