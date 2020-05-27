import { Component, OnInit } from '@angular/core';
import { HrefService } from 'src/app/services/href.service';

@Component({
  selector: 'app-documentation',
  templateUrl: './documentation.page.html',
  styleUrls: ['./documentation.page.scss'],
})
export class DocumentationPage implements OnInit {

  constructor(private hrefService: HrefService) { }

  ngOnInit() {
  }

  getUrl(url: string): string
  {    
    return this.hrefService.getUrl() + url;
  }

}
