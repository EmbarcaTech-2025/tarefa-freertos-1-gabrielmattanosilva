#ifndef BUTTONS_H
#define BUTTONS_H

#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6

#define DEBOUNCE_TIME_MS 200

typedef void (*button_callback_t)(void);

void buttons_init(void);
void register_button_a_callback(button_callback_t callback);
void register_button_b_callback(button_callback_t callback);

#endif // BUTTONS_H