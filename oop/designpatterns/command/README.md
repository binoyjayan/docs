### Command design pattern

An object which represents an instruction to perform a particular action.
Contains all the information necessary for the action to be taken.

 - Encapsulate all the details of an operation in a separate object
 - Define instruction for applying the command
 - Optionally define instructions for rollback
 - Create composite commands such as macros

#### Motivation

Ordinary c++ statements are perishable
 - Cannot undo a field/propery assignment
 - Cannot directly serialize a sequence of actions (calls)

Want an object that represents an operation
 - X should change its field Y to the value of Z
 - X should do W()

Uses: GUI commands, multilevel undo/redo, macro recording etc

#### Command and query seperation

Command = asking for an action or change (e.g. please set attack value to 2)
Query = asking for information (e.g. please give your attack value)
CQS = having separate means of sending commands and queries
GOF - In GOF context, commands and queries are represented with the common
      Command design pattern.



