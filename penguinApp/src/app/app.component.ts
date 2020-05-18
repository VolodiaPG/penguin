import { Component, OnInit } from '@angular/core';

import { Platform } from '@ionic/angular';
import { SplashScreen } from '@ionic-native/splash-screen/ngx';
import { StatusBar } from '@ionic-native/status-bar/ngx';

@Component({
  selector: 'app-root',
  templateUrl: 'app.component.html',
  styleUrls: ['app.component.scss']
})
export class AppComponent implements OnInit {
  public selectedIndex = 0;
  public appPages = [
    {
      title: 'Home',
      url: '/home',
      icon: 'home'
    },
    {
      title: 'Game',
      url: '/game',
      icon: 'cube'
    },
    {
      title: 'Team',
      url: '/team',
      icon: 'people'
    },
    {
      title: 'About',
      url: '/about',
      icon: 'bookmarks'
    }
  ];

  public isWeb = true;

  public darkTheme: boolean;

  constructor(
    private platform: Platform,
    private splashScreen: SplashScreen,
    private statusBar: StatusBar
  ) {
    if (window.matchMedia('(prefers-color-scheme)').media !== 'not all') {
      console.log('🎉 Dark mode is supported');
    }

    // Use matchMedia to check the user preference
    const prefersDark = window.matchMedia('(prefers-color-scheme: dark)');

    this.toggleDarkTheme(prefersDark.matches);

    // Listen for changes to the prefers-color-scheme media query
    prefersDark.addListener(mediaQuery => this.toggleDarkTheme(mediaQuery.matches));

    this.initializeApp();
  }

  initializeApp() {
    this.platform.ready().then(() => {
      this.statusBar.styleDefault();
      this.splashScreen.hide();
    });
  }

  ngOnInit() {
    const path = window.location.pathname.split('pages/')[1];
    if (path !== undefined) {
      this.selectedIndex = this.appPages.findIndex(page => page.title.toLowerCase() === path.toLowerCase());
    }
  }

  // Called when the app loads
  toggleDarkTheme(shouldAdd: boolean): void {
    this.darkTheme = shouldAdd;
    console.log('Dark Theme switch');
    document.body.classList.toggle('dark', shouldAdd);
  }

  toggleTheme(): void {
    console.log('Dark theme : ' + this.darkTheme);
    this.darkTheme = !this.darkTheme;
    this.toggleDarkTheme(this.darkTheme);
  }
}
