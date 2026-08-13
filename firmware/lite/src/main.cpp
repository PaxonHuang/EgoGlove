// EchoGlove Lite — M2 骨架 (Task 1 桩; Task 5 填入真实任务)
#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    delay(200);
    Serial.println("LITE BOOT OK");
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(1000));
}
