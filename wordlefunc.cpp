#include "wordlefunc.h"
#include "json.hpp"
#include <fstream>
#include <ctime>
#include <algorithm>

using json = nlohmann::json;

WordleData ladda_all_data(){
    WordleData data;

    std::ifstream f1("wordles.json");
    if (f1.is_open()){
        json j1 = json::parse(f1);
        for (auto& s : j1){
            std::string ord = s.get<std::string>();
            data.potentiella_svar.push_back(ord);
            data.alla_giltiga_ord.insert(ord);
        }
    }

    std::ifstream f2("nonwordles.json");
    if (f2.is_open()) {
        json j2 = json::parse(f2);
        for (auto& s : j2){
            data.alla_giltiga_ord.insert(s.get<std::string>());
        }
    }
    return data;
}

std::string slumpa_ord(const WordleData& data) {
    if (data.potentiella_svar.empty()) return "";
    return data.potentiella_svar[std::rand() % data.potentiella_svar.size()];
}

bool ar_gissning_giltig(const std::string& gissning, const WordleData& data){
    std::string testOrd = gissning;
    std::transform(testOrd.begin(), testOrd.end(), testOrd.begin(), ::tolower);
    return data.alla_giltiga_ord.find(testOrd) != data.alla_giltiga_ord.end();
}

std::vector<Resultat> kolla_gissning(std::string gissning, std::string rattOrd) {
    std::vector<Resultat> resultat(5, GRA);
    std::vector<bool> rattOrdAnvant(5, false);

    for (int i = 0; i < 5; i++) {
        if (gissning[i] == rattOrd[i]) {
            resultat[i] = GRON;
            rattOrdAnvant[i] = true;
        }
    }

    for (int i = 0; i < 5; i++) {
        if (resultat[i] == GRON) continue;
        for (int j = 0; j < 5; j++) {
            if (!rattOrdAnvant[j] && gissning[i] == rattOrd[j]) {
                resultat[i] = GUL;
                rattOrdAnvant[j] = true;
                break;
            }
        }
    }
    return resultat;
}
