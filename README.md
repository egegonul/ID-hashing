# Description

In this code a hash table for TC ID's is implemented with three hashing functions:

* **Folding**: The key is simply divided into sections that are 3 digits long, 
and these sections are added together. The final hash value is (sum mod 
N) where N is size of the hash table. For example, if key=15726349053
and N=100, we divide k into 4 sections: 157, 263, 490, 53. Sum of these 
sections is 963 and the hash value is 63 for this key.

* **Middle Squaring**: Take middle 3 digits of the key and square them. The 
final hash value is (sum mod N) where N is size of the hash table. For 
example, if key=15726349053 and N=100, the middle 3 digits is 634.
Square of 634 is 401,956 and the hash value is 56 for this key.

* **Truncation**: Delete the first 9 digits and use only the last 2 digits of the 
key. The final hash value is (sum mod N) where N is size of the hash 
table. For example, if key=15726349053 and N=100, the last two digits 
is 53 and the hash value is 53 for this key.

The menu driven user interface provides the following operations to be performed on the hash table:

   **1.** Initialize Hash Table

  **2.** Load T.C. ID Numbers from file

  **3.** Add new T.C. ID Number

  **4.** Delete a T.C. ID Number

  **5.** Search for a T.C. ID Number

  **6.** Print out Hash Table
