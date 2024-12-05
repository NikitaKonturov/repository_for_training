#define __STDC_WANT_LIB_EXT1__ 1
#define _XOPEN_SOURCE
#include<time.h>
#include "funcs.hpp"



void CheckArgumentsAmount(int arguments_amount)
{
    if (arguments_amount != 2) {
        throw std::invalid_argument(std::format("Invalid command line arguments amount: current {}, required {}", arguments_amount, 2));
    }
}

void CheckInputPath(const std::filesystem::path& path_to_filesysteam_object)
{
    if(!path_to_filesysteam_object.has_extension() || path_to_filesysteam_object.extension() != std::filesystem::path(".json")) {
        throw std::invalid_argument(std::format("Filesystem object by path {} has invalid extension!", std::filesystem::absolute(path_to_filesysteam_object).string()));
    }
}

tm GetRequiredDateTime()
{
    tm resultTime;
    time_t currentTime;
    currentTime = time(NULL);
    if (localtime_r(&currentTime, &resultTime) == nullptr){
        throw std::runtime_error("Time conversion error...");
    }
    time_t timeInNowYear = resultTime.tm_yday * 86400 + resultTime.tm_hour * 3600 + resultTime.tm_min * 60 + resultTime.tm_sec + 1;
    currentTime -= timeInNowYear;
    if (localtime_r(&currentTime, &resultTime) == nullptr){
        throw std::runtime_error("Time conversion error...");
    }
    resultTime.tm_year += 1900;
    ++resultTime.tm_mon;
    return resultTime;
}

nlohmann::json TmToJson(tm date_time)
{
    
    nlohmann::json result;
    result["tm_year"] = date_time.tm_year;
    result["tm_mon"] = date_time.tm_mon;
    result["tm_mday"] = date_time.tm_mday;
    result["tm_hour"] = date_time.tm_hour;
    result["tm_min"] = date_time.tm_min;
    result["tm_sec"] = date_time.tm_sec;
    result["tm_wday"] = date_time.tm_wday;
    result["tm_yday"] = date_time.tm_yday;

    return result;
}
