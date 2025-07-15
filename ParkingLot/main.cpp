#include <bits/stdc++.h>
using namespace std;

enum VehicleType {
    motorcycle,
    compact,
    large,
    xlarge
};

class Vehicle {
public:
    string licensePlate;
    VehicleType type;

    Vehicle(const string& lp, const VehicleType type): licensePlate(lp), type(type) {}
};

int main() {
    return 0;
}



/*
 * ENTITIES:
 *
 * Vehicles
 * Tickets
 * Spots
 * ParkingManager
 * PaymentManager
 */

/*
 * Vehicle {
 *  license_plate_no
 *  type
 * }
 */

/*
 * ParkingSpot {
 *  type
 *  id
 *  }
 */

/*
 * Level {
 *  List<ParkingSpot*>
 * }
 */


/*
 * Ticket {
 *  double rate
 *  ParkingSpot* spot
 *  int entry_time
 *  int exit_time
 *  }
 */

