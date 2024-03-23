#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

struct Trade {
    long long currTimeStamp;
    long long maxTimeGap;
    int volume;
    int weightedPriceSum;
    int weightedPriceAvg; 
    int maxPrice;
    Trade() : currTimeStamp(0), maxTimeGap(0), volume(0), weightedPriceSum(0), weightedPriceAvg(0), maxPrice(0){};
    Trade(long long timeStamp, int volume, int price){
        this->currTimeStamp = timeStamp;
        this->volume = volume;
        this->weightedPriceSum = price * volume;
        this->maxTimeGap = 0;
    }
};

/*
* input: string format of each transaction
* output: each symbol's trade statements
*/
int update_trade_info(vector<std::string>& data, std::unordered_map<std::string, Trade>& trades){
    long long currTimeStamp = std::stoi(data[0]);
    long long timeGap = currTimeStamp - trades[data[1]].currTimeStamp;
    if (timeGap > trades[data[1]].maxTimeGap) {
        trades[data[1]].maxTimeGap = timeGap;
    }
    trades[data[1]].currTimeStamp = currTimeStamp;
    trades[data[1]].volume += std::stoi(data[2]);
    trades[data[1]].weightedPriceSum += std::stoi(data[3]) * std::stoi(data[2]);
    if (trades[data[1]].volume > 0){
        trades[data[1]].weightedPriceAvg = trades[data[1]].weightedPriceSum / trades[data[1]].volume;;
    }
    if (std::stoi(data[3]) > trades[data[1]].maxPrice){
        trades[data[1]].maxPrice = std::stoi(data[3]);
    }
    return 0;
}

int output_csv(string csv_name, std::unordered_map<std::string, Trade>& trades){
    std::ofstream outputFile(csv_name);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open file for writing.\n";
        return 1; 
    }
    for (const auto& pair : trades) {
        outputFile << pair.first << ',' << pair.second.maxTimeGap << ','  << pair.second.volume << ','  << pair.second.weightedPriceAvg << ',' << pair.second.maxPrice << std::endl;
    }
    outputFile.close(); // 关闭文件流
    std::cout << "Data has been written to output.csv.\n";
    return 0;
}

int main(){
    std::unordered_map<std::string, Trade> trades;
    std::ifstream file("input.csv");
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream s(line);
        std::string cell;
        while (std::getline(s, cell, ',')) {
            row.push_back(cell);
        }
        auto it = trades.find(row[1]);
        if (it == trades.end()) {
            trades[row[1]] = Trade(
                std::stoll((row[0])),
                std::stoi(row[2]),
                std::stoi(row[3])
            );
        } else {
            update_trade_info(row, trades);
        }
    }
    // output is much smaller than the input file.
    if (output_csv("output.csv",trades) != 0){
        cout<< "output csv failed"<<endl;
    }else{
        cout<< "output csv success"<<endl;
    }
    return 0;
}

