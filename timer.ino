const uint8_t undo_button = A3;
const uint8_t ones_button = A2;
const uint8_t tens_button = A1;
const uint8_t start_button = A5;

uint32_t user_input = 0;
uint32_t start_time;

uint16_t start = 0;
uint8_t undo_state = 0;

uint32_t get_min_left(uint32_t time_left);
uint32_t get_sec_left(uint32_t time_left);

void setup() {
  Serial.begin(9600);

  pinMode(undo_button, INPUT);
  pinMode(ones_button, INPUT);
  pinMode(tens_button, INPUT);
  pinMode(start_button, INPUT);

  while (!start) {

    if (analogRead(ones_button)) {
      while (analogRead(ones_button)) {
      }
      user_input += 60000;
      undo_state = 1;
      Serial.print("ones set: ");
      Serial.print(get_min_left(user_input));
      Serial.print(".");
      Serial.println(get_sec_left(user_input));
    }

    if (analogRead(tens_button)) {
      while (analogRead(tens_button)) {
      }
      user_input += 600000;
      undo_state = 10;
      Serial.print("tens set: ");
      Serial.print(get_min_left(user_input));
      Serial.print(".");
      Serial.println(get_sec_left(user_input));
    }

    if (analogRead(undo_button)) {
      while (analogRead(undo_button)) {
      }
      
      if (undo_state == 1 && user_input > 60000) {
        user_input -= 60000;
      } 
      else if (undo_state == 10 && user_input > 600000) {
        if (user_input - 600000 >= 60000) {
          user_input -= 600000;
        }
      }
      Serial.print("undo set: ");
      Serial.print(get_min_left(user_input));
      Serial.print(".");
      Serial.println(get_sec_left(user_input));
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
  return time_left / 60000;
}

uint32_t get_sec_left(uint32_t time_left) {
  return (time_left % 60000) / 1000;
}
