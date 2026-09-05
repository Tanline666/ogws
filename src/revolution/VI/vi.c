#include <revolution/VI.h>

static VIRetraceCallback PreCB;
static void* CurrBufAddr;

/**
 * @brief Sets the function used before retracing the screen (executed once per field).
 * 
 * @param callback Function name
 * @return The prior callback function 
 */
VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback callback) {
    VIRetraceCallback currCB = PreCB;
    BOOL enabled = OSDisableInterrupts();
    PreCB = callback;
    OSRestoreInterrupts(enabled);
    return currCB;
}

/**
 * @brief Gets pointer to the current frame buffer.
 * 
 * @return void*: Pointer to address
 */
void* VIGetCurrentFrameBuffer() {
    return CurrBufAddr;
}
