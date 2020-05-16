import { Machine, interpret } from 'xstate';

/**
 * Final State Machine to control the state of the whole application
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
export const appMachine = Machine(
  {
    id: 'appLogic',
    initial: 'settings',
    context: {
      nbHexa: 8,
      nbPeng: 2
    },
    states: {
      settings: {
        on: {
          NEXTSTEP: {
            target: 'initPosPenguin',
            actions: ['notifySettings']
          }
        }
      },
      initPosPenguin: {
        on: {
          PENGUINSPOSED: {
            target: 'initPosWasmPenguin',
            actions: ['notifyPenguinPosed']
          }
        }
      },
      initPosWasmPenguin: {
        on: {
          STARTGAME: {
            target: 'gameStarted',
            actions: ['notifyGameStarted']
          }
        }
      },
      gameStarted: {
        on: {
          PENGUINSPOSED: {
            target: 'initPosWasmPenguin',
            actions: ['notifyPenguinPosed']
          }
        }
      }
    }
  },
  {
    actions: {
      notifySettings: (context, event) => {
        // console.log('You choice to play with', context.nbHexa, context.nbPeng);
      },
      notifyPenguinPosed: (context, event) => {
        console.log('Penguins posed');
      },
      notifyGameStarted: (context, event) => {
        console.log('Game Started');
      }
    }
  }
);

/**
 * Define a service to be able to access the application Final State Machine, in the angular components,
 * Then start it.
 */
export const appService = interpret(appMachine)
  .onTransition(state => {
    console.log(state.toStrings());
  })
  .onDone(() => console.log('done'))
  .start(); // returns started service
