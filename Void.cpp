#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <set> //for tracking previous destinations

using namespace std;

class Seat {
public:
    Seat(int seatNumber) : seatNumber(seatNumber), occupied(false) {}

    int getSeatNumber() const {
        return seatNumber;
    }

    bool isOccupied() const {
        return occupied;
    }

    void occupy() {
        occupied = true;
    }

    void vacate() {
        occupied = false;
    }

private:
    int seatNumber;
    bool occupied;
};

class Train {
public:
    Train(int capacity) : capacity(capacity) {
        for (int i = 1; i <= capacity; ++i) {
            seats.push_back(Seat(i)); // Associate seat numbers with seat objects
        }
    }

    int getCapacity() const {
        return capacity;
    }

    const Seat& getSeat(int seatNumber) const {
        return seats[seatNumber - 1];
    }

    bool isAvailable(int numOfSeats) const {
        int contiguousEmptySeats = 0;
        for (const Seat& seat : seats) {
            if (!seat.isOccupied()) {
                contiguousEmptySeats++;
                if (contiguousEmptySeats == numOfSeats) {
                    return true;
                }
            } else {
                contiguousEmptySeats = 0;
            }
        }
        return false;
    }

    bool allocateSeats(int numOfSeats, vector<int>& allocatedSeats) {
        int contiguousEmptySeats = 0;
        for (int i = 0; i < capacity; ++i) {
            if (!seats[i].isOccupied()) {
                contiguousEmptySeats++;
                allocatedSeats.push_back(seats[i].getSeatNumber());
                //allocatedSeats.push_back(i+1);
                if (contiguousEmptySeats == numOfSeats) {
                    // Allocate contiguous seats
                    for (int seatNumber : allocatedSeats) {
                        seats[seatNumber - 1].occupy();
                    }
                    return true;
                }
            } else {
                contiguousEmptySeats = 0;
                allocatedSeats.clear();
            }
        }
        return false; // No contiguous seats available
    }

    void deallocateSeatsTill(int preSeats , int vacantSizeTill) {
        for (int i = preSeats; i < vacantSizeTill; ++i) {
            seats[i].vacate();
        }
    }

private:
    int capacity;
    vector<Seat> seats;
};

class Route {
public:
    Route(string source, string destination, vector<string> stations)
        : source(source), destination(destination), stations(stations) {}

    string getSource() const {
        return source;
    }

    string getDestination() const {
        return destination;
    }

    const vector<string>& getStations() const {
        return stations;
    }

private:
    string source;
    string destination;
    vector<string> stations;
};

int main() {
    
    Train train(72); 

    vector<string> stations = {"Jabalpur", "Damoh", "Sagar", "Bhopal", "Indore"};
    string source, destination;
    vector<string> previousDestinations; // Keep track of previous destinations
    vector<int> previousGroupsize; //Last entered groupsize k liye
    cout << "List of stations:" << endl;
    for (int i = 0; i < stations.size(); ++i) {
        cout << i + 1 << ". " << stations[i] << endl;
    }

    while (true) {
        int sourceIndex, destinationIndex;
        cout << "Enter source station (1-" << stations.size() << ") or 0 to exit: ";
        cin >> sourceIndex;

        if (sourceIndex == 0) {
            cout<<"Humhara Application use karne k liye dhanyawaad!"<<endl;
            cout<<"Team Void"<<endl;
            break; // Exit the loop if 0 is entered as the source station
        }

        // if (sourceIndex < 1 || sourceIndex > stations.size()) {
        //     cout << "Invalid source station index. Please enter a valid index." << endl;
        //     continue; // Go back to the beginning of the loop
        // }

        cout << "Enter destination station (1-" << stations.size() << "): ";
        cin >> destinationIndex;

        // if (destinationIndex < 1 || destinationIndex > stations.size()) {
        //     cout << "Invalid destination station index. Please enter a valid index." << endl;
        //     continue; // Go back to the beginning of the loop
        // }

        source = stations[sourceIndex - 1];
        destination = stations[destinationIndex - 1];


        int groupSize;
        cout << "Enter your group size: ";
        cin >> groupSize;

        vector<int> allocatedSeats;

        if (groupSize <= 0 || groupSize > train.getCapacity()) {
            cout << "Invalid group size. Please enter a valid group size." << endl;
            continue; // Go back to the beginning of the loop
        }

        Route route(source, destination, stations);
        cout << "Selected route: " << route.getSource() << " to " << route.getDestination() << endl;
        
        if (find(previousDestinations.begin(), previousDestinations.end(), source) != previousDestinations.end()) {
            
            vector<string>::iterator it;

            it = find(previousDestinations.begin(), previousDestinations.end(), source);
            int index = it - previousDestinations.begin();
            cout <<" " <<previousGroupsize[index]<<" seats were vacated at "<< source << endl;
            
            int preSeats=0;
            for(int i=0; i<index; i++)
                preSeats += previousGroupsize[i];
            
            int vacantSizeTill = preSeats + previousGroupsize[index];
            train.deallocateSeatsTill(preSeats , vacantSizeTill); // Deallocate seats 
            previousDestinations[index]= destination; // Will update the destination to current one
        }

        previousGroupsize.push_back(groupSize);
        
        if (train.isAvailable(groupSize)) {
            if (train.allocateSeats(groupSize, allocatedSeats)) {
                cout << "Seats allocated successfully: ";
                sort(allocatedSeats.begin(), allocatedSeats.end());
                for (int seatNumber : allocatedSeats) {
                    cout << seatNumber << " ";
                }
                cout << endl<<endl;;
                previousDestinations.push_back(destination); // Add destination to previous destinations
            } else {
                cout << "Failed to allocate contiguous seats for your group." << endl;
            }
        } else {
            cout << "Not enough contiguous seats available for your group." << endl;
        }
    }

    return 0;
}
