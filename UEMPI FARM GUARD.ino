#define BLYNK_TEMPLATE_ID "TMPL6rsCUeOa4"
#define BLYNK_TEMPLATE_NAME "SMART FARM IoT BASED"
#define BLYNK_AUTH_TOKEN "uNnf3MLj20KqmEfLOk-js96_B8OSlnHx"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

char ssid[] = "mahardikaXR";
char pass[] = "12345678";

#define DHTPIN 15
#define DHTTYPE DHT22
#define MQ135_PIN 34
#define RELAY_PIN 25
#define LED_HIJAU 12
#define LED_MERAH 13

DHT dhtSensor(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);

float suhu, kelembapan;
int gasValue;
bool kipasState = false;
bool modeOtomatis = true;
unsigned long kipasOffDelayStart = 0;   // waktu mulai delay mati kipas
bool pendingOff = false;                // status penundaan kipas mati

BLYNK_WRITE(V3) {
  if (!modeOtomatis) {
    kipasState = param.asInt();
    digitalWrite(RELAY_PIN, kipasState ? HIGH : LOW);
    Blynk.virtualWrite(V5, kipasState);
  }
}

BLYNK_WRITE(V4) {
  int mode = param.asInt();
  modeOtomatis = (mode == 0);
  Serial.print("Mode: ");
  Serial.println(modeOtomatis ? "Otomatis" : "Manual");
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  SMARTFARM SYSTEM ");
  delay(1500);
  lcd.clear();

  dhtSensor.begin();
  pinMode(MQ135_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_HIJAU, LOW);
  digitalWrite(LED_MERAH, HIGH);

  Serial.println("Menghubungkan ke WiFi...");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi terhubung!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  Blynk.config(BLYNK_AUTH_TOKEN);
  while (!Blynk.connect()) {
    Serial.println("Menghubungkan ke Blynk...");
    delay(1000);
  }
  Serial.println("Terhubung ke Blynk Cloud!");
}

void loop() {
  Blynk.run();

  suhu = dhtSensor.readTemperature();
  kelembapan = dhtSensor.readHumidity();
  gasValue = analogRead(MQ135_PIN);

  if (isnan(suhu) || isnan(kelembapan)) return;

  if (modeOtomatis) {
    bool kondisiAktif = (suhu > 30.99 || gasValue > 500);

    if (kondisiAktif) {
      kipasState = true;
      pendingOff = false;  // batalkan delay jika kondisi aktif lagi
    } else {
      // jika sebelumnya kipas menyala dan belum delay
      if (kipasState && !pendingOff) {
        pendingOff = true;
        kipasOffDelayStart = millis();
      }
      // jika sudah 5 detik berlalu sejak kondisi turun
      if (pendingOff && (millis() - kipasOffDelayStart >= 5000)) {
        kipasState = false;
        pendingOff = false;
      }
    }

    digitalWrite(RELAY_PIN, kipasState ? HIGH : LOW);
  }

  if (kipasState) {
    digitalWrite(LED_HIJAU, HIGH);
    digitalWrite(LED_MERAH, LOW);
  } else {
    digitalWrite(LED_HIJAU, LOW);
    digitalWrite(LED_MERAH, HIGH);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp : ");
  lcd.print(suhu, 2);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humy : ");
  lcd.print(kelembapan, 2);
  lcd.print(" %");

  lcd.setCursor(0, 2);
  lcd.print("Gas  : ");
  lcd.print(gasValue);
  lcd.setCursor(13, 2);
  lcd.print("ppm");

  lcd.setCursor(0, 3);
  lcd.print("Mode:");
  lcd.print(modeOtomatis ? "AUTO " : "MAN  ");
  lcd.setCursor(12, 3);
  lcd.print("Fan:");
  lcd.print(kipasState ? "ON " : "OFF");

  Blynk.virtualWrite(V0, suhu);
  Blynk.virtualWrite(V1, kelembapan);
  Blynk.virtualWrite(V2, gasValue);
  Blynk.virtualWrite(V5, kipasState);
  Blynk.virtualWrite(V6, modeOtomatis);

  delay(2000);
}
