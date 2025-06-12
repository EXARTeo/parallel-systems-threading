Μπορείτε να εκτελέσσετε το πρόγραμμα μόλις το μεταγλωττίσετε με make ως εξής:
./main <thread_count> <priority> <insert_count> <total_operations> <percent_of_searches> <percent_of_inserts>

- thread_count: ο αριθμός των νημάτων
- priority: 1 αν δίνουμε προτεραιότητα στους writers, 0 στους readers
- insert_count: οι συνολικές εισαγωγές κλειδιών στη δομή μας
- total_operations: οι συνολικές λειτουργίες που θα εκτελεστούν (members, inserts, deletes)
- percent_of_searches: ποσοστό των αναζητήσεων (από 0 ως 1)
- percent_of_inserts: ποσοστό των εισαγωγών (από 0 ως 1)
(οι deletes αποτελούν το υπόλοιπο 1 - percent_of_searches - percent_of_inserts)

Στα αρχεία txt έχουμε εκτελέσει το πρόγραμμα με writer και reader priority αντίστοιχα. Παρατηρούμε πως όσο αυξάνεται το insert percentage, αυξάνεται και ο χρόνος. 