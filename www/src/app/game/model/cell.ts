import { Pos } from './pos';

/**
*
* The cell object represents one map hex cell.
*/

export class Cell {
        row: number;
        column: number;
        center: Pos = {x: 0, y: 0};
        terrainIndex: number;
        poly: object;
        outline: object;
        inner: object;
        hex: object;
        isEmpty: boolean;
        isOver: boolean;
        alpha: number;
}
