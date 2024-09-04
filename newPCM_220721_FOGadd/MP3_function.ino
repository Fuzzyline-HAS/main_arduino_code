//****************************************mp3_setup()****************************************************************
void Mp3_Setup(){
  //Serial.println();
  Serial.println("DFRobot DFPlayer Mini Demo");
  Serial.println("Initializing DFPlayer ... (May take 3~5 seconds)");
  myDFPlayer.setTimeOut(1000); //Set serial communictaion time out 1000 ms
  if (!myDFPlayer.begin(Serial3)) { //Use softwareSerial to communicate with mp3.
    Serial.println("Unable to begin:");
    Serial.println("1.Please recheck the connection!");
    Serial.println("2.Please insert the SD card!");
    while(true);
  }
  Serial.println("DFPlayer Mini online.");
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  myDFPlayer.volume(30);  //Set volume value (0~30).
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  //myDFPlayer.enableDAC();  //Enable On-chip DAC
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

}//void MP3_SETUP

void mp3_play_VO(String VO_NUM){
  String num_front = "";
  String num_back = "";
  int num_2;
  int num_1;
  int index = VO_NUM.indexOf('_');
  if(index == -1)                       //'_'가 포함되어 있지 않은 경우
    num_front = VO_NUM.substring(2);
  else{                                 //'_'가 포함되어 있는 경우
    num_front =  VO_NUM.substring(2,index);
    num_back = VO_NUM.substring(index+1);
    num_2 = num_back.toInt();
  }
  num_1 = num_front.toInt();
  switch(num_1)
  {
    case 1:   myDFPlayer.playLargeFolder(F1,VO1);  delay(7000); break;
    case 2:   myDFPlayer.playLargeFolder(F1,VO2);  break;
    case 3:   myDFPlayer.playLargeFolder(F1,VO3);  delay(6500);break;
    case 4:   myDFPlayer.playLargeFolder(F1,VO4);  break;
    case 5:   myDFPlayer.playLargeFolder(F1,VO5);  break;
    case 6:   myDFPlayer.playLargeFolder(F1,VO6);  break;
    case 7:   
      if(num_2 == 1) {
        myDFPlayer.playLargeFolder(F1,VO7_1);
        delay(5500);
      }
      else {
        myDFPlayer.playLargeFolder(F1,VO7_2);   
        delay(1000);
      }break;
    case 8:
      if(num_2 == 1) {
          myDFPlayer.playLargeFolder(F1,VO8_1);
          delay(4500);
        }
      else myDFPlayer.playLargeFolder(F1,VO8_2);   delay(1000);break;
    case 9:   myDFPlayer.playLargeFolder(F1,VO9);  break;
    case 10:  myDFPlayer.playLargeFolder(F1,VO10); delay(2000);break;
    case 11:  myDFPlayer.playLargeFolder(F1,VO11); break;
    case 12:  myDFPlayer.playLargeFolder(F1,VO12); break;
    case 13:  myDFPlayer.playLargeFolder(F1,VO13); delay(7000); myDFPlayer.playLargeFolder(F1,VO53); delay(3000); break;
    case 14:  myDFPlayer.playLargeFolder(F1,VO14); delay(7000); myDFPlayer.playLargeFolder(F1,VO53); delay(3000); break;
    case 15:  myDFPlayer.playLargeFolder(F1,VO15); break;
    case 16:  myDFPlayer.playLargeFolder(F1,VO16); break;
    case 17:  myDFPlayer.playLargeFolder(F1,VO17); break;
    case 18:  myDFPlayer.playLargeFolder(F1,VO18); break;
    case 19:
      if(num_2 == 1) myDFPlayer.playLargeFolder(F1,VO19_1);
      else myDFPlayer.playLargeFolder(F1,VO19_2);  break;
    case 20:  myDFPlayer.playLargeFolder(F1,VO20); break;
    case 21:
      if(num_2 == 1) myDFPlayer.playLargeFolder(F1,VO21_1);
      else if(num_2 == 2) myDFPlayer.playLargeFolder(F1,VO21_2);
      else if(num_2 == 3) myDFPlayer.playLargeFolder(F1,VO21_3);
      else if(num_2 == 4) myDFPlayer.playLargeFolder(F1,VO21_4);
      else myDFPlayer.playLargeFolder(F1,VO21_5); delay(2500); break;
    case 22:  myDFPlayer.playLargeFolder(F1,VO22); delay(3600); break;
    case 23:  myDFPlayer.playLargeFolder(F1,VO23); delay(2500);break;
    case 24:  myDFPlayer.playLargeFolder(F1,VO24); delay(2000); break;
    case 25:  myDFPlayer.playLargeFolder(F1,VO25); delay(7000); myDFPlayer.playLargeFolder(F1,VO53); delay(3000); break;
    case 26:
      if(num_2 == 1) myDFPlayer.playLargeFolder(F1,VO26_1);
      else myDFPlayer.playLargeFolder(F1,VO26_2);   delay(1000);break;
    case 27:  myDFPlayer.playLargeFolder(F1,VO27); break;
    case 28:  myDFPlayer.playLargeFolder(F1,VO28); break;
    case 29:  myDFPlayer.playLargeFolder(F1,VO29); break;
    case 30:  myDFPlayer.playLargeFolder(F1,VO30); break;  
    case 31:  myDFPlayer.playLargeFolder(F1,VO31); delay(8000); break;   
    case 32:  myDFPlayer.playLargeFolder(F1,VO32); delay(8000); break;   
    case 33:  myDFPlayer.playLargeFolder(F1,VO33); delay(5000); delay(5000); break;
    case 34:  myDFPlayer.playLargeFolder(F1,VO34); delay(5000); delay(5000); break;
    case 35:  myDFPlayer.playLargeFolder(F1,VO35); delay(8000); break;   
    case 36:  myDFPlayer.playLargeFolder(F1,VO36); delay(5000); delay(5000); break;
    case 37:  myDFPlayer.playLargeFolder(F1,VO37); delay(7000); break;   
    case 38:  myDFPlayer.playLargeFolder(F1,VO38); delay(7000); break;  
    case 39:  myDFPlayer.playLargeFolder(F1,VO39); delay(6000); delay(5000); break;
    case 40:  myDFPlayer.playLargeFolder(F1,VO40); delay(6000); delay(5000);  myDFPlayer.playLargeFolder(F1,VO50); delay(3000);break;
    case 41:  myDFPlayer.playLargeFolder(F1,VO41); delay(5000); delay(5000); break;    
    case 42:  myDFPlayer.playLargeFolder(F1,VO42); delay(5000); delay(5000); break;
    case 43:  myDFPlayer.playLargeFolder(F1,VO43); delay(5000); delay(5000); break;
    case 44:  myDFPlayer.playLargeFolder(F1,VO44); delay(5000); delay(5000); break;
    case 45:  myDFPlayer.playLargeFolder(F1,VO45); delay(5000); delay(5000); break;    
    case 46:  myDFPlayer.playLargeFolder(F1,VO46); delay(5000); delay(5000); break; 
    case 47:  myDFPlayer.playLargeFolder(F1,VO47); delay(7000); delay(7800); break; 
    case 48:  myDFPlayer.playLargeFolder(F1,VO48);  break; 
    case 49:  myDFPlayer.playLargeFolder(F1,VO49); delay(7000); break; 
    case 50:  myDFPlayer.playLargeFolder(F1,VO50); delay(4000); break; 
    case 51:  myDFPlayer.playLargeFolder(F1,VO51); delay(6000); break; 
    case 52:  myDFPlayer.playLargeFolder(F1,VO52); delay(1500); break; 
    case 53:  myDFPlayer.playLargeFolder(F1,VO53); delay(6000); break;    
    case 54:  myDFPlayer.playLargeFolder(F1,VO54); delay(6500); break; 
    case 55:  myDFPlayer.playLargeFolder(F1,VO55); delay(3300); break; 
    case 56:  myDFPlayer.playLargeFolder(F1,VO56); delay(5300); break; 
    case 57:  myDFPlayer.playLargeFolder(F1,VO57); delay(5300); break;    
    case 58:  myDFPlayer.playLargeFolder(F1,VO58); delay(4300); break; 
    case 59:  myDFPlayer.playLargeFolder(F1,VO59); delay(4300); break; 
    case 60:  myDFPlayer.playLargeFolder(F1,VO60); delay(8300); break;
    case 61:  myDFPlayer.playLargeFolder(F1,VO61); delay(5000); break;
    case 62:  myDFPlayer.playLargeFolder(F1,VO62); delay(8000); break;
   
  }
}
void mp3_play_VN(String Nx_NUM){
  String num = "";
  num = Nx_NUM.substring(2);
  int vn_num = num.toInt();
  Serial.println(vn_num);
  switch(vn_num)
  {
    case 30:  myDFPlayer.playLargeFolder(F3,N30); break;
    case 25:  myDFPlayer.playLargeFolder(F3,N25); break;
    case 20:  myDFPlayer.playLargeFolder(F3,N20); break;
    case 15:  myDFPlayer.playLargeFolder(F3,N15); break;
    case 10:  myDFPlayer.playLargeFolder(F3,N10); break;
    case 5:   myDFPlayer.playLargeFolder(F3,N5);  break;
    case 3:   myDFPlayer.playLargeFolder(F3,N3);  break;
    case 1:   myDFPlayer.playLargeFolder(F3,N1);  break;   
  }
  delay(1000);
  myDFPlayer.playLargeFolder(F1,VO26_1);
  delay(800);
  myDFPlayer.playLargeFolder(F1,VO26_2); 
   delay(800);
}


