#include <stdbool.h>
#include <string.h>

#define MAX_EVENTS 10 // Maximum number of events to store

// Event queue to handle multiple key presses
static KeyEvent event_queue[MAX_EVENTS];
static int event_queue_start = 0;
static int event_queue_end = 0;

// Function to add an event to the queue
static void enqueue_event(KeyEvent event) {
    if ((event_queue_end + 1) % MAX_EVENTS != event_queue_start) { // Check if queue is not full
        event_queue[event_queue_end] = event;
        event_queue_end = (event_queue_end + 1) % MAX_EVENTS;
    }
}

// Function to get an event from the queue
static bool dequeue_event(KeyEvent *event) {
    if (event_queue_start != event_queue_end) { // Check if queue is not empty
        *event = event_queue[event_queue_start];
        event_queue_start = (event_queue_start + 1) % MAX_EVENTS;
        return true;
    }
    return false;
}

KeyEvent Key_Scan(void) {
    KeyEvent event = {.key_id = KEY_ID_COUNT}; // Invalid event default value
    uint32_t current_tick = HAL_GetTick(); // Get current tick once per scan

    for (int i = 0; i < KEY_ID_COUNT; i++) {
        // Read current key state (pressed is low level)
        uint8_t curr_state = (HAL_GPIO_ReadPin(key_config[i].gpio_port,
                                               key_config[i].gpio_pin) == GPIO_PIN_RESET);

        // State change detection
        if (curr_state != key_states[i].last_state) {
            // Update state and record time
            key_states[i].last_state = curr_state;
            key_states[i].press_time = current_tick;

            if (curr_state) { // Press action
                key_states[i].long_triggered = 0;
            } else { // Release action
                // Generate short press event on release (if long press not triggered)
                if (!key_states[i].long_triggered) {
                    event.key_id = key_config[i].key_id;
                    event.event_type = KEY_EVENT_SHORT_PRESS;
                    event.timestamp = current_tick;
                    enqueue_event(event); // Add event to queue
                }
            }
        }

        // Long press detection (pressed longer than threshold)
        if (curr_state &&
            (current_tick - key_states[i].press_time > LONG_PRESS_MS) &&
            !key_states[i].long_triggered) {

            key_states[i].long_triggered = 1; // Mark long press triggered
            event.key_id = key_config[i].key_id;
            event.event_type = KEY_EVENT_LONG_PRESS;
            event.timestamp = current_tick;
            enqueue_event(event); // Add event to queue
        }
    }

    // Return the next event from the queue
    if (dequeue_event(&event)) {
        return event;
    }

    return event; // Return invalid event if no events in queue
} 