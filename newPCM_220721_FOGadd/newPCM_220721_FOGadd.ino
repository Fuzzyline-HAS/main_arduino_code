#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"
//#define SERIAL_BUFFER_SIZE 256
//****************************************XBEE3 SETUP****************************************************************
byte xbee3_ATcommand_DB[14][10] = { {0x7E ,0x00 ,0x05 ,0x08 ,0x01 ,0x43 ,0x45 ,0x01 ,0x6D}, // CE:1 COORDINATOR로 설정
                                  {0x7E ,0x00 ,0x06 ,0x08 ,0x01 ,0x49 ,0x44 ,0x20 ,0x23 ,0x26}, //ID:2023으로 설정0x30 ,0x21 ,0x18//,0x20 ,0x23 ,0x26
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
//****************************************XBEE3 Serial1 SETUP*****************************************************
void XBEE3_serial1_setting();
byte XBEE3_serial1_Receiving_Data();
byte XBEE3_serial1_Transmit_Request_ASCII(byte adr[8], String str);
byte XBEE3_Transmit_Request_HEX(byte adr[8], byte hex[], int hex_length);
int serial1_Mode_Change(byte SH[4], byte SL[4], byte MY[2], byte DATA[], int DATA_LENGTH);

byte my_address_serial1[4];       // SL 저장
bool at_get_serial1 = true;       // at_command_recevied 받으면 true로 반환
int at_num_serial1 = 0;           // 현재 실행중인 at_command 번호 저장용
bool status_chk_serial1 = false;  // transmit_request한 후에 trasmit_status 반환 받나 안받나 확인용
//****************************************mp3 SETUP****************************************************************
DFRobotDFPlayerMini myDFPlayer;
void Mp3_Setup();
void mp3_play_VS(String Nx_NUM);
//****************************************Generator_fix****************************************************************
int fixed_generator = 0;
void Generator_Alarm();

//****************************************주소 모음집****************************************************************
struct XBEE {
  String name;
  byte mac[8];
  byte ip[2];
  bool state;
};
enum {BR1=0, BR2, LR1, LR2, CR1, CR2, SR1, SR2, TR1, TR2};
enum {BI1=0, BI2, LI1, CI1, CI2, SI1, SI2, TI1};
enum {BG=0, LG, CG, SG, TG};
enum {CES=0, SES, TES}; //ES:ESCAPE -> CE를 사용하는 변수가 있어서 변경
enum {BT=0, CT, ST, TT};
enum {LT=0};
enum {BD=0, CD, SD1, TD};
enum {BV1=0, BV2, LV, CV, SV, TV};
enum {AL = 0};
enum {BF = 0};

enum {VO1 = 1, VO2,VO3,VO4,VO5,VO6,VO7_1,VO7_2,VO8_1,VO8_2,VO9,VO10,VO11,VO12,VO13,VO14,VO15,VO16,VO17
     ,VO18,VO19_1,VO19_2,VO20,VO21_1,VO21_2,VO21_3,VO21_4,VO21_5,VO22,VO23,VO24,VO25,VO26_1,VO26_2,VO27
     ,VO28,VO29,VO30,VO31,VO32,VO33,VO34,VO35,VO36,VO37,VO38,VO39,VO40,VO41,VO42,VO43,VO44,VO45,VO46
     ,VO47,VO48,VO49,VO50,VO51,VO52,VO53,VO54,VO55,VO56,VO57,VO58,VO59 ,VO60,VO61,VO62};
enum {C1 = 1, C2, C3, C4, C5, C6, C7, C8, C9, C10};
enum {N1 = 1,N2,N3,N4,N5,N6,N7,N8,M9,N10,N11,N12,N13,N14,N15,N16,N17,N18,N19,N20,N21,N22,N23,N24
      ,N25,N26,N27,N28,N29,N30,N31,N32,N33,N34,N35};
enum {F1 = 1, F2,F3};                       
int Generator_modeValue[2][3] = {{8,0,0},
                                 {60,120,180}};
int escape_modeValue = 60;
int itembox_modeValue[3][5]= {{250,120,70,40,0},
                               {5,25,7,30,40},
                               {3,1,60,0,0}};
int vent_modeValue[2] = {200 ,0};
                        
XBEE revive[10];
XBEE itembox[8];
XBEE generator[5];
XBEE escape[3];
XBEE temple[1];
XBEE door[4];
XBEE vent[6];
XBEE light[1];
XBEE fog[1];

void set_adr();
void mp3_play_VO(String VO_num);
void mp3_play_VN(String Nx_num);

void revive_one_send(int device, String data);
void itembox_one_send(int device, String data);

void revive_place(String revive_place);
void itembox_place(String itembox_place);
void revive_command(int r_name, String revive_command);
void itmebox_command(int i_name, String itembox_command);
void generator_place(String generator_place);
void generator_command(int i_name, String generator_command);
void escape_place(String escape_place);
void escape_command(int i_name, String escape_command);
void door_place(String door_place);
void door_command(int i_name, String door_command);
void vent_place(String vent_place);
void vent_command(int i_name, String vent_command);
void temple_command(String vent_command);
void all_command(String all_command);
void light_command(String controlboard_RX);
void vent_adrSender();
//****************************************생명장치 랜덤 시작****************************************************************
int rnd_revive_cnt = 2; //처음에 3개 키고 시작함
int useable_revive = 7; //처음에 3개 키고 시작해서 활성화 남은 생명장치 7개
int rnd_escape[3][2] = {{CES,SES},{CES,TES},{SES,TES}};
int escape_sel = 1;

bool revive_block = false;
bool itembox_block = false;
bool door_block = false;

//****************************************c#과 통신용****************************************************************
void control_panel();
void auto_transmit(struct XBEE *machine, int machine_num);
 
void setup() {
  Serial.begin(9600);   //pc 통신
  Serial.print(SERIAL_RX_BUFFER_SIZE);
  Serial.print(SERIAL_TX_BUFFER_SIZE);
  Serial.print(_SS_MAX_RX_BUFF);
  Serial1.begin(9600);  //XBEE 통신
  Serial3.begin(9600);  //mp3 통신
  Mp3_Setup();
  set_adr();
  XBEE3_serial1_setting();

}

void loop() {
  XBEE3_serial1_Receiving_Data();
  control_panel();
  
}
