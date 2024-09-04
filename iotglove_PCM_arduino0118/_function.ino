void serialInput(){
  if(Serial.available()){
    String iot_controlboard_RX = Serial.readStringUntil('\n');
    //Serial.println(iot_controlboard_RX);
    String iotgroup = iot_controlboard_RX.substring(0,2);
    
    if(iotgroup == "G1"){
      Serial.println("G1 SELECTED");
      iotControl_serial1(iot_controlboard_RX);
    }
    else if(iotgroup == "G2"){
      Serial.println("G2 SELECTED");
      iotControl_serial2(iot_controlboard_RX);
      
    }
  }
}
void iotControl_serial1(String iot_controlboard_RX){

  if(iot_controlboard_RX == "G1_LN"){         //술래 결정 보내기
    Serial.println("killer send");
    byte killer_adr1[4];
    for(int i = 0; i < 4; i++)
      killer_adr1[i] = G1[G1_killer_player].mac[i+4]; 
    Serial.println(G1[G1_killer_player].name + " is KILLER!");
    XBEE3_serial1_Transmit_Request_HEX(xbee3_broadcast_adr, killer_adr1, sizeof(killer_adr1));
  }
  else if(iot_controlboard_RX == "G1_LR"){    //16bit_setting 보내기
    Serial.println("killer set");
    XBEE3_serial1_Transmit_Request_ASCII(xbee3_broadcast_adr, "16bit_setting ");
    //Serial1.write(xbee3_serial1_16bit_setting,sizeof(xbee3_serial1_16bit_setting));
  }
  else if(iot_controlboard_RX == "G1_RR"){         //술래 재결정 보내기
    Serial.println("killer RE send");
    byte killer_RE_adr[6] = {0x52,0x45,0x00,0x00,0x00,0x00};
    for(int i = 0; i < 4; i++)
      killer_RE_adr[i+2] = G1[G1_killer_player].mac[i+4];
    Serial.println(G1[G1_killer_player].name + " is RE KILLER!");
    XBEE3_serial1_Transmit_Request_HEX(xbee3_broadcast_adr, killer_RE_adr, sizeof(killer_RE_adr));
  }
  else if(iot_controlboard_RX == "G1_AT"){         //술래 재결정 보내기
    Serial.println("killer TEMPLE START send");
    byte killer_RE_adr[6] = {0x41,0x54,0x00,0x00,0x00,0x00};
    for(int i = 0; i < 4; i++)
      killer_RE_adr[i+2] = G1[G1_killer_player].mac[i+4];
    Serial.println(G1[G1_killer_player].name + " is TEMPLE KILLER!");
    XBEE3_serial1_Transmit_Request_HEX(xbee3_broadcast_adr, killer_RE_adr, sizeof(killer_RE_adr));
  }
  else if(iot_controlboard_RX == "G1_RT"){         //술래 재결정 보내기R
    Serial.println("killer RETEMPLE START send");
    byte killer_RE_adr[6] = {0x52,0x54,0x00,0x00,0x00,0x00};
    for(int i = 0; i < 4; i++)
      killer_RE_adr[i+2] = G1[G1_killer_player].mac[i+4];
    Serial.println(G1[G1_killer_player].name + " is RETEMPLE KILLER!");
    XBEE3_serial1_Transmit_Request_HEX(xbee3_broadcast_adr, killer_RE_adr, sizeof(killer_RE_adr));
  }
  else if(iot_controlboard_RX == "G1_START"){         //술래 재결정 보내기
    Serial.println("killer BROADCAST START send");
    XBEE3_serial1_Transmit_Request_ASCII(xbee3_broadcast_adr, "KILLER_TEMPLE_START ");
  }
  else if(iot_controlboard_RX == "G1_SHOW"){
    Serial.println("SHOW!!!!!!!");
    XBEE3_serial1_Transmit_Request_ASCII(xbee3_broadcast_adr, "SHOW ");
  }
  else if(iot_controlboard_RX == "G1_VIBE_TEST"){
    Serial.println("VIBE_TEST");
    XBEE3_serial1_Transmit_Request_ASCII(xbee3_broadcast_adr, "VIBE_TEST ");
  }
  else if(iot_controlboard_RX == "G1_VIBE_ON"){
    Serial.println("VIBE_ON");
    XBEE3_serial1_Transmit_Request_ASCII(xbee3_broadcast_adr, "VIBE_ON ");
  }
  else if(iot_controlboard_RX == "G1_VIBE_OFF"){
    Serial.println("VIBE_OFF");
    XBEE3_serial1_Transmit_Request_ASCII(xbee3_broadcast_adr, "VIBE_OFF ");
  }
  else if(iot_controlboard_RX == "G1_ALL_RESET"){
    Serial.println("G1_ALL_RESET");
    XBEE3_serial1_Transmit_Request_ASCII(xbee3_broadcast_adr, "W ");
  }
  else if(iot_controlboard_RX == "G1_ALL_NIGHT"){
    Serial.println("G1_ALL_NIGHT");
    XBEE3_serial1_Transmit_Request_ASCII(xbee3_broadcast_adr, "N ");
  }
  else if(iot_controlboard_RX == "G1_ALL_DAY"){
    Serial.println("G1_ALL_DAY");
    XBEE3_serial1_Transmit_Request_ASCII(xbee3_broadcast_adr, "D ");
  }
  else if(iot_controlboard_RX == "G1_WT_89"){
    Serial.println("G1_90sec");
    XBEE3_serial1_Transmit_Request_ASCII(xbee3_broadcast_adr, "WT_89 ");
  }
  else if(iot_controlboard_RX == "G1_WT_179"){
    Serial.println("G1_180sec");
    XBEE3_serial1_Transmit_Request_ASCII(xbee3_broadcast_adr, "WT_179 ");
  }
  else if(iot_controlboard_RX == "G1_STN"){
    Serial.println("G1_showtime");
    XBEE3_serial1_Transmit_Request_ASCII(xbee3_broadcast_adr, "STN ");
  }
  else if(iot_controlboard_RX == "G1_STA"){
    Serial.println("G1_showtime");
    XBEE3_serial1_Transmit_Request_ASCII(xbee3_broadcast_adr, "STA ");
  }
  else if(iot_controlboard_RX == "G1_STL_90"){
    Serial.println("G1_180sec");
    XBEE3_serial1_Transmit_Request_ASCII(xbee3_broadcast_adr, "STL90 ");
  }
  
  else if(iot_controlboard_RX == "G1_P1"){
    G1_killer_player = G1_P1;
    Serial.println("SET P1 as KILLER");
  }
  else if(iot_controlboard_RX == "G1_P2"){
    G1_killer_player = G1_P2;
    Serial.println("SET P2 as KILLER");
  }
  else if(iot_controlboard_RX == "G1_P3"){
    G1_killer_player = G1_P3;
    Serial.println("SET P3 as KILLER");
  }
  else if(iot_controlboard_RX == "G1_P4"){
    G1_killer_player = G1_P4;
    Serial.println("SET P4 as KILLER");
  }
  else if(iot_controlboard_RX == "G1_P5"){
    G1_killer_player = G1_P5;
    Serial.println("SET P5 as KILLER");
  }
  else if(iot_controlboard_RX == "G1_P6"){
    G1_killer_player = G1_P6;
    Serial.println("SET P6 as KILLER");
  }
  else if(iot_controlboard_RX == "G1_P7"){
    G1_killer_player = G1_P7;
    Serial.println("SET P7 as KILLER");
  }
  else if(iot_controlboard_RX == "G1_P8"){
    G1_killer_player = G1_P8;
    Serial.println("SET P8 as KILLER");
  }
}

