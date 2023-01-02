#pragma once
#include <iostream>
#include <Arduino.h>

class State
{
    public:
        String name;
        String action;
        String str;
        char *point;
        char ary[0];
        virtual void doAction(int del_num) = 0;

        virtual void Up(int del_num) {
            ary[11] = 0xDC;
            ary[12] = 0x05;
            ary[14] = 0xDC;
            ary[15] = 0x05;
            this->action = "、Up";

            doAction(del_num);

            this->action = "";
        }

        virtual void Down(int del_num) {
            ary[11] = 0xD0;
            ary[12] = 0x07;
            ary[14] = 0xE8;
            ary[15] = 0x03;
            this->action = "Down";

            doAction(del_num);

            this->action = "";
        }

        virtual void Open_Paw(int del_num) {
            ary[23] = 0xF4;
            ary[24] = 0x01;
            this->action = "、Open paw";

            doAction(del_num);

            this->action = "";
        }

        virtual void Close_Paw(int del_num) {
            ary[23] = 0xC4;
            ary[24] = 0x09;
            this->action = "、Close paw";

            doAction(del_num);

            this->action = "";
        }
};

class Init : public State
{
    protected:
        char ary[25] = {0x55,0x55,0x17,0x03,0x06,0x88,0x13,
                        0x01,0xDC,0x05,
                        0x02,0xDC,0x05,
                        0x03,0xDC,0x05,
                        0x04,0xDC,0x05,
                        0x05,0xDC,0x05,
                        0x06,0xC4,0x09 + '\0'};

        virtual void doAction(int del_num) {
            this->point = ary;
            
            while(*point)
            {
                this->str += *point;
                *point++;
            }

            this->name = "Init";
            Serial.println("State: " + this->name + this->action + "\n");
            Serial2.print(str);

            delay(del_num);
        }
};


class Right : public State
{
    protected:
        char ary[25] = {0x55,0x55,0x17,0x03,0x06,0x88,0x13,
                        0x01,0xF4,0x01,
                        0x02,0xDC,0x05,
                        0x03,0xDC,0x05,
                        0x04,0xDC,0x05,
                        0x05,0xDC,0x05,
                        0x06,0xC4,0x09 + '\0'};
        
        virtual void doAction(int del_num) {
            this->point = ary;
            
            while(*point)
            {
                this->str += *point;
                *point++;
            }

            this->name = "Turn Right";
            Serial.println("State: " + this->name + this->action + "\n");
            Serial2.print(str);

            delay(del_num);
        }
};

class Left : public State
{
    protected:
        char ary[25] = {0x55,0x55,0x17,0x03,0x06,0x88,0x13,
                        0x01,0xC4,0x09,
                        0x02,0xDC,0x05,
                        0x03,0xDC,0x05,
                        0x04,0xDC,0x05,
                        0x05,0xDC,0x05,
                        0x06,0xC4,0x09 + '\0'
                        };
        
        virtual void doAction(int del_num) {
            this->point = ary;
            
            while(*point)
            {
                this->str += *point;
                *point++;
            }

            this->name = "Turn Left";
            Serial.println("State: " + this->name + this->action + "\n");
            Serial2.print(str);

            delay(del_num);
        }
};