import re

with open('miniWeather.ino', 'r') as f:
    content = f.read()

# 1. Remove #include <EEPROM.h>
content = re.sub(r'#include\s*<EEPROM.h>\n', '', content)

# 2. Remove Relay PIN and Firecrit blocks
content = re.sub(r'// ====== PIN RELAY \(WEMOS D1 MINI\) ======.*?FirebaseConfig config;\n', '', content, flags=re.DOTALL)

# 3. Remove EEPROM.begin(512);
content = re.sub(r'\s*EEPROM\.begin\(512\);\s*// Alokasikan 512 byte EEPROM\n', '', content)

# 4. Remove Relay setup in setup()
content = re.sub(r'\s*pinMode\(RELAY1_PIN, OUTPUT\);\s*pinMode\(RELAY2_PIN, OUTPUT\);\s*// Ambil kondisi terakhir dari EEPROM\s*l1 = EEPROM.read\(0\);\s*// alamat 0 untuk l1\s*l2 = EEPROM.read\(1\);\s*// alamat 1 untuk l2\s*// Terapkan kondisi terakhir ke relay \(aktif LOW\)\s*digitalWrite\(RELAY1_PIN, l1 \? LOW : HIGH\);\s*digitalWrite\(RELAY2_PIN, l2 \? LOW : HIGH\);\n', '', content)

# 5. Remove Firebase setup in setup()
content = re.sub(r'\s*// Firecrit\s*config\.api_key = API_KEY;.*?Firebase\.setDoubleDigits\(2\);\n', '', content, flags=re.DOTALL)

# 6. Remove set_relay() call in loop()
content = re.sub(r'\s*set_relay\(\);\n', '\n', content)

# 7. Remove set_relay() function
content = re.sub(r'void set_relay\(\)\{.*?\n\}\n', '', content, flags=re.DOTALL)

# 8. Remove Firebase upload in set_weather()
content = re.sub(r'\s*if \(currentYear == tahunSekarang\)\{.*?\}\n\s*\}\n', '\n', content, flags=re.DOTALL)

with open('miniWeather.ino', 'w') as f:
    f.write(content)
