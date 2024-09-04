#include <DmxSimple.h>
#include<SoftwareSerial.h>

#define XBEE3_RX            (11)  
#define XBEE3_TX            (12)

//****************************************XBEE3 SETUP****************************************************************
SoftwareSerial XBEE3(XBEE3_RX,XBEE3_TX); // RX, TX
byte xbee3_ATcommand_DB[7][8] = { {0x7E ,0x00 ,0x04 ,0x08 ,0x01 ,0x43 ,0x45 ,0x6E}, //CE: Device Role 출력
                                  {0x7E ,0x00 ,0x04 ,0x08 ,0x01 ,0x49 ,0x44 ,0x69}, //ID: Pan ID 출력
                                  {0x7E ,0x00 ,0x04 ,0x08 ,0x01 ,0x4A ,0x56 ,0x56}, //JV: Coordinator Verification
                                  {0x7E ,0x00 ,0x04 ,0x08 ,0x01 ,0x4E ,0x49 ,0x5F}, //NI: Node Identifier
                                  {0x7E ,0x00 ,0x04 ,0x08 ,0x01 ,0x41 ,0x50 ,0x65}, //AP: Api mode
                                  {0x7E ,0x00 ,0x04 ,0x08 ,0x01 ,0x53 ,0x48 ,0x5B}, //SH: Address High
                                  {0x7E ,0x00 ,0x04 ,0x08 ,0x01 ,0x53 ,0x4C ,0x57}};//SL: Address LOW

void XBEE3_Receiving_Data();
void Xbee3_Setting();
void XBEE3_Transmit_Request(byte adr[8], String str);
int Mode_Change(byte SH[4], byte SL[4], byte MY[2], byte DATA[], int DATA_LENGTH);

byte xbee3_cordinator_address[8]= {0x00, 0x13, 0xA2, 0x00, 0x41, 0xE3, 0x4E, 0x8F};
bool at_get = true;
int at_num = 0;
int at_success = 0;
byte at_transparent[3] = {0,0,0};
byte my_address[4];
bool mode_a = false;

void setup() 
{
  Serial.begin(9600);
  DmxSimple.usePin(6);
  Xbee3_Setting();
}

