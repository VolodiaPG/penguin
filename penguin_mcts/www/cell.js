/**
*
* The HexPixi.Cell object represents one map hex cell.
*/
export class Cell {

    constructor(rowNo, columnNo, terrainIndex) {
        this.row = rowNo;
        this.column = columnNo;
        this.center = { x: 0, y: 0 };
        this.terrainIndex = terrainIndex ? terrainIndex : 0;
        this.poly = null; // The cell's poly that is used as a hit area.
        this.outline = null; // The PIXI.Graphics outline of the cell's hex.
        this.inner = []; // If a non-textured cell then this is the PIXI.Graphics of the hex inner, otherwise a PIXI.Sprite.
        this.hex = null; // The parent container of the hex's graphics objects.
        this.isEmpty = false; // The cell is empty if set to true.
        this.isOver = false;
        this.alpha = 1;
    }

    resetGraphics() {
        this.terrainIndex = 0;
        this.poly = null; // The cell's poly that is used as a hit area.
        this.outline = null; // The PIXI.Graphics outline of the cell's hex.
        this.inner = null; // If a non-textured cell then this is the PIXI.Graphics of the hex inner.
        this.hex = null; // The parent container of the hex's graphics objects.
    }

    
    onCellClick(map) {
        var r, c;
        console.log("Cell selected : (" + this.row + "," + this.column + ")");
        
     
        // //diago droite
        // var cellX = cell.column - (cell.row + (cell.row & 1)) / 2;
      
        // //ligne
        // var cellZ = cell.row;
      
        // //diago gauche
        // var cellY = - cellX - cellZ;
      
        // for(var r = 0; r < m.cells.length ; r+=1) {
        //     for(var c = 0 ; c < m.cells[r].length ; c+=1) {
        //         var tempX = m.cells[r][c].column - (m.cells[r][c].row + (m.cells[r][c].row & 1)) / 2;
        //         var tempZ = m.cells[r][c].row;
        //         var tempY = - tempX - tempZ;
      
        //         if ((tempX == cellX) || (tempY == cellY) || (tempZ == cellZ)){
        //             m.setCellTerrainType(m.cells[r][c], 1);
        //         }
      
        //     }
        // }     
    }

    onCellHover(map) {
        this.isOver = true;
        console.log("Cell Hover : (" + this.row + "," + this.column + ")");
        this.updateColorOutline(map.hexLineColorSelected);
    }

    onCellOut(map) {   
        this.isOver = false;
        this.updateColorOutline(map.hexLineColor);
    }

    updateColorOutline(color){   
        var len = this.outline.geometry.graphicsData.length;    
        for (var i = 0; i < len; i++) {        
          var data = this.outline.geometry.graphicsData[i];
          data.lineStyle.color = color;     
        }  
        this.outline.geometry.invalidate();  
      };

}


