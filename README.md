# UEMPI-FARM-GUARD
# Smart Farm IoT Based (ESP32 + Blynk + DHT22 + MQ135)

Proyek ini merupakan sistem Smart Farm IoT berbasis ESP32, yang dapat memantau suhu, kelembapan, dan kadar gas menggunakan sensor DHT22 dan MQ135.  
Sistem ini juga dapat mengontrol kipas secara otomatis maupun manual melalui platform Blynk Cloud dan menampilkan data secara langsung di LCD I2C 20x4.

**Fitur Utama**
- Pemantauan Suhu dan Kelembapan menggunakan DHT22  
- Pemantauan Kualitas Udara (gas amonia, CO₂, dll) dengan sensor MQ135  
- Kontrol Kipas Otomatis/Manual melalui aplikasi Blynk  
- Indikator LED untuk status kipas  
- LCD I2C 20x4 menampilkan data real-time  
- Terintegrasi Blynk IoT Cloud* dengan antarmuka dashboard

**Komponen yang Digunakan**
- ESP32 | Microcontroller | Otak sistem dan koneksi WiFi 
- DHT22 | Sensor suhu & kelembapan | Mengukur suhu dan kelembapan 
- MQ135 | Sensor gas | Mendeteksi gas amonia/CO₂ 
- Relay 5V | Modul output | Menghidupkan kipas 
- LCD I2C 20x4 | Display | Menampilkan data sensor 
- LED Hijau & Merah | Indikator | Menunjukkan status kipas 
- Blynk Cloud | Platform IoT | Kontrol dan pemantauan online 

**Pinout ESP32**
- DHT22 | GPIO 15 
- MQ135 | GPIO 34 (Analog) 
- Relay | GPIO 25 
- LED Hijau | GPIO 12 
- LED Merah | GPIO 13 
- LCD I2C | SDA (21), SCL (22) 

**Logika Sistem**
- Jika suhu > 30.99°C atau gas > 500 ppm, kipas akan menyala otomatis.  
- Kipas akan mati dengan delay 5 detik setelah kondisi normal kembali.  
- Mode manual memungkinkan kontrol kipas langsung dari aplikasi Blynk.

**Dashboard Blynk**
- | V0 | Suhu 
- | V1 | Kelembapan 
- | V2 | Gas (ppm) 
- | V3 | Kontrol kipas manual 
- | V4 | Pilih mode otomatis/manual 
- | V5 | Status kipas 
- | V6 | Indikator mode 

**Cara Upload Program**
1. Buka *Arduino IDE*
2. Pilih board *ESP32 Dev Module*
3. Masukkan *Blynk Template ID*, *Name*, dan *Auth Token*
4. Upload ke ESP32 melalui kabel data
5. Jalankan dan pantau hasil di *LCD* dan *Blynk App*

---

**Pengembang**
*Trisna Azka Mahardika*  
> Sistem IoT ini dikembangkan untuk otomatisasi lingkungan peternakan berbasis sensor dan koneksi cloud.
