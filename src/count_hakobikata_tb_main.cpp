#include <count_hakobikata_tb/utils.hpp>

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

