import {Cell} from './cell.js';
import { Board } from './board.js';

var map;

function setupPixiJs() {
  
  map = new Board();

  // add the renderer view element to the DOM
  var div = document.getElementById('stage');

  //Add the canvas that Pixi automatically created for you to the HTML document
  div.appendChild(map.pixiApp.view);
}

function initPage() {
  setupPixiJs();
  map.generateMap(2);

  console.log("Ordre du tableau : ");

  for(var r = 0; r < map.cells.length ; r+=1) {
      for(var c = 0 ; c < map.cells[r].length ; c+=1) {
          console.log("Cell : (" + map.cells[r][c].row + "," + map.cells[r][c].column + ")");
      }
  }

  map.setCellTerrainType(map.cells[1][1], 1);
}

initPage();



