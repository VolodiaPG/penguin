import { Application } from 'pixi.js';

import { Pos } from './pos';
import { Board } from './board';

/**
*
* The cell object represents one map hex cell.
*/

export class Cell {
        row: number;
        column: number;
        center: Pos = { x: 0, y: 0 };

        terrainIndex: number;

        poly: any;
        hitPoly: any;
        outline: any;
        inner: any;
        hex: any;

        isEmpty: boolean;
        isOver: boolean;
        alpha: number;

        constructor(row: number, column: number, terrainIndex: number) {
                this.row = row;
                this.column = column;
                if (terrainIndex === -1) {
                        this.isEmpty = true;
                } else {
                        this.terrainIndex = terrainIndex ? terrainIndex : 0;
                }
        }

        resetGraphics() {
                this.terrainIndex = 0;
                this.poly = null; // The cell's poly that is used as a hit area.
                this.outline = null; // The PIXI.Graphics outline of the cell's hex.
                this.inner = null; // If a non-textured cell then this is the PIXI.Graphics of the hex inner.
                this.hex = null; // The parent container of the hex's graphics objects.
        }


        onCellClick(map: Board) {
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

        onCellHover(map: Board) {
                this.isOver = true;
                // console.log("Cell Hover : (" + this.row + "," + this.column + ")");
                this.updateColorOutline(map.hexLineColorSelected);
        }

        onCellOut(map: Board) {
                this.isOver = false;
                this.updateColorOutline(map.hexLineColor);
        }

        updateColorOutline(color: number) {
                var len = this.outline.geometry.graphicsData.length;
                for (var i = 0; i < len; i++) {
                        var data = this.outline.geometry.graphicsData[i];
                        data.lineStyle.color = color;
                }
                this.outline.geometry.invalidate();
        };

}
