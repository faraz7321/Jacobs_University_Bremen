This is a collection of sample programs that has grown over the
years. There is a toplevel cmake setup and hence to compile all
programs, you can do:

$ mkdir build
$ cd build
$ cmake ..
$ make

You can do the same in each of the program directories if you
are only interested in specific sample programs.

* airplanes

  Airplanes approaching a runway and then taxiing to the gates.
  Solution using pthreads and semaphores.

* bounded

  Implementation of a solution for the bounded buffer (producer /
  consumer) problem using pthreads and condition variables. There is
  also a bounded buffer implementation in go and java.

* bridge

  An old bridge which crosses a river from east to west. Since it is a
  small bridge, cars can only go in one direction at a time and no
  more than 3 cars are allowed on the bridge. Solution using pthreads
  and condition variables.
  
* cat

  An implementation of cat emulating the POSIX cat as close as
  possible. The implementation uses memory mapped I/O on regular
  files.

* cat++

  An implementation of cat supporting dynamically loadable
  transformations.

* cookie-break

  Simulates what happens during an IETF cookie break.

* cooking

  Students meet to cook together. Some are lazy but later they have to
  cleanup the kitchen. Shows the usage of pthread barriers. There is
  also an implementation in go.

* datehack

  A demonstration how to intercept library calls at dynamic link time.

* daytime

  Simple TCP and UDP clients retrieving the current date and time from
  a daytime server.

* daytimed

  Simple TCP, UDP and joint TCP/UDP servers providing access to the
  current date and time.

* echo

  Implementations of the echo utility (sequential, concurrent
  processes, and concurrent threats).

* expect

  A simplified implementation of expect in plain C. It demonstrates
  the usage of ptys to automate applications running on a tty.

* finger

  A simple finger client utilizing the finger protocol over TCP.

* ftpd

  A simple FTP (RFC 959) server.

* gsh

  A very simple but working minimal shell implemented using the glib
  API.

* happy

  Do a happy eyeballs inspired concurrent non-blocking connects to
  various endpoints identified on the command line and report how
  fast the connection was established.

* hello

  Several versions of a hello world program using buffered stream I/O
  (puts(3)) system call wrapper functions (write(2)), or manually
  invoking a system using the syscall(2) wrapper. There are also
  versions that use glib and glib's event and thread APIs.

* inetd

  Implementation of the core of an inetd. See the assignment sheet #6
  from the Spring 2011 OS course for the description.

* kernel

  Linux kernel specific code (usually in the form of loadable kernel
  modules).

* lm

  Implementation of a simple license manager server (lmd) and a
  license manager client (lmc).

* ls

  Implementation of a subset of the good old ls program.

* mcp

  A program copying regular files using memory mappings.

* memory

  A program demonstrating various a collection of memory related
  programming errors. Commands line arguments can be used to trigger a
  certain sequence of memory related programming errors.

* memstress

  A program initializing a large array in row-by-row and
  column-by-column order. This is commonly used as an example that
  locality (row-by-row) improves efficiency, for example, by causing
  less page faults. Well, on most systems, it does _not_ show this but
  instead it shows that CPU caching looses efficiency if you go
  column-by-column order. Overall a great example why naive
  measurements may be totally misleading.

* msh

  A very simple but working minimal shell.

* msh2

  A somewhat advanced version of a minimal shell.

* nanomsg

  A collection of examples demonstrating the nanomsg communication
  library.

* parallel

  A very simple implementation of the GNU parallel program.

* pee

  This program demonstrates the usage of pipes by implementing a piped
  version of tee (hence the name pee).

* pets

  Solution for the cats and mice synchronization problem using
  pthreads and condition variables.

* philosophers

  Solution of the dining philosophers problem.

* pipe

  This program demonstrates the usage of pipes. It displays texts read
  from stdin either by writing it directly to stdout if it contains
  only a few lines or by piping the text through a pager.
  
* popen

  Implementation of popen(3) and pclose(3) functions. This version
  keeps information about forked processes, but it is not thread safe.
  
* pthread

  Several simple programs demonstrating the pthread API. Includes a
  simple program to start threads and processes which allows to
  compare execution costs of thread and process creation.

* race

  A simple program demonstrating data race conditions. Note that it is
  system specific how frequently race conditions occur.

* rad

  Implementation of the Ricart-Agrawala distributed synchronization
  algorithm. See Operating Systems 2015 homework sheet #5.

* semaphore

  Implementation of counting semaphores on top of pthread mutexes and
  condition variables. For an explanation, see A.B. Downey: "The
  Little Book of Semaphores".

* semutil

  A simple wrapper around the POSIX semaphore API for named
  semaphores. It allows to create (-c) or open (-o) a named semaphore
  and to read its value (-v), to post it (-p), or to wait for it
  (-w). The unlink option (-u) removes the name of the named semaphore
  and hence no other process can open it anymore. The name of the
  semaphore can be specified with the -n option (it defaults to the
  program name).
  
* sleep

  This little example demonstrates how to use the POSIX signal
  functions to wait reliably for a signal.

* smokers

  Implementation of the cigarette smokers synchronization problem
  using pthreads and condition variables.

* snake

  Implementation of the classic snake terminal game. Demonstrates the
  usage of curses (or ncurses).

* syncbox

  Using the Linux inotify API, detect changes in a src directory and
  synchronize the src directory to a dst directory using rsync.

* unisex

  Solution for the unisex bathroom problem using pthreads, mutex locks
  and condition variables.

* wc

  A simple program to count words in files concurrently. For each
  file, a separate thread is created to count the words. The solution
  uses pthreads.

* worker

  A simple program demonstrating the "thread pool pattern". The
  dispatching thread reads numbers from stdin and places them into a
  queue processed by a fixed number of worker threads.  Once the end
  of the input has been reached, the worker threads exit when the
  queue becomes empty. The queue is implemented using a fixed size
  bounded buffer.
