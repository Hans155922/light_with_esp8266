#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#define LED_PIN 2 //板载led
#define LED 3 //外挂led
/*************************************************************
***                     By Hnas155922                      *** 
***       Q Q:1559220768 问题答案随便填，防机器人的qwq      *** 
***                 Q Q群：暂无                       *** 
***               Twitter @hans1559220768                  *** 
***                 Bilibili 吃月球的喵酱                   *** 
***             仅供学习使用，严禁任何商业用途              *** 
***未经本人许可禁止转载本代码，一般来说加我QQ都会同意转载qwq *** 
***             使用本代码，即视为同意以上条款               *** 
***             1.连接wifi_light_开头的wifi；               *** 
***           2.密码 12345678可以在setup里面改              ***
***            3.进入后台192.168.1.1控制灯开关              ***
**************************************************************/
IPAddress localip(192, 168, 1, 1); //  内网IP地址
IPAddress softGateway(192, 168, 1, 1);
IPAddress softSubnet(255, 255, 255, 0);
ESP8266WebServer server(80);
void handleRoot() {
String page = "<html>\r\n";
 page +="<head><meta charset=\"utf-8\">\r\n";
page +="<title>点灯</title>\r\n</head>\r\n";
page += "<body>\r\n";
page += "<font>当前状态:";
 if (digitalRead(LED)) page +="开";
 else page +="关";
page += "</font>\r\n";
page +="<input type=\"button\" value=\"打开\" onclick=\"javascrtpt:window.location.href='/ON'\" /></br>\r\n";
page +="<input type=\"button\" value=\"关闭\" onclick=\"javascrtpt:window.location.href='/OFF'\" />\r\n";
page +="</body>\r\n";
page +="</html>\r\n";
server.send(200, "text/html", page);
}
void ON() {
digitalWrite(LED, HIGH);
String page = "<html>\r\n";
page +="<head><meta charset=\"utf-8\">\r\n";
page +="<title>点灯</title>\r\n</head>\r\n";
page += "<body>\r\n";
page += "<font>当前状态:开</font></br>\r\n";
page +="<input type=\"button\" value=\"关闭\" onclick=\"javascrtpt:window.location.href='/OFF'\" />\r\n";
page +="</body>\r\n";
page +="</html>\r\n";
server.send(200, "text/html", page);
}
void OFF() {
digitalWrite(LED, LOW);
String page = "<html>\r\n";
page +="<head><meta charset=\"utf-8\">\r\n";
page +="<title>点灯</title>\r\n</head>\r\n";
page += "<body>\r\n";
page += "<font>当前状态:关</font>\r\n";
page +="<input type=\"button\" value=\"打开\" onclick=\"javascrtpt:window.location.href='/ON'\" />\r\n";
page +="</body>\r\n";
page +="</html>\r\n";
server.send(200, "text/html", page);
}
void Notfound() {
  server.send(404, "text/html", "404");
}
void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  Serial.begin(115200);
  WiFi.softAPConfig(localip, softGateway, softSubnet);
  String wifiName = ("wifi_light_" + (String)ESP.getChipId()); // 设置WIFI名称
  const char *softAPName = wifiName.c_str();
  String WifiPassword="12345678";//密码
  WiFi.softAP(softAPName, WifiPassword);
  Serial.println("");
  Serial.print("WiFiName: ");  // 输出WIFI 名称
  Serial.println(wifiName);
  Serial.print("WiFiPassword: ");  // 输出WIFI 密码
  Serial.println(WifiPassword);
  Serial.println("");
  pinMode(LED, OUTPUT);
  Serial.println();
  server.on("/", handleRoot);
  server.on("/ON", ON);
  server.on("/OFF", OFF);
  server.onNotFound(Notfound);
  server.begin();
  Serial.println("HTTP server started");
  server.handleClient();
  MDNS.update();
  digitalWrite(LED_PIN, LOW);
  Serial.println("初始化成功");
  digitalWrite(LED, HIGH);//默认亮
}
void loop() {
  server.handleClient();
}
