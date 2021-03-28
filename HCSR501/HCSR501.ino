#define irSensor 8
#define LED 12
 
void setup() {
  // 初始化 串口通讯
  Serial.begin(9600);
  pinMode(LED, OUTPUT); //连接内置LED的引脚设置为输出模式
  pinMode(irSensor, INPUT);     //连接人体红外感应模块的OUT引脚设置为输入模式
}
  
// 
void loop() {
  bool sensorReading = digitalRead(irSensor);  //建立变量存储感应模块的输出信号
  
  if ( sensorReading ) {
    digitalWrite(LED, HIGH);   // 模块感应到人.输出高电平.点亮LED
  }
  else {
    digitalWrite(LED, LOW);   //  无人状态保持LED关闭
  }
    Serial.println(sensorReading);  //将模块输出信号通过串口监视器显示
}
