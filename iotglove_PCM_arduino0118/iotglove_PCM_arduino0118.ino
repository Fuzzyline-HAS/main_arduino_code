//****************************************주소 모음집****************************************************************
struct XBEE {
  String name;
  byte mac[8];
  byte ip[2];
  bool state;
};
XBEE G1[8];
XBEE G2[8];
XBEE G3[6];
enum {G1_P1=0, G1_P2, G1_P3, G1_P4, G1_P5, G1_P6, G1_P7, G1_P8};
enum {G2_P1=0, G2_P2, G2_P3, G2_P4, G2_P5, G2_P6, G2_P7, G2_P8};
enum {G3_P1=0, G3_P2, G3_P3, G3_P4, G3_P5, G3_P6};


//****************************************XBEE3 공용 SETUP*****************************************************
byte xbee3_ATcommand_DB1[14][10] = { {0x7E ,0x00 ,0x05 ,0x08 ,0x01 ,0x43 ,0x45 ,0x01 ,0x6D}, // CE:1 COORDINATOR로 설정
                                  {0x7E ,0x00 ,0x06 ,0x08 ,0x01 ,0x49 ,0x44 ,0x11 ,0x11 ,0x47}, //ID:1111으로 설정0x11 ,0x11 ,0x47
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
byte xbee3_broadcast_adr[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF};
byte xbee3_tagger_adr[22] = {0x7E ,0x00 ,0x12 ,0x10 ,0x01 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0xFF ,0xFF ,0xFF ,0xFE 
                                    ,0x00 ,0x00 ,0x041 ,0xE3 ,0x64 ,0x3F ,0x2C};                      
byte xbee3_16bit_setting[31] = {0x7E ,0x00 ,0x1B ,0x10 ,0x01 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0xFF ,0xFF ,0xFF ,0xFE 
                                        ,0x00 ,0x00 ,0x31 ,0x36 ,0x62 ,0x69 ,0x74 ,0x5F ,0x73 ,0x65 ,0x74 ,0x74 ,0x69 ,0x6E ,0x67 ,0xF0};
//****************************************XBEE3 Serial1 SETUP*****************************************************
void XBEE3_serial1_setting();
byte XBEE3_serial1_Receiving_Data();
void XBEE3_serial1_Transmit_Request_ASCII(byte adr[8], String str);
void XBEE3_serial1_Transmit_Request_HEX(byte adr[8], byte hex[], int hex_length);
int serial1_Mode_Change(byte SH[4], byte SL[4], byte MY[2], byte DATA[], int DATA_LENGTH);

byte my_address_serial1[4];       // SL 저장
bool at_get_serial1 = true;       // at_command_recevied 받으면 true로 반환
int at_num_serial1 = 0;           // 현재 실행중인 at_command 번호 저장용
bool status_chk_serial1 = false;  // transmit_request한 후에 trasmit_status 반환 받나 안받나 확인용
//****************************************XBEE3 Serial2 SETUP*****************************************************
byte xbee3_ATcommand_DB2[14][10] = { {0x7E ,0x00 ,0x05 ,0x08 ,0x01 ,0x43 ,0x45 ,0x01 ,0x6D}, // CE:1 COORDINATOR로 설정
                                  {0x7E ,0x00 ,0x06 ,0x08 ,0x01 ,0x49 ,0x44 ,0x22 ,0x22 ,0x25}, //ID:2023으로 설정
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
void XBEE3_serial2_setting();
byte XBEE3_serial2_Receiving_Data();
void XBEE3_serial2_Transmit_Request_ASCII(byte adr[8], String str);
void XBEE3_serial2_Transmit_Request_HEX(byte adr[8], byte hex[], int hex_length);
int serial2_Mode_Change(byte SH[4], byte SL[4], byte MY[2], byte DATA[], int DATA_LENGTH);

byte my_address_serial2[4];       // SL 저장
bool at_get_serial2 = true;       // at_command_recevied 받으면 true로 반환
int at_num_serial2 = 0;           // 현재 실행중인 at_command 번호 저장용
bool status_chk_serial2 = false;  // transmit_request한 후에 trasmit_status 반환 받나 안받나 확인용

//****************************************GameControl_Serial3 SETUP**************************************
void set_adr();
void serialInput();
void iotControl_serial1(String iot_controlboard_RX);
void iotControl_serial2(String iot_controlboard_RX);
int G1_killer_player = G1_P1; //술래로 정할 플레이어 저장 변수: 기본 세팅 p1 술래
int G2_killer_player = G2_P1; //술래로 정할 플레이어 저장 변수: 기본 세팅 p1 술래
//****************************************VOID SETUP**************************************************
void setup() {
  Serial.begin(9600);   //PC 통신
  Serial1.begin(9600);  //xbee3_(1) 통신
  Serial2.begin(9600);  //xbee3_(2) 통신
  set_adr();
  XBEE3_serial1_setting();
  XBEE3_serial2_setting();
}

//****************************************VOID LOOP**************************************************
void loop() {
  XBEE3_serial1_Receiving_Data();
  XBEE3_serial2_Receiving_Data();
  serialInput();
}
