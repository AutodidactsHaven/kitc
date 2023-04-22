# Contributors Guide

## Style Guide

### Naming Conventions

`object_new` indicates memory will be allocated internally by the function to
store the object based on the **new** in the function name. That memory should
be freed later with the respective `object_free`.

`system_init` indicates that the user will pass in storage for the object and
the function will initialise the struct members and internal state as denoted
by the **init** in the function name. Some systems/objects may require an accompanying
`system_shutdown`.
