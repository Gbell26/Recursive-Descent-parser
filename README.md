A recursive descent parser that takes an input and determines whether it is a valid expression according to the following grammar rules:


        <expr> ::= <term> * <term>
        <expr> ::= <term> - <term>
        <expr> ::= <term>
        <term> ::= <factor> / <factor>
        <term> ::= <factor> + <factor>
        <term> ::= <factor>
      <factor> ::= <identifier> | <number> | (<expr>)
  <identifier> ::= <alpha><alphanumrest> | <alpha>
       <alpha> ::= a|b|c...|y|z|A|B|...|Y|Z|_
<alphanumrest> ::= <alphanum><alphanumrest>|<alphanum>
    <alphanum> ::= <alpha> | <digit>
      <number> ::= <nonzerodigit><rest>|<digit>
        <rest> ::= <digit><rest>|<digit>
<nonzerodigit> ::= 1|2|3|4|5|...|9
       <digit> ::= 0|1|2|3|4|5|...|9
