import {Cell} from './cell.js';
import { Board } from './board.js';

var map, board;
const canvas = document.getElementById('mycanvas');

map = new PIXI.Application({
  view: canvas,
  width: window.innerWidth,         // default: 800
  height: window.innerHeight,        // default: 600
  antialias: true,    // default: false
  transparent: true, // default: false
  resolution: 1,      // default: 1
  resizeTo: window
});

// Loader for the textures.
var loader = PIXI.Loader.shared;
loader.add("images/game/tileWater_full.png")
    .add("images/game/tileSnow.png")
    .on("progress", handleLoadProgress)
    .on("load", handleLoadAsset)
    .on("error", handleLoadError)
    .load(handleLoadComplete);

    console.log(PIXI.utils.TextureCache);


function setupPixiJs() {
  board = new Board(map, loader);
  
  // map.pixiApp.ticker.add(animate);
  // map.pixiApp.ticker.start();

}

function initPage() {
  setupPixiJs();
  board.generateCell();

  // console.log("Ordre du tableau : ");
  // for(var r = 0; r < map.cells.length ; r+=1) {
  //     for(var c = 0 ; c < map.cells[r].length ; c+=1) {
  //         console.log("Cell : (" + map.cells[r][c].row + "," + map.cells[r][c].column + ")");
  //     }
  // }
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

  initPage();
  // var img = new PIXI.Sprite(loader.resources.tileNormal.texture);
  // map.stage.addChild(img);
}



