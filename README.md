# flight-seat-availability-checking-system
This project is a flight seat availability checking system built with C++, Oracle Database, and SQL.

# Purpose
The goal of this project is to create a menu-driven application that allows users to check, book, and cancel flight seats in real time. It uses C++ and connects to an Oracle Database via Oracle OCCI, which stands for Oracle C++ Call Interface.

This helps in:

1. Automating flight seat management.

2. Preventing overbooking with live seat availability updates.

3. Simulating a real-world airline booking system at a smaller scale.

# Features
1. Seat Availability Check → Retrieve available seats for a given flight.

2. Book a Seat → Reduce available seats by 1 when a seat is booked.

3. Cancel a Seat → Increase available seats by 1 when a booking is canceled.

4. Menu-Driven Interface → Console-based user interaction.

5. Oracle Database Integration → Real-time data handling using SQL queries.

6. Data Consistency → Prevents booking when no seats are available.

7. Scalable → Can be extended with GUI (Qt/JavaFX) or Web front-end (Flask/Node.js).

# Usage
Start the Oracle Database (XE or 19c/21c).

Create the flights table:
CREATE TABLE flights (
    flight_id INT PRIMARY KEY,
    flight_name VARCHAR2(50),
    available_seats INT
);

INSERT INTO flights VALUES (101, 'IndiGo - Delhi to Mumbai', 5);
INSERT INTO flights VALUES (102, 'Air India - Bangalore to Goa', 3);
INSERT INTO flights VALUES (103, 'SpiceJet - Pune to Jaipur', 0);

Compile the C++ code (with Oracle OCCI libraries).

Run the program:

1. Enter choice from menu (Check/Book/Cancel/Exit).

2. Provide flight_id.

3. See results in real-time.

# Customization

Add More Flight Data → Extend table with more flights.

Passenger Details → Add a new table passengers to track who booked which seat.

GUI → Use Qt/GTK+ to build a desktop app instead of console.

Web API → Wrap C++ logic with REST API and integrate with a website.


# Dependencies

1. C++ Compiler (g++, MSVC, etc.)

2. Oracle Database (Oracle XE 21c or Oracle 19c)

3. Oracle OCCI Libraries (comes with Oracle Instant Client / full DB)

      occi.h
      oci.h

5. SQL*Plus / Oracle SQL Developer (to manage database manually).

