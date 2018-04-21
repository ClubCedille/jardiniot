import { Component, OnInit, Input } from '@angular/core';
import { Bucket } from '../bucket/bucket';

@Component({
    selector: 'app-bucket-detail',
    templateUrl: './bucket-detail.component.html',
    styleUrls: ['./bucket-detail.component.css']
})
export class BucketDetailComponent implements OnInit {

    @Input() bucket: Bucket;

    constructor() { }

    ngOnInit() {
    }

    function select(bucket) {
        alert("test");
    }

}
