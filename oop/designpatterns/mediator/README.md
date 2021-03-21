### Mediator design pattern

A mediiator is a component that facilitates communication between components
without them necessarily being aware of each other or having direct references
to each other.

#### Motivation

Components may go in and out of a system at any time
 - Chat room participants
 - Players in an MMORPG

It does not make sense for them to have references to one another

Solution:
Have them refer to some central component that facilitates communication

#### Summary

 - Create the mediator and have each object in the system refer to it
 - Mediator engages in bidi communication with its connected components
 - Mediator has functions the components can call
 - Components have functions the mediator can call
 - Event processing (e.g. Rx) libraries make communication easier to implement

