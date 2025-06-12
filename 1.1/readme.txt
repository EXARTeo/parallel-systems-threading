Στον παράλληλο αλγόριθμο χρειάζεται να χρησιμοποιήσουμε συγχρονισμό, γιατί αλλιώς θα έχουμε race condition μεταξύ των threads για την global μεταβλητή sum που αυξάνουμε κατά circle_arrows κάθε φορά. Για να λύσουμε το πρόβλημα, χρησιμοποιούμε mutex. 

Ακολουθούν ενδεικτικές εκτελέσεις.

Με 4 νήματα, και 10^7, 10^8, 10^9 συνολικές ρίψεις αντίστοιχα:

$ ./main 10000000 4
pi estimation (ordinal algorithm): 3.140498
Time: 0.260750
pi estimation (parallel algorithm): 3.140960
Time: 0.078049

$ ./main 100000000 4
pi estimation (ordinal algorithm): 3.141612
Time: 2.527907
pi estimation (parallel algorithm): 3.142323
Time: 0.715520

$ ./main 1000000000 4
pi estimation (ordinal algorithm): 3.141650
Time: 25.222815
pi estimation (parallel algorithm): 3.141662
Time: 6.961643

Όπως μπορούμε να παρατηρήσουμε, ο παράλληλος αλγόριθμος είναι πάντα πιο γρήγορος από τον σειριακό, αλλά όχι απαιραίτητα πιο ακριβής.

Με 12 νήματα, και 10^7, 10^8, 10^9 συνολικές ρίψεις αντίστοιχα:

$ ./main 10000000 12
pi estimation (ordinal algorithm): 3.140498
Time: 0.260848
pi estimation (parallel algorithm): 3.138150
Time: 0.073871

$ ./main 100000000 12
pi estimation (ordinal algorithm): 3.141612
Time: 2.527637
pi estimation (parallel algorithm): 3.141800
Time: 0.687010

$ ./main 1000000000 12
pi estimation (ordinal algorithm): 3.141650
Time: 25.260570
pi estimation (parallel algorithm): 3.141770
Time: 6.898193

Επαληθεύεται ο προηγούμενος ισχυρισμός μας και με 12 νήματα. Παρατηρούμε ότι ενώ τα νήματα τριπλασιάστηκαν, γλυτώσαμε κάτι λιγότερο από το μισό χρόνο.