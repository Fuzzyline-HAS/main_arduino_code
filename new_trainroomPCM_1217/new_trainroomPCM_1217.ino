#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"

#define XBEE3_TX    (53)
#define XBEE3_RX    (52)
//****************************************XBEE3 SETUP****************************************************************
SoftwareSerial XBEE3(XBEE3_RX,XBEE3_TX); // RX, TX
byte xbee3_ATcommand_DB[14][10] = { {0x7E ,0x00 ,0x05 ,0x08 ,0x01 ,0x43 ,0x45 ,0x01 ,0x6D}, // CE:1 COORDINATOR로 설정
                                  {0x7E ,0x00 ,0x06 ,0x08 ,0x01 ,0x49 ,0x44 ,0x30 ,0x21,0x18}, //ID:3021으로 설정
                                  {0x7E ,0x00 ,0x05 ,0x08 ,0x01 ,0x4A ,0x56 ,0x01 ,0x55}, // JV:0로 설정
                                  {0x7E ,0x00 ,0x05 ,0x08 ,0x01 ,0x4E ,0x4A ,0xFF ,0x5F}, // NJ:0xff로 설정
                                  {0x7E ,0x00 ,0x05 ,0x08 ,0x01 ,0x41 ,0x50 ,0x01 ,0x64}, // api1로 설정
                                  {0x7E ,0x00 ,0x04 ,0x08 ,0x01 ,0x57 ,0x52 ,0x4D}, // WR
                                  {0x7E ,0x00 ,0x04 ,0x08 ,0x01 ,0x41 ,0x43 ,0x72}, // AC
                                  {0x7E ,0x00 ,0x04 ,0x08 ,0x01 ,0x43 ,0x45 ,0x6E}, //CE: Device Role 출력
                                  {0x7E ,0x00 ,0x04 ,0x08 ,0x01 ,0x49 ,0x44 ,0x69}, //ID: Pan ID 출력
                                  {0x7E ,0x00 ,0x04 ,0x08 ,0x01 ,0x4A ,0x56 ,0x56}, //JV: Coordinator Verification
                                  {0x7E ,0x00 ,0x04 ,0x08 ,0x01 ,0x4E ,0x4A ,0x5E}, //Nj: Node Identifier
                                  {0x7E ,0x00 ,0x04 ,0x08 ,0x01 ,0x41 ,0x50 ,0x65}, //AP: Api mode
                                  {0x7E ,0x00 ,0x04 ,0x08 ,0x01 ,0x53 ,0x48 ,0x5B}, //SH: Address High
                                  {0x7E ,0x00 ,0x04 ,0x08 ,0x01 ,0x53 ,0x4C ,0x57}};//SL: Address LOW
int len[14] = {9,10,9,9,9,8,8,8,8,8,8,8,8,8}; 
void XBEE3_setting();
void XBEE3_Receiving_Data();
void XBEE3_Transmit_Request(byte adr[8], String str);
int Mode_Change(byte SH[4], byte SL[4], byte MY[2], byte DATA[], int DATA_LENGTH);

// byte my_address[4];       // SL 저장
bool at_get = true;
int at_num = 0;
// bool status_chk = false;  // transmit_request한 후에 trasmit_status 반환 받나 안받나 확인용

byte my_address[4];

//****************************************XBEE3 SETUP****************************************************************
DFRobotDFPlayerMini myDFPlayer;
void Mp3_Setup();

//****************************************주소 모음집****************************************************************
struct XBEE {
  String name;
  byte mac[8];
  byte ip[2];
  bool state;
};
enum {EM=0,
      ET,
      ER,
      EI
      };

XBEE training[10];

void set_adr();

int rnd_cnt[10] = {0,1,2,3,4,5,6,7,8,9};
int r_cnt = 0;
bool status_chk = false;
void setup() {
  Serial.begin(9600);   //pc 통신
  Serial1.begin(9600);  //mp3 통신
  XBEE3.begin(9600);    //xbee 통신
  Mp3_Setup();
  set_adr();
  while(at_num < 14){
    XBEE3_Receiving_Data();
    XBEE3_setting();
  }
}

void loop() {  
  XBEE3_Receiving_Data();
  if(Serial.available()){
    String controlboard_RX = Serial.readStringUntil('\n');
    Serial.println(controlboard_RX);
   
    if(controlboard_RX == "MR"){                                   // 훈련소 나레이션 스타트
      XBEE3_Transmit_Request(training[EM].mac, "A ");
      myDFPlayer.play(1);
    }
    else if(controlboard_RX == "MS"){                                   // 훈련소 나레이션 잠시멈춤
      XBEE3_Transmit_Request(training[EM].mac, "S ");
      myDFPlayer.stop();
     }
    else if(controlboard_RX == "MP"){                                   // 훈련소 나레이션 멈춘구간부터 다시 실행
      XBEE3_Transmit_Request(training[EM].mac, "P ");
      myDFPlayer.start();
    }
    
    else if(controlboard_RX == "TR"){                      
      XBEE3_Transmit_Request(training[ET].mac, "R ");
    }
    else if(controlboard_RX == "TS"){                                   
      XBEE3_Transmit_Request(training[ET].mac, "S ");
    }
    else if(controlboard_RX == "TB"){                                   
      XBEE3_Transmit_Request(training[ET].mac, "B ");
    }
    
    else if(controlboard_RX == "RR"){                                   
      XBEE3_Transmit_Request(training[ER].mac, "R ");
    }
    else if(controlboard_RX == "RS"){                                   
      XBEE3_Transmit_Request(training[ER].mac, "S ");
    }
    else if(controlboard_RX == "RB"){                                   
      XBEE3_Transmit_Request(training[ER].mac, "B ");
    }
    
    else if(controlboard_RX == "IR"){                                   
      XBEE3_Transmit_Request(training[EI].mac, "R ");
    }
    else if(controlboard_RX == "IS"){                                   
      XBEE3_Transmit_Request(training[EI].mac, "S ");
    }
    else if(controlboard_RX == "IB"){                                   
      XBEE3_Transmit_Request(training[EI].mac, "B ");
    }
    
    
  }
}
