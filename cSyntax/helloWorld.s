.section    __TEXT,__text,regular,pure_instructions
.build_version macos, 12, 0  sdk_version 12, 3
.globl  _main                           ; -- Begin function main
.p2align  2
_main:                                  ; @main
    .cfi_startproc
; %bb.0:
    sub sp, sp, #16                     ; Allocate stack space
    .cfi_def_cfa_offset 16

    adrp    x0, _msg@PAGE                ; Load address of the message into x0
    add     x0, x0, _msg@PAGEOFF         ; Adjust address to the lower 12 bits
    mov     w1, #13                      ; Length of the message
    mov     w2, #1                       ; File descriptor 1 - standard output
    movz    x16, #0x200004, lsl #0       ; syscall number for write (sys_write)
    svc     #0x80                        ; System call to write the message
    mov     w0, #0                       ; Set return value to 0

    add sp, sp, #16                      ; Deallocate stack space
    ret
    .cfi_endproc
                                        ; -- End function
.subsections_via_symbols

.section    __DATA,__data
_msg:   .asciz  "Hello, World!\n"
