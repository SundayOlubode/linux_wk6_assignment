section .data
    num1_prompt db "Enter first number: ", 0
    operator_prompt db "Enter operator (+, -, *, /): ", 0
    num2_prompt db "Enter second number: ", 0
    result_msg db "Result:  ", 0
    invalid_op db "Invalid operator!", 0
    newline db 0xA, 0
    buffer db 0, 0      ; Buffer for operator input (2 bytes: operator + null terminator)
    num1 dd 0           ; First number
    num2 dd 0           ; Second number
    result dd 0         ; Result of calculation

section .bss
    temp resb 10        ; Temporary buffer for number input

section .text
    global _start

_start:
    ; Prompt for the first number
    mov eax, 4
    mov ebx, 1
    mov ecx, num1_prompt
    mov edx, 20
    int 0x80

    ; Read the first number
    mov eax, 3
    mov ebx, 0
    mov ecx, temp
    mov edx, 10
    int 0x80
    call atoi
    mov [num1], eax

    ; Prompt for the operator
    mov eax, 4
    mov ebx, 1
    mov ecx, operator_prompt
    mov edx, 30
    int 0x80

    ; Read the operator
    mov eax, 3
    mov ebx, 0
    mov ecx, buffer
    mov edx, 2
    int 0x80
    mov al, [buffer]
    cmp al, 0xA         ; Check for newline
    je invalid_operator
    mov byte [buffer+1], 0   ; Null-terminate the buffer

    ; Prompt for the second number
    mov eax, 4
    mov ebx, 1
    mov ecx, num2_prompt
    mov edx, 20
    int 0x80

    ; Read the second number
    mov eax, 3
    mov ebx, 0
    mov ecx, temp
    mov edx, 10
    int 0x80
    call atoi
    mov [num2], eax

    ; Perform the operation
    mov al, [buffer]
    cmp al, '+'
    je add_op
    cmp al, '-'
    je sub_op
    cmp al, '*'
    je mul_op
    cmp al, '/'
    je div_op
    jmp invalid_operator

add_op:
    mov eax, [num1]
    add eax, [num2]
    jmp print_result

sub_op:
    mov eax, [num1]
    sub eax, [num2]
    jmp print_result

mul_op:
    mov eax, [num1]
    imul eax, [num2]
    jmp print_result

div_op:
    mov eax, [num1]
    xor edx, edx       ; Clear remainder
    mov ebx, [num2]
    div ebx            ; Divide eax by ebx
    jmp print_result

invalid_operator:
    mov eax, 4
    mov ebx, 1
    mov ecx, invalid_op
    mov edx, 17
    int 0x80
    jmp exit

print_result:
    mov [result], eax
    call itoa
    mov eax, 4
    mov ebx, 1
    mov ecx, result_msg
    mov edx, 8
    int 0x80

    ; Print the result (after converting it to string)
    mov eax, 4
    mov ebx, 1
    mov ecx, temp
    mov edx, 10
    int 0x80

    ; Print a newline after the result
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80

    jmp exit

exit:
    mov eax, 1
    xor ebx, ebx
    int 0x80

; Function: atoi (Convert ASCII to integer)
atoi:
    xor eax, eax
    xor ebx, ebx
atoi_loop:
    mov bl, byte [ecx]
    cmp bl, 0xA         ; Newline character
    je atoi_done
    sub bl, '0'         ; Convert ASCII to number
    imul eax, eax, 10
    add eax, ebx
    inc ecx
    jmp atoi_loop
atoi_done:
    ret

; Function: itoa (Convert integer to ASCII)
itoa:
    xor ebx, ebx
    mov ecx, 10
itoa_loop:
    xor edx, edx
    div ecx             ; Divide eax by 10
    add dl, '0'         ; Convert remainder to ASCII
    push dx
    inc ebx
    test eax, eax
    jnz itoa_loop
itoa_done:
    mov edi, temp
itoa_pop:
    pop ax
    stosb
    dec ebx
    jnz itoa_pop
    mov byte [edi], 0   ; Null-terminate string
    ret
