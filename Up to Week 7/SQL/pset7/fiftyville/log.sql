-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT * FROM crime_scene_reports WHERE year = 2024 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time –
-- each of their interview transcripts mentions the bakery.

SELECT * FROM interviews WHERE year = 2024 AND month = 7 AND day = 28;
-- 161 | Ruth    | 2024 | 7     | 28  |
-- Sometime within ten minutes of the theft,
--  I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot,
-- you might want to look for cars that left the parking lot in that time frame.

-- | 162 | Eugene  | 2024 | 7     | 28  |
-- I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- | 163 | Raymond | 2024 | 7     | 28  |
-- As the thief was leaving the bakery,
-- they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket. |

SELECT * FROM bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25;
SELECT * FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
SELECT caller FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60;
SELECT * FROM airports;
-- | 8  | CSF          | Fiftyville Regional Airport             | Fiftyville    |
SELECT id FROM flights WHERE year = 2024 AND month = 7 AND day = 29 AND origin_airport_id = 8;
SELECT * FROM people WHERE phone_number in (SELECT caller FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60) AND license_plate in (SELECT license_plate FROM bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10);
+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 398010 | Sofia  | (130) 555-0289 | 1695452385      | G412CB7       |
| 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       |
| 514354 | Diana  | (770) 555-1861 | 3592750733      | 322W7JE       |
| 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+--------+----------------+-----------------+---------------+
SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw');
SELECT passport_number FROM people WHERE phone_number in (SELECT caller FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60) AND license_plate in (SELECT license_plate FROM bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 and 25) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'));
SELECT * FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2024 AND month = 7 AND day = 29 AND origin_airport_id = 8) AND passport_number IN (SELECT passport_number FROM people WHERE phone_number in (SELECT caller FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60) AND license_plate in (SELECT license_plate FROM bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw')));
+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 18        | 3592750733      | 4C   |
| 36        | 5773159633      | 4A   |
+-----------+-----------------+------+
-- 18 can skip as earliest flight is 36
SELECT name FROM people WHERE passport_number IS 5773159633;
-- Bruce is the Thief
SELECT name FROM people WHERE phone_number IS (SELECT receiver FROM phone_calls WHERE caller IS (SELECT phone_number FROM people WHERE passport_number IS 5773159633) AND year = 2024 AND month = 7 AND day = 28 AND duration < 60);
-- Robin is the Accomplice
SELECT city FROM airports WHERE id IS (SELECT destination_airport_id FROM flights WHERE id = 36);
-- New York City is where the thief went to



