//****************************************Mode_change()****************************************************************
int serial1_Mode_Change(byte SH[4], byte SL[4], byte MY[2], byte DATA[], int DATA_LENGTH){        // Receive packet일때 실행되는 함수
 String data_string = "";
// Serial.print("ADDR: ");
// for(int i = 0; i< 4; i++)
//  Serial.print(" 0x"+ String(SH[i],HEX));
// for(int i = 0; i< 4; i++)
//  Serial.print(" 0x"+ String(SL[i],HEX));
// Serial.println("");
// 
    for(int i = 0 ; i < DATA_LENGTH; i++)
        data_string += String((char)DATA[i]);
    Serial.println( "ASCII: " + data_string);
    Message_recived(SL,DATA[0],data_string.substring(1));
    
    if(SL[2] == temple[LT].mac[6] && SL[3] == temple[0].mac[7]){
      Serial.println(temple[LT].name  + " message received");
      if(DATA[0] >= 49 && DATA[0] <= 57){
        myDFPlayer.playLargeFolder(F1,VO8_1);
        delay(4300);
        switch(DATA[0]){
          case '1': Serial.println("lb_" + temple[LT].name + "_I"  + 1); myDFPlayer.playLargeFolder(F2,C9); break;
          case '2': Serial.println("lb_" + temple[LT].name + "_I"  + 2); myDFPlayer.playLargeFolder(F2,C8); break;
          case '3': Serial.println("lb_" + temple[LT].name + "_I"  + 3); myDFPlayer.playLargeFolder(F2,C7); break;
          case '4': Serial.println("lb_" + temple[LT].name + "_I"  + 4); myDFPlayer.playLargeFolder(F2,C6); break;
          case '5': Serial.println("lb_" + temple[LT].name + "_I"  + 5); myDFPlayer.playLargeFolder(F2,C5); break;
          case '6': Serial.println("lb_" + temple[LT].name + "_I"  + 6); myDFPlayer.playLargeFolder(F2,C4); break;
          case '7': Serial.println("lb_" + temple[LT].name + "_I"  + 7); myDFPlayer.playLargeFolder(F2,C3); break;
          case '8': Serial.println("lb_" + temple[LT].name + "_I"  + 8); myDFPlayer.playLargeFolder(F2,C2); break;
          case '9': Serial.println("lb_" + temple[LT].name + "_I"  + 9); myDFPlayer.playLargeFolder(F2,C1); break;
        }
        delay(1000);
        myDFPlayer.playLargeFolder(F1,VO8_2); 
        delay(1000);
        if(DATA[0] == '9'){
          myDFPlayer.playLargeFolder(F1,VO10);
          delay(2000);
        }
      }
      else if(data_string == "KILLER WIN!") Serial.println("lb_" + temple[LT].name + "_Q");
    }
}
void Message_recived(byte SL[4],char Device_name, String data){           //어느 장치에서 왔는지 MAC 확인 
  //SL -> SL 넣고
    String message_txt;
    switch (Device_name){ 
        case 'R' :
            for(int i = 0; i < 10; i++){                                                     //sizeof(revive) 사이즈 제대로 되는지 확인 필요,,
                if(SL[2] == revive[i].mac[6] && SL[3] == revive[i].mac[7]) {
                  Serial.println(revive[i].name + " message received");
                  Serial.println("lb_"  + revive[i].name + '_'  + data);
                }
            } break;
        case 'I' :
            for(int i = 0; i < 8; i++){
                if(SL[2] == itembox[i].mac[6] && SL[3] == itembox[i].mac[7]){
                  Serial.println(itembox[i].name + " message received");
                  Serial.println("lb_"  + itembox[i].name + '_'  + data);
                }
            } break;
        case 'G' :
            for(int i = 0; i < 5; i++){
                if(SL[2] == generator[i].mac[6] && SL[3] == generator[i].mac[7]){
                  Serial.println(generator[i].name  + " message received");
                  Serial.println("lb_"  + generator[i].name + '_'  + data);
                }
            }  break;
        case 'E' :
            for(int i = 0; i < 3; i++){
                if(SL[2] == escape[i].mac[6] && SL[3] == escape[i].mac[7]){
                  Serial.println(escape[i].name + " message received");
                  Serial.println("lb_"  + escape[i].name + '_'  + data);
                }
            }  break;
         case 'T' :
            if(SL[2] == temple[LT].mac[6] && SL[3] == temple[0].mac[7]){
              Serial.println( temple[LT].name  + " message received");
              Serial.println("lb_" + temple[LT].name + '_'  + data);
            } 
            break;
        case 'D' :
            for(int i = 0; i < 4; i++){
              if(SL[2] == door[i].mac[6] && SL[3] == door[i].mac[7]){
                Serial.println(door[i].name  + " message received");
                Serial.println("lb_"  + door[i].name + '_'  + data);
              }
            } break;
        case 'V' :
            for(int i = BV1; i <= TV; i++){
              if(SL[2] == vent[i].mac[6] && SL[3] == vent[i].mac[7]){
                if((data.substring(0,1)=="T") || (data.substring(0,1)=="L")){
                  Serial.println( vent[i].name + " message received");
                  Serial.println("lb_"  + vent[i].name + '_'  + data);
                  int SET_vent;
                  switch(i){
                    case BV1: SET_vent = SV;    break;                     
                    case BV2: SET_vent = TV;    break;   
                    case LV:  SET_vent = CV;    break;
                    case CV:  SET_vent = LV;    break;
                    case SV:  SET_vent = BV1;   break;
                    case TV:  SET_vent = BV2;   break;           
                  }
                  Serial.println(vent[SET_vent].name + " message received");
                  Serial.println("lb_"  + vent[SET_vent].name + '_'  + data);
                }
                else{
                  Serial.println( vent[i].name + " message received");
                  Serial.println("lb_"  + vent[i].name + '_'  + data);
                }
              }
            } 
            break;
          case 'F' :
            for(int i = 0; i < 1; i++){
              if(SL[2] == fog[i].mac[6] && SL[3] == fog[i].mac[7]){
                Serial.println(fog[i].name  + " message received");
                Serial.println("lb_"  + fog[i].name + '_'  + data);
              }
            } 
            break;
    default :   Serial.println("Something else received");
  }
}
