# Analisa Flow Program miniWeather

Program ini merupakan sistem penunjuk cuaca IoT (Internet of Things) berbasis ESP8266 (Wemos D1 Mini). Fungsi utamanya adalah:
Mengambil data cuaca dan metrik lingkungan dari internet (menggunakan API eksternal) dan menampilkan informasi tersebut secara *real-time* di layar OLED, beserta waktu terkini.

Program ini kini dipecah menjadi dua buah file ekstensi `.ino`:
- `miniWeather.ino`: File utama yang memuat konfigurasi awal (inisialisasi WiFi, NTP, layar), loop penjadwalan utama, serta logika untuk *request* HTTP dan me-render data cuaca ke layar.
- `z_icon.ino`: File sumber daya visual yang berisi sekumpulan data *bitmap array* (disimpan di PROGMEM) untuk menggambar ikon-ikon cuaca pada layar OLED.

---

## Alur Program (Program Flow)

### 1. Inisialisasi - Fungsi `setup()`
Blok ini berjalan satu kali setiap kali perangkat menyala atau mengalami restart.
- **Inisialisasi Perangkat Keras & Layar:** Memulai komunikasi `Serial` untuk keperluan *debugging*, serta menginisialisasi modul layar OLED (`display.begin()`). Teks pembuka seperti "OLED WEATHER MONITORING" akan ditampilkan sejenak di layar.
- **Koneksi Jaringan Pintar (WiFiManager):** Perangkat tidak lagi menyimpan *SSID* dan *Password* secara kaku di dalam kode. Jika gagal terhubung ke jaringan yang tersimpan, ia akan memancarkan sinyal hotspot (*Access Point*) bernama **Wemos_Cuaca**. Pengguna dapat terhubung ke hotspot tersebut lewat *smartphone* atau laptop, dan sebuah halaman portal web otomatis akan muncul untuk memasukkan *SSID* dan sandi WiFi lokal. Layar OLED juga akan memandu proses ini.
- **Over-The-Air (OTA):** Mengaktifkan `ArduinoOTA` yang mendengarkan permintaan *upload code* dari Arduino IDE lewat jaringan WiFi. Selama proses *upload* nirkabel berjalan, layar OLED akan menampilkan persentase progres unduhan, membuat pembaruan *firmware* masa depan bisa dilakukan murni tanpa kabel.
- **Memulai Layanan:** Menjalankan klien NTP (`timeClient.begin()`) untuk menyinkronkan jam dengan server internet (NTP). Karena data cuaca menggunakan HTTPS, program juga mengatur `client.setInsecure()` agar ESP8266 dapat mengakses HTTPS API tanpa perlu memverifikasi sertifikat SSL.

### 2. Loop Utama - Fungsi `loop()`
Blok ini dieksekusi terus-menerus tiada henti.
- Program menggunakan metode penundaan tanpa blokir (*non-blocking delay*) dengan perintah `millis()`. Metode ini membuat program menanti hingga **5 detik (5000 ms)** berlalu.
- Setiap kali durasi 5 detik tersebut tercapai, *timer* di-*reset* ulang dan program akan mengeksekusi rutinitas `set_weather()`.

### 3. Logika Cuaca & Sinkronisasi Layar - Fungsi `set_weather()`
Fungsi inti ini dipanggil dari dalam *loop* setiap 5 detik. Alur dari instruksinya terbagi menjadi dua tahapan:

**Tahap A: Sinkronisasi Waktu dan Celah *Rate Limit***
- **Update Waktu:** Memanggil NTP Client untuk mengambil nilai jam dan menit terkini dengan zona waktu yang telah diatur (WIB).
- **Gateway Menit:** Mengingat penyedia API biasanya memiliki batas jumlah panggilan maksimal, program membandingkan *menit yang tertera saat ini* dengan *menit saat terakhir kali API berhasil dipanggil*.
- Jika belum terjadi pergantian menit di jam internal, fungsi akan ditolak dan dihentikan dengan perintah `return;`. Layar OLED membiarkan data sebelumnya terpampang statis.
- Jika angka menit pada jam berubah, fungsi berlanjut ke tahap *request*.

**Tahap B: Eksekusi API & Render Layar (Berjalan 1 Menit Sekali)**
- **HTTPS GET API:** ESP8266 meluncurkan request aman menggunakan `WiFiClientSecure` ke server *API Ryzumi* khusus untuk cuaca di kota Tulungagung. Jika kode respons yang diterima bukan 200 (seperti *timeout* / tidak ada koneksi), perangkat memunculkan pesan peringatan "Fetching Data" dan akan berputar-putar mencoba request ulang tiap 1 detik.
- **Ekstraksi JSON:** Setelah sukses menarik data JSON dari server, program menggunakan `ArduinoJson` untuk membedah (*parsing*) respons tersebut. Properti seperti *temp* (suhu aktual), *feels_like* (suhu terasa), *humidity* (kelembapan), dan *description* (kondisi awan/cuaca) diekstrak dan disimpan di variabel.
- **Me-Render ke Layar OLED:**
  - Kanvas layar dibersihkan total (`clearDisplay()`).
  - Beragam elemen diletakkan: jam dan menit di pojok kanan atas, nama kota di bawahnya dengan garis bawah dekoratif.
  - Ikon cuaca statis digambar di sisi kiri layar dengan instruksi `drawBitmap()`.
  - Angka suhu utama ditampilkan besar di sebelah kanan ikon, sementara suhu terasa (*feels like*) digambar lebih kecil.
  - Teks kondisi cuaca (deskripsi dan persentase kelembapan) ditaruh di sisi paling bawah layar.
  - Semua visual baru diunggah ke *hardware* OLED (`display()`).
  - Terakhir, animasi *marquee* (*scroll*) dihidupkan untuk baris bagian bawah supaya tulisan deskripsi yang memanjang bisa terbaca dengan bergerak secara horizontal.

### 4. Aset Grafis Sub-rutin - File `z_icon.ino`
Berperan sebagai pustaka aset/elemen UI *hardcoded*. Memuat sekumpulan tipe data larik heksadesimal yang menyusun matriks piksel ikon cuaca (awan, hujan, badai, dll). Memanfaatkan sintaks memori `PROGMEM` agar matriks berukuran besar ini diarsip ke memori ROM (Flash) tanpa membebani memori eksekusi utama (SRAM) ESP8266.

---
## Kesimpulan
Sistem modular program ini bekerja dengan keseimbangan interval waktu: parameter internal (*timer* jam) diperiksa secara reaktif tiap **5 detik**, sementara proses unduhan data suhu dan cuaca dari API eksternal hanya dilakukan **sekali dalam semenit**. Penggunaan format *secure client* dan pembatasan laju (*rate limiting*) ini membuat penarikan data JSON dari API berjalan aman, ramah beban, sekaligus menyuguhkan tayangan status cuaca seketika (real-time) dengan tata letak visual pada layar OLED mungil.
