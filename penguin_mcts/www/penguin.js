/**
*
* The HexPixi.Cell object represents one map hex cell.
*/
export class Penguin {

    constructor(map, loader, rowNo, columnNo) {
        this.row = rowNo;
        this.column = columnNo;
        this.center = map.getCellCenter(this.row, this.column);
        this.sprite = new PIXI.Sprite(loader.resources["images/penguin.png"].texture);

        this.sprite.width = map.hexWidth / 1.2;
        this.sprite.height = map.hexHeight / 1.2;

        this.sprite.x = this.center.x - this.sprite.width / 2;
        this.sprite.y = this.center.y - this.sprite.height / 2;

        this.sprite.interactive = true;
        this.sprite.buttonMode = true;
        this.sprite.on('click', (event) => {this.onPenguinClick(map)})
                       .on('pointerover', (event) => {this.onPenguinHover(map)})
                       .on('pointerout', (event) => {this.onPenguinOut(map)});



        this.poly = null; // The cell's poly that is used as a hit area.
        this.outline = null; // The PIXI.Graphics outline of the cell's hex.
        this.inner = []; // If a non-textured cell then this is the PIXI.Graphics of the hex inner, otherwise a PIXI.Sprite.
        this.hex = null; // The parent container of the hex's graphics objects.
        this.isOver = false;

        this.uniforms = {delta: 0};
    }


    
    onPenguinClick(map) {
        var r, c;
        console.log("Pos Penguin selected : (" + this.row + "," + this.column + ")");
         
        //diago droite
        var cellX = this.column - (this.row + (this.row & 1)) / 2;
      
        //ligne
        var cellZ = this.row;
      
        //diago gauche
        var cellY = - cellX - cellZ;
      
        for(var r = 0; r < map.cells.length ; r+=1) {
            for(var c = 0 ; c < map.cells[r].length ; c+=1) {
                var tempX = map.cells[r][c].column - (map.cells[r][c].row + (map.cells[r][c].row & 1)) / 2;
                var tempZ = map.cells[r][c].row;
                var tempY = - tempX - tempZ;
      
                if ((tempX == cellX) || (tempY == cellY) || (tempZ == cellZ)){
                    map.setCellSelectedTexture(map.cells[r][c], true);
                }
      
            }
        }

    }

    onPenguinHover(map) {
        this.isOver = true;
    
        // pixi.js/packages/core/src/fragments/default.vert
        var vertexShader = `
            attribute vec2 aVertexPosition;
            attribute vec2 aTextureCoord;
            uniform mat3 projectionMatrix;
            varying vec2 vTextureCoord;
            void main(void)
            {
                gl_Position = vec4((projectionMatrix * vec3(aVertexPosition, 1.0)).xy, 0.0, 1.0);
                vTextureCoord = aTextureCoord;
            }`

        var fragmentShader = `
            varying vec2 vTextureCoord;
            uniform sampler2D uSampler;
            uniform float delta;
            void main(void)
            {
                vec4 color = texture2D(uSampler, vTextureCoord);
                if (color.a != 0.0){
                    color.r = delta;
                    color.g -= delta;
                    color.b -= delta;
                }
                gl_FragColor = color;
            }`

        const myFilter = new PIXI.Filter(vertexShader, fragmentShader, this.uniforms);

            
        this.sprite.filters = [myFilter];
    }

    onPenguinOut(map) {   
        this.isOver = false;
        this.sprite.x = this.center.x - this.sprite.width / 2;
        this.sprite.y = this.center.y - this.sprite.height / 2;
        this.sprite.filters = [];
    }

}