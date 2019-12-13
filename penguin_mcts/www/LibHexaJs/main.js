import {Cell} from './cell.js';
import { Board } from './board.js';

let type = "WebGL"
if(!PIXI.utils.isWebGLSupported()){
  type = "canvas"
}

PIXI.utils.sayHello(type);


var c1 = new Cell(0,0,0,null);

console.log(c1.getRow());

var map = new Board();

//Add the canvas that Pixi automatically created for you to the HTML document
document.body.appendChild(map.pixiApp.view);