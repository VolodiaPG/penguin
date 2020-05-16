import { Machine, interpret } from 'xstate';

/**
 * Final State Machine to control the state of the whole penguin game
 * |- id: noun of the FSM,
 * |- initial: state in the beginning of the app,
 * |- context: initial part,
 * |- states: to define all the states in the FSM
 * | |- settings: describe the state
 * | | |-on: define a possible action,
 * | | | |- {identifier}
 * | | | | |- target: destination state
 * | | | | |- actions: to perform when the action was called
 */
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
          },
          MCTSPLAYED: 'movePerformed'
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

/**
 * Define a service to be able to access the ^penguin game Final State Machine, in the angular components,
 * Then start it.
 */
export const gameService = interpret(gameMachine)
  .onTransition(state => {
    console.log(state.toStrings());
  })
  .onDone(() => console.log('done'))
  .start(); // returns started service
