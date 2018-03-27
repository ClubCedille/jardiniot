import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { BucketComponent } from './bucket.component';

@NgModule({
    imports: [
        CommonModule
    ], exports: [ 
        BucketComponent
    ],
    declarations: [BucketComponent]
})
export class BucketModule { }
