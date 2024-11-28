
# - MiniShell - 

MiniShell is a command-line interface application that mimics the basic features of a Unix shell like Bash. This project was developed as part of the `42 School` program to strengthen fundamental system programming skills.  

## ✨ Key Features  

- **Command Execution**: Supports execution of external commands like `ls`, `echo`, `cat`, etc.  
- **Pipelines**: Handles commands connected with `|`.  
- **Redirections**: Input (`<`) and output (`>`), as well as append (`>>`).  
- **Environment Variable Management**: Dynamic environment variable handling.  
- **Built-in Commands**: Includes `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.  
- **Signal Handling**: Graceful handling of `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`.  
- **Heredoc Support**: Implements `<<` functionality for inline input redirection.  
- **Minimalist Design**: Mimics Bash behavior while adhering to project rules.  

---  

## 📋 Requirements  

- **System**: Linux or macOS  
- **Compiler**: GCC or Clang  
- **Libraries**: Standard C library (libc)  

## Installation  

 Clone the repository

   ```bash
   - git clone https://github.com/your-username/minishell.
   ```
 Go to the directory
   ```bash
   cd minishell
   ```
 #### Compilation 
   ```bash
   make
   ```
 Action
   ```bash
   ./minishell
   ```

## Command structs that handled 
* Echo:  
   ```bash
    $ echo "Hello, World!"  
   ```
* Use pipes
   ```bash  
    ls -la | grep minishell  
   ```
* Input redirection 
    ```bash
   $ cat < input.txt  
   ```
* Output redirection  
    ```bash
   $ echo "Hello" > output.txt  
   ```
* Heredoc example  
   ```bash
   $ cat << EOF  
   > This is a heredoc example.  
   > EOF  
   ```
* Environment variable  
    ```bash
   $ export MY_VAR=42  
   $ echo $MY_VAR  
   ```

## Authors

- [@cankarabulut-db](https://www.github.com/cankarabulut-db)
- [@AhmeetKaar](https://github.com/AhmeetKaar)

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)








   
    





