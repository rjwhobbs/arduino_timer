const uint8_t down_button = A3;
const uint8_t up_button = A2;
const uint8_t unit_button = A1;
const uint8_t start_button = A5;
const uint32_t max_mins = 5940000;
const uint32_t ones_mins = 60000;
const uint32_t tens_mins = 600000;

uint32_t user_input = 60000;
uint32_t start_time;
uint16_t start = 0;
uint8_t unit_button_state = 0;

// 4 digit 7 segment display
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
uint16_t display_rate = 600;
uint32_t flash_time;
uint16_t flash_rate = 350;
uint8_t flash_state = 0;
uint8_t flash_d1 = 0;
uint8_t flash_d2 = 1;
uint8_t flash_end_state = 1;

uint8_t get_min_left(uint32_t time_left);
uint8_t get_sec_left(uint32_t time_left);
void set_digit(uint8_t digit);
void print_0();
void print_1();
void print_2();
void print_3();
void print_4();
void print_5();
void print_6();
void print_7();
void print_8();
void print_9();
void clear_display(uint8_t has_point);
void display_number(uint8_t n);
void display_digit(uint8_t digit, uint8_t num);
void display_all();
void set_flash_state();

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

  flash_time = millis();

  while (!start) {

    set_flash_state();

    if (analogRead(up_button)) {
      while (analogRead(up_button)) {
        set_flash_state();
        display_all();
      }
      if (!unit_button_state && user_input < max_mins) {
        user_input += ones_mins;
      }
      else if (unit_button_state && (user_input + tens_mins) <= max_mins) {
        user_input += tens_mins;
      }
    }

    if (analogRead(down_button)) {
      while (analogRead(down_button)) {
        set_flash_state();
        display_all();
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
    }

    if (analogRead(unit_button)) {
      while (analogRead(unit_button)) {
        set_flash_state();
        display_all();
      }
      unit_button_state = !unit_button_state;
      flash_d1 = !flash_d1;
      flash_d2 = !flash_d2;
    }

    if (analogRead(start_button)) {
      while (analogRead(start_button))  {
        set_flash_state();
        display_all();
      }
      start = true;
      flash_d1 = 0;
      flash_d2 = 0;
    }

    display_all();
  }
  
  start_time = millis();
}

void loop() {
  
  if (millis() > start_time + 1000 && user_input) {
    start_time += 1000;
    user_input -= 1000;
  }

  if (!user_input) {
    start_time = millis();
  }
  
  while (!user_input) {
    if (start_time > millis() - 650) {
      if (flash_end_state) {
        // Serial.println(flash_end_state);
        display_all();
      }
    } 
    else {
      start_time = millis();
      flash_end_state = !flash_end_state;
    }
  }

  if (user_input) {
    display_all();
  }
}

void display_all() {
  if (flash_d1) {
    if (flash_state) {
      display_digit(1, get_min_left(user_input) / 10);
      delayMicroseconds(display_rate);
      clear_display(0);
    }
  }
  else {
    display_digit(1, get_min_left(user_input) / 10);
    delayMicroseconds(display_rate);
    clear_display(0);
  }
    
  if (flash_d2) {
    if (flash_state) {
      display_digit(2, get_min_left(user_input) % 10);
      delayMicroseconds(display_rate);
      clear_display(0);
    }
  } 
  else {
    display_digit(2, get_min_left(user_input) % 10);
    delayMicroseconds(display_rate);
    clear_display(0);
  }

  set_digit(2);
  clear_display(1);
  delayMicroseconds(display_rate);
  clear_display(0);
  display_digit(3, get_sec_left(user_input) / 10);
  delayMicroseconds(display_rate);
  clear_display(0);
  display_digit(4, get_sec_left(user_input) % 10);
  delayMicroseconds(display_rate);
  clear_display(0);
}

void display_digit(uint8_t digit, uint8_t num) {
  set_digit(digit);
  display_number(num);
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

void display_number(uint8_t n) {
  switch(n) {
    case 0: print_0(); break;
    case 1: print_1(); break;
    case 2: print_2(); break;
    case 3: print_3(); break;
    case 4: print_4(); break;
    case 5: print_5(); break;
    case 6: print_6(); break;
    case 7: print_7(); break;
    case 8: print_8(); break;
    case 9: print_9(); break;
    default: clear_display(0); break; 
  }
}

void print_0() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
  digitalWrite(dp, HIGH);
}

void print_1() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, HIGH);
}

void print_2() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
  digitalWrite(dp, HIGH);
}

void print_3() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
  digitalWrite(dp, HIGH);
}

void print_4() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(dp, HIGH);
}

void print_5() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(dp, HIGH);
}

void print_6() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(dp, HIGH);
}

void print_7() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, HIGH);
}

void print_8() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(dp, HIGH);
}

void print_9() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(dp, HIGH);
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

void set_flash_state() {
  if (millis() > flash_time + flash_rate) {
    flash_state = !flash_state;
    flash_time = millis();
  }
}

uint8_t get_min_left(uint32_t time_left) {
  return time_left / ones_mins;
}

uint8_t get_sec_left(uint32_t time_left) {
  return (time_left % ones_mins) / 1000;
}
