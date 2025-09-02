#include <occi.h>
#include <iostream>
#include <string>
using namespace oracle::occi;
using namespace std;

class FlightBookingSystem {
private:
    Environment *env;
    Connection *conn;

public:
    // Constructor to establish a connection with the Oracle database
    FlightBookingSystem(string user, string pass, string db) {
        env = Environment::createEnvironment(Environment::DEFAULT);
        conn = env->createConnection(user, pass, db);
        cout << "✅ Connected to Oracle Database successfully!\n";
    }

    // Destructor to close the Oracle database connection
    ~FlightBookingSystem() {
        conn->commit(); // Ensure pending transactions are saved
        env->terminateConnection(conn);
        Environment::terminateEnvironment(env);
        cout << "❎ Disconnected from Oracle Database.\n";
    }

    // Function to check seat availability for a given flight
    bool checkSeatAvailability(int flightID) {
        string query = "SELECT available_seats FROM flights WHERE flight_id = :1";
        Statement *stmt = conn->createStatement(query);
        stmt->setInt(1, flightID);
        ResultSet *rs = stmt->executeQuery();

        bool result = false;
        if (rs->next()) {
            int availableSeats = rs->getInt(1);
            result = (availableSeats > 0);
        }

        conn->terminateStatement(stmt);
        return result;
    }

    // Function to book a seat for a given flight
    bool bookSeat(int flightID) {
        if (checkSeatAvailability(flightID)) {
            string updateQuery = "UPDATE flights SET available_seats = available_seats - 1 WHERE flight_id = :1 AND available_seats > 0";
            Statement *stmt = conn->createStatement(updateQuery);
            stmt->setInt(1, flightID);
            int rowsUpdated = stmt->executeUpdate();
            conn->commit();  // 🔥 Commit transaction
            conn->terminateStatement(stmt);
            return rowsUpdated > 0;
        }
        return false;
    }

    // Function to cancel a booked seat for a given flight
    bool cancelSeat(int flightID) {
        string updateQuery = "UPDATE flights SET available_seats = available_seats + 1 WHERE flight_id = :1";
        Statement *stmt = conn->createStatement(updateQuery);
        stmt->setInt(1, flightID);
        int rowsUpdated = stmt->executeUpdate();
        conn->commit();  // 🔥 Commit transaction
        conn->terminateStatement(stmt);
        return rowsUpdated > 0;
    }
};

// Function to display the menu for user interaction
void displayMenu() {
    cout << "\n===== Flight Booking System =====\n";
    cout << "1. Check Seat Availability\n";
    cout << "2. Book a Seat\n";
    cout << "3. Cancel a Seat\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    // Database credentials (replace with actual Oracle DB credentials)
    string user = "system";        // Your Oracle DB username
    string pass = "diviya";        // Your Oracle DB password
    string db   = "localhost:1521/XE";  // Service name or TNS (not "HR")

    try {
        FlightBookingSystem system(user, pass, db);

        int choice, flightID;
        while (true) {
            displayMenu();
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter flight ID to check availability: ";
                    cin >> flightID;
                    if (system.checkSeatAvailability(flightID)) {
                        cout << "✅ Seats are available for flight ID " << flightID << ".\n";
                    } else {
                        cout << "❌ No seats available for flight ID " << flightID << ".\n";
                    }
                    break;

                case 2:
                    cout << "Enter flight ID to book a seat: ";
                    cin >> flightID;
                    if (system.bookSeat(flightID)) {
                        cout << "✅ Seat successfully booked for flight ID " << flightID << ".\n";
                    } else {
                        cout << "❌ Failed to book seat. Maybe no seats are available.\n";
                    }
                    break;

                case 3:
                    cout << "Enter flight ID to cancel a seat: ";
                    cin >> flightID;
                    if (system.cancelSeat(flightID)) {
                        cout << "✅ Seat successfully canceled for flight ID " << flightID << ".\n";
                    } else {
                        cout << "❌ Failed to cancel seat.\n";
                    }
                    break;

                case 4:
                    cout << "Exiting the system...\n";
                    return 0;

                default:
                    cout << "⚠️ Invalid choice! Please try again.\n";
            }
        }
    }
    catch (SQLException &ex) {
        cerr << "💥 Oracle Error: " << ex.getMessage() << endl;
        return 1;
    }
}