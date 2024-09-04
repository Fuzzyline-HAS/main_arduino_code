void Xbee3_Setting()
{
  XBEE3.begin(9600);
  delay(1000);
  Serial.println("START");
  
  Serial.print("Entering XBEE3 Setup Mode... ");
  XBEE3.write("+++",3);
  while(!(XBEE3.available()));
  XBEE3.readBytes(at_transparent,3);
  if(at_transparent[0] == 'O' && at_transparent[1]== 'K'){
    Serial.println("SUCCED");
    at_success++;
  }
  else
    Serial.println("FAILED");
  delay(10);

  Serial.print("Change mode to ATCE:0 ");
  byte atce0[6] = {0x41 ,0x54 ,0x43 ,0x45 ,0x30 ,0x0D};
  XBEE3.write(atce0,sizeof(atce0));
  while(!(XBEE3.available()));
  XBEE3.readBytes(at_transparent,3);
  if(at_transparent[0] == 'O' && at_transparent[1]== 'K'){
    Serial.println("SUCCED");
    at_success++;
  }
  else
    Serial.println("FAILED");
  delay(10);
  
  Serial.print("Change mode to ATID:3021... ");
  byte atid3021[9] = {0x41 ,0x54 ,0x49 ,0x44 ,0x33 ,0x30 ,0x32 ,0x31 ,0x0D};
  XBEE3.write(atid3021,sizeof(atid3021));
  while(!(XBEE3.available()));
  XBEE3.readBytes(at_transparent,3);
  if(at_transparent[0] == 'O' && at_transparent[1]== 'K'){
    Serial.println("SUCCED");
    at_success++;
  }
  else
    Serial.println("FAILED");
  delay(10);

  Serial.print("Change mode to ATJV1... ");
  byte atjv1[6] = {0x41 ,0x54 ,0x4A ,0x56 ,0x31 ,0x0D};
  XBEE3.write(atjv1,sizeof(atjv1));
  while(!(XBEE3.available()));
  XBEE3.readBytes(at_transparent,3);
  if(at_transparent[0] == 'O' && at_transparent[1]== 'K'){
    Serial.println("SUCCED");
    at_success++;
  }
  else
    Serial.println("FAILED");
  delay(10);

  Serial.print("Change mode to ATNJ:0XFF... ");
  byte atnj0xff[9] = {0x41 ,0x54 ,0x4E ,0x4A ,0x30 ,0x58 ,0x46 ,0x46 ,0x0D};
  XBEE3.write(atnj0xff,sizeof(atnj0xff));
  while(!(XBEE3.available()));
  XBEE3.readBytes(at_transparent,3);
  if(at_transparent[0] == 'O' && at_transparent[1]== 'K'){
    Serial.println("SUCCED");
    at_success++;
  }
  else
    Serial.println("FAILED");
  delay(10);
  
  Serial.print("Change mode to API1... ");
  byte atap1[6] = {0x41 ,0x54 ,0x41 ,0x50 ,0x31 ,0x0D};
  XBEE3.write(atap1,sizeof(atap1));
  while(!(XBEE3.available()));
  XBEE3.readBytes(at_transparent,3);
  if(at_transparent[0] == 'O' && at_transparent[1]== 'K'){
    Serial.println("SUCCED");
    at_success++;
  }
  else
    Serial.println("FAILED");
  delay(10);

  Serial.print("Saving Setting... ");
  byte atwr[5] = {0x41 ,0x54 ,0x57 ,0x52 ,0x0D};
  XBEE3.write(atwr,sizeof(atwr));
  while(!(XBEE3.available()));
  XBEE3.readBytes(at_transparent,3);
  if(at_transparent[0] == 'O' && at_transparent[1]== 'K'){
    Serial.println("SUCCED");
    at_success++;
  }
  else
    Serial.println("FAILED");
  delay(10);

  Serial.print("Reboot XBEE3... ");
  byte atcn[5] = {0x41 ,0x54 ,0x43 ,0x4E ,0x0D};
  XBEE3.write(atcn,sizeof(atcn));
  while(!(XBEE3.available()));
  XBEE3.readBytes(at_transparent,3);
  if(at_transparent[0] == 'O' && at_transparent[1] == 'K'){
    Serial.println("SUCCED");
    at_success++;
  }
  else
    Serial.println("FAILED");
  delay(10);
}

