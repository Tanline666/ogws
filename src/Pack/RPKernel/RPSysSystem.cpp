#include "RPSystem/RPSysRenderMode.h"
#include <RPKernel/RPSysHomeMenuMgr.h>
#include <RPSystem/RPSysDvdStatus.h>

#include <Pack/RPSystem/RPSysSceneMgr.h>
#include <Pack/RPSystem/RPSysSystem.h>

#include <egg/core/eggGraphicsFifo.h>
#include <egg/core/eggXfbManager.h>
#include <egg/gfxe/eggScreen.h>

#include <revolution/SC/scapi.h>
#include <revolution/SC/scsystem.h>
#include <revolution/VI/vi.h>
#include <revolution/OS/OSArena.h>

void RPSysSystem::setupTVMode() {
    int i;

    VIInit();
    for (i = 0; i < 60; i++) {
        if (SCCheckStatus() == 0) {
            break;
        }
        VIWaitForRetrace();
    }
    if (SCGetAspectRatio() == 1) {
        EGG::Screen::SetTVMode(EGG::Screen::TV_MODE_WIDE);
    }
    else {
        EGG::Screen::SetTVMode(EGG::Screen::TV_MODE_STD);
    }
}

/**
 * @brief Controls whether the game restarts or returns to the Wii Menu upon a
 * soft reset.
 */

void RPSysSystem::softResetCallBack() {
    if (RPSysDvdStatus::instance()->isErrorOccured() != 0) {
        RPSysSceneMgr::instance()->returnToMenu(FALSE);
    } else {
        VIEnableDimming(false);
        if (RPSysSceneMgr::instance()->isNormalState() and
            !RPSysHomeMenuMgr::instance()->startBlackOut()) {
            RPSysSceneMgr::instance()->softReset(FALSE);
        }
    }
}

void RPSysSystem::shutdownSystemCallBack() {
    RPSysSceneMgr::instance()->shutdownSystem(FALSE);
}
