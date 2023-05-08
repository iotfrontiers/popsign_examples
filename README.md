## 아두이노 설정

### IDE Setting (LighitBoard, Weight Display . . .)

- Board - ESP32 Dev Module
- Upload Speed - 921600
- CPU Frequency - 240MHz
- Flash Frequency - 80MHz
- Flash Mode - QIO
- PSRAM - Enabled
- Arduino Runs On - Core 0
- Events Run On - Core 1
- Flash Size - 16MB
- Partition Scheme - Popsign 16M Flash

* Arduino Runs On 0, vents Run On 1 으로 설정하는 경우 loop에서 최소 delay() 주지 않으면 Reset 되는 이슈 있음
-> 솔루션 1:Arduino Runs On 1, vents Run On 0 
   솔루션 2:Arduino Runs On 0, vents Run On 1 (loop() 함수 내 delay 추가)  -> 해당 방법이 core 속도면에서 뛰어남

### Board Config
##### config.h 파일에서 "#define MODEL_VALUE"에 원하는 보드를 설정한다.
- LIGHT1 : MASTER_0064_0032_16M
- LIGHT2 : MASTER_0128_0032_16M
- LIGHT3 : MASTER_0192_0032_16M
- LoRa3 : LORA_0192_0032_16M
