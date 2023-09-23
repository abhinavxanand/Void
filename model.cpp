#include <iostream>
#include <string>

class IndianTrainSeat {
public:
    IndianTrainSeat(int seatNumber) : seatNumber(seatNumber) {
        // Calculate the seat type (lower, upper, side lower, side upper) and compartment number
        compartmentNumber = (seatNumber - 1) / seatsPerCompartment + 1;
        int seatWithinCompartment = (seatNumber - 1) % seatsPerCompartment;
        
        if (seatWithinCompartment == 0) {
            seatType = "Lower";
        } else if (seatWithinCompartment == 1) {
            seatType = "Upper";
        } else if (seatWithinCompartment == 2) {
            seatType = "Side Lower";
        } else if (seatWithinCompartment == 3) {
            seatType = "Side Upper";
        }
    }

    void printSeatInfo() {
        std::cout << "Seat Number: " << seatNumber << std::endl;
        std::cout << "Compartment Number: " << compartmentNumber << std::endl;
        std::cout << "Seat Type: " << seatType << std::endl;
    }

private:
    int seatNumber;
    int compartmentNumber;
    std::string seatType;
    static const int seatsPerCompartment = 6;
};

int main() {
    int seatNumber;

    std::cout << "Enter seat number (1-52): ";
    std::cin >> seatNumber;

    if (seatNumber >= 1 && seatNumber <= 52) {
        IndianTrainSeat seat(seatNumber);
        seat.printSeatInfo();
    } else {
        std::cout << "Invalid seat number. Seat numbers range from 1 to 52." << std::endl;
    }

    return 0;
}