#include "ti_msp_dl_config.h"

#define s1 0
#define s2 1

extern volatile uint32_t interruptVectors[];
static volatile int button_press, event_flag = 0; // button flags

int main(void) {
    volatile int n_s = 0;

    SYSCFG_DL_init();
    NVIC_EnableIRQ(GPIO_SWITCHES_INT_IRQN);

    while (1) {
        __WFI();

        while(event_flag == 0){}
        event_flag = 0;

        if (button_press == s2) {
            n_s = 1;
        }

        if (n_s == 1) {
           // led sequence for pedestrian lights

            // Step 1: G2 and R1 on
            DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_G2_PIN | GPIO_LEDS_R1_PIN);
            delay_cycles(32000000); // 1 second delay

            // Step 2: R1 stays on, G2 off, Y2 on
            DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_G2_PIN);
            DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_Y2_PIN);
            delay_cycles(32000000); // 1 second delay

            // Step 3: R1 off, Y2 off, R2 on, G1 on
            DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_R1_PIN | GPIO_LEDS_Y2_PIN);
            DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_R2_PIN | GPIO_LEDS_G1_PIN);
            delay_cycles(64000000); // 5 second delay

            // Step 4: Y1 blinking
            DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_G1_PIN);
            for (int i = 0; i < 20; i++) {
                DL_GPIO_togglePins(GPIO_LEDS_PORT, GPIO_LEDS_Y1_PIN);
                delay_cycles(3200000); // short delay
            }

            //Y1 off after blinking
            DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_Y1_PIN);

            // Step 5: R2 on, G2 on, G1 off
            DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_R1_PIN | GPIO_LEDS_G2_PIN);
            DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_G1_PIN | GPIO_LEDS_R2_PIN);
            delay_cycles(160000000); // 5 second delay

            // Reset
            n_s = 0;
        }
    }
}

void GROUP1_IRQHandler(void) {
    switch (DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1)) {
        case GPIO_SWITCHES_INT_IIDX:
            // s1 high when pressed
            if (DL_GPIO_readPins(GPIO_SWITCHES_PORT, GPIO_SWITCHES_S1_PIN)) {
                button_press = s1;
            } else if (!DL_GPIO_readPins(GPIO_SWITCHES_PORT, GPIO_SWITCHES_S2_PIN)) {
                button_press = s2;
            }
            event_flag = 1;
            break;
    }
}

