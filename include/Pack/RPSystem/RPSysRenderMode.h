#ifndef RP_SYSTEM_RENDER_MODE_H
#define RP_SYSTEM_RENDER_MODE_H

#include <types.h>

#include <egg/gfxe/eggScreen.h>

class RPSysRenderMode {
public:
    enum EFormat {
        EFormat_NTSC,
        EFormat_NTSC_Prog,
        EFormat_PAL50,
        EFormat_PAL60,
        EFormat_PAL_Prog,

        EFormat_Max
    };

void adjust(u16 *pOriginX, u16 *pWidth, EFormat pFormat, EGG::Screen::TVMode pTvMode);

};

#endif
