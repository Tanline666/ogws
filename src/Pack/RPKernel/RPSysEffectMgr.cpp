#include <Pack/RPKernel.h>

#include <nw4r/ef.h>

void RPSysEffectMgr::setCreator(RPSysEffectCreator* pCreator, u32 pEffectScene) {
    if (pCreator != NULL) {
        mEffectCreators[pEffectScene] = pCreator;
    }
}

void RPSysEffectMgr::stopAllEffect() {
    int i;
    int j;
    nw4r::ef::EffectSystem* effSysInst = nw4r::ef::EffectSystem::GetInstance();

    for (i = 0; i < 0x180; i++) {
        effSysInst->RetireEmitterAll(i);
        effSysInst->RetireParticleAll(i);
    }
    
    for (j = 0; j < 3; j++) {
        if (mEffectCreators[0] != NULL && mEffectCreators[0]->getEffectSystem() != 0) {
            mEffectCreators[0]->stopAllEffect();
        }
    }
}

void RPSysEffectMgr::createEffect(u32 pGroupID, u16 pCalcRemain, u32 pCreator) {
    mEffectCreators[pCreator]->createEffect(pGroupID, pCalcRemain);
}
