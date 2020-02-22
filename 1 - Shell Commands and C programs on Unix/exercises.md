#### Exercise 1
##### a)
| Command  | Function |
|-------|------|
| cd    | Changes your current directory. Use  ~ to go back to your home directory. |
| ls    |  lists the files and folders in the directory. |
| mkdir | Create new directories in the filesystem. |
| rmdir | Removes empty directories from a filesystem. If you want to remove a directory that is not empty (and also remove everything it contains), you can use the rm command with the -r (recursive) option. |
| cp    | Copy files and directories. cp [options] source dest  |
| mv    | Move files and directories from directory to directory. |
| cat   | Concatenate FILE(s) to standard output. Lists the contents of files to the terminal window.    |
| more  | View the text files in the command prompt. Similar to less. |
| tail  | Gives you a listing of the last 10 lines of a file. |
| pwd   | Prints the working directory. |
| ps    | Lists running processes. |
| find  | Track down files |
| grep  | Searches for lines which contain a search pattern. |
| chmod | |
| clear | Used to clear the terminal screen. |
| echo  | Prints (echoes) a string of text to the terminal window.|

See [37 important linux commands](https://www.howtogeek.com/412055/37-important-linux-commands-you-should-know/).

##### b)

&& -> Executar um depois do outro
|| -> Executa o segundo se o primeiro falhar
&  -> Manda comando para background
|  -> Para mandar o resultado do primeiro para o segundo

#### Exercise 2

##### a)

Compile and run the code below.

```c
#include <stdio.h>
int main(void)
{
 printf("Hello !\n");
 return 0;
}
```

##### b)

/usr/lib/gcc/x86_64-linux-gnu/7/../../../x86_64-linux-gnu/Scrt1.o: In function `_start':
(.text+0x20): undefined reference to `main'
collect2: error: ld returned 1 exit status


#### Exercise 3

##### a) 
$? -> return value of the last executed command


#### Exercise 4

##### a) and b)

- [] is the scanset character. ^\n tells to take input until newline doesn’t get encountered.
- %*c it reads newline character and here used * indicates that this newline character is discarded.
```c
#include <stdio.h> 
int main() 
{ 
    char str[20]; 
    int n;
    printf("Number: ");
    scanf("%d%*c", &n);
    
    printf("Your name: ");
    scanf("%[^\n]%*c", str); 
   
    for(size_t i = 0; i < n; i++) {
        printf("Hello %s \n", str); 
    }
  
    return 0; 
} 
```

#### Exercise 5

##### d)

Cria a variável de ambiente
export VAR_NAME = VAR_VALUE

Elimina a variável de ambiente
unset VAR_NAME

#### Exercise 6

error.c

#### Exercise 7

##### b)

+1x handler -> Executados conforme a posição na stack
abort       -> Não é evocada a rotina atexit
exit()      -> Não acontece nada

#### Exercise 8

#### Exercise 9

