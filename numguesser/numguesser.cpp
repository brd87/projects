#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
//"n" before fild names states for "number of"
//"WAB" states for "Weights And Biases"
/////////////////////////////////////////////////////////////////////////////
struct MINSTdata {
    int label;
    std::vector<int> pixels;
};
/////////////////////////////////////////////////////////////////////////////
class InputLayer {
private:
    std::vector<double> neurons;
public:
    int nNeurons;
    void setNeuronActivation(int neuronIndex, double activation) {
    }
};
/////////////////////////////////////////////////////////////////////////////
class HiddenLayer {
private:
    std::vector<double> neurons;
    std::vector<double> bias;
    std::vector<std::vector<double>> weights;
public:
    int nNeurons;

    void setNeuronActivation(int neuronIndex, double activation) {
    }
    void calculateActivation(const std::vector<double>& inputs) {
    }
    //modify
    void modify_hiBias(const std::vector<double>& newbias) {
        bias = newbias;
    }
    void modify_hiWeights(const std::vector<std::vector<double>>& newweights) {
        weights = newweights;
    }
};
/////////////////////////////////////////////////////////////////////////////
class OutputLayer {
private:
    std::vector<double> neurons;
    std::vector<double> bias;
    std::vector<std::vector<double>> weights;
public:
    int nNeurons;

    void setNeuronActivation(int neuronIndex, double activation) {
    }
    void calculateActivation(const std::vector<double>& inputs) {
    }
    //modify
    void modify_ouBias(const std::vector<double>& newbias) {
        bias = newbias;
    }
    void modify_ouWeights(const std::vector<std::vector<double>>& newweights) {
        weights = newweights;
    }
};
/////////////////////////////////////////////////////////////////////////////
class Network {
private:
    std::vector<InputLayer> inLayers;
    std::vector<HiddenLayer> hiLayers;
    OutputLayer ouLayer;
public:
    int nInput;
    int nOutput;
    int nHiddenLayers;
    int nHiddenNeurons;

    void initializeWAB() {
    }

    void forwardPropagation() {
    }

    void backwardPropagation() {
    }

    void updateWAB() {
    }

    std::vector<double> getOutput() {
    }
    //modify
    void modify_hiLayers(const std::vector<HiddenLayer>& newhiLayers) {
        hiLayers = newhiLayers;
    }
    void modify_ouLayer(const OutputLayer& newouLayer) {
        ouLayer = newouLayer;
    }
};
/////////////////////////////////////////////////////////////////////////////
class Menu {
private:
    Network network;
public:
    
    void start() {
    }

    void loadWAB(const std::string& fileName) {
        std::vector<HiddenLayer> hold_hiLayers;
        OutputLayer hold_ouLayer;
        HiddenLayer hold_hiLayer;
        std::vector<double> hold_bias;
        std::vector<double> hold_nuronWeights;
        std::vector<std::vector<double>> hold_weights;
        std::ifstream file(fileName);
        std::string line;
        std::string value;
        bool isH = false;
            if (file.is_open()) {
                while (std::getline(file, line)) {
                    if (line == "W") {
                        if (isH) {
                            hold_hiLayer.modify_hiBias(hold_bias);
                            hold_hiLayer.modify_hiWeights(hold_weights);
                            hold_hiLayers.push_back(hold_hiLayer);
                        }
                        else {
                            hold_ouLayer.modify_ouBias(hold_bias);
                            hold_ouLayer.modify_ouWeights(hold_weights);
                        }
                        isH = 1;
                        hold_bias.clear();
                        hold_weights.clear();
                        continue;
                    }
                    std::stringstream ss(line);
                    hold_nuronWeights.clear();
                    std::getline(ss, value, ',');
                    hold_bias.push_back(std::stod(value));
                    while (std::getline(ss, value, ',')) {
                        hold_nuronWeights.push_back(std::stod(value));
                    }
                    hold_weights.push_back(hold_nuronWeights);
                }
                file.close();
                network.modify_hiLayers(hold_hiLayers);
                network.modify_ouLayer(hold_ouLayer);
            }
            else {
                std::cout << "Error: Faild to open a file." << std::endl;
            }
    }

    void train(const std::string& fileName) {
        std::vector<MINSTdata> minst;
        std::ifstream file(fileName);
        std::string line;
        std::string value;
        if (file.is_open()) {
            while (std::getline(file, line)) {
                MINSTdata item;
                std::stringstream ss(line);
                std::getline(ss,value, ',');
                item.label = std::stoi(value);
                while (std::getline(ss, value, ',')) {
                    item.pixels.push_back(std::stoi(value));
                }
                minst.push_back(item);
            }
            file.close();
        }
        else {
            std::cout << "Error: Faild to open a file." << std::endl;
        }
    }

    void saveWAB(const std::string& fileName) {
    }

    void feed(const std::string& inputData) {
    }
};
/////////////////////////////////////////////////////////////////////////////
int main()
{
    std::cout << "H E L L O   WELLCOME, IN, MY, NETWORK, HERE YOU WILL DO SMART NETWORK STUFF LIKE:\n PROPAGANDA IN BOTH SIDES,\n FEEDING THE NETWORK WITH YUMMY DATA,\n AND WATCH RANDOM STRING OF NUMBERS TO FEEL SMARTER\n HEIL HOBBIT";
}