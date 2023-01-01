#pragma once
#include <iostream>
#include <Arduino.h>
#include <State.h>

class Controller
{
    public:
        const int IO[8] = {15, 14, 13, 12, 11, 10, 9, 8};

        void doAction(State *state, int del_num)
        {
            state->doAction(del_num);
        }

        void Up(State *state, int del_num)
        {
            state->Up(del_num);
        }

        void Down(State *state, int del_num)
        {
            state->Down(del_num);
        }

        void Open_Paw(State *state, int del_num)
        {
            state->Open_Paw(del_num);
        }

        void Close_Paw(State *state, int del_num)
        {
            state->Close_Paw(del_num);
        }

        void IOMonitor()
        {
            for(int i = 0; i < 8; i++)
            {
                Serial.printf("IO%d: %d\n", i+1, digitalRead(IO[i]));
            }
            Serial.println("----------------------------------");

            delay(500);
        }
};