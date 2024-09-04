/*
 * AD _R 같은 전체 장치 명령에는 포그머신은 추가하지 않음 -> 하드모드에서만 쓸 수 있게 하려고
 * 하드모드에세만 따로 메인에서 처리 하도록 ex) BF _R
 */

void control_panel(){
  if(Serial.available()){
    String controlboard_RX = Serial.readStringUntil('\n');
    Serial.println(controlboard_RX);
    if(controlboard_RX.charAt(0) == 'P')
    {
      switch(controlboard_RX.charAt(1))
      {
        case 'P':                                         break;//플레이 인원
        case 'M':                                         break;//플레이 셋팅
        case 'S':                                         break;//OS 관련
        case 'G': all_command_withoutR(controlboard_RX);  break;//OS 관련
        case 'T': vent_adrSender();                       break;
      }
    }
    else if(controlboard_RX.charAt(0) == 'V')
    {
      switch(controlboard_RX.charAt(1))
      {
        case 'O': mp3_play_VO(controlboard_RX);         break;// 나레이션 OS관련
        case 'N': mp3_play_VN(controlboard_RX);         break;// 나레이션 시간관련
        case 'S': mp3_play_VS(controlboard_RX);         break;// 장난용
        case 'C': mp3_play_VC(controlboard_RX);         break;
      }
    }
    else
    {
      switch(controlboard_RX.charAt(1))
      {
        case 'A': all_command(controlboard_RX);         break;  //모든 장치
        case 'R': revive_place(controlboard_RX);        break;  //부활 장치
        case 'I': itembox_place(controlboard_RX);       break;  // 아이템박스
        case 'G': generator_place(controlboard_RX);     break;  //발전기
        case 'E': escape_place(controlboard_RX);        break;  //탈출장치
        case 'V': vent_place(controlboard_RX);          break;  //덕트
        case 'D': door_place(controlboard_RX);          break;  //도어
        case 'T': temple_command(controlboard_RX);      break;  //제단
        case 'L': light_command(controlboard_RX);       break;  //조명
        case 'F': fog_command(controlboard_RX);       break;  //포그머신
      }
    }
  } // if(serial.available)
} //control paneml 함수종료
void all_command(String all_command){
  String zb_send = "";
  zb_send += all_command.substring(4,all_command.length());
  zb_send += ' ';
  
  Serial.println("--------ALL DOOR--------");
  for(int i = BD; i <= TD; i++)   door_command(i,zb_send);
  Serial.println("------ALL ITEMBOX-------");
  for(int i = BI1; i <= TI1; i++) itmebox_command(i,zb_send);
  Serial.println("-----ALL GENERATOR-----");
  for(int i = BG; i <= TG; i++)   generator_command(i,zb_send);
  Serial.println("------ALL ESCAPSE------"); 
  for(int i = CES; i <= TES; i++) escape_command(i,zb_send);  
  Serial.println("-------ALL VENT-------"); 
  for(int i = BV1; i <= TV; i++)  vent_command(i,zb_send);
  Serial.println("--------ALL REVIVE--------");
  for(int i = BR1; i <= TR2; i++) revive_command(i,zb_send);
  Serial.println("--------TEMPLE--------");
  temple_command(all_command);
}

