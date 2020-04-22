import { Machine, interpret } from 'xstate';

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
      initPosWasmPenguin: {}
    }
  },
  {
    actions: {
      notifySettings: (context, event) => {
        // console.log('You choice to play with', context.nbHexa, context.nbPeng);
      },
      notifyPenguinPosed: (context, event) => {
        console.log('Now we could begin !');
      }
    }
  }
);

export const appService = interpret(appMachine)
  .onTransition(state => {
    console.log(state.toStrings());
  })
  .onDone(() => console.log('done'))
  .start(); // returns started service
