### Observer design pattern

Getting notification when things happen.

An observer is an object that wishes to be informed about
events happening in the system. The entity generating the
events is the observable.

#### Motivation

 - Need for certain components to be informed when certain things happen
 - Listen to events and get notified of, when these events occur
 - Terminology
   - event and subscriber
 
#### Summary

Two participant
 - Observable provides a way of subscribing to an event (signal)
 - Observer performs the subscription
Pbservable implementation is always intrusive (observer doesn't need to)
Multithreaded/reentrant use can cause issues
Ready-made implementations of Observer are available



