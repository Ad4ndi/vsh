# VivaShell v2.2 Recoded

Vsh is a minimalist shell written in C. It supports basic command-line functionality, custom modules and unicode. There is no command history or auto-completion yet, but it will be soon...

### Dependencies

- clang
- guile
- nasm

### Installation Steps

1. **Clone the repository:**

   ```bash
   git clone https://github.com/Ad4ndi/vsh
   cd vsh
   ```
   
2. **Run the installation script:**

   ```bash
   guile build.scm
   ```

### Configuration

The configuration file is located in **config.asm**, where you can configure only the prompt and the path to the binary files for now.

### Custom modules

Custom modules are located in the **"lib"** directory. To create your own, you can follow the example of the ready-made **"hello.c"** module

To compile ours together with our module, you need to add the **"-l"** option, and then specify the directory to your .c file:

   ```bash
   guile build.scm -l lib/hello.c
   ```

You can call module using **"call"** command in the shell:

   ```bash
   call hello Ad4ndi
   ```

### Screenshots

![image](https://github.com/user-attachments/assets/866589b9-de36-4a98-b9d3-6aba428551b4)

