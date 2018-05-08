import { Component, OnInit } from '@angular/core';
import { Bucket } from '../bucket/bucket';
import { ActivatedRoute } from '@angular/router';
import { BucketDetailService } from './bucket-detail.service';

@Component({
    selector: 'app-bucket-detail',
    templateUrl: './bucket-detail.component.html',
    styleUrls: ['./bucket-detail.component.css'],
    providers: [BucketDetailService]
})
export class BucketDetailComponent implements OnInit {

    id: number;
    public bucket;
    private sub: any;


    constructor(private bucketDetailService: BucketDetailService,
                private route: ActivatedRoute) { }

    ngOnInit() {
        this.sub = this.route.params.subscribe(params => {
            this.id = +params['id'];
        });
        this.getBucket(this.id);
    }

    getBucket(id: number){
        this.bucketDetailService.getBucket(this.id).subscribe(
            data => {this.bucket = data},
            err => console.error(err),
            () => console.log('done loading bucket ' + this.bucket.name)
        );
    }



}
