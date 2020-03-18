## Exercise 1

a)

Quando é enviado um sinal

SIGINT (CTRL-C):
- O programa é terminado com valor de retorno 0

kill -USR1 pid
- Ver o pid noutro terminal
- O valor de retorno após executar o comando é 138


b)


c)

Flags for sigaction:
https://www.gnu.org/software/libc/manual/html_node/Flags-for-Sigaction.html

```c
struct sigaction sigAct, oldAct;

sigAct.sa_handler = sigint_handler;
sigemptyset(&sigAct.sa_mask);
sigAct.sa_flags = 0;
```

## Exercise 2

a) A cada 10 segundo, é processado 1 interrupção de CTRL-C. Se enquanto estiver a ser processado é dado n CTRL-C, só 1 vai ser processado depois.

b) O processo é terminado por completo.

## Exercise 4

a)
Aqui o principal inconveniente tem a ver com o tempo de execução. Como não se sabe ao certo quais filhos / trabalho do pai, vai demorar mais, pode levar a que se perca muito tempo a esperar por um filho em especifico, ou um filho a esperar muito tempo para ver o seu exit code recolhido devido ao pai estar a demorar muito nas suas tarefas.
