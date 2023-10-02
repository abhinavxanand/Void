#include <iostream>
#include <vector>

namespace IndianRailways {
    enum class SeatType { LOWER, UPPER, SIDE_LOWER, SIDE_UPPER };

    class Seat {
    public:
        Seat(int seatNumber) : seatNumber(seatNumber) {
            // Calculate the seat type (lower, upper, side lower, side upper) and compartment number
            compartmentNumber = (seatNumber - 1) / seatsPerCompartment + 1;
            int seatWithinCompartment = (seatNumber - 1) % seatsPerCompartment;

            switch (seatWithinCompartment) {
                case 0:
                    seatType = SeatType::LOWER;
                    break;
                case 1:
                    seatType = SeatType::UPPER;
                    break;
                case 2:
                    seatType = SeatType::SIDE_LOWER;
                    break;
                case 3:
                    seatType = SeatType::SIDE_UPPER;
                    break;
            }
        }

        SeatType getSeatType() const {
            return seatType;
        }

        int getSeatNumber() const {
            return seatNumber;
        }

    private:
        int seatNumber;
        int compartmentNumber;
        SeatType seatType;
        static const int seatsPerCompartment = 4;  // Updated to match the new numbering scheme
    };

    void listSeatsByType(const std::vector<Seat>& seats, SeatType targetSeatType) {
        std::cout << "Seat numbers of type '";
        switch (targetSeatType) {
            case SeatType::LOWER:
                std::cout << "Lower";
                break;
            case SeatType::UPPER:
                std::cout << "Upper";
                break;
            case SeatType::SIDE_LOWER:
                std::cout << "Side Lower";
                break;
            case SeatType::SIDE_UPPER:
                std::cout << "Side Upper";
                break;
        }
        std::cout << "':" << std::endl;

        for (const Seat& seat : seats) {
            if (seat.getSeatType() == targetSeatType) {
                std::cout << seat.getSeatNumber() << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    using namespace IndianRailways;

    std::vector<Seat> seats;
    for (int seatNumber = 1; seatNumber <= 52; ++seatNumber) {
        seats.push_back(Seat(seatNumber));
    }

    int choice;
    do {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. List Lower Berths" << std::endl;
        std::cout << "2. List Upper Berths" << std::endl;
        std::cout << "3. List Side Lower Berths" << std::endl;
        std::cout << "4. List Side Upper Berths" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                listSeatsByType(seats, SeatType::LOWER);
                break;
            case 2:
                listSeatsByType(seats, SeatType::UPPER);
                break;
            case 3:
                listSeatsByType(seats, SeatType::SIDE_LOWER);
                break;
            case 4:
                listSeatsByType(seats, SeatType::SIDE_UPPER);
                break;
            case 5:
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter a valid option (1-5)." << std::endl;
                break;
        }
    } while (choice != 5);

    return 0;
}
