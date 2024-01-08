

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

typedef enum{
    SRC2DST,
    SRC2POOL,
    POOL2DST
}ACTION;

void listHakobikataRecursive(const int n_source,
                             const int n_pool,
                             const int max_n_pool,
                             const std::vector<ACTION>& soremade_no_hakobikata,
                             std::vector<std::vector<ACTION> >& result){

    result.clear();

    // 終了
    if(n_source == 0 && n_pool == 0){
        result.push_back(soremade_no_hakobikata);
        return;
    }

    // SRC2DSTの場合
    if(n_source > 0){
        std::vector<ACTION> case_src2dst = soremade_no_hakobikata;
        case_src2dst.push_back(SRC2DST);
        std::vector<std::vector<ACTION> > result_src2dst;
        listHakobikataRecursive(n_source - 1,
                                n_pool,
                                max_n_pool,
                                case_src2dst,
                                result_src2dst);

        result.insert(result.end(), result_src2dst.begin(), result_src2dst.end());
    }

    // SRC2POOLの場合
    if(n_source > 0 && n_pool < max_n_pool){
        std::vector<ACTION> case_src2pool = soremade_no_hakobikata;
        case_src2pool.push_back(SRC2POOL);
        std::vector<std::vector<ACTION> > result_src2pool;
        listHakobikataRecursive(n_source - 1,
                                n_pool + 1,
                                max_n_pool,
                                case_src2pool,
                                result_src2pool);

        result.insert(result.end(), result_src2pool.begin(), result_src2pool.end());
    }

    // POOL2DSTの場合
    if(n_pool > 0
       && n_source == 0 /* 「SRCからの運搬を優先する」場合 */
    ){
        std::vector<ACTION> case_pool2dst = soremade_no_hakobikata;
        case_pool2dst.push_back(POOL2DST);
        std::vector<std::vector<ACTION> > result_pool2dst;
        listHakobikataRecursive(n_source,
                                n_pool - 1,
                                max_n_pool,
                                case_pool2dst,
                                result_pool2dst);

        result.insert(result.end(), result_pool2dst.begin(), result_pool2dst.end());
    }

    return;
}

size_t countHakobikata(const int n_source, const int max_n_pool,
                       std::vector<std::vector<ACTION> >& hakobikata){

    hakobikata.clear();

    std::vector<ACTION> dummy;
    listHakobikataRecursive(n_source, 0, max_n_pool, dummy, hakobikata);

    return hakobikata.size();
}

bool writeHakobikataToCsv(const std::string& file_name,
                          const std::vector<std::vector<ACTION> >& hakobikata){

    std::ofstream fout(file_name);

    if(! fout){
        std::cerr << "Error: Could not open " << file_name << std::endl;
        return false;
    }

    fout << "#Index,Num of actions,Actions" << std::endl;

    for(size_t i = 0; i < hakobikata.size(); i++){
        fout << i << ',' << hakobikata[i].size();
        for(size_t j = 0; j < hakobikata[i].size(); j++){
            switch(hakobikata[i][j]){
            case SRC2DST:
                fout << ",SRC2DST";
                break;
            case SRC2POOL:
                fout << ",SRC2POOL";
                break;
            case POOL2DST:
                fout << ",POOL2DST";
                break;
            default:
                fout << "ERROR";
                break;
            }
        }
        fout << std::endl;
    }

    fout.close();

    return true;
}

int main(int argc, char** argv){

    if(argc != 3){
        std::cout << "Usage: " << argv[0] << " <num of items in source> <maximum num of temporay pool>" << std::endl;
        return 1;
    }

    const int n_source = std::stoi(argv[1]);
    const int max_n_pool = std::stoi(argv[2]);

    std::vector<std::vector<ACTION> > result;

    countHakobikata(n_source, max_n_pool, result);

    std::cout << "Found " << result.size() << " patterns" << std::endl;

    if(writeHakobikataToCsv("hakobikata.csv", result)){
        std::cout << "Worte results to hakobikata.csv" << std::endl;
    }

    return 0;
}

