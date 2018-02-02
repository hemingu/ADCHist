#pragma once

const int ADC_CH = 1;
const int NUMBER_OF_ELEMENTS_PER_CH = 4;
const int NUMBER_OF_ADC_CH = 8;
const int NUMBER_OF_ELEMENTS_PER_LINE = NUMBER_OF_ELEMENTS_PER_CH * NUMBER_OF_ADC_CH + 1;

const Int_t HIST_MIN = 0;
const Int_t HIST_MAX = 700;
const TString AXIS = ";ADC Channel;Count";