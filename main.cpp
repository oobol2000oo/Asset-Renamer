#include "json.hpp"
#include <fstream>

using namespace std;
using namespace nlohmann;

void _error(){
    cerr << R"(Error! "AssetPathsManifest" not found or not correct format!!!)" << "\n\n";
    system("pause");
}

ifstream input;
ofstream output;
json js;
vector <string> missFile;

int main(){
    puts("Asset Renamer made by H3x4n1um version 1.3");
    puts(R"(Usage: put this tool and file "AssetPathsManifest" in PvZH_AB_Download_Beta\Downloads and run it)");
    puts("Credits: nlohmann for his awesome JSON parser\n");
    /*Read*/
    try{
        input.open("AssetPathsManifest");
        input >> js;
        input.close();
        for (auto i : js.at("BundleNameToDetails").get<map<string, json> >()){
            string fileName = i.first;
            int ver = i.second.at("Version").get<int>();
            if (rename(fileName.c_str(), (fileName + '_' + to_string(ver)).c_str()) != 0 &&
                rename((fileName + '_' + to_string(ver)).c_str(), (fileName + '_' + to_string(ver)).c_str()) != 0) missFile.push_back(fileName);
        }
    }
    catch (invalid_argument e){
        _error();
        return 1;
    }
    catch (out_of_range e){
        _error();
        return 1;
    }
    if (missFile.size() > 0){
        output.open("missing_file.log");
        output << "/*****************************************" << endl;
        output << "*This file was generated by Asset Renamer*" << endl;
        output << "*Version: 1.3                            *" << endl;
        output << "*Made by: H3x4n1um                       *" << endl;
        output << "*****************************************/" << endl;
        for (auto i : missFile) output << i << endl;
        output.close();
    }
    puts("Done! Check missing_file.log (if existed) for missing file\n");
    system("pause");
    return 0;
}
