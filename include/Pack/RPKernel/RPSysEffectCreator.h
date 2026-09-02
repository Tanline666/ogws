#ifndef RP_KERNEL_EFFECT_CREATOR_H
#define RP_KERNEL_EFFECT_CREATOR_H
#include <Pack/types_pack.h>
#include <nw4r/ef.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Effect creator
 */
class RPSysEffectCreator {
public:
    /**
     * @brief Constructor
     *
     * @param effectScene Effect scene index
     */
    RPSysEffectCreator(u32 effectScene);

    /**
     * @brief Destructor
     */
    virtual ~RPSysEffectCreator(); // at 0x8

    void setResource(u8* pEffData, u8* pTexData);
    void nullCtor1();
    void nullCtor2();
    /**
     * @brief Sets the current frame rate. Uses constant values.
     * 
     * @param pFrameRate Can either be ticks per millisecond or ticks per minute.
     */
    void setFrameRate(f32 pFrameRate);
    void createEffect(u32 pGroupID, u16 pCalcRemain);
    bool isSlowEffect() const;
    bool getUnk20() const;
    void stopAllEffect();
    void draw(const nw4r::ef::DrawInfo& pDrawInfo, u32 pGroupID_1, u32 pGroupID_2);

private:
    char unk4[0xB]; // at 0x4
    u32 mUnknownID; // at 0x10
    nw4r::ef::EffectProject* mEffectProject; // at 0x14
    nw4r::ef::TextureProject* mTextureProject; // at 0x18
    u32 unk1c; // at 0x1c
    BOOL unk20; // at 0x20
    char unk24[4]; // at 0x24
    f32 mFrameRate; // at 0x28
    nw4r::ef::EffectSystem* mEffectSystem; // at 0x2C
    u32 unk30; // at 0x30
    char unk34[0x10];
};

//! @}

#endif
