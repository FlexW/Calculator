# c-math-parser
A recursive math parser

This is a command-line math parser, that I have written to understand how a parser works.

Error handling is not to well and is not meant to be used in the real world. 
It's for learning purpose. 
Also note that the datatype double that I used is not precise enough for a real calculator.

However, you can improve it.

To build it simple run the make script. Should be straightforward. I've only tested on Linux but should also run on Windows.

Calculator handels this operations (spaces and tab will be ignored):

    Pi        Pi number
    e         Euler's number
    sqrt()    Square root
    cos()     Cosine 
    sin()     Sine 
    tan()     Tangent 
    lg()      Decimal logarithm
    ln()      Natural logarithm
    ()        Brackets
    ||        Absolute value
    !         Factorial
    -         Unary minus
    ^         Exponent
    mod()     Modulus divide 
    *, /      Multiply, Divide 
    +, -      Add, Subtract

Usage:

You can use it interactivly like this (-i):

    $ ./calc -i
    $ << 5 * 2
    $ >> 10

Or you can specify multiple expressions via a file (-f):

    $ ./calc -f my_excercises.txt

Note only one expression each line.

Also you can use it directly on command line type the operation (-d). Don't forget "".:
    
    $ ./calc -d "5 * 2"
    $ >> 10

