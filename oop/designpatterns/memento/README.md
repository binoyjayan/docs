### Memento design pattern

A memento is a token/handle representing the system state.
It lets us rollback to the state when the token was generated.
It may or may not directly expose the state information.

An object or system goes through changes
 - E.g. a bank account
One way is to record every change (command)
Another is to simply have snapshots of the system

#### Summary
 - Mementos are used to rollback states arbitrarily
 - A memento is simply a token/handle class with (typically)
 no functioons of its own
 - A memento is not required to expose directly the state(s)
   to which it reverts the system.
 - It can also be used to implement undo/redo


