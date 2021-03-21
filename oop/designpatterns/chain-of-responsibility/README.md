### Chain of responsibility

A chain of components who all get a chance to process a command or a query,
optionally having default processing implementation and an ability to
terminate the processing chain.


CoR can be implemented as
 - A chain of pointers/references
 - Centralized list using a broker

Enlist objects in the chain, possibly controlling their order
Object removal from chain (e.g. disconnect from a signal)

