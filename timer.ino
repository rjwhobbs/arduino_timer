const uint8_t down_button = A3;
const uint8_t up_button = A2;
const uint8_t unit_button = A1;
const uint8_t start_button = A5;
const uint32_t max_mins = 5940000;
const uint32_t ones_mins = 60000;
const uint32_t tens_mins = 600000;

uint32_t user_input = 0;
uint32_t start_time;
uint16_t start = 0;
uint8_t unit_button_state = 0;

// 4 digit
//Set cathode interface
int a = 1;
int b = 2;
int c = 3;
int d = 4;
int e = 5;
int f = 6;
int g = 7;
int dp = 8;
//Set anode interface
int d4 = 9;
int d3 = 10;
int d2 = 11;
int d1 = 13;

uint8_t get_min_left(uint32_t time_left);
uint8_t get_sec_left(uint32_t time_left);
void set_digit(uint8_t digit);
void print_0(uint8_t has_point);
void print_1(uint8_t has_point);
void print_2(uint8_t has_point);
void print_3(uint8_t has_point);
void print_4(uint8_t has_point);
void print_5(uint8_t has_point);
void print_6(uint8_t has_point);
void print_7(uint8_t has_point);
void print_8(uint8_t has_point);
void print_9(uint8_t has_point);
void clear_display(uint8_t has_point);
void display_number(uint8_t n, uint8_t has_point);
void display_all(uint8_t digit, uint8_t num, uint8_t has_point);

void setup() {
  // Serial.begin(9600);

  pinMode(down_button, INPUT);
  pinMode(up_button, INPUT);
  pinMode(unit_button, INPUT);
  pinMode(start_button, INPUT);

  // 4 digit
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dp, OUTPUT);

  while (!start) {

    if (analogRead(up_button)) {
      while (analogRead(up_button)) {
      }
      if (!unit_button_state && user_input < max_mins) {
        user_input += ones_mins;
      }
      else if (unit_button_state && (user_input + tens_mins) <= max_mins) {
        user_input += tens_mins;
      }
      // Serial.print("time set: ");
      // Serial.print(get_min_left(user_input));
      // Serial.print(".");
      // Serial.println(get_sec_left(user_input));
    }

    if (analogRead(down_button)) {
      while (analogRead(down_button)) {
      }
      if (!unit_button_state) {
        if (user_input > ones_mins) {
          user_input -= ones_mins;
        }
      }
      else if (unit_button_state) {
        if (user_input > tens_mins && user_input - tens_mins >= ones_mins) {
          user_input -= tens_mins;
        }
      }
      // Serial.print("time set: ");
      // Serial.print(get_min_left(user_input));
      // Serial.print(".");
      // Serial.println(get_sec_left(user_input));
    }

    if (analogRead(unit_button)) {
      while (analogRead(unit_button)) {
      }
      unit_button_state = !unit_button_state;
    }

    if (analogRead(start_button)) {
      while (analogRead(start_button))  {
      }
      start = true;
    }

    display_all(1, get_min_left(user_input) / 10, 0);
    delay(1);
    clear_display(0);
    display_all(2, get_min_left(user_input) % 10, 1);
    delay(1);
    clear_display(0);
    display_all(3, get_sec_left(user_input) / 10, 0);
    delay(1);
    clear_display(0);
    display_all(4, get_sec_left(user_input) % 10, 0);
    delay(1);
    clear_display(0);
  }
  
  start_time = millis();
}

void loop() {
  
  if (millis() > start_time + 1000 && user_input) {
    start_time += 1000;
    user_input -= 1000;

    if (user_input) {
      // Serial.print("time: ");
      // Serial.print(get_min_left(user_input));
      // Serial.print(".");
      // Serial.println(get_sec_left(user_input));
    }

  } else if (!user_input) {
    // Serial.print("time: ");
    // Serial.print(get_min_left(user_input));
    // Serial.print(".");
    // Serial.println(get_sec_left(user_input));
    delay(1000);
  }

}

uint8_t get_min_left(uint32_t time_left) {
  return time_left / ones_mins;
}

uint8_t get_sec_left(uint32_t time_left) {
  return (time_left % ones_mins) / 1000;
}

void set_digit(uint8_t digit) {
  switch(digit) {
    case 1: 
      digitalWrite(d1, HIGH);
      digitalWrite(d2, LOW);
      digitalWrite(d3, LOW);
      digitalWrite(d4, LOW);
      break;
    case 2: 
      digitalWrite(d1, LOW);
      digitalWrite(d2, HIGH);
      digitalWrite(d3, LOW);
      digitalWrite(d4, LOW); 
      break;
	  case 3: 
	    digitalWrite(d1, LOW);
 	    digitalWrite(d2, LOW);
	    digitalWrite(d3, HIGH);
	    digitalWrite(d4, LOW); 
	    break;
	  case 4: 
	    digitalWrite(d1, LOW);
 	    digitalWrite(d2, LOW);
	    digitalWrite(d3, LOW);
	    digitalWrite(d4, HIGH); 
	    break;
    default :
      digitalWrite(d1, LOW);
	    digitalWrite(d2, LOW);
	    digitalWrite(d3, LOW);
	    digitalWrite(d4, LOW);
      break;
	}
}

void display_all(uint8_t digit, uint8_t num, uint8_t has_point) {
  set_digit(digit);
  display_number(num, has_point);
  // delay(1);
  // clear_display();
}

void display_number(uint8_t n, uint8_t has_point) {
  switch(n) {
    case 0: print_0(has_point); break;
    case 1: print_1(has_point); break;
    case 2: print_2(has_point); break;
    case 3: print_3(has_point); break;
    case 4: print_4(has_point); break;
    case 5: print_5(has_point); break;
    case 6: print_6(has_point); break;
    case 7: print_7(has_point); break;
    case 8: print_8(has_point); break;
    case 9: print_9(has_point); break;
    default: clear_display(has_point); break; 
  }
}

void print_0(uint8_t has_point) {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
  digitalWrite(dp, has_point ? LOW : HIGH);
}

void print_1(uint8_t has_point) {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, has_point ? LOW : HIGH);
}

void print_2(uint8_t has_point) {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
  digitalWrite(dp, has_point ? LOW : HIGH);
}

void print_3(uint8_t has_point) {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
  digitalWrite(dp, has_point ? LOW : HIGH);
}

void print_4(uint8_t has_point) {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(dp, has_point ? LOW : HIGH);
}

void print_5(uint8_t has_point) {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(dp, has_point ? LOW : HIGH);
}

void print_6(uint8_t has_point) {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(dp, has_point ? LOW : HIGH);
}

void print_7(uint8_t has_point) {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, has_point ? LOW : HIGH);
}

void print_8(uint8_t has_point) {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(dp, has_point ? LOW : HIGH);
}

void print_9(uint8_t has_point) {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(dp, has_point ? LOW : HIGH);
}

void clear_display(uint8_t has_point) {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, has_point ? LOW : HIGH);
}
