import {
    Machine,
    State,
    actions,
    assign,
    send,
    sendParent,
    interpret,
    spawn,
    MachineConfig
} from 'xstate';

type GameEvent =
    | { type: 'PENGUINSELECTED' }
    | { type: 'CELLSELECTED' }
    | { type: 'FINISHED' }
    | { type: 'PLAYERSWITCHED' }
    | { type: 'WAITING' };

interface GameStateSchema {
    states: {
        waiting: {};
        penguinSelected: {};
        movePerformed: {};
        gameFinished: {};
        playerSwitched: {};
    };
}

interface GameContext {
    count: number;
}


export const gameMachine = Machine<GameContext, GameStateSchema, GameEvent>(
  {
    id: 'gameLogic',
    initial: 'waiting',
    context: {
        count: 0
      },
    states: {
        waiting: {
            on: {
                PENGUINSELECTED: 'penguinSelected',
                CELLSELECTED: 'waiting'
            }
        },
        penguinSelected: {
            on: {
                PENGUINSELECTED: 'waiting',
                CELLSELECTED: 'movePerformed'
            }
        },
        movePerformed: {
            on: {
                FINISHED: 'gameFinished',
                PLAYERSWITCHED: 'playerSwitched'
            }
        },
        gameFinished: {
            type: 'final'
        },
        playerSwitched: {
            on: {
                WAITING: 'waiting'
            }
        }
    }
});

export const gameService = interpret(gameMachine);