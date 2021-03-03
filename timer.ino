const uint8_t down_button = A3;
const uint8_t up_button = A2;
const uint8_t val_button = A1;
const uint8_t start_button = A5;
const uint32_t max_mins = 5940000;
const uint32_t ones_mins = 60000;
const uint32_t tens_mins = 600000;

uint32_t user_input = 0;
uint32_t start_time;
uint16_t start = 0;
uint8_t button_state = 0;

uint32_t get_min_left(uint32_t time_left);
uint32_t get_sec_left(uint32_t time_left);

void setup() {
  Serial.begin(9600);

  pinMode(down_button, INPUT);
  pinMode(up_button, INPUT);
  pinMode(val_button, INPUT);
  pinMode(start_button, INPUT);

  while (!start) {

    if (analogRead(up_button)) {
      while (analogRead(up_button)) {
      }
      if (!button_state && user_input < max_mins) {
        user_input += ones_mins;
      }
      else if (button_state && (user_input + tens_mins) <= max_mins) {
        user_input += tens_mins;
      }
      Serial.print("time set: ");
      Serial.print(get_min_left(user_input));
      Serial.print(".");
      Serial.println(get_sec_left(user_input));
    }

    if (analogRead(down_button)) {
      while (analogRead(down_button)) {
      }
      if (!button_state) {
        if (user_input > ones_mins) {
          user_input -= ones_mins;
        }
      }
      else if (button_state) {
        if (user_input > tens_mins && user_input - tens_mins >= ones_mins) {
          user_input -= tens_mins;
        }
      }
      Serial.print("time set: ");
      Serial.print(get_min_left(user_input));
      Serial.print(".");
      Serial.println(get_sec_left(user_input));
    }

    if (analogRead(val_button)) {
      while (analogRead(val_button)) {
      }
      button_state = !button_state;
    }

    if (analogRead(start_button)) {
      while (analogRead(start_button))  {
      }
      start = true;
    }
  }
  
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
  return time_left / ones_mins;
}

uint32_t get_sec_left(uint32_t time_left) {
  return (time_left % ones_mins) / 1000;
}
