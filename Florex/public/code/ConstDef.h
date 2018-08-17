#pragma once

#include <string>

using namespace std;

const string tableTimeStepEnd_mm = "_mm";
const string tableTimeStepEnd_15m = "_15m";
const string tableTimeStepEnd_hh = "_hh";
const string tableTimeStepEnd_4h = "_4h";
const string tableTimeStepEnd_dd = "_dd";
const string tableTimeStepEnd_ww = "_ww";

const int timeStepStep_def = 0;
const int timeStepStep_mm = 1;
const int timeStepStep_15m = 2;
const int timeStepStep_hh = 3;
const int timeStepStep_4h = 4;
const int timeStepStep_dd = 5;
const int timeStepStep_ww = 6;

const string florexDbName = "florex";
const string coreDbName = "core";

const static int maxLineRead = 10000;

const string rateNames[] = {"testRate","eurusd","usdjpy","xauusd","gbpusd","audusd"};


