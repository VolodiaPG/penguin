/**
*
* The HexPixi.Cell object represents one map hex cell.
*/
export class Cell {

    constructor(rowNo, columnNo, terrainIndex, cellData) {
        this.row = rowNo;
        this.column = columnNo;
        this.center = { x: 0, y: 0 };
        this.terrainIndex = terrainIndex ? terrainIndex : 0;
        this.poly = null; // The cell's poly that is used as a hit area.
        this.outline = null; // The PIXI.Graphics outline of the cell's hex.
        this.inner = []; // If a non-textured cell then this is the PIXI.Graphics of the hex inner, otherwise a PIXI.Sprite.
        this.hex = null; // The parent container of the hex's graphics objects.
        this.isEmpty = false; // The cell is empty if set to true.
        this.data = cellData;
        this.isOver = false;
    }

    getRow() {
        return this.row;
    }

    resetGraphics() {
        this.terrainIndex = 0;
        this.poly = null; // The cell's poly that is used as a hit area.
        this.outline = null; // The PIXI.Graphics outline of the cell's hex.
        this.inner = null; // If a non-textured cell then this is the PIXI.Graphics of the hex inner.
        this.hex = null; // The parent container of the hex's graphics objects.
    }

    onHexClick(m, cell) {
        var r, c;
        console.log("Cell selected : (" + cell.row + "," + cell.column + ")");
        
        for(c = 0; c < m.cells[cell.row].length ; c+=1) {
            // console.log("Cell row : (" + map.cells[cell.row][c].row + "," + map.cells[cell.row][c].column + ")")
            m.setCellTerrainType(m.cells[cell.row][c], 1);
        }
      
        //diago droite
        var cellX = cell.column - (cell.row + (cell.row & 1)) / 2;
      
        //ligne
        var cellZ = cell.row;
      
        //diago gauche
        var cellY = - cellX - cellZ;
      
        for(var r = 0; r < m.cells.length ; r+=1) {
            for(var c = 0 ; c < m.cells[r].length ; c+=1) {
                var tempX = m.cells[r][c].column - (m.cells[r][c].row + (m.cells[r][c].row & 1)) / 2;
                var tempZ = m.cells[r][c].row;
                var tempY = - tempX - tempZ;
      
                if ((tempX == cellX) || (tempY == cellY) || (tempZ == cellZ)){
                    m.setCellTerrainType(m.cells[r][c], 1);
                }
      
            }
        }
      
        m.setCellTerrainType(cell, 0);
      
    }

}


