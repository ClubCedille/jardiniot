import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { AppComponent } from './app.component';
import { BucketComponent } from './bucket/bucket.component';
import { BucketDetailComponent } from './bucket-detail/bucket-detail.component';

const routes: Routes = [
    {
        path: '',
        redirectTo:'buckets',
        pathMatch: 'full'
    },
    {
        path: 'buckets',
        component: BucketComponent,
        children: [{
            path:':id',
            component: BucketDetailComponent,
        }]
    }
];

@NgModule({
    imports: [RouterModule.forRoot(routes)],
    exports: [RouterModule]
})
export class AppRoutingModule { }
