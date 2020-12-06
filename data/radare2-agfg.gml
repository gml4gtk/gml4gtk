# r_core_anal_graph_GML()
graph [
 node [id 19696 label "  ; CALL XREF from fcn.000047d0 @ 0x47e5
  ; CALL XREFS from fcn.000048b0 @ 0x4bc6, 0x4cbd
120: fcn.00004cf0 (int64_t arg1);
; arg int64_t arg1 @ rdi
0x00004cf0      push r12
0x00004cf2      push rbp
0x00004cf3      push rbx
0x00004cf4      mov rbx, rdi                                           ; arg1
0x00004cf7      call sym.imp.fileno                                    ; int fileno(FILE *stream)
0x00004cfc      test eax, eax
0x00004cfe      mov rdi, rbx
0x00004d01      js 0x4d57
"]
 node [id 19715 label "0x00004d03      call sym.imp.__freading
0x00004d08      test eax, eax
0x00004d0a      jne 0x4d38
"]
 node [id 19724 label "; CODE XREF from fcn.00004cf0 @ 0x4d52
0x00004d0c      mov rdi, rbx                                           ; int64_t arg1
0x00004d0f      call fcn.00004d70
0x00004d14      test eax, eax
0x00004d16      je 0x4d54
"]
 node [id 19736 label "0x00004d18      call sym.imp.__errno_location
0x00004d1d      mov r12d, dword [rax]
0x00004d20      mov rdi, rbx                                           ; FILE *stream
0x00004d23      mov rbp, rax
0x00004d26      call sym.imp.fclose                                    ; int fclose(FILE *stream)
0x00004d2b      test r12d, r12d
0x00004d2e      jne 0x4d60
"]
 node [id 19760 label "; CODE XREF from fcn.00004cf0 @ 0x4d69
0x00004d30      pop rbx
0x00004d31      pop rbp
0x00004d32      pop r12
0x00004d34      ret
"]
 node [id 19768 label "; CODE XREF from fcn.00004cf0 @ 0x4d0a
0x00004d38      mov rdi, rbx                                           ; FILE *stream
0x00004d3b      call sym.imp.fileno                                    ; int fileno(FILE *stream)
0x00004d40      xor esi, esi
0x00004d42      mov edx, 1
0x00004d47      mov edi, eax
0x00004d49      call sym.imp.lseek
0x00004d4e      cmp rax, 0xffffffffffffffff
0x00004d52      jne 0x4d0c
"]
 node [id 19796 label "; CODE XREF from fcn.00004cf0 @ 0x4d16
0x00004d54      mov rdi, rbx
"]
 node [id 19799 label "; CODE XREF from fcn.00004cf0 @ 0x4d01
0x00004d57      pop rbx
0x00004d58      pop rbp
0x00004d59      pop r12
0x00004d5b      jmp sym.imp.fclose
"]
 node [id 19808 label "; CODE XREF from fcn.00004cf0 @ 0x4d2e
0x00004d60      mov dword [rbp], r12d
0x00004d64      mov eax, 0xffffffff                                    ; -1
0x00004d69      jmp 0x4d30
"]
 edge [ source 19696 target 19799]
 edge [ source 19696 target 19715]
 edge [ source 19715 target 19768]
 edge [ source 19715 target 19724]
 edge [ source 19724 target 19796]
 edge [ source 19724 target 19736]
 edge [ source 19736 target 19808]
 edge [ source 19736 target 19760]
 edge [ source 19768 target 19724]
 edge [ source 19768 target 19796]
 edge [ source 19796 target 19799]
 edge [ source 19808 target 19760]
]
