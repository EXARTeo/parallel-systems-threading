Με 4 νήματα, και 10^6, 10^7, 10^8, και 10^9, αντίστοιχα, συνολική "δουλειά" κάθε νήματος, έχουμε τα εξής: (σαν argument δίνονται ο αριθμός επαναλήψεων του ενός νήματος, και ο αριθμός των νημάτων)

$ ./main 1000000 4
====== Mutex-lock implementation ======
== Total sum from all threads : 4000000
== Time: 0.180433
=======================================

====== Atomic-lock implementation ======
== Total sum from all threads : 4000000
== Time: 0.125919
=======================================


$ ./main 10000000 4
====== Mutex-lock implementation ======
== Total sum from all threads : 40000000
== Time: 1.736922
=======================================

====== Atomic-lock implementation ======
== Total sum from all threads : 40000000
== Time: 1.250347
=======================================


$ ./main 100000000 4
====== Mutex-lock implementation ======
== Total sum from all threads : 400000000
== Time: 18.473605
=======================================

====== Atomic-lock implementation ======
== Total sum from all threads : 400000000
== Time: 12.392235
=======================================


$ ./main 1000000000 4
====== Mutex-lock implementation ======
== Total sum from all threads : 4000000000
== Time: 182.627960
=======================================

====== Atomic-lock implementation ======
== Total sum from all threads : 4000000000
== Time: 125.398085
=======================================


---


Με 12 νήματα, έχουμε:

$ ./main 1000000 12
====== Mutex-lock implementation ======
== Total sum from all threads : 12000000
== Time: 0.531257
=======================================

====== Atomic-lock implementation ======
== Total sum from all threads : 12000000
== Time: 0.370185
=======================================


$ ./main 10000000 12
====== Mutex-lock implementation ======
== Total sum from all threads : 120000000
== Time: 4.949773
=======================================

====== Atomic-lock implementation ======
== Total sum from all threads : 120000000
== Time: 3.760401
=======================================


$ ./main 100000000 12
====== Mutex-lock implementation ======
== Total sum from all threads : 1200000000
== Time: 52.426785
=======================================

====== Atomic-lock implementation ======
== Total sum from all threads : 1200000000
== Time: 37.864421
=======================================


./main 1000000000 12
====== Mutex-lock implementation ======
== Total sum from all threads : 12000000000
== Time: 562.683422
=======================================

====== Atomic-lock implementation ======
== Total sum from all threads : 12000000000
== Time: 383.330122
=======================================

Παρατηρούμε ότι όσο λιγότερα είναι τα νήματα, τόσο πιο γρήγορα τελειώνει το πρόγραμμα. Αυτό συμβαίνει γιατί υπάρχει λιγότερος ανταγωνισμός, κι άρα λιγότερες φορές θα εκτελεστούν συναρτήσεις που αποκλείουν το race condition (π.χ., η pthread_mutex_lock). Άρα λιγότερα νήματα θα περιμένουν για να αποκτήσουν πρόσβαση στην κοινόχρηστη μεταβλητή. 

Παρατηρούμε, επίσης, ότι το Atomic-lock implementation τελειώνει πιο γρήγορα από το Mutex-lock. Αυτό οφείλεται στο τρόπο υλοποίησης του Atomic lock.

Στο Atomic lock έχουμε τα εξής οφέλη:

- Δεν απαιτούνται system calls κι άρα έχει μειωμένο overhead.
- Όλες οι λειτουργίες εκτελούνται σε επίπεδο user space και hardware, κι άρα δεν έχουμε context switching.
- Οι atomic λειτουργίες εκτελούνται πιο αποτελεσματικά γιατί είναι single-cycle στις σύγχρονες αρχιτεκτονικές CPU.