void loop() 
{
  XBEE3_Receiving_Data();
  if(at_get == true && at_num < 7){
    XBEE3.write(xbee3_ATcommand_DB[at_num],sizeof(xbee3_ATcommand_DB[at_num]));
    //Serial.println("send");
    at_get = false;
  }

    if(mode_a == true){
    // 파일이름 : 하이드앤시크_하스할배 수정본
    
    // 파일 스타트 (기본)
    DmxSimple.write(1,0); //rotate
    DmxSimple.write(2,0); //rotate speed
    DmxSimple.write(3,0); //flip
    DmxSimple.write(4,0);// flip speed
    DmxSimple.write(5,0); // ?
    DmxSimple.write(6,0); //brightness
    DmxSimple.write(7,0); // twin0kle
    DmxSimple.write(8,0); //color 10 blue
    DmxSimple.write(9,0);
    delay(33000); 

    // 회전문으로 이동
    DmxSimple.write(1,90); //rotate
    DmxSimple.write(3,10); //flip
    DmxSimple.write(6,0); //brightness
    delay(3500);
    
    // 회전문 지도(00:35 ~ 00:40+00:01)rotate = 90 / flip = 10
    DmxSimple.write(1,90); //rotate
    DmxSimple.write(2,0); //rotate speed
    DmxSimple.write(3,10); //flip
    DmxSimple.write(4,0);// flip speed
    DmxSimple.write(5,0); // ?
    DmxSimple.write(6,50); //brightness
    DmxSimple.write(7,0); // twin0kle
    DmxSimple.write(8,0); //color 10 blue
    DmxSimple.write(9,0);
    delay(4900);

    // 회전문지도앞이동하면서 색상변경 (색상 변경 [흰 -파랑 - 보라]}
    DmxSimple.write(3,25); //flip
    DmxSimple.write(6,0); //brightness
    DmxSimple.write(8,20); //color 10 blue
    delay(14000);
    
    // 회전문 지도 앞
    DmxSimple.write(1,90); //rotate
    DmxSimple.write(2,0); //rotate speed
    DmxSimple.write(3,25); //flip
    DmxSimple.write(4,0);// flip speed
    DmxSimple.write(5,0); // ?
    DmxSimple.write(6,50); //brightness
    DmxSimple.write(7,0); // twin0kle
    DmxSimple.write(8,20); //color 
    DmxSimple.write(9,0);
    delay(3300);

    // 색상변경하면서 캐비닛으로 이동(색상변경[보라-파랑-흰])
    DmxSimple.write(1,5); //rotate
    DmxSimple.write(3,68); //flip
    DmxSimple.write(6,0); //brightness
    DmxSimple.write(8,0); //color 10 blue
    delay(800);
    
    // 캐비닛
    DmxSimple.write(1,20); //rotate
    DmxSimple.write(2,0); //rotate speed
    DmxSimple.write(3,70); //flip
    DmxSimple.write(4,0);// flip speed
    DmxSimple.write(5,0); // ?
    DmxSimple.write(6,50); //brightness
    DmxSimple.write(7,0); // twin0kle
    DmxSimple.write(8,0); //color 
    DmxSimple.write(9,0);
    delay(7500);

    // 불끄면서 아이템상자로 이동
    DmxSimple.write(1,127); //rotate
    DmxSimple.write(3,30); //flip
    DmxSimple.write(6,0); //brightness
    delay(3200);

    // 선반 위 아이템 상자
    DmxSimple.write(1,127); //rotate
    DmxSimple.write(2,0); //rotate speed
    DmxSimple.write(3,30); //flip
    DmxSimple.write(4,0);// flip speed
    DmxSimple.write(5,0); // ?
    DmxSimple.write(6,50); //brightness
    DmxSimple.write(7,0); // twin0kle
    DmxSimple.write(8,0); //color 
    DmxSimple.write(9,0);
    delay(8200);

    // 불끄면서 전원공급장치로 이동
    DmxSimple.write(1,74); //rotate
    DmxSimple.write(3,20); //flip
    DmxSimple.write(6,0); //brightness
    delay(1300);

    // 전원공급장치
    DmxSimple.write(1,74); //rotate
    DmxSimple.write(2,0); //rotate speed
    DmxSimple.write(3,20); //flip
    DmxSimple.write(4,0);// flip speed
    DmxSimple.write(5,0); // ?
    DmxSimple.write(6,50); //brightness
    DmxSimple.write(7,0); // twin0kle
    DmxSimple.write(8,0); //color 
    DmxSimple.write(9,0);
    delay(2500);

    // 불끄기
    DmxSimple.write(6,0); //brightness
    delay(500);
    
    // 벽면 전원공급장치
    DmxSimple.write(1,74); //rotate
    DmxSimple.write(2,0); //rotate speed
    DmxSimple.write(3,20); //flip
    DmxSimple.write(4,0);// flip speed
    DmxSimple.write(5,0); // ?
    DmxSimple.write(6,50); //brightness
    DmxSimple.write(7,0); // twin0kle
    DmxSimple.write(8,0); //color 
    DmxSimple.write(9,0);
    delay(19000);

    // 불끄면서 탈출장치로 이동
    DmxSimple.write(1,85); //rotate
    DmxSimple.write(3,55); //flip
    DmxSimple.write(6,0); //brightness
    delay(4500);
    
    // 탈출장치 
    DmxSimple.write(1,85); //rotate
    DmxSimple.write(2,0); //rotate speed
    DmxSimple.write(3,55); //flip
    DmxSimple.write(4,0);// flip speed
    DmxSimple.write(5,0); // ?
    DmxSimple.write(6,50); //brightness
    DmxSimple.write(7,0); // twin0kle
    DmxSimple.write(8,0); //color 
    DmxSimple.write(9,0);
    delay(3700);
   
    // 탈출장치(색상변경[흰-파-보-초])
    DmxSimple.write(6,0); //brightness
    DmxSimple.write(8,40); //color 10 blue
    delay(2500);
    
    // 탈출장치 
    DmxSimple.write(1,85); //rotate
    DmxSimple.write(2,0); //rotate speed
    DmxSimple.write(3,55); //flip
    DmxSimple.write(4,0);// flip speed
    DmxSimple.write(5,0); // ?
    DmxSimple.write(6,50); //brightness
    DmxSimple.write(7,0); // twin0kle
    DmxSimple.write(8,40); //color 
    DmxSimple.write(9,0);
    delay(6500);

    // 색상변경(색상변경[초록-주황-빨강])하면서 캐비닛방향 이동
    DmxSimple.write(1,0); //rotate
    DmxSimple.write(2,0); //rotate speed
    DmxSimple.write(3,50); //flip
    DmxSimple.write(4,0);// flip speed
    DmxSimple.write(6,0); //brightness
    DmxSimple.write(8,70); //color 10 blue
    delay(12500);
    
    // 캐비닛
    DmxSimple.write(1,0); //rotate
    DmxSimple.write(2,0); //rotate speed
    DmxSimple.write(3,50); //flip
    DmxSimple.write(4,0);// flip speed
    DmxSimple.write(5,0); // ?
    DmxSimple.write(6,50); //brightness
    DmxSimple.write(7,0); // twin0kle
    DmxSimple.write(8,70); //color 
    DmxSimple.write(9,0);
    delay(6000);
    
    // 불끄면서 회전문 지도 앞으로 이동
    DmxSimple.write(1,90); //rotate
    DmxSimple.write(3,25); //flip
    DmxSimple.write(6,0); //brightness
    delay(12000);

    // 회전문 지도 앞
    DmxSimple.write(1,90); //rotate
    DmxSimple.write(2,0); //rotate speed
    DmxSimple.write(3,25); //flip
    DmxSimple.write(4,0);// flip speed
    DmxSimple.write(5,0); // ?
    DmxSimple.write(6,50); //brightness
    DmxSimple.write(7,0); // twin0kle
    DmxSimple.write(8,70); //color 
    DmxSimple.write(9,0);
    delay(6000);

    // 불끄기
    DmxSimple.write(1,138); //rotate
    DmxSimple.write(3,50); //flip
    DmxSimple.write(6,0); //brightness
    delay(3900);

    // 제단
    DmxSimple.write(1,138); //rotate
    DmxSimple.write(2,0); //rotate speed
    DmxSimple.write(3,50); //flip
    DmxSimple.write(4,0);// flip speed
    DmxSimple.write(5,0); // ?
    DmxSimple.write(6,50); //brightness
    DmxSimple.write(7,0); // twin0kle
    DmxSimple.write(8,70); //color 
    DmxSimple.write(9,0);
    delay(7400);

    // 술래 카드에 대한 내용 시나리오 작성 후 실행해야함
    DmxSimple.write(6,0); //brightness
    delay(20000);

    // 색상변경하면서 훈련소 도어로 이동(색상변경[빨-주-노-초-파-보-하-흰)
    DmxSimple.write(1,100); //rotate
    DmxSimple.write(3,30); //flip
    DmxSimple.write(6,0); //brightness
    DmxSimple.write(8,0); //color 10 blue
    delay(5500);
  
    // 훈련소 도어
    DmxSimple.write(1,100); //rotate
    DmxSimple.write(2,0); //rotate speed
    DmxSimple.write(3,30); //flip
    DmxSimple.write(4,0);// flip speed
    DmxSimple.write(5,0); // ?
    DmxSimple.write(6,50); //brightness
    DmxSimple.write(7,0); // twin0kle
    DmxSimple.write(8,0); //color 
    DmxSimple.write(9,0);
    delay(7000);


    // 색상변경(색상변경[흰-하-보-파-초])
    DmxSimple.write(6,0); //brightness
    DmxSimple.write(8,40); //color 10 blue
    delay(1000);
    
    // 훈련소 도어
    DmxSimple.write(1,100); //rotate
    DmxSimple.write(2,0); //rotate speed
    DmxSimple.write(3,30); //flip
    DmxSimple.write(4,0);// flip speed
    DmxSimple.write(5,0); // ?
    DmxSimple.write(6,50); //brightness
    DmxSimple.write(7,0); // twin0kle
    DmxSimple.write(8,40); //color 
    DmxSimple.write(9,0);
    delay(12000);

    // 불끄기
    DmxSimple.write(6,0); //brightness
    delay(1500);
    

    mode_a = false;
    XBEE3_Transmit_Request(xbee3_cordinator_address, "DMX_FIN ");
   }
}
