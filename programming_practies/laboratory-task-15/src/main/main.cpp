
#include "../task-2/task-2.hpp"
#include "../task-3/task-3.hpp"
#include "../task-4/task-4.hpp"
#include "../task-5/task-5.hpp"
#include "../task-6/task-6.hpp"


int main()
{
    try {
 //   secondTask();
    thirdTask();
    fourthTask();
    std::string pathToTrains = "src/resource/Trains.txt";
    std::string pathToStudents = "src/resource/Student.txt";
    fiveTask(pathToStudents);
    sixTask(pathToTrains);
    }
    catch(std::runtime_error& err) {
        std::cerr << "Runtime error: " << err.what() << std::endl;
    }
    catch(std::invalid_argument& err) {
        std::cerr << "Invalid argument: " << err.what() << std::endl;
    }
    catch(std::ios_base::failure& err) {
        std::cerr << "Ios base failure: " << err.what() << std::endl;
    }
    catch(std::exception err) {
        std::cerr << "Any errors: " << err.what() << std::endl;
    }
    return 0;
}
