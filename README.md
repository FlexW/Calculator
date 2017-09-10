# Calculator
A recursive math parser.

This is a calculator that I have written to understand how a parser works.
It's for learning purpose.

To build it, simple run the make script. Should be straightforward. I've tested only on Ubuntu.

```
cd ~
git clone https://github.com/FlexW/math-parser.git
cd math-parser
make
sudo make install
```

Calculator handels this operations (spaces and tab and new lines will be ignored):

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

    $ calc -i
    $ << 5 * 2
    $ >> 10

Or you can specify multiple expressions via a file (-f):

    $ calc -f my_excercises.txt

Note only one expression each line.

Also you can use it directly on command line type the operation (-d). Don't forget "".:
    
    $ calc -d "5 * 2"
    $ >> 10