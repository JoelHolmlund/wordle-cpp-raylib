#ifndef wordlefunc_H
#define wordlefunc_H
#include <string>
#include <vector>
#include <unordered_set>
    enum Resultat { GRA, GUL, GRON };

    struct SparadGissning {
        std::string ord;
        std::vector<Resultat> färger;
    };

    struct WordleData {
        std::vector<std::string> potentiella_svar;
        std::unordered_set<std::string> alla_giltiga_ord;
    };

    WordleData ladda_all_data();

    std::string slumpa_ord(const WordleData& data);
    bool ar_gissning_giltig(const std::string& gissning, const WordleData& data);
    std::vector<Resultat> kolla_gissning(std::string gissning, std::string rattOrd);

#endif
