#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // ширина дисплея в пикселях
#define SCREEN_HEIGHT 64 // высота дисплея в пикселях

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Пины
#define BUTTON_PIN 0 // Кнопка для переключения заставок

// Переменные для заставок
int currentScreenSaver = 0;
const int totalScreenSavers = 6; // Общее количество заставок
unsigned long lastSwitchTime = 0;
const unsigned long switchInterval = 10000; // Интервал переключения заставок (мс)

// Переменные для заставки 1 (DVD логотип)
int x = 0;
int y = 0;
int xSpeed = 2;
int ySpeed = 2;
int logoWidth = 32;
int logoHeight = 16;

// Переменные для заставки 2 (Матрица)
const int numColumns = SCREEN_WIDTH / 6;
int drops[numColumns];

// Переменные для заставки 3 (Бегущая строка)
String scrollText = "Привет, это бегущая строка!";
int16_t scrollX = SCREEN_WIDTH;

// Переменные для заставки 4 (Звёздное небо)
struct Star {
  int x;
  int y;
  int brightness;
};
const int numStars = 50;
Star stars[numStars];

// Переменные для заставки 5 (Аналоговые часы)
// Нет дополнительных переменных

// Переменные для заставки 6 (Пользовательский битмап)
const unsigned char myBitmap[] PROGMEM = {
  // Пример простого битмапа 16x16 пикселей
  0xFF, 0xFF, 0x81, 0x81, 0xBD, 0xBD, 0xA5, 0xA5,
  0xA5, 0xA5, 0xBD, 0xBD, 0x81, 0x81, 0xFF, 0xFF,
  // Добавьте здесь остальные данные вашего битмапа
};
int bitmapWidth = 16;
int bitmapHeight = 16;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Инициализация дисплея
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Не удалось инициализировать дисплей SSD1306"));
    for (;;);
  }
  display.clearDisplay();

  // Инициализация для заставки "Матрица"
  for (int i = 0; i < numColumns; i++) {
    drops[i] = random(-20, 0);
  }

  // Инициализация звёзд
  for (int i = 0; i < numStars; i++) {
    stars[i].x = random(0, SCREEN_WIDTH);
    stars[i].y = random(0, SCREEN_HEIGHT);
    stars[i].brightness = random(0, 2);
  }

  lastSwitchTime = millis();
}

void loop() {
  // Автоматическое переключение заставок по времени
  if (millis() - lastSwitchTime > switchInterval) {
    currentScreenSaver = (currentScreenSaver + 1) % totalScreenSavers;
    lastSwitchTime = millis();
  }

  // Проверка нажатия кнопки для ручного переключения заставок
  if (digitalRead(BUTTON_PIN) == LOW) {
    currentScreenSaver = (currentScreenSaver + 1) % totalScreenSavers;
    delay(200); // Антидребезг
  }

  switch (currentScreenSaver) {
    case 0:
      screenSaverDVDLogo();
      break;
    case 1:
      screenSaverMatrix();
      break;
    case 2:
      screenSaverScrollingText();
      break;
    case 3:
      screenSaverStarfield();
      break;
    case 4:
      screenSaverAnalogClock();
      break;
    case 5:
      screenSaverBitmap();
      break;
  }
}

// Заставка 1: Плавающий логотип DVD
void screenSaverDVDLogo() {
  display.clearDisplay();
  display.fillRect(x, y, logoWidth, logoHeight, SSD1306_WHITE);
  display.display();

  x += xSpeed;
  y += ySpeed;

  if (x <= 0 || x + logoWidth >= SCREEN_WIDTH) {
    xSpeed = -xSpeed;
  }
  if (y <= 0 || y + logoHeight >= SCREEN_HEIGHT) {
    ySpeed = -ySpeed;
  }

  delay(20);
}

// Заставка 2: Матрица
void screenSaverMatrix() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  for (int i = 0; i < numColumns; i++) {
    char c = random(33, 126);
    int x = i * 6;
    int y = drops[i] * 8;

    display.setCursor(x, y);
    display.write(c);

    if (drops[i] * 8 > SCREEN_HEIGHT && random(0, 100) > 98) {
      drops[i] = random(-10, 0);
    } else {
      drops[i]++;
    }
  }

  display.display();
  delay(50);
}

// Заставка 3: Бегущая строка
void screenSaverScrollingText() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(scrollX, SCREEN_HEIGHT / 2);
  display.print(scrollText);
  display.display();

  scrollX -= 2;
  if (scrollX < -scrollText.length() * 6) {
    scrollX = SCREEN_WIDTH;
  }

  delay(20);
}

// Заставка 4: Звёздное небо
void screenSaverStarfield() {
  display.clearDisplay();

  for (int i = 0; i < numStars; i++) {
    display.drawPixel(stars[i].x, stars[i].y, stars[i].brightness ? SSD1306_WHITE : SSD1306_BLACK);
    stars[i].brightness = !stars[i].brightness;
  }

  display.display();
  delay(100);
}

// Заставка 5: Аналоговые часы
void screenSaverAnalogClock() {
  display.clearDisplay();

  int centerX = SCREEN_WIDTH / 2;
  int centerY = SCREEN_HEIGHT / 2;
  int radius = min(centerX, centerY) - 5;

  // Циферблат
  display.drawCircle(centerX, centerY, radius, SSD1306_WHITE);

  // Часовые метки
  for (int i = 0; i < 12; i++) {
    float angle = i * 30 * PI / 180;
    int x1 = centerX + (radius - 2) * sin(angle);
    int y1 = centerY - (radius - 2) * cos(angle);
    int x2 = centerX + radius * sin(angle);
    int y2 = centerY - radius * cos(angle);
    display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
  }

  // Секундная стрелка
  float secondAngle = millis() / 1000.0 * 6 * PI / 180;
  int xSec = centerX + (radius - 5) * sin(secondAngle);
  int ySec = centerY - (radius - 5) * cos(secondAngle);
  display.drawLine(centerX, centerY, xSec, ySec, SSD1306_WHITE);

  display.display();
  delay(100);
}

// Заставка 6: Пользовательский битмап
void screenSaverBitmap() {
  display.clearDisplay();

  // Отображаем битмап в центре экрана
  display.drawBitmap(
    (SCREEN_WIDTH - bitmapWidth) / 2,
    (SCREEN_HEIGHT - bitmapHeight) / 2,
    myBitmap,
    bitmapWidth,
    bitmapHeight,
    SSD1306_WHITE
  );

  display.display();
  delay(2000); // Отображаем битмап в течение 2 секунд
}