void iotControl_serial2(String iot_controlboard_RX){

  if(iot_controlboard_RX == "G2_LN"){         //술래 결정 보내기
    Serial.println("killer send");
    byte killer_adr2[4];
    for(int i = 0; i < 4; i++)
      killer_adr2[i] = G2[G2_killer_player].mac[i+4]; 
    Serial.println(G2[G2_killer_player].name + " is KILLER!");
    XBEE3_serial2_Transmit_Request_HEX(xbee3_broadcast_adr, killer_adr2, sizeof(killer_adr2));
  }
  else if(iot_controlboard_RX == "G2_LR"){    //16bit_setting 보내기
    Serial.println("killer set");
    XBEE3_serial2_Transmit_Request_ASCII(xbee3_broadcast_adr, "16bit_setting ");
  }
  else if(iot_controlboard_RX == "G2_RR"){         //술래 재결정 보내기
    Serial.println("killer RE send");
    byte killer_RE_adr[6] = {0x52,0x45,0x00,0x00,0x00,0x00};
    for(int i = 0; i < 4; i++)
      killer_RE_adr[i+2] = G2[G2_killer_player].mac[i+4];
    Serial.println(G2[G2_killer_player].name + " is RE KILLER!");
    XBEE3_serial2_Transmit_Request_HEX(xbee3_broadcast_adr, killer_RE_adr, sizeof(killer_RE_adr));
  }
  else if(iot_controlboard_RX == "G2_AT"){         //술래 제단결정 보내기
    Serial.println("killer TEMPLE START send");
    byte killer_RE_adr[6] = {0x41,0x54,0x00,0x00,0x00,0x00};
    for(int i = 0; i < 4; i++)
      killer_RE_adr[i+2] = G2[G2_killer_player].mac[i+4];
    Serial.println(G2[G2_killer_player].name + " is TEMPLE KILLER!");
    XBEE3_serial2_Transmit_Request_HEX(xbee3_broadcast_adr, killer_RE_adr, sizeof(killer_RE_adr));
  }
  else if(iot_controlboard_RX == "G2_RT"){         //술래 제단결정 보내기
    Serial.println("killer RETEMPLE START send");
    byte killer_RE_adr[6] = {0x52,0x54,0x00,0x00,0x00,0x00};
    for(int i = 0; i < 4; i++)
      killer_RE_adr[i+2] = G2[G2_killer_player].mac[i+4];
    Serial.println(G2[G2_killer_player].name + " is RETEMPLE KILLER!");
    XBEE3_serial2_Transmit_Request_HEX(xbee3_broadcast_adr, killer_RE_adr, sizeof(killer_RE_adr));
  }
  else if(iot_controlboard_RX == "G2_START"){         //술래 재결정 보내기
    Serial.println("killer BROADCAST START send");
    XBEE3_serial2_Transmit_Request_ASCII(xbee3_broadcast_adr, "KILLER_TEMPLE_START ");
  }
  else if(iot_controlboard_RX == "G2_SHOW"){
    Serial.println("SHOW!!!!!!!");
    XBEE3_serial2_Transmit_Request_ASCII(xbee3_broadcast_adr, "SHOW ");
  }
    else if(iot_controlboard_RX == "G2_KILLER_COLOR"){
    Serial.println("KILLER_COLOR");
    XBEE3_serial2_Transmit_Request_ASCII(xbee3_broadcast_adr, "KILLER_COLOR ");
  }
  else if(iot_controlboard_RX == "G2_VIBE_TEST"){
    Serial.println("G2_VIBE_TEST");
    XBEE3_serial2_Transmit_Request_ASCII(xbee3_broadcast_adr, "VIBE_TEST ");
  }
  else if(iot_controlboard_RX == "G2_VIBE_ON"){
    Serial.println("G2_VIBE_ON");
    XBEE3_serial2_Transmit_Request_ASCII(xbee3_broadcast_adr, "VIBE_ON ");
  }
  else if(iot_controlboard_RX == "G2_VIBE_OFF"){
    Serial.println("G2_VIBE_OFF");
    XBEE3_serial2_Transmit_Request_ASCII(xbee3_broadcast_adr, "VIBE_OFF ");
  }
  
  else if(iot_controlboard_RX == "G2_WATCHDOG"){
    Serial.println("G2_WATCHDOG");
    XBEE3_serial2_Transmit_Request_ASCII(xbee3_broadcast_adr, "WATCHDOG ");
  }
  else if(iot_controlboard_RX == "G2_ALL_NIGHT"){
    Serial.println("G2_ALL_NIGHT");
    XBEE3_serial2_Transmit_Request_ASCII(xbee3_broadcast_adr, "N ");
  }
  else if(iot_controlboard_RX == "G2_ALL_DAY"){
    Serial.println("G2_ALL_DAY");
    XBEE3_serial2_Transmit_Request_ASCII(xbee3_broadcast_adr, "D ");
  }

  else if(iot_controlboard_RX == "G2_WT_89"){
    Serial.println("G2_89sec");
    XBEE3_serial2_Transmit_Request_ASCII(xbee3_broadcast_adr, "WT_89 ");
  }
  else if(iot_controlboard_RX == "G2_WT_179"){
    Serial.println("G2_179sec");
    XBEE3_serial2_Transmit_Request_ASCII(xbee3_broadcast_adr, "WT_179 ");
  }
  else if(iot_controlboard_RX == "G2_STN"){
    Serial.println("G2_showtime");
    XBEE3_serial2_Transmit_Request_ASCII(xbee3_broadcast_adr, "STN ");
  }
  else if(iot_controlboard_RX == "G2_STA"){
    Serial.println("G2_showtime");
    XBEE3_serial2_Transmit_Request_ASCII(xbee3_broadcast_adr, "STA ");
  }
  else if(iot_controlboard_RX == "G2_STL_90"){
    Serial.println("G2_showtime_90");
    XBEE3_serial2_Transmit_Request_ASCII(xbee3_broadcast_adr, "STL90 ");
  }
  
  else if(iot_controlboard_RX == "G2_P1"){
    G2_killer_player = G2_P1;
    Serial.println("SET P1 as KILLER");
  }
  else if(iot_controlboard_RX == "G2_P2"){
    G2_killer_player = G2_P2;
    Serial.println("SET P2 as KILLER");
  }
  else if(iot_controlboard_RX == "G2_P3"){
    G2_killer_player = G2_P3;
    Serial.println("SET P3 as KILLER");
  }
  else if(iot_controlboard_RX == "G2_P4"){
    G2_killer_player = G2_P4;
    Serial.println("SET P4 as KILLER");
  }
  else if(iot_controlboard_RX == "G2_P5"){
    G2_killer_player = G2_P5;
    Serial.println("SET P5 as KILLER");
  }
  else if(iot_controlboard_RX == "G2_P6"){
    G2_killer_player = G2_P6;
    Serial.println("SET P6 as KILLER");
  }
  else if(iot_controlboard_RX == "G2_P7"){
    G2_killer_player = G2_P7;
    Serial.println("SET P7 as KILLER");
  }
  else if(iot_controlboard_RX == "G2_P8"){
    G2_killer_player = G2_P8;
    Serial.println("SET P8 as KILLER");
  }
}
