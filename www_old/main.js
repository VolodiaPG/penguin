import {Cell} from './cell.js';
import { Board } from './board.js';
import { Penguin } from './penguin.js';

var map, board, penguin, penguin2;
const canvas = document.getElementById('mycanvas');

// Create our application instance
map = new PIXI.Application({
  view: canvas,
  width: window.innerWidth,         // default: 800
  height: window.innerHeight,        // default: 600
  antialias: true,    // default: false
  transparent: false, // default: false
  resolution: 1,      // default: 1
  resizeTo: window
});

// Loader for the textures.
var loader = PIXI.Loader.shared;
loader.add("images/game/tileSnow_fish1.png")
    .add("images/game/tileSnow_fish2.png")
    .add("images/game/tileSnow_fish3.png")
    .add("images/game/tileWater_fish1.png")
    .add("images/game/tileWater_fish2.png")
    .add("images/game/tileWater_fish3.png")
    .add("images/penguin.png")
    .add("images/water.png")
    .on("progress", handleLoadProgress)
    .on("load", handleLoadAsset)
    .on("error", handleLoadError)
    .load(handleLoadComplete);

    console.log(PIXI.utils.TextureCache);



function setupPixiJs() {

  board = new Board(map, loader);

  board.generateRandomMap();

  // console.log("Ordre du tableau : ");
  // for(var r = 0; r < board.cells.length ; r+=1) {
  //     for(var c = 0 ; c < board.cells[r].length ; c+=1) {
  //         console.log("Cell : (" + board.cells[r][c].row + "," + board.cells[r][c].column + ")");
  //     }
  // }

  board.pixiApp.ticker.add(animate);

  penguin = new Penguin(board, loader, board.cells[2][2]);
  penguin2 = new Penguin(board, loader, board.cells[5][5]);

  board.pixiApp.stage.addChild(penguin.sprite);
  board.pixiApp.stage.addChild(penguin2.sprite);
}

let delta = 0;
function animate() {
  delta += 0.1;
  if(penguin.isOver){
    penguin.uniforms.delta = 0.5 + Math.sin(delta) * 0.5;
    penguin.sprite.y = penguin.sprite.y + Math.sin(delta) * 0.2;
  }
  if(penguin2.isOver){
    penguin2.uniforms.delta = 0.5 + Math.sin(delta) * 0.5;
    penguin2.sprite.y = penguin2.sprite.y + Math.sin(delta) * 0.2;
  }
}

function handleLoadProgress(loader, resource) {
  console.log(loader.progress + "% loaded");
}
function handleLoadAsset(loader, resource) {
  console.log("asset loaded " + resource.name);
}
function handleLoadError() {
  console.error("load error");
}
function handleLoadComplete() {
  console.log("Load completed");

  setupPixiJs();


}



