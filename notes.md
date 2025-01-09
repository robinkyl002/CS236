Class Notes

- Join Slack
- Lab times will be available 2-3 times each week to allow you to meet with TAs and other students to work on labs
- Reading should be done by Friday (4 pages total)
-

Tokens

```

void quote () {

    print (

        "To err is human, but to really foul things up you need a computer." +
        " - Paul Ehrlich"

    );
}

```

- each character of void is a token
- quote function is token
- all parts of single string make single token

```
Schemes:
    childOf(X,Y)
    marriedTo(X,Y)
```

- operators such as :- or ++ are considered single token
- Schemes is single token
- ChildOf
- (
- X
- ,
- Y

**_Scanner (Lexical Analyzer)_**

- takes input (probably from text file) - figure out what makes up token
- output - tokens
- Project 1

**_Parser_**

- Input - tokens
- checks syntax (is sequence correct)
- Output - data structure (holds info about everything in program, i.e. functions, variables, etc.)
- Project 2

**_Interpreter_**

- Input - Data structure
- Output - result of executing code
- Project 3, 4, 5

```
class Token
    value(chars)
    Type (string, ID, ...)
    line #
```

```
Facts:
    childOf('Ned','Bea')
```

Scanner output:
value Facts - Facts - line 1
value : - colon - line 1
value childOf - identifier
value ( - left parenthesis - line 2
value Ned - string - line 2
