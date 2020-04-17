import { Machine, interpret } from 'xstate';

export const gameMachine = Machine(
  {
    id: 'gameLogic',
    initial: 'waiting',
    context: {
      count: 0
    },
    states: {
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
  },
  {
    actions: {
      notifyPenguinSelected: (context, event) => {
        console.log('Select a cell to move this penguin');
      }
    }
  }
);

export const gameService = interpret(gameMachine)
  .onTransition(state => {
    console.log(state.value);
  })
  .onDone(() => console.log('done'))
  .start(); // returns started service
