#include <count_hakobikata_tb/utils.hpp>



int main(int argc, char** argv){

    if(argc != 2){
        std::cout << "Usage: " << argv[0] << " <scenario generation config YAML>" << std::endl;
        return 1;
    }

    const std::string config_yaml_path = argv[1];
    
    YAML::Node config_yaml = YAML::LoadFile(config_yaml_path);

    const std::string station_list_path = config_yaml["layouts"]["forklift"]["station_list"].as<std::string>();
    // StationList station_list;
    // loadStationList(station_list_path, &station_list);

    const size_t vehicle_num = config_yaml["vehicles"].size();
    
    for(size_t i = 0; i < vehicle_num; i++){

        const int n_source = config_yaml["objects"].size();    
        const int max_n_pool = 6;

        std::vector<std::vector<ACTION> > result;

        countHakobikata(n_source, max_n_pool, result);

        std::cout << "Found " << result.size() << " patterns" << std::endl;

        if(writeHakobikataToCsv("hakobikata.csv", result)){
            std::cout << "Worte results to hakobikata.csv" << std::endl;
        }
    }

    return 0;
}


