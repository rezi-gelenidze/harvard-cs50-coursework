-- Keep a log of any SQL queries you execute as you solve the mystery.
-- All you know is that the theft took place on July 28, 2020 and that it took place on Chamberlin Street.
SELECT description FROM 'crime_scene_reports' WHERE street = 'Chamberlin Street' AND day = 28 AND month = 7;

-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses
-- who were present at the time — each of their interview transcripts mentions the courthouse.

SELECT name, transcript FROM 'interviews' WHERE day = 28 AND month = 7;

/*
    Ruth - Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse
 parking lot and drive away. If you have security footage from the courthouse parking lot, you might
 want to look for cars that left the parking lot in that time frame.

    Eugene - I don't know the thief's name, but it was someone I recognized. Earlier this morning,
 before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.

    Raymond - As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call,
 I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the
 person on the other end of the phone to purchase the flight ticket.
*/


-- interseted data of people whose are satisfying every detail that we know from witnesses

-- people who withdrawed money in this moment
SELECT * FROM people
	WHERE id IN
    	(SELECT person_id FROM 'bank_accounts'
         WHERE account_number IN
         	(SELECT account_number FROM 'atm_transactions'
             WHERE atm_location = 'Fifer Street' AND
   			 transaction_type = 'withdraw' AND day = 28 AND month = 7))
INTERSECT
-- people has earliest flight ticket from fiftyville next day
SELECT * FROM people
	WHERE passport_number IN
    	(SELECT passport_number FROM passengers
         	WHERE flight_id IN (SELECT id FROM flights WHERE month = 7 AND day = 29
    		AND origin_airport_id IN (SELECT id FROM airports WHERE city = 'Fiftyville') ORDER BY hour LIMIT 1))
INTERSECT
-- people who exited courthouse within 10 minutes from theft
SELECT * from people
	WHERE license_plate IN
    (SELECT license_plate FROM courthouse_security_logs WHERE activity = 'exit' AND day = 28 AND
     month = 7 AND hour = 10 AND minute <= 25)
INTERSECT
-- people who called on that day with duration less than 60
SELECT * from people Where phone_number in
	(SELECT caller FROM phone_calls WHERE duration < 60);

/* Thief:
   id   |  name  | phone_number   | passport_number | license_plate
 686048 | Ernest | (367) 555-5533 |    5773159633   |    94KL13X
*/



-- accomplice who received call from the thief
SELECT * FROM people WHERE phone_number IN
	(SELECT receiver FROM phone_calls WHERE caller = '(367) 555-5533' AND day = 28 AND month = 7 AND duration < 60)

/* accompice
   id   |   name   |  phone_number  | passport_number | license_plate
 864400 | Berthold | (375) 555-8161 |                 |    4V16VO0
*/