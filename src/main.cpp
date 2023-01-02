#include <Arduino.h>
#include <iostream>

// ---- 自訂類別 ----
#include <State.h>
#include <Controller.h>

// 與機械手臂溝通之腳位
#define RX 16
#define TX 17

void grafcet();
void printState();

// --- 建立物件 ---
Controller *ctr = new Controller();
State *state;

Init *ini = new Init();
Right *right = new Right();
Left *left = new Left();

// ---- 儲存各種狀態是否 be activated ----
int X[8]; // X0:初始點, X1:左轉, X2:右轉, X3:往上, X4:往下, X5:關爪, X6:開爪

// --- 初始化 ---
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RX, TX);

  // 設定15 ~ 8 pinMode to input，接收語音模組訊號
  for(int i = 0; i < 8; i++)
  {
    pinMode(ctr->IO[i], INPUT);
  }
}

// --- 執行grafcet ---
void loop() 
{
  grafcet();
}

// --- print狀態 ---
void printState()
{
  for(int i = 0; i < sizeof(X) / sizeof(int); i++)
  {
    Serial.printf("X%d=%d、", i, X[i]);
  }
  Serial.println("");

  delay(500);
}

void grafcet()
{
  // --- 讀取語音博組訊號 ---
  for(int i = 0; i < sizeof(X) / sizeof(int); i++)
  {
    X[i] = digitalRead(ctr->IO[i]);
  }
  

  if(X[0] == 1) //初始位置
  {
    state = ini;
    printState();
    ctr->doAction(state, 5000);
  }
  else if(X[1] == 1) //左轉
  {
    state = left;
    printState();
    ctr->doAction(state, 5000);
  }
  else if(X[2] == 1) //右轉
  {
    state = right;
    printState();
    ctr->doAction(state, 5000);
  }
  else if(X[3] == 1) //往上
  {
    printState();
    ctr->Up(state, 5000);
  }
  else if(X[4] == 1) //往下
  {
    printState();
    ctr->Down(state, 5000);
  }
  else if(X[5] == 1) //關爪
  {
    printState();
    ctr->Close_Paw(state, 5000);
  }
  else if(X[6] == 1) //開爪
  {
    printState();
    ctr->Open_Paw(state, 5000);
  }
  else if(X[7] == 1)
  {
    printState();
    Serial.println("Dancing");
    delay(4500);
  }
  
}