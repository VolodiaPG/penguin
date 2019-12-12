// <reference path="pixi/pixi.min.js" />
// <reference path="HexPixiJs/scripts/hexpixi.js" />
(function (window) {
    'use strict';
    var hp = window.HexPixi;
    var map = null,
        stage = new hp.PIXI.Stage(0x061639),
        renderer = new hp.PIXI.autoDetectRenderer(520, 430, { //520, 430
            antialiasing: false,
            transparent: true,
            resolution: 1
        });

    function onHexClick(m, cell) {
        var r, c;
        console.log("Cell selected : (" + cell.row + "," + cell.column + ")");
        
        for(c = 0; c < map.cells[cell.row].length ; c+=1) {
            // console.log("Cell row : (" + map.cells[cell.row][c].row + "," + map.cells[cell.row][c].column + ")")
            map.setCellTerrainType(map.cells[cell.row][c], 1);
        }

        //diago droite
        var cellX = cell.column - (cell.row + (cell.row & 1)) / 2;

        //ligne
        var cellZ = cell.row;

        //diago gauche
        var cellY = - cellX - cellZ;

        for(var r = 0; r < map.cells.length ; r+=1) {
            for(var c = 0 ; c < map.cells[r].length ; c+=1) {
                var tempX = map.cells[r][c].column - (map.cells[r][c].row + (map.cells[r][c].row & 1)) / 2;
                var tempZ = map.cells[r][c].row;
                var tempY = - tempX - tempZ;

                if ((tempX == cellX) || (tempY == cellY) || (tempZ == cellZ)){
                    map.setCellTerrainType(map.cells[r][c], 1);
                }

            }
        }

        map.setCellTerrainType(cell, 0);

    }

    function animate() {
        requestAnimFrame(animate);
        // render the stage
        renderer.render(stage);
    }

    function getOptions() {
        return {
            mapWidth: 8,
            mapHeight: 8,
            coordinateSystem: 3,
            // showCoordinates: true,
            hexLineWidth: 2,
            hexLineColor: 0xd0d0d0,
            hexWidth: 65,
            hexHeight: 65,
            hexBottomPad: 24,
            onHexClick: onHexClick,
            textures: [
                "images/game/tileStone_full.png",
                "images/game/tileSnow.png",
            ],
            terrainTypes: [
                { name: "empty", color: 0xffffff, isEmpty: true },
                { name: "stone", tileIndex: 0, color: 0x808080 },
                { name: "snow", tileIndex: 1, color: 0xe2e2fa }
            ],
            onAssetsLoaded: function () { requestAnimFrame(animate); }
        };
    }


    function setupPixiJs() {
        // add the renderer view element to the DOM
        var div = document.getElementById('stage');
        div.appendChild(renderer.view);

        map = new hp.Map(stage, getOptions());
    }

    function initPage() {
        setupPixiJs();
        map.generateMap(2);

        // console.log("Ordre du tableau : ");

        // for(var r = 0; r < map.cells.length ; r+=1) {
        //     for(var c = 0 ; c < map.cells[r].length ; c+=1) {
        //         console.log("Cell : (" + map.cells[r][c].row + "," + map.cells[r][c].column + ")");
        //     }
        // }
    }

    window.requestAnimFrame = (function(callback) {
        return window.requestAnimationFrame || window.webkitRequestAnimationFrame || window.mozRequestAnimationFrame || window.oRequestAnimationFrame || window.msRequestAnimationFrame || function(callback) {
            window.setTimeout(callback, 1000 / 60);
        };
    })();

    initPage();

}(window));
