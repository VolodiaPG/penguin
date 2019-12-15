/**
*
* The HexPixi.Cell object represents one map hex cell.
*/
export class Penguin {

    constructor(map, loader, rowNo, columnNo) {
        this.row = rowNo;
        this.column = columnNo;
        this.cellPosition = map.cells[this.row][this.column];
        this.center = map.getCellCenter(this.row, this.column);
        this.sprite = new PIXI.Sprite(loader.resources["images/penguin.png"].texture);

        // center the penguins's anchor point
        this.sprite.anchor.set(0.5);

        this.sprite.scale.set(0.16);
        // this.sprite.width = map.hexWidth / 1.2;
        // this.sprite.height = map.hexHeight / 1.2;

        this.sprite.position.set(this.center.x, this.center.y);


        this.sprite.interactive = true;
        this.sprite.buttonMode = true;
        this.sprite.dragging = false;
        // setup events for mouse + touch using
        // the pointer events
        this.sprite.on('pointerover', (event) => {this.onPenguinHover(map)})
                   .on('pointerout', (event) => {this.onPenguinOut(map)})
                   .on('pointerdown', (event) => {this.onDragStart(event, map)})
                   .on('pointermove', (event) => {this.onDragMove(map)})
                   .on('pointerup', (event) => {this.onDragEnd(map)})
                   .on('pointerupoutside', (event) => {this.onDragEnd(map)})
                   ;

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
         
        map.setDiagoSelectedTexture(map.cells[this.row][this.column], true, 1);

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

        map.setDiagoSelectedTexture(map.cells[this.row][this.column], true, 0.75);
    }

    onPenguinOut(map) {   
        this.isOver = false;
        this.sprite.position.set(this.center.x, this.center.y);
        this.sprite.alpha = 1;
        this.sprite.filters = [];

        map.setDiagoSelectedTexture(map.cells[this.row][this.column], false, 1);
    }

    onDragStart(event, map) {
        // store a reference to the data
        // the reason for this is because of multitouch
        // we want to track the movement of this particular touch
        // this.sprite.data = event.data;
        this.sprite.alpha = 0.75;
        // this.sprite.dragging = true;

        map.setDiagoSelectedTexture(map.cells[this.row][this.column], true, 1);
    }
    
    onDragEnd(map) {
        this.sprite.alpha = 1;
        // this.sprite.dragging = false;
        // set the interaction data to null
        this.sprite.data = null;
    }
    
    onDragMove(map) {
            var newCellPosition = map.getCellHover();

            if(newCellPosition !== null){
                this.cellPosition = newCellPosition;
                const newPosition = this.cellPosition.getCellCenter();
                this.sprite.x = newPosition.x;
                this.sprite.y = newPosition.y;
            } else {

            }

            // const newPosition = this.sprite.data.getLocalPosition(this.sprite.parent);
             
    }
    

}