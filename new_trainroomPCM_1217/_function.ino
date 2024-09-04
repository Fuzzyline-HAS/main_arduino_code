void set_adr(){
  training[EM] = {"EM",{0x00,0x13,0xA2,0x00,0x41,0xE3,0x86,0x4C},{0x00,0x00},false}; // 훈련소 무빙라이트  
  training[ET] = {"ET",{0x00,0x13,0xA2,0x00,0x41,0xE3,0x85,0xF9},{0x00,0x00},false}; // 훈련소 태그머신
  training[ER] = {"ER",{0x00,0x13,0xA2,0x00,0x41,0xE3,0x73,0xB0},{0x00,0x00},false}; // 훈련소 생명장치  73  B0
  training[EI] = {"EI",{0x00,0x13,0xA2,0x00,0x41,0xE3,0x63,0xA7},{0x00,0x00},false}; // 훈련소 아이템박스 63  A7
}

//****************************************Mode_change()****************************************************************
int Mode_Change(byte SH[4], byte SL[4], byte MY[2], byte DATA[], int DATA_LENGTH){        // Receive packet일때 실행되는 함수
  Serial.print("64bit_Address: ");                          // address: 0~7 행열 data: 8~n 행열
  for(int i = 0 ; i <4; i++){ 
    Serial.print("0x");                               // address 출력
    Serial.print(SH[i],HEX);  
    Serial.print(", ");
  }
  for(int i = 0 ; i <4; i++){ 
    Serial.print("0x");                               // address 출력
    Serial.print(SL[i],HEX);  
    Serial.print(", ");
  }
  Serial.print("\n16bit_Address: ");
  for(int i = 0 ; i <2; i++){ 
    Serial.print("0x");                               // address 출력
    Serial.print(MY[i],HEX);  
    Serial.print(", ");
  }
  Serial.print("\nASCII: ");                           // address: 0~7 행열 data: 8~n 행열
  String data_string = "";
  for(int i = 0 ; i < DATA_LENGTH; i++){
    Serial.print((char)DATA[i]);
    data_string += String((char)DATA[i]);
  }
}



//****************************************Mp3_Setup()****************************************************************
void Mp3_Setup(){
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  myDFPlayer.setTimeOut(1000); //Set serial communictaion time out 1000 ms

  if (!myDFPlayer.begin(Serial1)) { //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  //----Set volume----
  myDFPlayer.volume(30);  //Set volume value (0~30).
  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  //myDFPlayer.enableDAC();  //Enable On-chip DAC
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  //myDFPlayer.play(1);  //Play the first mp3
  //Serial.println(myDFPlayer.readState());
}//void MP3_SETUP