//****************************************XBEE3_Receiving_Data()****************************************************************
void XBEE3_Receiving_Data()
{
  if(XBEE3.available())                                       //xbee3 Rx 들어올때 실행
  {
    //Serial.println("DATA_receiving...");
    byte received_data_confirm[1];
    XBEE3.readBytes(received_data_confirm ,1);
    if(received_data_confirm[0] == 0x7E){                          //api1 모드 일때 첫 데이터 0x7E인지 확인
      byte received_data_length[2];                              //패킷 length까지 byte[3]배열 생성
      XBEE3.readBytes(received_data_length ,2);                   //패킷 length까지 데이터 받기
      byte received_data[received_data_length[1]+1];             //패킷 length에 맞는 byte 배열 생성
      XBEE3.readBytes(received_data,received_data_length[1]+1);  //패킷 checksum 끝까지 데이터 받기
      
  //Receieve패킷 일때
      if(received_data[0] == 0x90){                             
        Serial.println("Receieved_Packet");                     
        int ASCII_LENGTH = received_data_length[1]-12;       //ASCII 갯수 저장
        byte received_SH[4];                                //64bit address high
        byte received_SL[4];                                //64bit address high
        byte received_MY[4];                                //16bit address 
        byte received_ASCII[ASCII_LENGTH];      //전송받은 ascii 데이터
        
        for(int i = 1; i <= 4; i++)
          received_SH[i-1] = received_data[i];              //64bit address HIGH 주소 분할 저장
        for(int i = 5; i <= 8; i++)
          received_SL[i-5] = received_data[i];              //64bit address LOW 주소 분할 저장
        for(int i = 9; i <= 10; i++)
          received_MY[i-9] = received_data[i];              //16bit address 주소 저장
        for(int i = 12; i <= 12+ASCII_LENGTH; i++)
          received_ASCII[i-12] = received_data[i];             //들어온 ascii 저장
          
        Mode_Change(received_SH ,received_SL ,received_MY ,received_ASCII, ASCII_LENGTH);
 
      }
  //transmit_status패킷 일때
      else if(received_data[0] == 0x8B){                        
        Serial.print("Transmit_Status: 0x");
        Serial.println(received_data[5],HEX);                   //transmit status 출력
      }
      
  //modem_status 패킷일때
      else if(received_data[0] == 0x8A){                       
        Serial.print("Modem_Status: 0x");
        Serial.println(received_data[1],HEX);                   //modem_status 출력
      }
      
  //AT _command_response 패킷일때
      else if(received_data[0] == 0x88){
        Serial.print((char)received_data[2]);   //at command high
        Serial.print((char)received_data[3]); //at command low
        Serial.print(": ");
        if(received_data[4] == 0){ //at command response success일때
          for(int i = 5; i < received_data_length[1]; i++){
            Serial.print(",0x");
            Serial.print(received_data[i],HEX);
          }
          Serial.println();
        }
        else
          Serial.println("FAIL to get data");
        at_get = true;
        at_num++;
        
        if((received_data[2] == 0x53) && (received_data[3] == 0x4C)){ //my_addr 저장용
          for(int i = 0; i < 4; i++)
            my_address[i] = received_data[i+5];
        }
      }
      else{
        Serial.println("Something else received");                     // 정의되지 않은 zigbee command 입력됨
        for(int i = 0; i < received_data_length[1]; i++){
            Serial.print(",0x");
            Serial.print(received_data[i],HEX);
        }
        Serial.println();
      }
    }
    else{
      //byte at_reboot[9] = {0x7E,0x00,0x05,0x88,0x01,0x43,0x4E,0x00,0xE5};
      //XBEE3.write(at_reboot,sizeof(at_reboot));
    }
  }
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
  Serial.println();
  
  if(data_string == "A"){
    Serial.println("\n-----GAME START-----");
    mode_a = true;

  }
  
  else if(data_string == "S"){
   Serial.println("\n-----GAME OVER-----");    
   Serial.println("----------------------");
   mode_a = false;

  }
}

//****************************************XBEE3_Transmit_Request()****************************************************************
void XBEE3_Transmit_Request(byte adr[8], String str){
  int sum = 0; //checksum계산용 변수
  int data_length = 18 + str.length()-1;  //패킷 총길이: string null문자 1개 제외
  char data[str.length()];                //String->char 변환위한 char 배열
  str.toCharArray(data,str.length());     //String ->char 형변환
  //transmit requeset 기본 셋팅 패킷
  byte transmit_data[data_length] = {0x7E ,0x00 ,0x00 ,0x10 ,0x01   //SETUP
              ,0x00 ,0x13 ,0xA2 ,0x00 ,0x41 ,0xE3 ,0x90 ,0x6A       //ADDRESS
              ,0xFF ,0xFE ,0x00 ,0x00};                             //SETUP
  //패킷 세팅             
  transmit_data[2] = data_length - 3 - 1;             //LENGTH: 총길이 - startdelimiter-legnth-checksum
  for(int i = 9; i <= 12; i++)                        //MAC_ADDR: 전역 배열에서 몇번쨰인지 불러와서 매핑
    transmit_data[i] = adr[i-9];
  for(int i =17; i < data_length-1; i++)              //ASCII: 입력받은 String에서 변환후 패킷에 매핑
    transmit_data[i] = data[i-17];
  for(int i =3; i < data_length-1; i++)               //CheckSum 계산용 
    sum += transmit_data[i];                          //checksum = length다음 byte부터 checksum 다 더하고 0xff에서 뺀값
  byte checksum = 255-(sum % 256);
  transmit_data[data_length-1] = checksum;            // Checksum: 체크섬 마지막에 매핑
  XBEE3.write(transmit_data,sizeof(transmit_data));   // Xbee3로 전송
  for(int i = 0; i < data_length; i++){               // 전송된 hex 출력
    Serial.print("0x");
    Serial.print(transmit_data[i],HEX);
    Serial.print(", ");
  }
  Serial.println();
}
