// <reference path="vend/pixi.dev.js" />
// <reference path="HexPixiJs/scripts/hexpixi.js" />
(function (window) {
    'use strict';
    var hp = window.HexPixi;
    var map = null,
        stage = new hp.PIXI.Stage(0xe0e0e0),
        renderer = new hp.PIXI.autoDetectRenderer(1000, 500, { //555, 440
            antialiasing: false,
            transparent: false,
            resolution: 1
        });

    function onHexClick(m, cell) {
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
            showCoordinates: true,
            hexLineWidth: 2,
            hexLineColor: 0xd0d0d0,
            hexWidth: 65,
            hexHeight: 65,
            hexBottomPad: 24,
            onHexClick: onHexClick,
            textures: [
                "images/game/tileSnow.png",
                "images/game/tileWater_full.png"
            ],
            terrainTypes: [
                { name: "empty", color: 0xffffff, isEmpty: true },
                { name: "snow", tileIndex: 0, color: 0xe2e2fa }
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
        map.generateMap(1);

        console.log(map.cells[4].length);
    }

    window.requestAnimFrame = (function(callback) {
        return window.requestAnimationFrame || window.webkitRequestAnimationFrame || window.mozRequestAnimationFrame || window.oRequestAnimationFrame || window.msRequestAnimationFrame || function(callback) {
            window.setTimeout(callback, 1000 / 60);
        };
    })();

    initPage();

}(window));
