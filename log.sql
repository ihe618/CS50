-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Start with crime scene reports
SELECT id, description FROM crime_scene_reports WHERE year = 2020 AND month LIKE 7 AND day = 28 AND street LIKE "Chamberlin%"
--295 | Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. 
--Interviews were conducted today with three witnesses who were present at the time
--each of their interview transcripts mentions the courthouse.

-- Look up interview transcripts
SELECT * FROM interviews WHERE year = 2020 AND month = 7 AND day = 28
--161 | Ruth | 2020 | 7 | 28 | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. 
--If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
--162 | Eugene | 2020 | 7 | 28 | I don't know the thief's name, but it was someone I recognized. 
--Earlier this morning, before   arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
--163 | Raymond | 2020 | 7 | 28 | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. 
--In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. 
--The thief then asked the person on the other end of the phone to purchase the flight ticket.

--Look up names of individuals with license plates that exited courthouse near 10:15 to 10 minutes after
SELECT * FROM people 
    JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
    WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10
--id | name | phone_number | passport_number | license_plate
--221103 | Patrick | (725) 555-4692 | 2963008352 | 5P2BI95 | 10:16 exit
--243696 | Amber | (301) 555-4174 | 7526138472 | 6P58WS2 | 10:18 exit
--745650 | Sophia | (027) 555-1068 | 3642612721 | 13FNH73 | 10:14 entrance
--686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X | 10:18 exit
--396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ | 10:21 exit
--398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7 | 10:20 exit
--467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8 | 10:19 exit
--514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE | 10:23 exit
--560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55 | 10:23 exit


-- Look up names of people who used ATM at Fifer on 7/28/2020
SELECT name FROM people
   ...> JOIN bank_accounts ON people.id = person_id
   ...> JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
   ...> WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location LIKE "Fifer%" AND transaction_type = "withdraw"
--Ernest*
--Russell*
--Roy
--Bobby
--Elizabeth
--Danielle*
--Madison
--Victoria

-- Look up names of people who made calls of less than a minute on 7/28/2020
SELECT name FROM  people 
   ...> JOIN phone_calls ON people.phone_number = phone_calls.caller
   ...> WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60
name
--Roger
--Evelyn
--Ernest*
--Evelyn
--Madison
--Russell*
--Kimberly
--Bobby
--Victoria
--* indicates duplicate names from above
-- queried more information regarding caller number and receiver number
SELECT * FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60
--id | caller | receiver | year | month | day | duration
--221 | (130) 555-0289 | (996) 555-8899 | 2020 | 7 | 28 | 51
--224 | (499) 555-9472 | (892) 555-8872 | 2020 | 7 | 28 | 36
--233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45
--234 | (609) 555-5876 | (389) 555-5198 | 2020 | 7 | 28 | 60
--251 | (499) 555-9472 | (717) 555-1342 | 2020 | 7 | 28 | 50
--254 | (286) 555-6063 | (676) 555-6554 | 2020 | 7 | 28 | 43
--255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49
--261 | (031) 555-6622 | (910) 555-3251 | 2020 | 7 | 28 | 38
--279 | (826) 555-1652 | (066) 555-9701 | 2020 | 7 | 28 | 55
--281 | (338) 555-6650 | (704) 555-2131 | 2020 | 7 | 28 | 54


-- look up flights the next day on 7/29/2020 out of location
SELECT name, origin_airport_id, city, hour, minute FROM people
   ...> JOIN passengers ON people.passport_number = passengers.passport_number
   ...> JOIN flights ON passengers.flight_id = flights.id
   ...> JOIN airports ON flights.destination_airport_id = airports.id
   ...> WHERE year = 2020 AND month = 7 AND day = 29 

--look for earliest flights on results and * indicates duplicate names from above   
--name | origin_airport_id | city | hour | minute   
--Doris | 8 | London | 8 | 20
--Roger | 8 | London | 8 | 20
--Ernest* | 8 | London | 8 | 20
--Edward | 8 | London | 8 | 20
--Evelyn | 8 | London | 8 | 20
--Madison | 8 | London | 8 | 20
--Bobby | 8 | London | 8 | 20
--Danielle | 8 | London | 8 | 20
--Daniel | 8 | Chicago | 9 | 30
--Carol | 8 | Chicago | 9 | 30
--Rebecca | 8 | Chicago | 9 | 30
--Sophia | 8 | Chicago | 9 | 30
--Heather | 8 | Chicago | 9 | 30
--Marilyn | 8 | Chicago | 9 | 30

-- Ernest satisfied all requirements- look up his accomplice- who he called
SELECT name FROM people WHERE phone_number = "(375) 555-8161"

--name
--Berthold


    
