#include <RPKernel/RPSysHomeMenuMgr.h>
#include <RPSystem/RPSysDvdStatus.h>
#include <Pack/RPSystem/RPSysSceneMgr.h>

#include <Pack/RPSystem/RPSysSystem.h>

#include <egg/core/eggGraphicsFifo.h>
#include <egg/core/eggXfbManager.h>
#include <revolution/OS/OSArena.h>

/**
 * @brief
 * Controls whether the game restarts or returns to the Wii Menu upon a soft
 * reset.
 */

void RPSysSystem::softResetCallBack() {
    if (RPSysDvdStatus::instance()->isErrorOccured() != 0) {
        RPSysSceneMgr::instance()->returnToMenu(FALSE);
    } else {
        VIEnableDimming(false);
        if (RPSysSceneMgr::instance()->isNormalState() and !RPSysHomeMenuMgr::instance()->startBlackOut()) {
            RPSysSceneMgr::instance()->softReset(FALSE);
        }
    }
}
