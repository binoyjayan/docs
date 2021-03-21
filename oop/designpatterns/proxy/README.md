### Proxy design pattern

A class that functions as an interface to a partitcular resource.
That resource may be remote, expensive to construct, or may require
logging or some other added functionality.

A proxy is different from the decorator in the sense that the
decorator enhances the interface. Decorators typically aggregates
(or has reference to) what it is decorating; proxy doesn't have to.
Proxy might not be working with a materialized object.

