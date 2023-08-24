global main
extern rintf
main:
call printf
mov eax, 0
mov edi, format
xor eax, eax
ret
format: db `Hello, Holberton\n`,0
