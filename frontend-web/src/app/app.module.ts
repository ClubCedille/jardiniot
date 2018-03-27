import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppComponent } from './app.component';
import { BucketModule } from './bucket/bucket.module';

@NgModule({
    declarations: [
        AppComponent
    ],
    imports: [
        BrowserModule,
        BucketModule,
    ],
    providers: [],
    bootstrap: [AppComponent]
})
export class AppModule { }
