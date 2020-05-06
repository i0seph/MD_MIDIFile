# esp32 SPIFFS 안에 있는 미디 파일 연주하기

## 필요한 것들

### 하드웨어
1. esp32 개발 보드
2. 점퍼선 3개
3. 스피커 또는 부저

### 소프트웨어
1. 아두이노 개발환경 + esp32 개발 환경
1. esp32 SPIFFS 용으로 바꾼 MD_MIDIFile 라이브러리
1. ESP32Servo 라이브러리

## 만들기

### 하드웨어
스피커 + 단자 ----------- io18, io19 
스피커 - 단자 ----------- ground
끝!

### 소프트웨어

이 MD_MIDIFile 패키지 전체를 zip 파일로 다운 받아 zip 파일을 아두이노 IDE에 등록하고, 

예제에서 ReadMidiFilebyESP32Tone 항목을 찾아 불러온 뒤, 
IDE 툴 메뉴에서 ESP32 Sketch Data Upload 메뉴를 선택해서, 예제 디렉터리안에 있는 data/score.mid 파일을 
SPIFFS 파티션으로 복사한다. 

예제 파일 컴파일 업로드.

바흐 인벤션 13번 Am 이다.

