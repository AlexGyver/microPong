#define OLED_ADDRESS            0x3C
#define OLED_COMMAND_MODE       0x00
#define OLED_ONE_COMMAND_MODE   0x80
#define OLED_DATA_MODE          0x40
#define OLED_ONE_DATA_MODE      0xC0

const int bufsize = 128 * 32 / 8 / 2;
byte oled_buf[bufsize];
byte Scale = 1;

const uint8_t _oled_init[] PROGMEM = {
  0xAE, // oled off
  0xD5, // CLOCK_DIV_RATIO
  0x80,
  0xA8, // Set multiplex
  0x1F, // for 32 rows
  0x8D, // Charge pump
  0x14,
  0x20, // Memory mode
  0x01, // Vertical OLED_ADDRESSing
  0xA1, // Flip horizontally
  0xC8, // Flip vertically
  0x81, // Set contrast
  0xCF, // brighter
  0xDB, // Set vcom detect
  0x40, // brighter
  0xDA,
  0x02,
  0x20,   // address
  0x0,    // col to row
  0xAF,  // Display on*
};

const uint8_t CharMap[][6] PROGMEM = {
  { 0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00 }, // 30
  { 0x00, 0x42, 0x7F, 0x40, 0x00, 0x00 },
  { 0x72, 0x49, 0x49, 0x49, 0x46, 0x00 },
  { 0x21, 0x41, 0x49, 0x4D, 0x33, 0x00 },
  { 0x18, 0x14, 0x12, 0x7F, 0x10, 0x00 },
  { 0x27, 0x45, 0x45, 0x45, 0x39, 0x00 },
  { 0x3C, 0x4A, 0x49, 0x49, 0x31, 0x00 },
  { 0x41, 0x21, 0x11, 0x09, 0x07, 0x00 },
  { 0x36, 0x49, 0x49, 0x49, 0x36, 0x00 },
  { 0x46, 0x49, 0x49, 0x29, 0x1E, 0x00 },
};

void oledInit() {
  Wire.beginTransmission(OLED_ADDRESS);
  Wire.write(OLED_COMMAND_MODE);
  for (uint8_t i = 0; i < 20; i++) Wire.write(pgm_read_byte(&_oled_init[i]));
  Wire.endTransmission();
}

void oledClear() {
  for (int i = 0; i < bufsize; i++) {
    oled_buf[i] = 0;
  }
  Wire.beginTransmission(OLED_ADDRESS);
  Wire.write(OLED_COMMAND_MODE);
  Wire.write(0x21); Wire.write(0); Wire.write(127);
  Wire.write(0x22); Wire.write(0); Wire.write(3);
  Wire.endTransmission();
  for (int i = 0; i < 32; i++) {
    Wire.beginTransmission(OLED_ADDRESS);
    Wire.write(OLED_DATA_MODE);
    for (int i = 0; i < 32; i++) Wire.write(0);
    Wire.endTransmission();
  }
}

void dot(byte x, byte y, boolean state) {
  byte byteY;
  if (y < 4) byteY = y;
  else if (y < 8) byteY = y - 4;
  else if (y < 12) byteY = y - 8;
  else byteY = y - 12;

  byte index = x + y / 4 * 64;
  byte thisByte = oled_buf[index];

  bitWrite(thisByte, byteY * 2, state);
  bitWrite(thisByte, byteY * 2 + 1, state);
  oled_buf[index] = thisByte;
  Wire.beginTransmission(OLED_ADDRESS);
  Wire.write(OLED_COMMAND_MODE);
  Wire.write(0x21); Wire.write(x * 2); Wire.write(127);
  Wire.write(0x22); Wire.write(y / 4); Wire.write(3);
  Wire.endTransmission();

  Wire.beginTransmission(OLED_ADDRESS);
  Wire.write(OLED_DATA_MODE);
  Wire.write(thisByte); Wire.write(thisByte);
  Wire.endTransmission();
  Wire.beginTransmission(OLED_ADDRESS);
}

void dotSet(byte x, byte y) {
  dot(x, y, 1);
}

void dotClear(byte x, byte y) {
  dot(x, y, 0);
}

void line(byte x0, byte y0, byte x1, byte y1) {
  if (x0 == x1) {
    for (byte i = y0; i < y1; i++) dotSet(x0, i);
  } else if (y0 == y1) {
    for (byte i = x0; i < x1; i++) dotSet(i, y0);
  } else {
    int sx, sy, e2, err;
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    if (x0 < x1) sx = 1; else sx = -1;
    if (y0 < y1) sy = 1; else sy = -1;
    err = dx - dy;
    for (;;) {
      dotSet(x0, y0);
      if (x0 == x1 && y0 == y1) return;
      e2 = err << 1;
      if (e2 > -dy) {
        err = err - dy;
        x0 = x0 + sx;
      }
      if (e2 < dx) {
        err = err + dx;
        y0 = y0 + sy;
      }
    }
  }
}

void digit(int c, int column, int line) {
  Wire.beginTransmission(OLED_ADDRESS);
  Wire.write(OLED_COMMAND_MODE);
  // Set column address range
  Wire.write(0x21); Wire.write(column * 6); Wire.write(column * 6 + Scale * 6 - 1);
  // Set page address range
  Wire.write(0x22); Wire.write(line); Wire.write(line + Scale - 1);
  Wire.endTransmission();
  Wire.beginTransmission(OLED_ADDRESS);
  Wire.write(OLED_DATA_MODE);
  for (uint8_t col = 0 ; col < 6; col++) {
    int bits = pgm_read_byte(&CharMap[c][col]);
    if (Scale == 1) Wire.write(bits);
    else {
      bits = Stretch(bits);
      for (int i = 2; i--;) {
        Wire.write(bits);
        Wire.write(bits >> 8);
      }
    }
  }
  Wire.endTransmission();
}

int Stretch (int x) {
  x = (x & 0xF0) << 4 | (x & 0x0F);
  x = (x << 2 | x) & 0x3333;
  x = (x << 1 | x) & 0x5555;
  return x | x << 1;
}
