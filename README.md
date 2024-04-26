![image](https://github.com/arokua/assignment-2-cosc1076/assets/57876746/df549dd8-3ca6-49a0-93c0-657ee4c98bd7)Repository for RMIT course Advanced Programming techinques Food Vendor assginment.

This will have an implementation of a list of food items as a linked list, where each foods is fundamentally a Node with some extra data.

Right now the linked list is implemented with a basic Node containing only an integer data type and a pointer to a next node.

A modified change making algorithm using dynamic programming to store the best possible coin set and print it out, if such a set is possible.

To run, type ```make``` in the terminal, should tests file be valid, then make test to run.

Update 26 April 2024: No validation has been done, and thus no tests is created yet.

To test linked list implentation, please enter input in the following syntax:
```n1 n2 n3 n4 ... n Q arg1 arg2``` where n1 to n are positive integers, Q is the query to insert, delete, get item or search.
Valid Q commands: "AF","AE", "AP" for add front, add end and add at position
  For add front and add end, arg1 is the integer value of the node to be add
  For add at position, arg2 is the integer value of the position to add arg1 to, 1-indexed
Delete queries are : "DF", "DE", "DP" for Delete front, delete node at end, delete node at a position
Search query (S) will print out the position of the node with data equal to arg1, get query (GI) will print out the value of index at arg1 , the indexes here are also 1-indexed.
Example:
![image](https://github.com/arokua/assignment-2-cosc1076/assets/57876746/01c5f0de-d90b-4225-b77a-e729b094be23)
After the linked list run is complete, the program will print out a list of change making values to give an example of the result of the change making algorithm

