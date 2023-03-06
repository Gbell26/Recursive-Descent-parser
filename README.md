A recursive descent parser that takes an input and determines whether it is a valid expression according to the following grammar rules:
        \<expr> ::= <term> * <term>\n
        \<expr> ::= <term> - <term>\n
        \<expr> ::= <term>\n
        \<term> ::= <factor> / <factor>\n
        \<term> ::= <factor> + <factor>\n
        \<term> ::= <factor>\n
      \<factor> ::= <identifier> | <number> | (<expr>)\n
  \<identifier> ::= <alpha><alphanumrest> | <alpha>\n
\<alphanumrest> ::= <alphanum><alphanumrest>|<alphanum>\n
    \<alphanum> ::= <alpha> | <digit>\n
      \<number> ::= <nonzerodigit><rest>|<digit>\n
        \<rest> ::= <digit><rest>|<digit>\n   
\<nonzerodigit> ::= 1|2|3|4|5|...|9\n
      \<digit> ::= 0|1|2|3|4|5|...|9\n
       \<alpha> ::= a|b|c...|y|z|A|B|...|Y|Z|_\n
                       
 A few sample input/outputs:
![Screenshot 2023-03-05 204217](https://user-images.githubusercontent.com/107581827/223233833-205bdb0d-b550-4fd0-b135-2931c00bb81d.png)
![Screenshot 2023-03-05 204258](https://user-images.githubusercontent.com/107581827/223233838-d99c6096-210b-45dc-9f1b-acd056df1063.png)
![Screenshot 2023-03-05 204431](https://user-images.githubusercontent.com/107581827/223233840-bcbbc12b-f73b-4667-8ca5-7527056742e8.png)
![Screenshot 2023-03-05 204538](https://user-images.githubusercontent.com/107581827/223234149-b4e96284-eb3a-4189-99a5-3141f63b76ab.png)