void mp3_play_VS(String Nx_NUM){
  String num = "";
  num = Nx_NUM.substring(2);
  int vn_num = num.toInt();
  Serial.println(vn_num);
  switch(vn_num)
  {
    case 5:   myDFPlayer.playLargeFolder(5,5); delay(2000); break;
    case 4:   myDFPlayer.playLargeFolder(5,4); delay(2000); break;
    case 3:   myDFPlayer.playLargeFolder(5,3); delay(7000); break;
    case 2:   myDFPlayer.playLargeFolder(5,2); delay(2000); break;
    case 1:   myDFPlayer.playLargeFolder(5,1); delay(2000); break;   
  }
}

void mp3_play_VC(String Nx_NUM){
  String num = "";
  num = Nx_NUM.substring(2);
  int vn_num = num.toInt();
  Serial.println(vn_num);
  switch(vn_num)
  {
    case 9:   myDFPlayer.playLargeFolder(F2,C9); delay(1000); break;
    case 8:   myDFPlayer.playLargeFolder(F2,C8); delay(1000); break;
    case 7:   myDFPlayer.playLargeFolder(F2,C7); delay(1000); break;
    case 6:   myDFPlayer.playLargeFolder(F2,C6); delay(1000); break;
    case 5:   myDFPlayer.playLargeFolder(F2,C5); delay(1000); break;  
    case 4:   myDFPlayer.playLargeFolder(F2,C4); delay(1000); break;
    case 3:   myDFPlayer.playLargeFolder(F2,C3); delay(1000); break;
    case 2:   myDFPlayer.playLargeFolder(F2,C2); delay(1000); break;
    case 1:   myDFPlayer.playLargeFolder(F2,C1); delay(1000); break;
  }
}
