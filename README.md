# example folio

Folios are a form of dynamically loaded shared libraries. Similar to
`dlopen` on Unix but instead of loading individual functions you load
the a collection of functions. Folios can contain both "user" and
"privilaged" (SWI) functions.

3DO did not advertise the existence Folios besides how to use the ones
they created. In early revisions of the official SDK you can find a
simple example showing how to build a folio but strictly for user
space functions. However, the example was incomplete and later
removed.

Using the [Portfolio OS
source](https://github.com/trapexit/portfolio_os) we have pieced
together how to build a proper Folio allowing for both user and SWI
functions. With SWI functions it is possible to interact with the
hardware directly.

As seen in the Makefile it is necessary to:
* Give the file the extension `.privfolio` if using privileged
  features.
* Sign with 3DO key.
* Set the executable's flags to 2 (to indicate it is to run privileged).
* Set the executable's folio subtype to 1 (KERNELNODE).
* Set the executable's node type to 4 (FOLIONODE).
* Set the executable's name to match that of the Folio name used in
  the code.


## Building

1. Get [3do-devkit](https://github.com/trapexit/3do-devkit)
2. `source 3do-devkit/activate-env`
3. `make`
4. `make install` will install the header and library into 3do-devkit
