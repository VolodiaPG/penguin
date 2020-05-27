import { Animation, AnimationController } from '@ionic/angular';


export const enterAnimation = (baseEl: HTMLElement, opts?: any): Animation => {
    const DURATION = 300;
    const animationCtrl = new AnimationController();

    console.log("transition");
    console.log('baseEl: ', baseEl);
    console.log('opts: ', opts);

    if (opts.direction === 'forward') {
        return animationCtrl.create()
            .addElement(opts.enteringEl)
            .duration(DURATION)
            .easing('ease-in')
            .fromTo('opacity', 0, 1);
    } else {
        const rootAnimation = animationCtrl.create()
            .addElement(opts.enteringEl)
            .duration(DURATION)
            .easing('ease-in')
            .fromTo('opacity', 0, 1);

        const leavingAnimation = animationCtrl.create()
        .addElement(opts.leavingEl)
        .duration(DURATION)
        .easing('ease-out')
        .fromTo('opacity', 1, 0);

        return animationCtrl.create().addAnimation([rootAnimation, leavingAnimation]);
    }

}