#ifndef TRAIN_HPP
#define TRAIN_HPP
#include <iostream>
#include <iomanip>

enum class trainType {
    Passenger,
    Express
};

class Train {
private:
size_t trainNumber;
std::string destination;
trainType typeOfTrain;
double departureTime;
double travelTime;
public:
    Train(size_t = 1, std::string = "", double = 0.0, double = 0.0, trainType = trainType::Passenger);
    ~Train() = default;

    void setTrainNumber(size_t);
    void setDestination(std::string);
    void setDepartureTime(double);
    void setTravelTime(double);
    void setTupeOfTrain(trainType);

    size_t getTrainNumber() const;
    std::string getDestination() const;
    double getDepartureTime() const;
    double getTravelTime() const;
    trainType getTypeOfTrain() const;

    friend std::ostream& operator<<(std::ostream&, const Train&);

};


#endif //TRAIN_HPP
