
/**
 * Pre defined here to be used later
 */
var init;

var initWrappers = () =>
{
    console.log("Initializing wrappers...");

    /**
     * Creates the global c++ side game instance
     * 
     * @returns {number} an exit value
     */
    var initGame = Module.cwrap('initGame', 'number', []);


    /**
     * Deletes the global c++ side game instance
     */
    var deleteGame = Module.cwrap('deleteGame', 'undefined', []);

    /**
     * Gets the next player Id 
     * 
     * @returns {number} the id
     */
    var getPlayerToPlayId = Module.cwrap('getPlayerToPlay', 'number', []);

    /**
     * Returns the current status of the game : the id of the player who won, 0 if nothing, -1 if draw
     * 
     * @returns {number}
     */
    var checkGameStatus = Module.cwrap('checkStatus', 'number', []);

    /**
     * play the player1
     * @param {number} row the row
     * @param {number} col the col
     * 
     * @returns {void}
     */
    var play = Module.cwrap('play', 'undefined', ['number', 'number']);

    /**
     * Plays the player 2 (computer)
     * 
     * @returns {number} the played cell's id
     */
    var mctsResult = Module.cwrap('mctsResult', 'number', []);

    console.log("Wrappers initialized");

    /**
    * Size of the board
    */
    var N_SIZE = 3;

    /**
     * First turn
     */
    var turn = 'X';

    /**
     * defines an empty cell
     */
    var EMPTY = '&nbsp;';

    /**
     * List of cells
     */
    var cells = [];

    /**
     * Transforms a turn into a status
     * @param {string} turn the turn : 'X' or 'O'
     * @returns {number} the turn
     */
    var statusFromTurn = (turn) => turn === 'X' ? 1 : 2;

    /**
     * Transforms the status into a turn
     * @param {number} status the status
     * @returns {string} the turn
     */
    var turnFromStatus = (status) => status === 1 ? 'X' : 'O';

    init = () =>
    {
        var board = document.createElement('table');
        board.setAttribute('border', 1);
        board.setAttribute('cellspacing', 0);

        var identifier = 0;
        for (var i = 0; i < N_SIZE; i++)
        {
            var row = document.createElement('tr');
            board.appendChild(row);
            for (var j = 0; j < N_SIZE; j++)
            {
                var td = document.createElement('td');
                var cell = document.createElement('div');
                var content = document.createElement('div');
                td.setAttribute('height', 120);
                td.setAttribute('width', 120);
                td.setAttribute('align', 'center');
                td.setAttribute('valign', 'center');

                td.classList.add('cell');
                cell.classList.add('cell-child');
                content.classList.add('cell-child-content');

                // if (i == j)
                // {
                //     cell.classList.add('diagonal0');
                // }
                // if (j == N_SIZE - i - 1)
                // {
                //     cell.classList.add('diagonal1');
                // }
                // cell.identifier = identifier;
                content.setAttribute('identifier', identifier);
                content.onclick = setOnEvent;
                cells.push(content);

                cell.appendChild(content);
                td.appendChild(cell);
                row.appendChild(td);

                identifier++;

            }
        }

        document.getElementById('tictactoe').appendChild(board);
        startNewGame();
    }

    var startNewGame = () =>
    {
        deleteGame();
        initGame();
        turn = 'X';
        cells.forEach(el =>
        {
            el.innerHTML = EMPTY;
            el.classList.remove('highlight-victory');
        });
        document.getElementById('turn').textContent = 'Player ' + turn;
        document.getElementById('hidden').style.display = 'none';
    }

    var getCellByIdentifier = (identifier) =>
    {
        for (let ii = 0; ii < cells.length; ++ii)
        {
            if (parseInt(cells[ii].getAttribute('identifier')) === parseInt(identifier))
            {
                console.log(cells[ii]);

                return cells[ii];
            }
        }
        return undefined;
    }

    var setOnEvent = (event) =>
    {
        let identifier = event.srcElement.getAttribute('identifier');
        console.log(`Clicked cell #${identifier}`);

        set(identifier);
    }

    var set = (identifier) =>
    {
        var self = getCellByIdentifier(identifier);

        if (!self || self.innerHTML !== EMPTY)
        {
            return;
        }

        self.innerHTML = turn;

        let row = parseInt(identifier / 3);
        let col = parseInt(identifier % 3);

        play(row, col);

        // flip the turns
        turn = turn === 'X' ? 'O' : 'X';
        document.getElementById('turn').textContent = 'Player ' + turn;

        let status = checkGameStatus();
        console.log(status);

        if (status > 0)
        { // A player won
            //alert(`Player ${turnFromStatus(status)} won!`);
            searchCombinaison(turnFromStatus(status));
            document.getElementById('hidden').style.display = 'block';
            document.getElementById('turn').textContent = 'Player ' + turnFromStatus(status) + ' won !';
            document.getElementById('playAgain').onclick = startNewGame;

        } else if (status < 0)
        { // draw
            document.getElementById('hidden').style.display = 'block';
            document.getElementById('turn').textContent = 'Draw !';
            document.getElementById('playAgain').onclick = startNewGame;
        } else
        { // nothing yet
            console.log(`Playing player #${getPlayerToPlayId()}`);
            // play player2
            if (getPlayerToPlayId() === 2)
            {
                let cellId = mctsResult();
                console.log(`Advised Cell #${cellId}`);

                set(cellId);
            }
        }
    }

    var searchCombinaison = (turn) => 
    {        
        if (cells[0].innerHTML == turn &&
            cells[1].innerHTML == turn &&
            cells[2].innerHTML == turn)
        {
            cells[0].parentElement.classList.add('highlight-victory');
            cells[1].parentElement.classList.add('highlight-victory');
            cells[2].parentElement.classList.add('highlight-victory');
        }

        if (cells[3].innerHTML == turn &&
            cells[4].innerHTML == turn &&
            cells[5].innerHTML == turn)
        {
            cells[3].parentElement.classList.add('highlight-victory');
            cells[4].parentElement.classList.add('highlight-victory');
            cells[5].parentElement.classList.add('highlight-victory');
        }

        if (cells[6].innerHTML == turn &&
            cells[7].innerHTML == turn &&
            cells[8].innerHTML == turn)
        {
            cells[6].parentElement.classList.add('highlight-victory');
            cells[7].parentElement.classList.add('highlight-victory');
            cells[8].parentElement.classList.add('highlight-victory');
        }

        if (cells[0].innerHTML == turn &&
            cells[3].innerHTML == turn &&
            cells[6].innerHTML == turn)
        {
            cells[0].parentElement.classList.add('highlight-victory');
            cells[3].parentElement.classList.add('highlight-victory');
            cells[6].parentElement.classList.add('highlight-victory');
        }

        if (cells[1].innerHTML == turn &&
            cells[4].innerHTML == turn &&
            cells[7].innerHTML == turn)
        {
            cells[1].parentElement.classList.add('highlight-victory');
            cells[4].parentElement.classList.add('highlight-victory');
            cells[7].parentElement.classList.add('highlight-victory');
        }

        if (cells[2].innerHTML == turn &&
            cells[5].innerHTML == turn &&
            cells[8].innerHTML == turn)
        {
            cells[2].parentElement.classList.add('highlight-victory');
            cells[5].parentElement.classList.add('highlight-victory');
            cells[8].parentElement.classList.add('highlight-victory');
        }

        if (cells[0].innerHTML == turn &&
            cells[4].innerHTML == turn &&
            cells[8].innerHTML == turn)
        {
            cells[0].parentElement.classList.add('highlight-victory');
            cells[4].parentElement.classList.add('highlight-victory');
            cells[8].parentElement.classList.add('highlight-victory');
        }

        if (cells[2].innerHTML == turn &&
            cells[4].innerHTML == turn &&
            cells[6].innerHTML == turn)
        {
            cells[2].parentElement.classList.add('highlight-victory');
            cells[4].parentElement.classList.add('highlight-victory');
            cells[6].parentElement.classList.add('highlight-victory');
        }
        multipleVictory.update();
    }
}

