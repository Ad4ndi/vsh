(use-modules (ice-9 popen) (ice-9 rdelim) (ice-9 regex) (srfi srfi-1))

(system "mkdir -p lib")

(define modules '())

(define (parse-args args)
  (let loop ((args args) (acc '()))
    (cond
     ((null? args) (set! modules (reverse acc)))
     ((string=? (car args) "-l") (loop (cdr args) '()))
     ((string-match "^-" (car args))
      (display "Invalid argument: ") (display (car args)) (newline) (exit 1))
     (else (loop (cdr args) (cons (car args) acc))))))

(parse-args (cdr (command-line)))

(for-each system '("nasm -f elf64 config.asm -o config.o"
                   "clang -c src/main.c -o main.o"
                   "clang -c src/color.c -o color.o"
                   "clang -c src/prompt.c -o prompt.o"))

(for-each (lambda (m)
            (system (string-append "clang -fPIC -shared -o lib/lib"
                                   (car (string-split (basename m) #\.))
                                   ".so " m)))
          modules)

(for-each system '("clang main.o config.o prompt.o color.o -ldl -o vsh"
                   "rm -f *.o"))

(display "OK\n")
