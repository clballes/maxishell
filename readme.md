# TEST MPANIC
## Echo DONE
test 16 ~
test 18, nos da bien error distinto si nos animamos mucho

## Exit DONE
### Alba


## Cd DONE
test 18 ~
test 19 ~

## Dollar DONE
127 128 129 caracter especial

## Quotes 
### Alba - si nos animamos
201 da bien
202 dabien
---
faltaria 203
faltaria 204

## Tilde DONE
caacter esecial no hay q hacer nada

## Syntax Error DONE
### Alba


## Redirections 
### Clara
### Alba
333 -
337 - 
338 - 
339 - 
340 -

## Status
### Clara
346 -  parsing y exit
348 - parsing y exit

## Shlvl test
### Clara
375
376

## PANIC MANDATORY
### Clara
### Alba
conveniente que no de seg fault

# Leaks Builtins & Normi
exit
env
pwd
export

## FALTA 
# Minishell y Norminette
- Signals HEREDOC
- Archivo exit.c 
	-> La funcion check_digit_args tiene mas de 25 lineas: He dejado una  comentada de menos de 25 lineas comprobar que funciona igual que la otra.
	-> la funcion exec_exit la he dividido en: exec_exit y la de valid_arguments_exit 

# *Si crees que es facil y te apetece 
/bin/ls/algoquenoexiste
en bash el mensaje es : Not a directory y la salida es 126 
en minishell el mensaje es : No such file or directory y salimos con 0.

JUNTAS
- Hacer la evaluacion y ver si hay leaks haciendo muchas pruebas