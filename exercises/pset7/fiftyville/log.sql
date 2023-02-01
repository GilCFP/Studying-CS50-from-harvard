-- Keep a log of any SQL queries you execute as you solve the mystery.
/*  .table
        airports                  crime_scene_reports       people
        atm_transactions          flights                   phone_calls
        bank_accounts             interviews
        courthouse_security_logs  passengers
);*/
SELECT description FROM crime_scene_reports WHERE(month = 7 AND day = 28 AND street like "Chamberlin Street%");
/*
Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.
*/
SELECT transcript FROM interviews WHERE(year = 2020 AND month = 7 AND day = 28 AND transcript LIKE "%courthouse%");
/*+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
|                                                                                                                                                       transcript                                                                                                                                                        |
+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.                                                      |

| I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.                                                                                                      |

| As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/
SELECT license_plate, activity, hour, minute FROM courthouse_security_logs WHERE(year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25);
/*
+---------------+----------+------+--------+
| license_plate | activity | hour | minute |
+---------------+----------+------+--------+
| 5P2BI95       | exit     | 10   | 16     |
| 94KL13X       | exit     | 10   | 18     |
| 6P58WS2       | exit     | 10   | 18     |
| 4328GD8       | exit     | 10   | 19     |
| G412CB7       | exit     | 10   | 20     |
| L93JTIZ       | exit     | 10   | 21     |
| 322W7JE       | exit     | 10   | 23     |
| 0NTHK55       | exit     | 10   | 23     |
+---------------+----------+------+--------+
*/
SELECT account_number, amount FROM atm_transactions WHERE(atm_location ="Fifer Street" AND year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw");
/*
+----------------+--------+
| account_number | amount |
+----------------+--------+
| 28500762       | 48     |
| 28296815       | 20     |
| 76054385       | 60     |
| 49610011       | 50     |
| 16153065       | 80     |
| 25506511       | 20     |
| 81061156       | 30     |
| 26013199       | 35     |
+----------------+--------+
*/
SELECT caller, receiver FROM phone_calls WHERE(duration < 60 AND year = 2020 AND month = 7 AND day = 28);
/*
+----------------+----------------+
|     caller     |    receiver    |
+----------------+----------------+
| (130) 555-0289 | (996) 555-8899 |
| (499) 555-9472 | (892) 555-8872 |
| (367) 555-5533 | (375) 555-8161 |
| (499) 555-9472 | (717) 555-1342 |
| (286) 555-6063 | (676) 555-6554 |
| (770) 555-1861 | (725) 555-3243 |
| (031) 555-6622 | (910) 555-3251 |
| (826) 555-1652 | (066) 555-9701 |
| (338) 555-6650 | (704) 555-2131 |
+----------------+----------------+
*/
SELECT id, full_name FROM airports WHERE full_name LIKE "fiftyville%"
/*
+----+-----------------------------+
| id |          full_name          |
+----+-----------------------------+
| 8  | Fiftyville Regional Airport |
+----+-----------------------------+
*/
SELECT id, origin_airport_id, destination_airport_id, hour, minute FROM flights WHERE(origin_airport_id = 8 AND year = 2020 AND month = 7 AND day = 29) ORDER BY hour, minute LIMIT 5;
/*
+----+-------------------+------------------------+------+--------+
| id | origin_airport_id | destination_airport_id | hour | minute |
+----+-------------------+------------------------+------+--------+
| 36 | 8                 | 4                      | 8    | 20     |
+----+-------------------+------------------------+------+--------+
*/
SELECT passport_number FROM passengers WHERE flight_id = 36;
/*
+-----------------+
| passport_number |
+-----------------+
| 7214083635      |
| 1695452385      |
| 5773159633      |
| 1540955065      |
| 8294398571      |
| 1988161715      |
| 9878712108      |
| 8496433585      |
+-----------------+
*/
SELECT name,id FROM people WHERE(
license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE(year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25))
AND
phone_number IN(SELECT caller FROM phone_calls WHERE(duration < 60 AND year = 2020 AND month = 7 AND day = 28))
AND passport_number IN(SELECT passport_number FROM passengers WHERE flight_id = 36))
/*
+--------+--------+
|  name  |   id   |
+--------+--------+
| Roger  | 398010 |
| Evelyn | 560886 |
| Ernest | 686048 |
+--------+--------+
*/
SELECT person_id FROM bank_accounts WHERE (person_id IN
(SELECT id FROM people WHERE(
license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE(year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25))
AND phone_number IN(SELECT caller FROM phone_calls WHERE(duration < 60 AND year = 2020 AND month = 7 AND day = 28))
AND passport_number IN(SELECT passport_number FROM passengers WHERE flight_id = 36)))
AND account_number IN(SELECT account_number FROM atm_transactions WHERE(atm_location ="Fifer Street" AND year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw")));
/*
+-----------+
| person_id |
+-----------+
| 686048    |
+-----------+
By having this id i can afirm that the thief is Ernest
*/
SELECT city FROM airports WHERE id = 4;
/*
+--------+
|  city  |
+--------+
| London |
+--------+
*/
SELECT name FROM people WHERE phone_number in (SELECT receiver FROM phone_calls WHERE
(caller in (SELECT phone_number FROM people WHERE id = 686048))
AND duration < 60
AND year = 2020
AND month = 7
AND day = 28);
/*
+----------+
|   name   |
+----------+
| Berthold |
+----------+
*/