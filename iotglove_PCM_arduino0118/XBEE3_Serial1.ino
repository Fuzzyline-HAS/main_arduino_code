void XBEE3_serial1_setting(){
  while(at_num_serial1 < 14){
    XBEE3_serial1_Receiving_Data();
    if(at_get_serial1 == true && at_num_serial1 < 14){
      Serial1.write(xbee3_ATcommand_DB1[at_num_serial1],len[at_num_serial1]);
      at_get_serial1 = false;
      //Serial.println("send");
    }
  }
}
//****************************************XBEE3_serial1_Receiving_Data()****************************************************************
byte XBEE3_serial1_Receiving_Data()
{
  if (Serial1.available())                                      //xbee3 Rx 들어올때 실행
  {
    //Serial.println("DATA_receiving...");
    byte received_data_confirm[1];
    Serial1.readBytes(received_data_confirm , 1);
    if (received_data_confirm[0] == 0x7E) {                        //api1 모드 일때 첫 데이터 0x7E인지 확인
      byte received_data_length[2];                              //패킷 length까지 byte[3]배열 생성
      Serial1.readBytes(received_data_length , 2);                  //패킷 length까지 데이터 받기
      byte received_data[received_data_length[1] + 1];           //패킷 length에 맞는 byte 배열 생성
      Serial1.readBytes(received_data, received_data_length[1] + 1); //패킷 checksum 끝까지 데이터 받기
      switch(received_data[0]){                                                                       //패킷 종류 구분 switch
        case 0x90: {                                                                                          //Receieve패킷 일때
          //Serial.println("Receieved_Packet");
          int ASCII_LENGTH = received_data_length[1] - 12;                    //ASCII 갯수 저장
          byte received_SH[4];                                                                       //64bit address high
          byte received_SL[4];                                                                       //64bit address high
          byte received_MY[4];                                                                       //16bit address
          byte received_ASCII[ASCII_LENGTH];                                         //전송받은 ascii 데이터

          for (int i = 1; i <= 4; i++)                                        received_SH[i - 1] = received_data[i];                        //64bit address HIGH 주소 분할 저장
          for (int i = 5; i <= 8; i++)                                        received_SL[i - 5] = received_data[i];                        //64bit address LOW 주소 분할 저장
          for (int i = 9; i <= 10; i++)                                      received_MY[i - 9] = received_data[i];                       //16bit address 주소 저장
          for (int i = 12; i <= 12 + ASCII_LENGTH; i++)   received_ASCII[i - 12] = received_data[i];                 //들어온 ascii 저장
          serial1_Mode_Change(received_SH , received_SL , received_MY , received_ASCII, ASCII_LENGTH);
          return 0;   break;
        }
        case 0x8B: {                                                                                                            //transmit_status패킷 일때
          status_chk_serial1 = true;
          return received_data[5]; break;
        }
        case 0x8A: {                                                                                                          //modem_status 패킷일때
          Serial.println("Modem_Status: 0x" + (received_data[1], HEX));
          return 0; break;
        }
        case 0x88: {                                                                                                          //AT _command_response 패킷일때
          at_get_serial1 = true;
          at_num_serial1++;
          Serial.println((String)((char)received_data[2]) + (String)((char)received_data[3]) + "\b");
          if (received_data[4] == 0) {                                                                                 //at command response success일때
              Serial.println("_SUCCED\b");
              for (int i = 5; i < received_data_length[1]; i++) 
                Serial.println("0x" +String(received_data[i],HEX) + ",\b");
              Serial.println(" ");
          }
          else    
              Serial.println("FAILED");
//          if ((received_data[2] == 0x53) && (received_data[3] == 0x4C)) {                //my_addr 저장용
//            for (int i = 0; i < 4; i++)
//              my_address_serial1[i] = received_data[i + 5];
//          }   //my_addr 저장용
        }   //AT _command_response 패킷일때
      }   //패킷 종류 구분 switch
    }   //api1 모드 일때 첫 데이터 0x7E인지 확인
  }   //xbee3 Rx 들어올때 실행
  return 0;
}
//****************************************Mode_change()****************************************************************
int serial1_Mode_Change(byte SH[4], byte SL[4], byte MY[2], byte DATA[], int DATA_LENGTH){        // Receive packet일때 실행되는 함수
  String data_string = "";
  for(int i = 0 ; i < DATA_LENGTH; i++)
    data_string += String((char)DATA[i]);
  for(int i = G1_P1; i <= G1_P8; i++)
    if(SL[2] == G1[i].mac[6] && SL[3] == G1[i].mac[7]){
      G1[i].state = true;
      Serial.println(G1[i].name + ": \b");
      Serial.println(data_string);
    }
}
//****************************************XBEE3_serial1_Transmit_Request()****************************************************************
void XBEE3_serial1_Transmit_Request_ASCII(byte adr[8], String str) {
  int sum = 0; //checksum계산용 변수
  int data_length = 18 + str.length() - 1; //패킷 총길이: string null문자 1개 제외
  char data[str.length()];                //String->char 변환위한 char 배열
  str.toCharArray(data, str.length());    //String ->char 형변환
  //transmit requeset 기본 셋팅 패킷
  byte transmit_data[data_length] = {0x7E , 0x00 , 0x00 , 0x10 , 0x01 //SETUP
                                     , 0x00 , 0x13 , 0xA2 , 0x00 , 0x41 , 0xE3 , 0x90 , 0x6A //ADDRESS
                                     , 0xFF , 0xFE , 0x00 , 0x00
                                    };                             //SETUP
  //패킷 세팅
  transmit_data[2] = data_length - 3 - 1;             //LENGTH: 총길이 - startdelimiter-legnth-checksum
  for (int i = 5; i <= 12; i++)                       //MAC_ADDR: 전역 배열에서 몇번쨰인지 불러와서 매핑
    transmit_data[i] = adr[i - 5];
  for (int i = 17; i < data_length - 1; i++)          //ASCII: 입력받은 String에서 변환후 패킷에 매핑
    transmit_data[i] = data[i - 17];
  for (int i = 3; i < data_length - 1; i++)           //CheckSum 계산용
    sum += transmit_data[i];                          //checksum = length다음 byte부터 checksum 다 더하고 0xff에서 뺀값
  byte checksum = 255 - (sum % 256);
  transmit_data[data_length - 1] = checksum;          // Checksum: 체크섬 마지막에 매핑
  Serial1.write(transmit_data, sizeof(transmit_data));  // Xbee3로 전송
  //  for (int i = 0; i < data_length; i++) {             // 전송된 hex 출력
//    Serial.print("0x");
//    Serial.print(transmit_data[i], HEX);
//    Serial.print(", ");
//  }
//  Serial.println();
  while(status_chk_serial1 != true)                            //transmit status를 받기 전까지 반복
    XBEE3_serial1_Receiving_Data();
  status_chk_serial1 = false;
}
//****************************************XBEE3_serial1_Transmit_Request()****************************************************************
void XBEE3_serial1_Transmit_Request_HEX(byte adr[8], byte hex[], int hex_length ) {
  int sum = 0; //checksum계산용 변수
  int data_length = 18 + hex_length;     //패킷 총길이 설정
  //transmit requeset 기본 셋팅 패킷
  byte transmit_data[data_length] = {0x7E , 0x00 , 0x00 , 0x10 , 0x01 //SETUP
                                     , 0x00 , 0x13 , 0xA2 , 0x00 , 0x41 , 0xE3 , 0x90 , 0x6A //ADDRESS
                                     , 0xFF , 0xFE , 0x00 , 0x00
                                    };                             //SETUP
  //패킷 세팅
  transmit_data[2] = data_length - 3 - 1;               //LENGTH: 총길이 - startdelimiter-legnth-checksum
  for (int i = 5; i <= 12; i++)                         //MAC_ADDR: 전역 배열에서 몇번쨰인지 불러와서 매핑
    transmit_data[i] = adr[i - 5];
  for (int i = 17; i < data_length - 1; i++)            //HEX: 입력받은 hex 패킷에 매핑
    transmit_data[i] = hex[i - 17];
  for (int i = 3; i < data_length - 1; i++)             //CheckSum 계산용
    sum += transmit_data[i];                            //checksum = length다음 byte부터 checksum 다 더하고 0xff에서 뺀값
  byte checksum = 255 - (sum % 256);
  transmit_data[data_length - 1] = checksum;            // Checksum: 체크섬 마지막에 매핑
  Serial1.write(transmit_data, sizeof(transmit_data));  // Xbee3로 전송
  //  for (int i = 0; i < data_length; i++) {           // 전송된 hex 출력
//    Serial.print("0x");
//    Serial.print(transmit_data[i], HEX);
//    Serial.print(", ");
//  }
//  Serial.println();
  while(status_chk_serial1 != true)                            //transmit status를 받기 전까지 반복
    XBEE3_serial1_Receiving_Data();
  status_chk_serial1 = false;
}
