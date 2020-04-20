import { Machine, interpret } from 'xstate';

export const gameMachine = Machine(
  {
    id: 'gameLogic',
    initial: 'moveBlocked',
    context: {
      count: 0
    },
    states: {
      moveBlocked: {
        on: {
          HUMANTURN: {
            target: 'waiting',
            actions: ['notifyHumanTurn']
          }
        }
      },
      waiting: {
        on: {
          PENGUINSELECTED: {
            target: 'penguinSelected',
            actions: ['notifyPenguinSelected']
          },
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
          SWITCHPLAYER: 'playerSwitched'
        }
      },
      gameFinished: {
        type: 'final'
      },
      playerSwitched: {
        on: {
          PLAYERSWITCHED: 'moveBlocked'
        }
      }
    }
  },
  {
    actions: {
      notifyHumanTurn: (context, event) => {
        console.log('It is your turn !');
      },
      notifyPenguinSelected: (context, event) => {
        console.log('Select a cell to move this penguin !');
      }
    }
  }
);

export const gameService = interpret(gameMachine)
  .onTransition(state => {
    console.log(state.toStrings());
  })
  .onDone(() => console.log('done'))
  .start(); // returns started service
