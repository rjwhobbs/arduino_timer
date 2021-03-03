const uint8_t button4 = A3;

uint32_t user_input = 2520000;
uint32_t start_time;

uint32_t get_min_left(uint32_t time_left);
uint32_t get_sec_left(uint32_t time_left);

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  start_time = millis();
}

void loop() {
  
  if (millis() > start_time + 1000 && user_input) {
    start_time += 1000;
    user_input -= 1000;

    if (user_input) {
      Serial.print("time: ");
      Serial.print(get_min_left(user_input));
      Serial.print(".");
      Serial.println(get_sec_left(user_input));
    }

  } else if (!user_input) {
    Serial.print("time: ");
    Serial.print(get_min_left(user_input));
    Serial.print(".");
    Serial.println(get_sec_left(user_input));
    delay(1000);
  }

}

uint32_t get_min_left(uint32_t time_left) {
  return time_left / 60000;
}

uint32_t get_sec_left(uint32_t time_left) {
  return (time_left % 60000) / 1000;
}
