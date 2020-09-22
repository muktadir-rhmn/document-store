%option noyywrap
%option prefix="condition_"

%{
#include <stdio.h>
%}

%%
[ \t\r\n] {}
\( {return OPENING_BRACKET;}
\) {return CLOSING_BRACKET;}
\{ {return OPENING_CURLY;}
\} {return CLOSING_CURLY;}
\. {return DOT;}
\, {return COMMA;}
\+ {return PLUS;}
\- {return MINUS;}
\* {return MULTIPLY;}
\/ {return DIVIDE;}
\% {return MODULUS;}
== {return EQUAL;}
!= {return NOT_EQUAL;}
> {return GREATER;}
>= {return GREATER_EQUAL;}
\< {return LESS;}
\<= {return LESS_EQUAL;}
&& {return AND;}
\|\| {return OR;}
[0-9]+ {yylval.data.text = yytext; return INTEGER;}
[0-9]+\.[0-9]+ {yylval.data.text = yytext; return FLOAT;}
[iI][nN] {return IN;}
[bB][eE][tT][wW][eE][eE][nN] {return BETWEEN;}
[a-zA-Z_]+ {yylval.data.text = yytext; return NAME_STRING;}
\".+\" {yylval.data.text = yytext; return STRING;}
%%
