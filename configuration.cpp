#include "configuration.h"
#include "src/userUsbHidKeyboardMouse/USBHIDKeyboardMouse.h"

const keyboard_configuration_t configurations[NUM_CONFIGURATION] = {
    { // Config 1
        .button = {
            [BTN_1] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_F16},
                    .length = 1,
                    .delay = 0
                }
            },
            [BTN_2] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_F17},
                    .length = 1,
                    .delay = 0
                }
            },
            [BTN_3] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_F18},
                    .length = 1,
                    .delay = 0
                }
            },
            [ENC_CW] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_F20},
                    .length = 1,
                    .delay = 0
                }
            },
            [ENC_CCW] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_F21},
                    .length = 1,
                    .delay = 0
                }
            },
            [BTN_ENC] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_F19},
                    .length = 1,
                    .delay = 0
                }
            },
        }
    }
};
