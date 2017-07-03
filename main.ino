#include <SoftwareSerial.h>
#include <SPI.h>
#include <math.h>
const int THERM_PIN = A0;//定义A0口连接体温传感器
unsigned char num[3];
unsigned long temp; 
SoftwareSerial BTSerial(8, 9); //定义蓝牙串口输入输出脚
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//设置波特率为9600
  Serial.println("start!");
  BTSerial.begin(9600);//设置蓝牙串口波特率为9600
}

void loop() {
  unsigned int v;
  unsigned int dat;
  v = analogRead(THERM_PIN);//读取传感器模拟值赋给v
  dat = (1200 - v)/20; //温度计算公式
  temp = dat; //把温度值赋给temp
  num[0]= temp%100/10; //取温度的十位上的字符
  num[1]= temp%10; //取温度的个位数的字符
  while(BTSerial.available()) //判断蓝牙串口是否接到数据，如果有数据传来则开始往下执行
  {
    
      char c=BTSerial.read();//把接收到的字符赋值给C
      if(c =='a'){ //判断接收到的字符如果是“a”，就开始发送温度数据给手机
        delay(1050);//延时1.5s
        //write(dat)函数把数据dat以二进制所对应的字符发送出去，67对应的二进制字符为'C'
        BTSerial.write(num[0]+48);//先发送十位的一个字节给手机
        delay(1050);//延时1.5s
        BTSerial.write(num[1]+48);//再发送个位数的一个字节给手机
        delay(1050);//延时1.5s
        BTSerial.write(67);//发送停止位C
        delay(1050);//延时1.5s
        }
      
    }
//  
//    delay(1050);
//    Serial.write(num[0]+48);
//    delay(1050);
//    Serial.write(num[1]+48);
//    delay(1050);
//    Serial.write(67);
//    delay(1050);

//
//        delay(1050);
//        BTSerial.write(num[0]+48);
//        delay(1050);
//        BTSerial.write(num[1]+48);
//        delay(1050);
//        BTSerial.write(67);
//        delay(1050);
    //BTSerial.println(dat);
    //BTSerial.println();
    //delay(3000);
}
