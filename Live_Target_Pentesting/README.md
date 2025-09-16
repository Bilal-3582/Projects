# Project 8 - Pentesting Live Targets

Time spent: 6 hours spent in total

> Objective: Identify vulnerabilities in three different versions of the Globitek website: blue, green, and red.

The six possible exploits are:
* Username Enumeration
* Insecure Direct Object Reference (IDOR)
* SQL Injection (SQLi)
* Cross-Site Scripting (XSS)
* Cross-Site Request Forgery (CSRF)
* Session Hijacking/Fixation

Each version of the site has been given two of the six vulnerabilities. (In other words, all six of the exploits should be assignable to one of the sites.)

## Blue

Vulnerability #1: SQL Injection (SQLi)

<img src="https://github.com/Tanvi20/Week-8-Project-Pentesting-Live-Targets/blob/master/Blue_SQLI.gif" width="800">

I clicked the salesperson info on pages (Red, Green and Blue target) and I see a format "?id=XX" in the url. I manipulated the url by adding a ' to the end of the url. While doing this, I see the red and green page simply redirect and the green page shows a SQL error message saying "Database query failed". 
This output gave away that blue page had SQL Injection vulnerability, as shown in the gif walkthrough which was discovered with a simple sleep command at the public/staff/salespeople/show.php?id=?? endpoint. The ?? was replaced with the following SQL syntax: ' OR SLEEP(5)=0--' which eventually becomes %27%20OR%20SLEEP(5)=0--%27 when encoded in the url. This extract forced the SQL query to pause for 5 seconds, thus indicating a successful SQL injection.

Vulnerability #2: Session Hijacking/Fixation

<img src="https://github.com/Tanvi20/Week-8-Project-Pentesting-Live-Targets/blob/master/Blue_Session%20Hijacking.gif" width="800">

For this vulnerability, I used Green Page's Session to Login to the Blue page that had the vulnerability. (Blue and Green pages were used as an example). In the Green Page, I logged in as an admin, and opened the following link that contained the tool to change the PHPSESSIONID- https://35.224.63.197/green/public/hacktools/change_session_id.php.

After getting the PHPSESSIONID from the Green Page I copied it and opened the same tool for the Blue Page- https://35.224.63.197/blue/public/hacktools/change_session_id.php. I, then entered the copied PHPSESSIONID of the Green Page to the Set a new PHPSESSIONID field (on blue page) and then clicked the change button.

PS- I was NOT logged in the Blue Website!!!
Now, by going to the following link: https://35.224.63.197/blue/public/index.php, I could see the administrator tools (eg: Users), without ever logging in to the Blue Page.


## Green

Vulnerability #1: Username Enumeration

<img src="https://github.com/Tanvi20/Week-8-Project-Pentesting-Live-Targets/blob/master/Green_Username%20Enumeration.gif" width="800">

To put this into simple words - The error message I got when a username exists in the database and log in was unsuccessful is BOLDED while it's not when the username does not exist in the databse. Also, using inspect helped. I figured out that the Developer assigned two different classes, "failed" and "failure", to the error message depending on the login attempt. The "failure" class has bold style in css while "failed" class doesn't have the same.

Vulnerability #2: Cross-Site Scripting (XSS)

<img src="https://github.com/Tanvi20/Week-8-Project-Pentesting-Live-Targets/blob/master/Green_Cross%20Site%20Scripting.gif" width="800">

A malicious attacker can inject an XSS in between the <script> tags in their feedback form of the "Contact Us" Page. Except the Green Page, other pages escaped the strings that the users can submit the feedback for.
Injected XSS Command:
<script>alert('Tanvi found the XSS, yayyy!');</script>. This XSS command runs once the admin goes to tyhe panel and checks the feedback page. This means, users can submit feedback that when accessed from the admin side, will eventually run code in a script tag!! 


## Red

Vulnerability #1: Insecure Direct Object Reference (IDOR)

<img src="https://github.com/Tanvi20/Week-8-Project-Pentesting-Live-Targets/blob/master/Red_IDOR.gif" width="800">

In this vulnerability, when I go to public's show salesperson page and change the query parameter ID to one that's not supposed to be visible, such as 10 and 11, it works and lets out the information that is not supposed to be publically available.
Thus, in the red Page, an IDOR vulnerability exists where in a user can see any account details that inclusing the ones that should be hidden. I used the public/salesperson.php?id=?? endpoint where ?? is the ID of the salesperson. 

In this example, I entered the ID 10 and ID 11. Thus, an attacker could simply guess ID numbers until they reach a hidden/deactivated account. Also, the blue and green page mitigate this act by simply redirecting the user back to the list of salespeople if a non-existent or deactivated ID is provided.

Vulnerability #2: Cross-Site Request Forgery (CSRF)

<img src="https://github.com/Tanvi20/Week-8-Project-Pentesting-Live-Targets/blob/master/Red_CSRF.gif" width="800">

The Red Page is vulnerable to CSRF. Using inspect helps! As per the GIF, I couldn't edit the username on Blue Page and got an error message "invalid request" when I tried to, because the the user didnot have permissions to update information in the database without a valid CSRF token. However, I could update the information in the database on the Red Page even without a valid CSRF token.

To mitigate this, the other sites (Blue and Green Page) are in fact validating the CSRF tokens on form submits and result in an invalid request error on submits with invalid tokens (as shown in the GIF).

## Notes

All the GIFs were created using LICEcap
