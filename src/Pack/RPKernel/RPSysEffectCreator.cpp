#include <Pack/RPKernel.h>

#include <nw4r/ef.h>

/**
 * @brief Destructor
 */
RPSysEffectCreator::~RPSysEffectCreator() {
    BOOL doRelocate = FALSE;
    nw4r::ef::Resource *resInstance = nw4r::ef::Resource::GetInstance();

    stopAllEffect();
    if (mEffectProject != NULL) {
        resInstance->RemoveEffectProject(mEffectProject);
        doRelocate = TRUE;
        mEffectProject = NULL;
    }
    if (mTextureProject != NULL) {
        resInstance->RemoveTextureProject(mTextureProject);
        doRelocate = TRUE;
        mTextureProject = NULL;
    }
    if (doRelocate) {
        resInstance->RelocateCommand();
    } //todo(texline) this implicitly calls ~Disposer
}

/**
 * @brief Registers and resolves given effects and textures.
 * 
 * @param pEffData pointer to given .breff data
 * @param pTexData pointer to given .breft data
 */

void RPSysEffectCreator::setResource(u8* pEffData, u8* pTexData) {
    if (mEffectProject == NULL && mTextureProject == NULL) {
        nw4r::ef::Resource *instance = nw4r::ef::Resource::GetInstance();
        mEffectProject = instance->Add(pEffData);
        mTextureProject = instance->AddTexture(pTexData);
        instance->RelocateCommand();
    }
}

/**
 * @brief Treated as constructor functions in createSlowSystem. Both are stubbed.
 */
void RPSysEffectCreator::nullCtor2() {} // 2 is first for linking purposes
void RPSysEffectCreator::nullCtor1() {}

/**
 * @brief Gets mEffectSystem.
 */
nw4r::ef::EffectSystem* RPSysEffectCreator::getEffectSystem() {
    // no idea why this is even done, but this is a 100% match???
    return (nw4r::ef::EffectSystem* )((-(int)mEffectSystem | (unsigned int)mEffectSystem) >> 31);
}

/**
 * @brief Temporary name. Returns an unknown BOOL at offset 0x20.
 * 
 * @details Function used in RPBoxScene function 802E6A00
 */
BOOL RPSysEffectCreator::getUnk20() {
    return ((unsigned int)-unk20 | unk20) >> 31;
}

/**
 * @brief Deletes all emitters and particles upon exiting a scene.
 */
void RPSysEffectCreator::stopAllEffect() {
    int i;
    int j;
    u32 pGroupID;
    u32 pGroupID_2;

    // todo(texline): regswaps
    // instance is set as its own variable because code gets less accurate otherwise
    nw4r::ef::EffectSystem* instance = nw4r::ef::EffectSystem::GetInstance();
    for (i = 0; i < 64; i++) {
        pGroupID = mUnknownID | i;
        instance->RetireEmitterAll(pGroupID);
        instance->RetireParticleAll(pGroupID);
    }
    if (mEffectSystem != NULL) {
        for (j = 0; j < 64; j++) {
            pGroupID_2 = mUnknownID | j;
            mEffectSystem->RetireEmitterAll(pGroupID_2);
            mEffectSystem->RetireParticleAll(pGroupID_2);
        }
    }
}

/**
 * @brief Renders effects that are part of a given group.
 * 
 * @param pDrawInfo reference to DrawInfo used in NintendoWare function
 * @param pGroupID_1 part of calculation for bitor'd groupID
 * @param pGroupID_2 part of calculation for bitor'd groupID
 */

void RPSysEffectCreator::draw(const nw4r::ef::DrawInfo& pDrawInfo, u32 pGroupID_1, u32 pGroupID_2) {
    nw4r::ef::EffectSystem *instance = nw4r::ef::EffectSystem::GetInstance();
    instance->Draw(pDrawInfo, pGroupID_1 | pGroupID_2 | mUnknownID);
    if (mEffectSystem != NULL) {
        mEffectSystem->Draw(pDrawInfo, pGroupID_1 | pGroupID_2 | mUnknownID);
    }
}
