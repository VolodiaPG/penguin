function _classCallCheck(n,t){if(!(n instanceof t))throw new TypeError("Cannot call a class as a function")}function _defineProperties(n,t){for(var e=0;e<t.length;e++){var o=t[e];o.enumerable=o.enumerable||!1,o.configurable=!0,"value"in o&&(o.writable=!0),Object.defineProperty(n,o.key,o)}}function _createClass(n,t,e){return t&&_defineProperties(n.prototype,t),e&&_defineProperties(n,e),n}(window.webpackJsonp=window.webpackJsonp||[]).push([[18],{CfhG:function(n,t,e){"use strict";e.r(t),e.d(t,"DocumentationPageModule",(function(){return d}));var o,i,c,r,a=e("ofXK"),b=e("3Pt+"),l=e("TEn/"),s=e("tyNb"),u=e("fXoL"),f=((o=function(){function n(t,e){_classCallCheck(this,n),this.document=t,this.locationStrategy=e}return _createClass(n,[{key:"getUrl",value:function(){return"".concat(this.document.location.origin,"/").concat(this.locationStrategy.getBaseHref())}}]),n}()).\u0275fac=function(n){return new(n||o)(u.Sb(a.c),u.Sb(a.g))},o.\u0275prov=u.Fb({token:o,factory:o.\u0275fac,providedIn:"root"}),o),h=[{path:"",component:(i=function(){function n(t){_classCallCheck(this,n),this.hrefService=t}return _createClass(n,[{key:"ngOnInit",value:function(){}},{key:"getUrl",value:function(n){return this.hrefService.getUrl()+n}}]),n}(),i.\u0275fac=function(n){return new(n||i)(u.Jb(f))},i.\u0275cmp=u.Db({type:i,selectors:[["app-documentation"]],decls:32,vars:2,consts:[["color","primary"],["slot","start"],["translate",""],["target","_blank",3,"href"]],template:function(n,t){1&n&&(u.Ob(0,"ion-header"),u.Ob(1,"ion-toolbar",0),u.Ob(2,"ion-buttons",1),u.Kb(3,"ion-menu-button"),u.Nb(),u.Ob(4,"ion-title"),u.Ob(5,"span",2),u.lc(6,"Documentation"),u.Nb(),u.Nb(),u.Nb(),u.Nb(),u.Ob(7,"ion-content"),u.Ob(8,"ion-grid"),u.Ob(9,"ion-row"),u.Ob(10,"ion-col"),u.Ob(11,"ion-card"),u.Ob(12,"ion-header"),u.Ob(13,"ion-title"),u.lc(14," Compodoc "),u.Nb(),u.Nb(),u.Ob(15,"ion-card-content"),u.Ob(16,"p"),u.lc(17,"This is the "),u.Ob(18,"a",3),u.lc(19,"documentation"),u.Nb(),u.lc(20," of the code of the Ionic Application you are currently experiencing"),u.Nb(),u.Nb(),u.Nb(),u.Nb(),u.Ob(21,"ion-col"),u.Ob(22,"ion-card"),u.Ob(23,"ion-header"),u.Ob(24,"ion-title"),u.lc(25," Doxygen "),u.Nb(),u.Nb(),u.Ob(26,"ion-card-content"),u.Ob(27,"p"),u.lc(28,"This is the "),u.Ob(29,"a",3),u.lc(30,"documentation"),u.Nb(),u.lc(31," of the code of the C++ part of the Application"),u.Nb(),u.Nb(),u.Nb(),u.Nb(),u.Nb(),u.Nb(),u.Nb()),2&n&&(u.zb(18),u.bc("href",t.getUrl("compodoc/index.html"),u.gc),u.zb(11),u.bc("href",t.getUrl("doxygen/index.html"),u.gc))},directives:[l.q,l.K,l.h,l.y,l.I,l.o,l.p,l.D,l.n,l.i,l.j],styles:[""]}),i)}],p=((r=function n(){_classCallCheck(this,n)}).\u0275mod=u.Hb({type:r}),r.\u0275inj=u.Gb({factory:function(n){return new(n||r)},imports:[[s.i.forChild(h)],s.i]}),r),d=((c=function n(){_classCallCheck(this,n)}).\u0275mod=u.Hb({type:c}),c.\u0275inj=u.Gb({factory:function(n){return new(n||c)},imports:[[a.b,b.a,l.L,p]]}),c)}}]);