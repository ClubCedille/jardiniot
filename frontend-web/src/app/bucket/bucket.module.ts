import { NgModule } from '@angular/core';
import { BrowserModule }  from '@angular/platform-browser';
import { FormsModule } from '@angular/forms';
import { CommonModule } from '@angular/common';
import { HttpClientModule } from '@angular/common/http';
import { BucketService } from './bucket.service';
import { BucketComponent } from './bucket.component';

@NgModule({
    imports: [BrowserModule, FormsModule, CommonModule],
    exports: [BucketComponent],
    providers: [BucketService],
    declarations: [BucketComponent]
})
export class BucketModule { }