void all_command_withoutR(String all_command){
  String zb_send = "";
  zb_send += all_command.substring(4,all_command.length());
  zb_send += ' ';
  
  Serial.println("--------ALL DOOR--------");
  for(int i = BD; i <= TD; i++)   door_command(i,zb_send); 
  Serial.println("------ALL ITEMBOX-------");
  for(int i = BI1; i <= TI1; i++) itmebox_command(i,zb_send);
//  Serial.println("-----ALL GENERATOR-----");
//  for(int i = BG; i <= TG; i++)   generator_command(i,zb_send);
//  Serial.println("-------ALL VENT-------");    
//  for(int i = BV1; i <= TV; i++)  vent_command(i,zb_send);
//  Serial.println("--------TEMPLE--------");
//  temple_command(all_command);
}
void revive_place(String revive_place)
{
  String zb_send = "";
  zb_send += revive_place.substring(4,revive_place.length());
  zb_send += ' ';
  switch(revive_place.charAt(0))
  {
    case 'A': 
      for(int i = BR1; i <= TR2; i++)         
        revive_command(i,zb_send);   
      Serial.println("SEND DONE");   break;
    case 'B': if(revive_place.charAt(2) == '1')       revive_command(BR1,zb_send);
              else if(revive_place.charAt(2) == '2')  revive_command(BR2,zb_send);    break;
    case 'L': if(revive_place.charAt(2) == '1')       revive_command(LR1,zb_send);
              else if(revive_place.charAt(2) == '2')  revive_command(LR2,zb_send);    break;
    case 'C': if(revive_place.charAt(2) == '1')       revive_command(CR1,zb_send);
              else if(revive_place.charAt(2) == '2')  revive_command(CR2,zb_send);    break;
    case 'S': if(revive_place.charAt(2) == '1')       revive_command(SR1,zb_send);
              else if(revive_place.charAt(2) == '2')  revive_command(SR2,zb_send);    break;
    case 'T': if(revive_place.charAt(2) == '1')       revive_command(TR1,zb_send);
              else if(revive_place.charAt(2) == '2')  revive_command(TR2,zb_send);    break;
  }
}
void itembox_place(String itembox_place)
{
  String zb_send = "";
  zb_send += itembox_place.substring(4,itembox_place.length());
  zb_send += ' ';
  switch(itembox_place.charAt(0))
  {
    case 'A': 
      for(int i = BI1; i <= TI1; i++)         
        itmebox_command(i,zb_send);  
      Serial.println("SEND DONE");   break;
    case 'B': if(itembox_place.charAt(2) == '1')      itmebox_command(BI1,zb_send);
              else if(itembox_place.charAt(2) == '2') itmebox_command(BI2,zb_send);   break;
    case 'L': itmebox_command(LI1,zb_send);                                           break;
    case 'C': if(itembox_place.charAt(2) == '1')      itmebox_command(CI1,zb_send);
              else if(itembox_place.charAt(2) == '2') itmebox_command(CI2,zb_send);   break;
    case 'S': if(itembox_place.charAt(2) == '1')      itmebox_command(SI1,zb_send);
              else if(itembox_place.charAt(2) == '2') itmebox_command(SI2,zb_send);   break;
    case 'T': itmebox_command(TI1,zb_send);                                           break;
  }
}
void generator_place(String generator_place)
{
  String zb_send = "";
  zb_send += generator_place.substring(4,generator_place.length());
  zb_send += ' ';
  switch(generator_place.charAt(0))
  {
    case 'A': 
      for(int i = BG; i <= TG; i++)          
        generator_command(i,zb_send); 
      Serial.println("SEND DONE");  break;
    case 'B': generator_command(BG,zb_send);                                          break;
    case 'L': generator_command(LG,zb_send);                                          break;
    case 'C': generator_command(CG,zb_send);                                          break;
    case 'S': generator_command(SG,zb_send);                                          break;
    case 'T': generator_command(TG,zb_send);                                          break;
  }
}
void escape_place(String escape_place)
{
  String zb_send = "";
  zb_send += escape_place.substring(4,escape_place.length());
  zb_send += ' ';
  switch(escape_place.charAt(0))
  {
    case 'A': 
      for(int i = CES; i <= TES; i++)       
        escape_command(i,zb_send);    
      Serial.println("SEND DONE");    break;
    case 'C': escape_command(CES,zb_send);                                            break;
    case 'S': escape_command(SES,zb_send);                                            break;
    case 'T': escape_command(TES,zb_send);                                            break;
  }
}
void door_place(String door_place)
{
  String zb_send = "";
  zb_send += door_place.substring(4,door_place.length());
  zb_send += ' ';
  switch(door_place.charAt(0))
  {
    case 'A': 
      for(int i = 0; i < 4; i++) 
        door_command(i,zb_send);                                       
      Serial.println("SEND DONE");       break;
    case 'B': door_command(BD,zb_send);                                               break;
    case 'C': door_command(CD,zb_send);                                               break;
    case 'S': door_command(SD1,zb_send);                                              break;
    case 'T': door_command(TD,zb_send);                                               break;
  }
}
void vent_place(String vent_place)
{
  String zb_send = "";
  zb_send += vent_place.substring(4,vent_place.length());
  zb_send += ' ';
  switch(vent_place.charAt(0))
  {
    case 'A': 
      for(int i = BV1; i <= TV; i++) 
        vent_command(i,zb_send);       
      Serial.println("SEND DONE");          
      break;
    case 'B': if(vent_place.charAt(2) == '1') vent_command(BV1,zb_send);              
              else if(vent_place.charAt(2) == '2') vent_command(BV2,zb_send);         break;
    case 'L': vent_command(LV,zb_send);                                               break;
    case 'C': vent_command(CV,zb_send);                                               break;
    case 'S': vent_command(SV,zb_send);                                               break;
    case 'T': vent_command(TV,zb_send);                                               break;
  }
}
void revive_command(int r_name, String revive_command)
{
  Serial.println(revive[r_name].name + "_send:" + revive_command + "...........\b");
  switch(XBEE3_serial1_Transmit_Request_ASCII(revive[r_name].mac, revive_command))
  {
    case 0:  Serial.println("SUCC"); Serial.println("lb_" + revive[r_name].name + '_' + revive_command);  break;
    default: Serial.println("FAIL"); Serial.println("lb_" + revive[r_name].name + "_X");                  break;
  }
}
void itmebox_command(int i_name, String itembox_command)
{
  Serial.println(itembox[i_name].name + "_send:" + itembox_command + "...........\b");
  switch(XBEE3_serial1_Transmit_Request_ASCII(itembox[i_name].mac, itembox_command))
  {
    case 0:  Serial.println("SUCC"); Serial.println("lb_" + itembox[i_name].name + '_' + itembox_command); break;
    default: Serial.println("FAIL"); Serial.println("lb_" + itembox[i_name].name + "_X");                  break;
  }
}
void generator_command(int g_name, String generator_command)
{
  Serial.println(generator[g_name].name + "_send:" + generator_command + "...........\b");
  switch(XBEE3_serial1_Transmit_Request_ASCII(generator[g_name].mac, generator_command))
  {
    case 0:  Serial.println("SUCC"); Serial.println("lb_" + generator[g_name].name + '_' + generator_command); break;
    default: Serial.println("FAIL"); Serial.println("lb_" + generator[g_name].name + "_X");                    break;
  }
}
void escape_command(int e_name, String escape_command)
{
  Serial.println(escape[e_name].name + "_send:" + escape_command + "...........\b");
  switch(XBEE3_serial1_Transmit_Request_ASCII(escape[e_name].mac, escape_command))
  {
    case 0:  Serial.println("SUCC"); Serial.println("lb_" + escape[e_name].name + '_' + escape_command); break;
    default: Serial.println("FAIL"); Serial.println("lb_" + escape[e_name].name + "_X");              break;
  }
}
void door_command(int d_name, String door_command)
{
  Serial.println(door[d_name].name + "_send:" + door_command + "...........\b");
  switch(XBEE3_serial1_Transmit_Request_ASCII(door[d_name].mac, door_command))
  {
    case 0:  Serial.println("SUCC"); Serial.println("lb_" + door[d_name].name + '_' + door_command); break;
    default: Serial.println("FAIL"); Serial.println("lb_" + door[d_name].name + "_X");              break;
  }
}
void vent_command(int v_name, String vent_command)
{
  Serial.println(vent[v_name].name + "_send:" + vent_command + "...........\b");
  switch(XBEE3_serial1_Transmit_Request_ASCII(vent[v_name].mac, vent_command))
  {
    case 0:  Serial.println("SUCC"); Serial.println("lb_" + vent[v_name].name + '_' + vent_command); break;
    default: Serial.println("FAIL"); Serial.println("lb_" + vent[v_name].name + "_X");                break;
  }
}
void temple_command(String temple_command)
{
  String temple_send = "";
  temple_send += temple_command.substring(4,temple_command.length()); temple_send += ' ';
  Serial.println(temple[LT].name + "_send:" + temple_send + "...........\b");
  switch(XBEE3_serial1_Transmit_Request_ASCII(temple[LT].mac, temple_send))
  {
    case 0:  Serial.println("SUCC"); Serial.println("lb_" + temple[LT].name + '_' + temple_send);  break;
    default: Serial.println("FAIL"); Serial.println("lb_" + temple[LT].name + "_X");           break;
  }
}
void light_command(String light_command)
{
  String light_send = "";
  light_send += light_command.substring(0,1);
  light_send += light_command.substring(4,light_command.length()); light_send += ' ';
  Serial.println(light_command.substring(0,1) + "L_send:" + light_command.substring(4,light_command.length()) + "...........\b");
  switch(XBEE3_serial1_Transmit_Request_ASCII(light[AL].mac, light_send))
  {
    case 0:  Serial.println("SUCC"); Serial.println("lb_" + light_command.substring(0,1) + "L_" + light_command.substring(4,light_command.length()));   break;
    default: Serial.println("FAIL"); Serial.println("lb_" + light_command.substring(0,1) + "L_" + "_X");                                                break;
  }
}
void fog_command(String fog_command)
{
  String fog_send = "";
  fog_send += fog_command.substring(4,fog_command.length()); fog_send += ' ';
  Serial.println(fog[BF].name + "_send:" + fog_send + "...........\b");
  switch(XBEE3_serial1_Transmit_Request_ASCII(fog[BF].mac, fog_send))
  {
    case 0:  Serial.println("SUCC"); Serial.println("lb_" + fog[BF].name + '_' + fog_send);  break;
    default: Serial.println("FAIL"); Serial.println("lb_" + fog[BF].name + "_X");           break;
  }
}
void vent_adrSender(){
  switch(XBEE3_Transmit_Request_HEX(vent[BV1].mac, vent[SV].mac, 8)){
      case 0:  Serial.println("BV1->SV ADR SUCC"); break;
      default:  Serial.println("BV1->SV ADR FAIL");
  }
  switch(XBEE3_Transmit_Request_HEX(vent[SV].mac, vent[BV1].mac, 8)){
      case 0: Serial.println("SV->BV1 ADR SUCC"); break;
      default: Serial.println("SV->BV1 ADR FAIL");
  }
  switch(XBEE3_Transmit_Request_HEX(vent[BV2].mac, vent[TV].mac, 8)){
      case 0: Serial.println("BV2->TV ADR SUCC"); break;
      default:  Serial.println("BV2->TV ADR FAIL");
  }
  switch(XBEE3_Transmit_Request_HEX(vent[TV].mac, vent[BV2].mac, 8)){
      case 0: Serial.println("TV->BV2 ADR SUCC"); break;
      default: Serial.println("TV->BV2 ADR FAIL");
  }
  switch(XBEE3_Transmit_Request_HEX(vent[LV].mac, vent[CV].mac, 8)){
      case 0: Serial.println("LV->CV ADR SUCC"); break;
      default: Serial.println("LV->CV ADR FAIL");
  }
  switch(XBEE3_Transmit_Request_HEX(vent[CV].mac, vent[LV].mac, 8)){
      case 0: Serial.println("CV->LV ADR SUCC"); break;
      default: Serial.println("CV->LV ADR FAIL");
  }
}
