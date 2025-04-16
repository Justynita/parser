Grammar 
<pre>
expression  -> logical ;
logical     -> equality (('and' | 'or') equality)* ;
equality    -> comparison (('!=' | '==') comparison)* ; 
comparison  -> term (('>=' | '<=' | '>' | '<') term)* ;
term        -> factor (('+' | '-') factor)* ; 
factor      -> unary (('*' | '/') unary)* ;
unary       -> ('!' | '-') unary | primary ;      
primary     -> NUMBER | STRING | 'true' | 'false' | '(' expression ')' ;
</pre>
