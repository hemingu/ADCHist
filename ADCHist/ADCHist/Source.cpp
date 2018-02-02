
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT 1

#include "Common.h"
#include "Const.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << argc << endl;
    for (volatile int i = 0; i < argc; i++)
    {
        cout << argv[i] << endl;
    }

    // Open ROOT window
    //TApplication app("Root Window", &argc, argv);

    for (int i = 1; i < argc; i++)
    {
        vector<int> AdcOutputs;

        string csvFilePath = argv[i];
        int pathPos = csvFilePath.find_last_of("\\");
        int extPos = csvFilePath.find_last_of(".");
        if (csvFilePath.substr(extPos, csvFilePath.size() - extPos) != ".csv") continue;
        TString fileName = csvFilePath.substr(pathPos + 1, extPos - pathPos - 1).c_str();
        string fileNameSub = csvFilePath.substr(pathPos + 1, extPos - pathPos - 1);

        ifstream ifs(csvFilePath);
        if (!ifs) {
            cout << "File input error" << endl;
            return 1;
        }

        string str;
        int elementsCounter = 0;
        while (getline(ifs, str))
        {
            string token;
            stringstream ss;
            istringstream stream(str);

            while (getline(stream, token, ','))
            {
                if (elementsCounter++ == NUMBER_OF_ELEMENTS_PER_CH * (ADC_CH - 1) + 1)
                {
                    int i;
                    ss << token;
                    ss >> i;
                    AdcOutputs.push_back(i);
                }
                if (elementsCounter >= NUMBER_OF_ELEMENTS_PER_LINE - 1) elementsCounter = 0;
            }
        }


        // Get maximum & minimum ADC output
        Int_t max = *max_element(AdcOutputs.begin(), AdcOutputs.end());
        Int_t min = *min_element(AdcOutputs.begin(), AdcOutputs.end());

        int numberOfData = AdcOutputs.size();

        TCanvas *canvas = new TCanvas();

        TH1D *hist = new TH1D(fileName, AXIS, HIST_MAX-HIST_MIN, HIST_MIN+1, HIST_MAX);

        for (auto itr = AdcOutputs.cbegin(); itr != AdcOutputs.cend(); ++itr)
        {
            hist->Fill((Double_t)*itr);
        }
        hist->Sumw2();
        hist->Draw();


        TString histFileName = fileName + ".root";
        TFile histFile(fileName + ".root", "RECREATE");
        hist->Write();
        histFile.Close();
    }
    

    //vector<int> AdcOutputs;

    //string csvFilePath = "C:\\Users\\hemingu\\Dropbox\\ë≤ã∆å§ãÜ\\é¿å±ÉfÅ[É^\\20180131\\ADC\\180131215555.csv";
    //int pathPos = csvFilePath.find_last_of("\\");
    //int extPos = csvFilePath.find_last_of(".");
    //string ext = csvFilePath.substr(extPos, csvFilePath.size() - extPos);
    //TString fileName = csvFilePath.substr(pathPos+1, extPos - pathPos -1).c_str();
    //string fileNameSub = csvFilePath.substr(pathPos+1, extPos - pathPos-1);


    //ifstream ifs(csvFilePath);
    //if (!ifs) {
    //    cout << "File input error" << endl;
    //    return 1;
    //}

    //string str;
    //int elementsCounter = 0;
    //while (getline(ifs, str))
    //{
    //    string token;
    //    stringstream ss;
    //    istringstream stream(str);

    //    while (getline(stream, token, ','))
    //    {
    //        if (elementsCounter++ == NUMBER_OF_ELEMENTS_PER_CH * (ADC_CH - 1) + 1)
    //        {
    //            int i;
    //            ss << token;
    //            ss >> i;
    //            AdcOutputs.push_back(i);
    //        }
    //        if (elementsCounter >= NUMBER_OF_ELEMENTS_PER_LINE - 1) elementsCounter = 0;
    //    }
    //}


    //// Get maximum & minimum ADC output
    //Int_t max = *max_element(AdcOutputs.begin(), AdcOutputs.end());
    //Int_t min = *min_element(AdcOutputs.begin(), AdcOutputs.end());

    //int numberOfData = AdcOutputs.size();

    //TCanvas *canvas = new TCanvas();
    //
    //TH1D *hist = new TH1D(fileName, AXIS, max - HIST_MIN + 1, HIST_MIN, max);

    //for (auto itr = AdcOutputs.cbegin(); itr != AdcOutputs.cend(); ++itr)
    //{
    //    hist->Fill((Double_t)*itr);
    //}
    //hist->Sumw2();
    //hist->Draw();


    //TString histFileName = fileName + ".root";
    //TFile histFile(fileName + ".root", "RECREATE");
    //hist->Write();
    //histFile.Close();

    //app.Run();


    return 0;
}