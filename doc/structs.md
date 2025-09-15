# C structs

In C programming language I actually can have something like classes using the `structs`:

```c

struct Point {
    x int;
    y int; 
}

```

we can acess the elements of the structs using `.` operator or if the struct has a pointer we use `->`

In C the order of the fields in structs actually metter because that we are telling actually to the computer is that we want to place the variables in the memory next to each other.
