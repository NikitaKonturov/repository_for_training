#include "Train.hpp"

/*======================================================*/
/*==================== Конструторы =====================*/
/*======================================================*/

Train::Train(size_t sTrainNumber, std::string sDestonation, double sDepartureTime, double sTravelTime, trainType sTypeOfTrain) : trainNumber(sTrainNumber), destination(sDestonation), typeOfTrain(sTypeOfTrain)
{
    if (sTrainNumber == 0) {
        throw std::invalid_argument("Train number must have natural number...");
    }
    if (sDepartureTime < 0.0 || sTravelTime < 0.0) {
        throw std::invalid_argument("Time must be unless 0.0...");
    }
    if (sDepartureTime > 23.59) {
        throw std::invalid_argument("Time must be less 23.59...");
    }
    if((sDepartureTime - static_cast<int>(sDepartureTime)) > 0.59) {
        throw std::invalid_argument("Munites must be less that 59...");
    }
    if((sTravelTime - static_cast<int>(sTravelTime)) > 0.59) {
        throw std::invalid_argument("Munites must be less that 59...");
    }
    this->travelTime = sTravelTime;
    this->departureTime = sDepartureTime;
}


/*======================================================*/
/*====================== Сетеры ========================*/
/*======================================================*/

void Train::setTrainNumber(size_t sTrainNumber)
{
    if (sTrainNumber == 0) {
        throw std::invalid_argument("Train number must have natural number...");
    }
    this->trainNumber = sTrainNumber;
}

void Train::setDestination(std::string sDestination)
{
    this->destination = sDestination;
}

void Train::setDepartureTime(double sDepartureTime)
{
    if (sDepartureTime < 0.0) {
        throw std::invalid_argument("Time must be unless 0.0");
    }
    if (sDepartureTime > 23.59) {
        throw std::invalid_argument("Time must be less 23.59");
    }
    if((sDepartureTime - static_cast<int>(sDepartureTime)) > 0.59) {
        throw std::invalid_argument("Munites must be less that 59");
    }

    this->departureTime = sDepartureTime;
}

void Train::setTravelTime(double sTravelTime)
{
    if (sTravelTime < 0.0) {
        throw std::invalid_argument("Time must be unless 0.0");
    }
    if((sTravelTime - static_cast<int>(sTravelTime)) > 0.59) {
        throw std::invalid_argument("Munites must be less that 59");
    }

    this->travelTime = sTravelTime;
}

void Train::setTupeOfTrain(trainType sTypeOfTrain) 
{
    this->typeOfTrain = sTypeOfTrain;
}


/*======================================================*/
/*====================== Гетеры ========================*/
/*======================================================*/


size_t Train::getTrainNumber() const 
{
    return this->trainNumber;
}

std::string Train::getDestination() const
{
    return this->destination;
}

double Train::getDepartureTime() const 
{
    return this->departureTime;
}

double Train::getTravelTime() const
{
    return this->travelTime;
}

trainType Train::getTypeOfTrain() const
{
    return this->typeOfTrain; 
}


/*======================================================*/
/*===================== Операторы ======================*/
/*======================================================*/

std::ostream& operator<<(std::ostream& out, const Train& source)
{
    out << "Номер поезда: "<< source.trainNumber << std::endl;
    out << "Пункт назначения: " << source.destination << std::endl;
    out << "Тип поезда: " << ((source.typeOfTrain == trainType::Passenger) ? "Passenger":"Express") << std::endl;
    out << "Время отправления: " << std::setprecision(4) << source.departureTime << std::endl;
    out << "Впемя в пути: " << std::setprecision(4) << source.travelTime << std::endl;
    return out;
}